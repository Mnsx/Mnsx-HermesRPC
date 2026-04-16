/** 
 * @file BasicUsage.cpp
 * @author Mnsx_x <xx1527030652@gmail.com>
 * @date 2026/4/15
 * @description 
 */
#include "../include/RpcServer.h"
#include <iostream>
#include <thread>
#include <chrono>

using namespace mnsx::hermes;

int main() {
    // 1. 初始化服务端，监听 8080 端口
    RpcServer server(8080);

    // 2. 注册业务路由：前线汇报战况
    server.getRouter().registerMethod("Valkyrie.Report", [](DataStream& stream) -> std::string {
        std::string reportData;
        stream >> reportData; // 从数据流中解析出情报

        std::cout << "\n[Valkyrie Hub] 收到前线战报: " << reportData << std::endl;

        // 模拟业务处理耗时 (比如存入数据库、图像识别)
        std::this_thread::sleep_for(std::chrono::milliseconds(500));

        // 返回处理结果给客户端
        return "指令已确认，准许开火！(针对战报: " + reportData + ")";
    });

    // 3. 启动网络层
    server.start();

    std::cout << "[Valkyrie Hub] 神经中枢已上线，等待前线节点接入..." << std::endl;

    // 4. 挂起主线程，让服务器持续运行
    // (如果你的 RpcServer 的 start() 没有自带阻塞的 loop_.loop()，请在这里用死循环防止 main 退出)
    while (true) {
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }

    return 0;
}