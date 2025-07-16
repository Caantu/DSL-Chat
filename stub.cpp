#include "stub.h"

extern Step steps[MAX_STEPS]; // 全局步骤数组

// 模拟脚本的内容
void loadScript_stub(const char* scriptFile) {
    // 模拟读取文件的行为，直接填充steps数组
    int currentStep = -1;

    // 模拟脚本的内容
    const char* scriptData[] = {
        "Step 1",
        "Speak Hello, $name! You have $amount items. How can I help you?",
        "Listen",
        "Branch yes 2",
        "Default 3",
        "Step 2",
        "Speak Goodbye, $name."
        "Exit"
        "Step 3",
        "Speak Sorry."
        "Exit"
    };
    int scriptIndex = 0;

    while (scriptIndex < sizeof(scriptData) / sizeof(scriptData[0])) {
        const char* line = scriptData[scriptIndex++];

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
}

// 替换变量的函数
void replaceVariables_stub(char* str, User* user) {
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

// 模拟用户数据
void test_loadScript() {
    
    User testUser = { 0000,"Alice",0,0 };

    // 调用loadScript_stub，模拟脚本加载
    loadScript_stub("test_script.txt");

    // 输出结果验证
    printf("Step 1 Speak: %s\n", steps[0].speak);
    printf("Step 1 Listen: %s\n", steps[0].listen);
    printf("Step 1 Branch 1: %s %d\n", steps[0].branches[0].words, steps[0].branches[0].branchNum);
    printf("Step 1 Branch 2: %s %d\n", steps[0].branches[1].words, steps[0].branches[1].branchNum);
    printf("Step 1 Default: %d\n", steps[0].defaultNum);
    printf("Step 1 Exit: %d\n", steps[0].isExit);
}

void test_replaceVariables() {
    // 测试替换变量功能
    char testString[] = "Hello, $name! You have $amount items.";
    User testUser = { 0000,"Alice",0,0 };

    // 调用replaceVariables_stub替换变量
    replaceVariables_stub(testString, &testUser);

    // 输出结果验证
    printf("Replaced String: %s\n", testString);  // 期望输出: Hello, Alice! You have 0 items.
}

// speakCommand的测试桩
void speakCommand_stub(User* user) {
    Step* step = &steps[user->crtStep];
    printf("Robot：%s\n", step->speak);

    // 输出Branches的关键字
    for (int i = 0; i < step->branchCount; i++) {
        printf("%s  ", step->branches[i].words);
    }
    printf("\n");
}

// listen_branch_defaultCommand的测试桩
void listen_branch_defaultCommand_stub(User* user) {
    Step* step = &steps[user->crtStep];
    // 这里模拟用户总是选择第一个分支
    user->crtStep = step->branches[0].branchNum;
    return;
    // 如果没有匹配，跳转到默认步骤
    user->crtStep = step->defaultNum;
}

// exitCommand的测试桩
void exitCommand_stub(User* user) {
    Step* step = &steps[user->crtStep];
    if (step->isExit == 1)
        printf("Exiting...\n");
    else {
        printf("Not exiting...\n");
    }
}

// 执行步骤的测试桩
void executeStep_stub(User* user) {
    Step* step = &steps[user->crtStep];
    // 变量替换
    replaceVariables_stub(step->speak, user);
    // Speak指令（使用stub）
    speakCommand_stub(user);
    // Exit指令（使用stub）
    exitCommand_stub(user);
    // Listen、Branches与Default指令（使用stub）
    listen_branch_defaultCommand_stub(user);
}