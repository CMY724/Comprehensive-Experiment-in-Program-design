#pragma once
#include <stdio.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>
#define MAXLEN 18
#define SIZE 100

typedef struct card
{
    char aId[MAXLEN];
    char aPwd[MAXLEN];
    int nStatus;
    time_t tStart;//开卡
    time_t tEnd;//到期
    float fTotalUse;//累计消费
    time_t tLast;//最后一次使用
    int nUseCount;
    float fBalance;
    int nDel;//删除标记
    struct card* next;
    struct card* next1;//链表指针
    //next 是主链表指针，用来维护系统中真正存储的数据链表；
    //next1 是辅助链表指针，主要用于临时查询结果，比如模糊查询卡号、筛选某段时间内的账单记录时，不破坏原来的主链表结构。
} Card;//一张卡的信息

typedef struct cards
{
    Card* head, * tail;
}Cards;//多张卡存放

typedef struct Billing
{
    char aCardName[18];
    time_t tStart;
    time_t tEnd;
    float fAmount;//消费金额
    int nStatus;
    int nDel;
    struct Billing* next;
    struct Billing* next1;
}Billing;//一条消费记录

typedef struct Billings
{
    Billing* head, * tail;
}Billings;//存放消费记录

typedef struct LoginInfo
{
    char aCardName[18];
    time_t tLogin;
    float fBalance;
}LoginInfo;

typedef struct SettleInfo
{
    char aCardName[18];
    time_t tStart;
    time_t tEnd;
    float fAmount;
    float fBalance;
}SettleInfo;

typedef struct Charge
{
    char aCardName[18]; // 卡号
    time_t tTime; // 充值退费的时间
    int nStatus; // 状态：0-表示充值；1-表示退费
    float fMoney; // 充值退费金额
    int nDel; // 删除标识，0-未删除,1-删除
    struct Charge* next;
    struct Charge* next1;
}Charge;

typedef struct Charges
{
    Charge* head, * tail;
}Charges;

void ShowStatistics(Cards* c, Billings* b, Charges* m);
void Exit(Cards* c, Billings* b, Charges* m);
void showDefault();

//扩展功能
void ShowOnlineCards(Cards* c);//查询当前正在上机的用户
void ShowLowBalanceCards(Cards* c);//查询余额不足10元的用户
void ShowArrearsCards(Cards* c);//查询欠费用户
void ShowChargeRecords(Charges* m);//查询某张卡的充值退费记录