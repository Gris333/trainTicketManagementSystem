#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME 50
#define MAX_STATION 30
#define MAX_TIME 10
#define MAX_TRAINS 100
#define MAX_BOOKINGS 1000

typedef struct {
    char trainNo[10];// 车次
    char startStation[MAX_STATION];// 始发站
    char endStation[MAX_STATION];// 终点站
    char startTime[MAX_TIME];// 发车时间
    char endTime[MAX_TIME];// 到站时间
    float price;// 票价
    int remainingTickets;// 剩余票数
} Train;

// 全局变量
Train trains[MAX_TRAINS];
int trainCount = 0;
Booking bookings[MAX_BOOKINGS];
int bookingCount = 0;

typedef struct {
    char trainNo[10];// 车次
    char passengerName[MAX_NAME];// 乘客姓名
    char idCard[20];// 身份证号
    char phone[15];// 联系电话
    int ticketCount;// 订票数量
} Booking;

// 全局变量
Train trains[MAX_TRAINS];
int trainCount = 0;
Booking bookings[MAX_BOOKINGS];
int bookingCount = 0;

// 函数声明
void showMenu();
void addTrain();
void searchTrain();
void bookTicket();
void modifyTrain();
void showTrains();
void saveData();
void loadData();
void clearInputBuffer();

// 主菜单
void showMenu() {
    printf("\n=== 火车票订票系统 ===\n");
    printf("1. 添加火车信息\n");
    printf("2. 查询火车信息\n");
    printf("3. 订票\n");
    printf("4. 修改火车信息\n");
    printf("5. 显示所有火车信息\n");
    printf("6. 保存数据\n");
    printf("7. 退出\n");
    printf("请选择: ");
}

// 添加火车信息
void addTrain() {
    if (trainCount >= MAX_TRAINS) {
        printf("火车信息已达到最大数量限制！\n");
        return;
    }

    Train newTrain;
    printf("\n=== 添加火车信息 ===\n");
    
    printf("请输入车次: ");
    scanf("%9s", newTrain.trainNo);
    clearInputBuffer();

    // 检查车次是否已存在
    for (int i = 0; i < trainCount; i++) {
        if (strcmp(trains[i].trainNo, newTrain.trainNo) == 0) {
            printf("该车次已存在！\n");
            return;
        }
    }

    printf("请输入始发站: ");
    scanf("%29s", newTrain.startStation);
    clearInputBuffer();

    printf("请输入终点站: ");
    scanf("%29s", newTrain.endStation);
    clearInputBuffer();

    printf("请输入发车时间(格式: HH:MM): ");
    scanf("%9s", newTrain.startTime);
    clearInputBuffer();

    printf("请输入到站时间(格式: HH:MM): ");
    scanf("%9s", newTrain.endTime);
    clearInputBuffer();

    printf("请输入票价: ");
    scanf("%f", &newTrain.price);
    clearInputBuffer();

    printf("请输入剩余票数: ");
    scanf("%d", &newTrain.remainingTickets);
    clearInputBuffer();

    trains[trainCount++] = newTrain;
    printf("火车信息添加成功！\n");
}