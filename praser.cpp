#include "main.h"

extern Step steps[MAX_STEPS]; // 全局步骤数组
extern User users[MAX_USERS]; // 全局用户数组

// 读取和解析步骤函数
void loadScript(const char* scriptFile) {
    FILE* file = fopen(scriptFile, "r");
    if (!file) {
        printf("无法打开文件\n");
        exit(1);
    }

    int currentStep = -1;
    char line[MAX_LINE_LENGTH];
    while (fgets(line, sizeof(line), file)) {
        // 去掉行末的换行符
        line[strcspn(line, "\n")] = 0;

        if (strncmp(line, "Step", 4) == 0) {
            currentStep++;
            steps[currentStep].branchCount = 0;
        }
        else if (strncmp(line, "Speak", 5) == 0) {
            // 保存Speak内容
            sscanf(line + 6, "%[^\n]", steps[currentStep].speak);
        }
        else if (strncmp(line, "Listen", 6) == 0) {
            // 保存Listen内容
            sscanf(line + 7, "%[^\n]", steps[currentStep].listen);
        }
        else if (strncmp(line, "Branch", 6) == 0) {
            // 保存Branch内容
            char branchKeyword[MAX_LINE_LENGTH];
            int branchNum;
            sscanf(line + 7, "%s %d", branchKeyword, &branchNum);
            strncpy(steps[currentStep].branches[steps[currentStep].branchCount].words, branchKeyword, MAX_LINE_LENGTH);
            steps[currentStep].branches[steps[currentStep].branchCount].branchNum = branchNum;
            steps[currentStep].branchCount++;
        }
        else if (strncmp(line, "Default", 7) == 0) {
            // 保存Default内容
            sscanf(line + 8, "%d", &steps[currentStep].defaultNum);
        }
        else if (strncmp(line, "Exit", 4) == 0) {
            // 保存Exit内容
            steps[currentStep].isExit = 1;
        }
    }

    fclose(file);
}

// 替换变量的函数
void replaceVariables(char* str, User* user) {
    char result[MAX_LINE_LENGTH];
    int i = 0, j = 0;

    while (str[i]) {
        if (str[i] == '$') {
            i++;
            if (strncmp(str + i, "name", 4) == 0) {
                i += 4;
                while (user->name[j]) {
                    result[j] = user->name[j];
                    j++;
                }
            }
            else if (strncmp(str + i, "amount", 6) == 0) {
                i += 6;
                char amountStr[MAX_LINE_LENGTH];
                snprintf(amountStr, MAX_LINE_LENGTH, "%d", user->amount);
                int k = 0;
                while (amountStr[k]) {
                    result[j++] = amountStr[k++];
                }
            }
        }
        else {
            result[j++] = str[i++];
        }
    }
    result[j] = '\0';
    strcpy(str, result);
}