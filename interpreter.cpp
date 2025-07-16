#include "main.h"

extern Step steps[MAX_STEPS]; // 全局步骤数组
extern User users[MAX_USERS]; // 全局用户数组

void speakCommand(User* user) {
    Step* step = &steps[user->crtStep];
    // 输出Speak内容
    printf("%s\n", step->speak);
    // 输出Branches的关键字
    for (int i = 0; i < step->branchCount; i++) {
        printf("%s  ", step->branches[i].words);
    }
    printf("\n");
}
void listen_branch_defaultCommand(User* user) {
    Step* step = &steps[user->crtStep];
    // 等待用户输入
    char input[MAX_LINE_LENGTH];
    fgets(input, sizeof(input), stdin);
    input[strcspn(input, "\n")] = 0;  // 去掉换行符
    // 查找用户输入匹配的分支
    for (int i = 0; i < step->branchCount; i++) {
        if (strncmp(input, step->branches[i].words, MAX_LINE_LENGTH) == 0) {
            user->crtStep = step->branches[i].branchNum;
            return;
        }
    }
    // 如果没有匹配，跳转到默认步骤
    user->crtStep = step->defaultNum;
}
void exitCommand(User* user) {
    Step* step = &steps[user->crtStep];
    if (step->isExit == 1)
        exit(0);
}

// 执行步骤函数
void executeStep(User* user) {
    Step* step = &steps[user->crtStep];
    // 变量替换
    replaceVariables(step->speak, user);
    // Speak指令
    speakCommand(user);
    // Exit指令
    exitCommand(user);
    // Listen、Branches与Default指令
    listen_branch_defaultCommand(user);
}