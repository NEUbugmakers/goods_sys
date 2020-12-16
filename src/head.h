

#ifndef GOOD_SYSTERM_HEAD_H
#define GOOD_SYSTERM_HEAD_H




#include<stdio.h>
#include<string.h>
#include<stdlib.h>


#define NAME_LENGHTH 40


typedef struct goods {
    int num;//商品编号
    int number;//商品类别编号
    double price_in;///商品进价
    double price_out;//商品售价
    char name[NAME_LENGHTH];//商品名字
    int amount;//商品数量
    struct goods* next;//下一个链表指针的位置
}goods, * goodslink;

typedef struct goods_list {
    int number;//商品类别编号
    char name[NAME_LENGHTH];//商品类别名字
    goodslink head;//商品链表的头指针
    struct goods_list* next;//下一个链表指针的位置
}goods_list, * goods_listlink;
int quicksort(const void* s[], int start, int end, int (*cmp)(const void*, const void*)) {
    int i, j;
    i = start;
    j = end;
    s[0] = s[start];
    while (i < j) {
        while (i < j && cmp(s[0], s[j]))j--;
        if (i < j)s[i++] = s[j];
        while (i < j && cmp(s[i], s[0]))i++;
        if (i < j)s[j--] = s[i];
    }
    s[i] = s[0];
    if (start < i)quicksort(s, start, j - 1, cmp);
    if (i < end)  quicksort(s, j + 1, end, cmp);
    return 0;
}
goods_listlink goods_listCreat() {
    goods_listlink linklist = (goods_listlink)malloc(sizeof(goods_list));
    linklist->next = NULL;
    linklist->number = -1;
    linklist->name[0] = 0;
/*	linklist->head = ()malloc(sizeof(goods_list));*/

    return linklist;
}
goods_listlink getSort_name(goods_listlink list, char* name) {//通过名字查找分类
    while (list) {
        if (strcmp(list->name, name) == 0)
            return list;
        else
            list = list->next;
    }
    return NULL;
}
int insertSort(goods_listlink l, char* name) {//插入分类
    if (strlen(name) >= NAME_LENGHTH) {
        return -1;
    }
    if(getSort_name(l,name)!=NULL)//分类已存在，默认插入成功
        return getSort_name(l,name)->number;
    while(l->next)
        l = l->next;
    l->next = goods_listCreat();
    strcpy(l->next->name, name);
    l->next->number = l->number + 1;
    l->next->head = (goods*)malloc(sizeof(goods));
    l->next->head->amount = -1;
    l->next->head->name[0] = 0;
    l->next->head->next = NULL;
    l->next->head->num = -1;
    l->next->head->number = -1;
    l->next->head->price_in = -1;
    l->next->head->price_out = -1;
    return l->next->number;
}
goods_listlink getSort_num(goods_listlink list, int num) {//通过编号查找分类
    while (list) {
        if (list->number == num)
            return list;
        else
            list = list->next;
    }
    return NULL;
}
goods* getGoods_num_number(goods_listlink link, int num, int number) {//通过编号查找商品
    goods* list = (getSort_num(link, number))->head->next;
    while (list) {
        if (list->num == num)
            return list;
    }
    return NULL;
}

//添加新商品
int insertGoods(goods_listlink l, int num, int number, double price_in, double price_out, char* name) {
    if (strlen(name) >= NAME_LENGHTH) {
        return 0;
    }
    goods* p = getSort_num(l, number)->head;
    while (p->next) {
        p = p->next;//第一个节点不存放数据，直接跳过，不做判断
        if (p->num == num) {//编号已存在
            return 0;
        }
    }
    p->next = (goods*)malloc(sizeof(goods));
    p->amount = 0;
    strcpy(p->name, name);
    p->next->num = num;
    p->next->number = number;
    p->next->price_in = price_in;
    p->next->price_out = price_out;
    p->next->next = NULL;
    return 1;
}
int deleteGoods_num_list(goodslink list, int num) {//从商品链表中删除商品
    while (list->next) {
        if (list->next->num == num) {
            goods* p = list->next->next;
            free(list->next);
            list->next = p;
            return 1;
        }
    }
    return 0;
}
int deleteGoods_num(goods_listlink l, int num, int number) {//从商品主链表中删除商品
    goods_listlink p = getSort_num(l, number);
    if (p)
        return deleteGoods_num_list(getSort_num(l, number)->head, num);
    else
        return 0;
}
int clearGoods_Link(goodslink list) {//删除某一商品链表，返回商品数量
    goodslink p = list;
    int count = -1;
    while (p) {
        p = list->next;
        free(list);
        list = p;
        count++;
    }
    return count;
}
int deleteSort(goods_listlink l, int num) {//删除某一分类
    while (l->next) {
        if (l->next->number == num) {
            clearGoods_Link(l->next->head);
            goods_listlink p = l->next->next;
            free(l);
            return 1;
        }
    }
    return 0;
}
int freeAll(goods_listlink l) {//全部删除
    if (!l)
        return 0;
    while (l) {
        clearGoods_Link(l->head);
        goods_listlink p = l->next;
        free(l);
        l = p;
    }
    return 1;
}
int cmp_num(goods a, goods b) {
    return a.num < b.num;
}
int cmp_number(goods a, goods b) {
    return a.number < b.number;
}
int goodsStorageAdd(goods_listlink link,int num, int number, int _amount) {//修改商品数量，1修改成功，0修改数量异常，-1商品不存在
    goods* item = getGoods_num_number(link, num, number);
    if (!item)
        return -1;
    if (item->amount + _amount >= 0) {
        item->amount += _amount;
        return 1;
    }
    else
        return 0;
}
int goodsNameModify(goods_listlink link, int num, int number, char* name) {//修改商品名称，1修改成功，0名称异常，-1商品不存在
    if (strlen(name) > NAME_LENGHTH)
        return 0;
    goods* item = getGoods_num_number(link, num, number);
    if (!item)
        return -1;
    strcpy(item->name, name);
    return 1;
}



#endif //GOOD_SYSTERM_HEAD_H
