/** 
 * @file ClientDemo.cpp
 * @author Mnsx_x <xx1527030652@gmail.com>
 * @date 2026/4/16
 * @description 
 */
/**
 * @file ClientDemo.cpp
 * @description HermesRPC 纯异步客户端测试点
 */
#include "RpcClient.h"
#include "reactor/EventLoop.h"
#include "KrakenPool.h"
#include <iostream>
#include <thread>
#include <chrono>
#include <string>

using namespace mnsx::hermes;

int main() {
    std::cout << "[Client Main] 正在初始化前线节点..." << std::endl;

    // 1. 准备底盘：网络引擎与海妖线程池
    mnsx::achilles::EventLoop loop;
    mnsx::kraken::KrakenPool kraken(4); // 召唤 4 根海妖触手

    // 2. 组装客户端
    RpcClient client(&loop, &kraken, "0.0.0.0", 8080);

    // ==========================================
    // 3. 【极度核心】：在独立线程点火网络引擎
    // ==========================================
    std::thread io_thread([&loop]() {
        std::cout << "[Client I/O] 网络引擎点火，接管底层收发。" << std::endl;
        loop.loop();
    });

    // 4. 发起连接 (异步瞬间返回)
    client.connect();

    // 稍微等待 1 秒，确保 TCP 三次握手成功
    std::this_thread::sleep_for(std::chrono::seconds(1));
    std::cout << "\n[Client Main] 链路已建立，开始疯狂倾泻火力 (发送请求)！" << std::endl;

    // ==========================================
    // 5. 纯异步调用：主线程像机关枪一样发射
    // ==========================================
    for (int i = 1; i <= 5; ++i) {
        std::string data = "发现敌军目标 " + std::to_string(i);

        DataStream stream("");
        stream << data;

        // 调用 asyncCall，瞬间返回，绝对不阻塞主线程！
        client.call("Valkyrie.Report", stream.data(), [i](const std::string& resp) {
            // 【这行代码运行在 KrakenPool 的某个工作线程里】
            std::cout << "[Kraken Thread] 收到第 " << i << " 次请求的回执: " << resp << std::endl;
        });

        std::cout << "[Client Main] 已发送: " << data << std::endl;
    }

    std::cout << "[Client Main] 火力倾泻完毕！主线程现在非常闲，可以去喝杯咖啡了。\n" << std::endl;

    // 6. 等待后台线程 (防止程序直接退出)
    io_thread.join();

    return 0;
}