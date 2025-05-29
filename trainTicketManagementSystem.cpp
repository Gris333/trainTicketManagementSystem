#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_NAME 50
#define MAX_STATION 30
#define MAX_TIME 10
#define MAX_TRAINS 100
#define MAX_BOOKINGS 1000

//车次结构体
typedef struct {
    char trainNo[10];// 车次
    char startStation[MAX_STATION];// 始发站
    char endStation[MAX_STATION];// 终点站
    char startTime[16];// 发车时间 
    char endTime[16];// 到站时间
    float price;// 票价
    int remainingTickets;// 剩余票数
} Train;

//订票结构体
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

    printf("请输入发车时间(格式: YYYY-MM-DD HH:MM): ");
    scanf("%15s", newTrain.startTime);
    clearInputBuffer();

    printf("请输入到站时间(格式: YYYY-MM-DD HH:MM): ");
    scanf("%15s", newTrain.endTime);
    clearInputBuffer();

    printf("请输入票价: ");
    scanf("%.2f", &newTrain.price);
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

    int found = 0;

    switch (choice) {
        case 1: {
            char trainNo[10];
            printf("请输入要查询的车次: ");
            scanf("%9s", trainNo);
            clearInputBuffer();

            found = 0;
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
                }
            }
            if (!found) {
                printf("未找到该车次信息！\n");
            }
            break;
        }
        case 2: {
            char city[MAX_STATION];
            printf("请输入要查询的城市: ");
            scanf("%29s", city);
            clearInputBuffer();

            found = 0;
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
            break;
        }
        default:
            printf("无效选择！\n");
            break;
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
        printf("没有找到符合条件的有票车次！\n");
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

// 修改火车信息
void modifyTrain() {
    char trainNo[10];
    printf("\n=== 修改火车信息 ===\n");
    printf("请输入要修改的车次: ");
    scanf("%9s", trainNo);
    clearInputBuffer();
    char newStartTime[16],newEndTime[16];

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

    printf("\n当前信息：\n");
    printf("始发站: %s\n", trains[trainIndex].startStation);
    printf("终点站: %s\n", trains[trainIndex].endStation);
    printf("发车时间: %s\n", trains[trainIndex].startTime);
    printf("到站时间: %s\n", trains[trainIndex].endTime);
    printf("票价: %.2f\n", trains[trainIndex].price);
    printf("剩余票数: %d\n", trains[trainIndex].remainingTickets);

    printf("\n请输入新的信息：\n");
    printf("始发站: ");
    scanf("%29s", trains[trainIndex].startStation);
    clearInputBuffer();

    printf("终点站: ");
    scanf("%29s", trains[trainIndex].endStation);
    clearInputBuffer();

    printf("发车时间(YYYY-MM-DD HH:MM): ");
    scanf("%15s", newStartTime);
    clearInputBuffer();

    printf("到站时间(YYYY-MM-DD HH:MM): ");
    scanf("%15s", newEndTime);
    clearInputBuffer();

    //验证通过再赋值
    strcpy(trains[trainIndex].startTime, newStartTime);
    strcpy(trains[trainIndex].endTime, newEndTime);

    printf("票价: ");
    scanf("%f", &trains[trainIndex].price);
    clearInputBuffer();

    printf("剩余票数: ");
    scanf("%d", &trains[trainIndex].remainingTickets);
    clearInputBuffer();

    printf("火车信息修改成功！\n");
}

// 显示所有火车信息
void showTrains() {
    printf("\n=== 所有火车信息 ===\n");
    if (trainCount == 0) {
        printf("暂无火车信息！\n");
        return;
    }

    for (int i = 0; i < trainCount; i++) {
        printf("\n车次: %s\n", trains[i].trainNo);
        printf("始发站: %s\n", trains[i].startStation);
        printf("终点站: %s\n", trains[i].endStation);
        printf("发车时间: %s\n", trains[i].startTime);
        printf("到站时间: %s\n", trains[i].endTime);
        printf("票价: %.2f\n", trains[i].price);
        printf("剩余票数: %d\n", trains[i].remainingTickets);
        printf("------------------------\n");
    }
}

// 保存数据
void saveData() {
    FILE *trainFile = fopen("trains.txt", "w");
    if (trainFile == NULL) {
        printf("无法打开火车信息文件！\n");
        return;
    }

    fprintf(trainFile, "火车总数: %d\n\n", trainCount);
    for (int i = 0; i < trainCount; i++) {
        fprintf(trainFile,
                "车次: %s\n"
                "始发站: %s\n"
                "终点站: %s\n"
                "发车时间: %s\n"
                "到站时间: %s\n"
                "票价: %.2f\n"
                "剩余票数: %d\n"
                "--------------------\n",
                trains[i].trainNo,
                trains[i].startStation,
                trains[i].endStation,
                trains[i].startTime,
                trains[i].endTime,
                trains[i].price,
                trains[i].remainingTickets);
    }
    fclose(trainFile);

    FILE *bookingFile = fopen("bookings.txt", "w");
    if (bookingFile == NULL) {
        printf("无法打开订票信息文件！\n");
        return;
    }

    fprintf(bookingFile, "订单总数: %d\n\n", bookingCount);
    for (int i = 0; i < bookingCount; i++) {
        fprintf(bookingFile,
                "车次: %s\n"
                "乘客姓名: %s\n"
                "身份证号: %s\n"
                "联系电话: %s\n"
                "订票数量: %d\n"
                "--------------------\n",
                bookings[i].trainNo,
                bookings[i].passengerName,
                bookings[i].idCard,
                bookings[i].phone,
                bookings[i].ticketCount);
    }
    fclose(bookingFile);

    printf("订票数据与列车数据已保存！\n");
}

// 加载数据
void loadData() {
    FILE *trainFile = fopen("trains.txt", "r");
    if (trainFile != NULL) {
        int total;
        if (fscanf(trainFile, "火车总数: %d\n", &total) == 1) {
            trainCount = total;
            for (int i = 0; i < trainCount; i++) {
                fscanf(trainFile, 
                    "车次: %s\n"
                    "始发站: %s\n"
                    "终点站: %s\n"
                    "发车时间: %s\n"
                    "到站时间: %s\n"
                    "票价: %f\n"
                    "剩余票数: %d\n"
                    "--------------------\n",
                    trains[i].trainNo,
                    trains[i].startStation,
                    trains[i].endStation,
                    trains[i].startTime,
                    trains[i].endTime,
                    &trains[i].price,
                    &trains[i].remainingTickets);
            }
        }
        fclose(trainFile);
    }

    FILE *bookingFile = fopen("bookings.txt", "r");
    if (bookingFile != NULL) {
        int total;
        if (fscanf(bookingFile, "订单总数: %d\n", &total) == 1) {
            bookingCount = total;
            for (int i = 0; i < bookingCount; i++) {
                fscanf(bookingFile,
                    "车次: %s\n"
                    "乘客姓名: %s\n"
                    "身份证号: %s\n"
                    "联系电话: %s\n"
                    "订票数量: %d\n"
                    "--------------------\n",
                    bookings[i].trainNo,
                    bookings[i].passengerName,
                    bookings[i].idCard,
                    bookings[i].phone,
                    &bookings[i].ticketCount);
            }
        }
        fclose(bookingFile);
    }
}

// 清除输入缓冲区
void clearInputBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int main() {
    int choice;
    
    // 加载保存的数据
    loadData();

    while (1) {
        showMenu();
        if (scanf("%d", &choice) != 1) {
            clearInputBuffer();
            printf("输入无效，请输入数字！\n");
            continue;
        }
        clearInputBuffer();

        switch (choice) {
            case 1:
                addTrain();
                break;
            case 2:
                searchTrain();
                break;
            case 3:
                bookTicket();
                break;
            case 4:
                modifyTrain();
                break;
            case 5:
                showTrains();
                break;
            case 6:
                saveData();
                break;
            case 7:
                printf("感谢使用，再见！\n");
                return 0;
            default:
                printf("无效的选择，请重试！\n");
        }
    }

    return 0;
} 