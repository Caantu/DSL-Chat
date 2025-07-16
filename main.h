#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 256
#define MAX_STEPS 100
#define MAX_BRANCHES 10
#define MAX_USERS 5

// 数据结构定义
typedef struct branch {
    char words[MAX_LINE_LENGTH];    // 分支关键词
    int branchNum;                  // 分支编号
} Branch;

typedef struct step {
    int num;                          // 步骤的编号
    char speak[MAX_LINE_LENGTH];      // 步骤的输出内容
    char listen[MAX_LINE_LENGTH];     // 步骤的用户输入内容
    Branch branches[MAX_BRANCHES];    // 所有的分支
    int branchCount;                  // 分支的数量
    int defaultNum;                   // 默认跳转编号
    int isExit;                       // 是否退出
} Step;

typedef struct user {
    int ID;
    char name[MAX_LINE_LENGTH];  // 用户名称
    int amount;                  // 用户账单金额
    int crtStep;                 // 当前所在步骤编号
} User;

void loadScript(const char* scriptFile);
void replaceVariables(char* str, User* user);
void executeStep(User* user);
void speakCommand(User* user);
void listen_branch_defaultCommand(User* user);
void exitCommand(User* user);