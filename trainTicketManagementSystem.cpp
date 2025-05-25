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

typedef struct {
    char trainNo[10];// 车次
    char passengerName[MAX_NAME];// 乘客姓名
    char idCard[20];// 身份证号
    char phone[15];// 联系电话
    int ticketCount;// 订票数量
} Booking;

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