

#ifndef GOOD_SYSTERM_FOREHEAD_H
#define GOOD_SYSTERM_FOREHEAD_H

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include "head.h"
#define _CRT_SECURE_NO_WARNINGS
//#pragma warning(disable:4996)

int menu();

void init_print(void) {

    printf("*********************************************************\n");
    printf("                欢迎进入商品管理系统\n");
    printf("*********************************************************\n");

    char name[NAME_LENGHTH];//name of the good
    int num=0;//code of good
    int number=0;//code variety of the good
    char name_kind[NAME_LENGHTH];//name of good's kind
    double price_in;//the in_price of good
    double price_out;//the out_price of good
    int amount=0;//the amount of good
    goods* p_good = NULL;
    int n_switch=0;
    //todo: 创建开头链表，
    //  发现插入分类函数没有判定已存在分类

    goods_listlink listlink = goods_listCreat();//创建链表



    int find = 0;//标记选项


    //todo: 完成循环
    //  目前进度完成度100%，测试进度25%

    while (1)
    {
        switch (menu())
        {//menu()函数为输入选项
            case 1:;
                find = 1;
                printf("已选择登记新商品入库\n");
                printf("请输入类别名称,最多15个中文字符\n");
                scanf("%s",name_kind);
                number = insertSort(listlink,name_kind);
                if (number==-1){
                    printf("生成失败，请检查输入名称是否符合标准！\n");
                    find =0;
                    break;
                }
                printf("请输入依次输入商品名称，商品编号，进价，售价\n");
                scanf("%s",name);
                scanf("%d  %lf %lf",&num,&price_in,&price_out);
                if (!insertGoods(listlink,num,number,price_in,price_out,name)){
                    printf("该商品已存在或者输入错误\n");
                    find=0;
                    break;
                } else{
                    printf("登记成功！\n");
                    printf("商品类别编号：%d\n",number);
                }

                find = 0;
                break;//选项1 登记新商品入库

            case 2:
                find = 2;
                printf("请输入商品的编号和商品类别编号:\n");
                num =0;
                number =0 ;
                scanf("%d%d",&num,&number);
                p_good = getGoods_num_number(listlink,num,number);
                if (p_good == NULL ){
                    printf("商品不存在或者输入错误！\n");
                    find =0;
                    break;
                }
                printf("商品查询成功！\n信息如下：\n");
                printf("商品类别编号：%d\n",p_good->number);
                printf("商品编号：%d\n",p_good->num);
                printf("商品名称：%s\n",p_good->name);
                printf("商品进价：%lf元\n",p_good->price_in);
                printf("商品售价：%lf元\n",p_good->price_out);
                printf("商品数量：%d\n",p_good->amount);
                printf("显示完毕！");
                find = 0;
                break;//选项2 查询某个商品

            case 3:
                find = 3;
                n_switch =0 ;
                printf("请输入选择修改什么信息：（1是商品数量，2是商品名称,-1是返回主界面）\n");
                scanf("%d",&n_switch);
                while (n_switch<1 || n_switch>2){
                    if(n_switch == -1 ){
                        printf("放回主界面！\n");
                        n_switch=0;
                        find =0;
                        break;
                    }
                    printf("输入错误！请检查输入！\n");
                    printf("请输入选择修改什么信息：（1是商品数量，2是商品名称,-1是返回主界面）\n");
                    scanf("%d",&n_switch);
                }
                if(n_switch == 1){
                    printf("选择修改商品数量！\n");
                    printf("请依次输入商品编号，商品类别编号，修改后的数量！\n");
                    num=0;
                    number=0;
                    amount =0;
                    scanf("%d%d%d",&num,&number,&amount);
                    if(goodsStorageAdd(listlink,num,number,amount) ==0){
                        printf("修改商品数量异常！\n");
                        find =0;
                        break;
                    }else if(goodsStorageAdd(listlink,num,number,amount) ==-1) {
                        printf("商品不存在！\n");
                        find = 0;
                        break;
                    }else{
                        printf("修改成功！\n");
                        find=0;
                        break;
                    }
                }else{
                    printf("选择修改商品名称！\n");
                    printf("请依次输入商品编号，商品类别编号\n");
                    num=0;
                    number=0;
                    strcpy(name,"");
                    scanf("%d%d",&num,&number);
                    printf("请输入修改后的名称：\n");
                    scanf("%s",name);

                    if(goodsNameModify(listlink,num,number,name) ==0){
                        printf("修改商品名称异常！\n");
                        find = 0;
                        break;
                    }else if(goodsNameModify(listlink,num,number,name) ==-1) {
                        printf("商品不存在！\n");
                        find = 0;
                        break;
                    }else{
                        printf("修改成功！\n");
                        find=0;
                        break;
                    }
                }
                find = 0;
                break;//选项3 修改某个商品

            case 4:
                find = 4;
                n_switch =0;
                printf("请选择进行的操作：（1是删除商品，2是删除商品类别，3是返回主界面）\n");
                scanf("%d",&n_switch);
                while (n_switch<1 || n_switch>2){
                    if(n_switch == -1 ){
                        printf("放回主界面！\n");
                        n_switch=0;
                        find =0;
                        break;
                    }
                    printf("输入错误！请检查输入！\n");
                    printf("请选择进行的操作：（1是删除商品，2是删除商品类别，3是返回主界面）\n");
                    scanf("%d",&n_switch);
                }
                if(n_switch == 1){
                    printf("选择删除商品！\n");
                    printf("请依次输入商品编号，商品类别编号\n");
                    num =0;
                    number=0;
                    scanf("%d%d",&num,&number);
                    if(deleteGoods_num(listlink,num,number) == 0){
                        printf("商品不存在！\n");
                        find =0;
                        break;
                    }else{
                        printf("修改成功！\n");
                        find=0;
                        break;
                    }
                }else{
                    printf("选择删除商品类别！\n");
                    printf("请依次输入商品类别编号\n");
                    num =0;
                    number=0;

                    scanf("%d",&number);
                    if(deleteSort(listlink,number) == 0){
                        printf("商品分类不存在！\n");
                        find = 0;
                        break;
                    }else{
                        printf("修改成功！\n");
                        find= 0;
                        break;
                    }
                }
                find = 0 ;
                break;//选项4 删除商品或商品类别

            case 5:
                printf("感谢您的使用，再见！\n");
                freeAll(listlink);
                exit(0);
        }
    }

}

int menu()
{//打印主菜单函数

    int n;//选项为整数
    printf("\n\n请选择下面的数字进行操作：\n");
    printf("--------------------------------------------\n");
    printf("1. 登记商品入库\n");
    printf("2. 查询某个商品\n");
    printf("3. 修改商品信息\n");
    printf("4. 删除商品或商品类别\n");
    printf("5. 退出程序\n");
    printf("--------------------------------------------\n");
    printf("请选择对应数字1~5 （每次只输入一个）\n");
    printf("本程序制作人: 2019级李浩、陈勇鹏、汤佳伟\n");


    while (1)
    {
        scanf("%d", &n);//接收数字
        if (n < 1 || n>5)//判断输入的选项是否正确
            printf("输入错误，请重新输入：\n");
        else//输入正确，结束循环
            break;
    }
    return n;//返回输入选项分
}




#endif //GOOD_SYSTERM_FOREHEAD_H
