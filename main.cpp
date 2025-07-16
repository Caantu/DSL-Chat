#include "main.h"
//#include "stub.h"

Step steps[MAX_STEPS]; // 全局步骤数组
User users[MAX_USERS] = {
    {1001, "张三",100,0},
    {1002,"李四",213,0},
    {1003,"王五",567234,0},
    {1004,"赵六",88800,0},
    {1005,"二狗",0,0}
}; // 初始化全局用户数组

int main() {
    // 用户初始化
    User user;
    int num = 0, id = 0;
    printf("请输入您的ID：（1001至1005）");
    scanf("%d", &id);
    getchar();
    for (int i = 0; i < MAX_USERS; i++) {
        if (users[i].ID == id) {
            num = i;
            break;
        }
    }
    // 查找对应用户
    user = users[num];
    // 加载脚本文件
    loadScript("robot_script1.txt");

    // 执行脚本
    while (1) {
        executeStep(&user);
    }
    return 0;
    //测试桩
    /*printf("Testing loadScript...\n");
    test_loadScript();

    printf("\nTesting replaceVariables...\n");
    test_replaceVariables();
    printf("\nTesting executeStep...\n");
    User testUser[1] = {{0000,"Alice",0,0}};
    executeStep_stub(testUser);
    return 0;*/
}