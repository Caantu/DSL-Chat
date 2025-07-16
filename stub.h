#include "main.h"
void loadScript_stub(const char* scriptFile); // 读取和解析步骤函数
void replaceVariables_stub(char* str, User* user);// 替换变量的函数
// 测试函数
void test_loadScript();
void test_replaceVariables();

void speakCommand_stub(User* user);
void listen_branch_defaultCommand_stub(User* user);
void exitCommand_stub(User* user);
void executeStep_stub(User* user);