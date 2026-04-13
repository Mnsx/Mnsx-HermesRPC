# Mnsx-Olympus

## 功能介绍

**Mnsx-Olympus**是一个基于C++11构建的高性能、非阻塞式分布式RPC框架

框架旨在解决现代分布式系统中高并发I/O压力与复杂业务逻辑解耦的矛盾，通过极致的内存管理与线程调度，为开发者提供丝滑的体验

## 核心组件

| 核心组件                                                     | 技术亮点                    | 说明                                                         |
| ------------------------------------------------------------ | --------------------------- | ------------------------------------------------------------ |
| [Mnsx-AchillesLink](https://github.com/Mnsx/Mnsx-AchillesLink) | Reactor模型 + Epoll多路复用 | **基于Linux原生Epoll实现的非阻塞事件循环**，杜绝I/O阻塞      |
| [Mnsx-KrakenPool](https://github.com/Mnsx/Mnsx-KrakenPool)   | 通用性延时线程池            | **采用延时任务队列与多工作线程模式**，实现I/O线程与业务逻辑的物理隔离 |
| [Mnsx-ArgusLog](https://github.com/Mnsx/Mnsx-ArgusLog)       | 多维度分发日志处理          | **按照生产者-消费者模型，提供拔插式异步日志处理**            |
| Mnsx-HydraConn（开发中）                                     |                             |                                                              |

