// SpyerModule.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "TurnToDesktopStrategy.h"
#include "StartSearchStrategy.h"
#include "CVoperate.h"

int main() {
    std::cout << "请选择策略：" << std::endl;
    std::cout << "1. 转到桌面策略" << std::endl;
    std::cout << "2. 开启搜索策略" << std::endl;

    // 读取用户输入
    std::string input;
    std::getline(std::cin, input);

    Strategy* setter;
    if (input == "1") {
        setter = new TurnToDesktopStrategy();
    }
    else if (input == "2") {
        std::cout << "请输入搜索问题：";
        std::string query;
        std::getline(std::cin, query);
        setter = new StartSearchStrategy(query);
    }
    else {
        std::cout << "无效的输入！" << std::endl;
        return 1;
    }

    CVoperate::setStrategy(setter);
    CVoperate::RUN(-1, -1, 640, 800);

    return 0;
}