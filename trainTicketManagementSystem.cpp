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

// 查询火车信息
void searchTrain() {
    int choice;
    printf("\n=== 查询火车信息 ===\n");
    printf("1. 按车次查询\n");
    printf("2. 按城市查询\n");
    printf("请选择查询方式: ");
    scanf("%d", &choice);
    clearInputBuffer();

    if (choice == 1) {
        char trainNo[10];
        printf("请输入要查询的车次: ");
        scanf("%9s", trainNo);
        clearInputBuffer();

        int found = 0;
        for (int i = 0; i < trainCount; i++) {
            if (strcmp(trains[i].trainNo, trainNo) == 0) {
                printf("\n车次: %s\n", trains[i].trainNo);
                printf("始发站: %s\n", trains[i].startStation);
                printf("终点站: %s\n", trains[i].endStation);
                printf("发车时间: %s\n", trains[i].startTime);
                printf("到站时间: %s\n", trains[i].endTime);
                printf("票价: %.2f\n", trains[i].price);
                printf("剩余票数: %d\n", trains[i].remainingTickets);
                found = 1;
                break;
            }
        }
        if (!found) {
            printf("未找到该车次信息！\n");
        }
    } else if (choice == 2) {
        char city[MAX_STATION];
        printf("请输入要查询的城市: ");
        scanf("%29s", city);
        clearInputBuffer();

        int found = 0;
        for (int i = 0; i < trainCount; i++) {
            if (strcmp(trains[i].startStation, city) == 0 || 
                strcmp(trains[i].endStation, city) == 0) {
                printf("\n车次: %s\n", trains[i].trainNo);
                printf("始发站: %s\n", trains[i].startStation);
                printf("终点站: %s\n", trains[i].endStation);
                printf("发车时间: %s\n", trains[i].startTime);
                printf("到站时间: %s\n", trains[i].endTime);
                printf("票价: %.2f\n", trains[i].price);
                printf("剩余票数: %d\n", trains[i].remainingTickets);
                printf("------------------------\n");
                found = 1;
            }
        }
        if (!found) {
            printf("未找到经过该城市的车次信息！\n");
        }
    } else {
        printf("无效的选择！\n");
    }
}

// 订票
void bookTicket() {
    if (bookingCount >= MAX_BOOKINGS) {
        printf("订票数量已达到最大限制！\n");
        return;
    }

    char city[MAX_STATION];
    printf("\n=== 订票 ===\n");
    printf("请输入目的地城市: ");
    scanf("%29s", city);
    clearInputBuffer();

    // 显示符合条件的车次
    int found = 0;
    printf("\n符合条件的车次信息：\n");
    for (int i = 0; i < trainCount; i++) {
        if (strcmp(trains[i].endStation, city) == 0 && trains[i].remainingTickets > 0) {
            printf("\n车次: %s\n", trains[i].trainNo);
            printf("始发站: %s\n", trains[i].startStation);
            printf("终点站: %s\n", trains[i].endStation);
            printf("发车时间: %s\n", trains[i].startTime);
            printf("到站时间: %s\n", trains[i].endTime);
            printf("票价: %.2f\n", trains[i].price);
            printf("剩余票数: %d\n", trains[i].remainingTickets);
            printf("------------------------\n");
            found = 1;
        }
    }

    if (!found) {
        printf("没有找到符合条件的车次！\n");
        return;
    }

    // 选择车次并订票
    char trainNo[10];
    printf("请输入要预订的车次: ");
    scanf("%9s", trainNo);
    clearInputBuffer();

    int trainIndex = -1;
    for (int i = 0; i < trainCount; i++) {
        if (strcmp(trains[i].trainNo, trainNo) == 0) {
            trainIndex = i;
            break;
        }
    }

    if (trainIndex == -1) {
        printf("未找到该车次！\n");
        return;
    }

    if (trains[trainIndex].remainingTickets <= 0) {
        printf("该车次已无余票！\n");
        return;
    }

    // 输入订票信息
    Booking newBooking;
    strcpy(newBooking.trainNo, trainNo);

    printf("请输入乘客姓名: ");
    scanf("%49s", newBooking.passengerName);
    clearInputBuffer();

    printf("请输入身份证号: ");
    scanf("%19s", newBooking.idCard);
    clearInputBuffer();

    printf("请输入联系电话: ");
    scanf("%14s", newBooking.phone);
    clearInputBuffer();

    printf("请输入订票数量: ");
    scanf("%d", &newBooking.ticketCount);
    clearInputBuffer();

    if (newBooking.ticketCount > trains[trainIndex].remainingTickets) {
        printf("剩余票数不足！\n");
        return;
    }

    // 更新剩余票数
    trains[trainIndex].remainingTickets -= newBooking.ticketCount;
    
    // 保存订票信息
    bookings[bookingCount++] = newBooking;

    printf("\n订票成功！\n");
    printf("订单信息：\n");
    printf("车次: %s\n", newBooking.trainNo);
    printf("乘客姓名: %s\n", newBooking.passengerName);
    printf("身份证号: %s\n", newBooking.idCard);
    printf("联系电话: %s\n", newBooking.phone);
    printf("订票数量: %d\n", newBooking.ticketCount);
    printf("总价: %.2f\n", newBooking.ticketCount * trains[trainIndex].price);
}
