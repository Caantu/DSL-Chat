# 基于领域特定语言的客服机器人

一个使用C语言实现的简单客服机器人系统，支持通过自定义的DSL脚本文件定义对话流程。

## 系统概述

本系统实现了一个基于领域特定语言(DSL)的客服机器人，可以根据预先定义的脚本文件与用户进行交互式对话。系统支持多用户、分支对话、变量替换等功能。

## 功能特性

- 支持自定义DSL脚本定义对话流程
- 多用户支持，每个用户有独立的对话状态
- 变量替换功能，可在对话中动态显示用户信息
- 分支对话支持，根据用户输入跳转到不同对话步骤
- 默认分支处理，处理无匹配输入的情况

## DSL语法

### 基本语法元素

- `Step <step_id>` - 定义一个对话步骤
- `Speak <message>` - 机器人输出的文本内容
- `Listen` - 等待用户输入
- `Branch <condition> <step_id>` - 根据用户输入进行分支跳转
- `Default <step_id>` - 默认跳转步骤
- `Exit` - 结束对话

### 变量支持

- `$name` - 用户姓名
- `$amount` - 用户账单金额

## 项目结构

```
├── main.h              # 主头文件，包含数据结构定义
├── main.cpp            # 主程序入口
├── praser.cpp          # 脚本解析器
├── interpreter.cpp     # 脚本解释器
├── stub.h              # 测试桩头文件
├── stub.cpp            # 测试桩实现
├── robot_script.txt    # 示例脚本1（投诉处理）
├── robot_script1.txt   # 示例脚本2（信息咨询）
└── robot_script2.txt   # 示例脚本3（餐厅点餐）
```

## 编译和运行

### 编译
```bash
gcc -o chatbot main.cpp praser.cpp interpreter.cpp
```

### 运行
```bash
./chatbot
```

程序启动后会提示输入用户ID（1001-1005），然后开始对话交互。

## 示例脚本

### 信息咨询脚本示例
```
Step 0
Speak $name您好，欢迎咨询！请问有什么问题我可以帮您解答？
Listen
Branch 营业时间 1
Branch 地址 2
Branch 服务 3
Default 5

Step 1
Speak 我们的营业时间是每天早上9点到晚上6点。
Listen
Branch 否 6
Default 5

Step 6
Speak 感谢您的咨询！祝您生活愉快！
Exit
```

## 数据结构

### 用户结构体
```c
typedef struct user {
    int ID;                           // 用户ID
    char name[MAX_LINE_LENGTH];       // 用户姓名
    int amount;                       // 账单金额
    int crtStep;                      // 当前对话步骤
} User;
```

### 步骤结构体
```c
typedef struct step {
    int num;                          // 步骤编号
    char speak[MAX_LINE_LENGTH];      // 输出内容
    char listen[MAX_LINE_LENGTH];     // 输入提示
    Branch branches[MAX_BRANCHES];    // 分支数组
    int branchCount;                  // 分支数量
    int defaultNum;                   // 默认跳转编号
    int isExit;                       // 是否退出
} Step;
```

## 测试

系统包含完整的测试桩代码，支持以下测试功能：

- 脚本加载测试
- 变量替换测试
- 对话执行测试

运行测试需要在main.cpp中取消注释测试代码部分。

## 系统限制

- 最大支持100个对话步骤
- 每个步骤最多10个分支
- 最大支持5个用户
- 每行文本最大256字符

## 使用说明

1. 根据需要修改或创建新的脚本文件
2. 在main.cpp中指定要加载的脚本文件名
3. 编译并运行程序
4. 输入用户ID开始对话交互

## 注意事项

- 脚本文件需要严格按照DSL语法格式编写
- 用户输入需要完全匹配分支关键词
- 系统会自动处理换行符和空格
- 退出步骤执行后程序会自动结束
