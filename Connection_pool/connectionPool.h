#ifndef CONNECTIONPOOL_H
#define CONNECTIONPOOL_H

#include <atomic>
#include <condition_variable>
#include <cstring>
#include <functional>
#include <iostream>
#include <memory>
#include <mutex>
#include <queue>
#include <string>
#include <thread>
#include "connection.h"

using std::atomic;
using std::queue;
using std::string;
using std::thread;

class ConnectionPool {
   public:
    // 对外部提供一个接口，用来获取单例线程池
    static ConnectionPool* get_pool();
    // 消费者获取一个连接
    std::shared_ptr<Connection> get_connection();
    // 测试代码用，可删除，用于打印所有的私有成员变量
    void print();
    ~ConnectionPool() = default;

   private:
    string m_ip;          // 数据库的IP
    string m_user;        // 数据库的用户名
    string m_password;    // 数据库的密码
    string m_dbname;      // 数据库使用的库名
    unsigned int m_port;  // 数据库的端口号
    int m_init_size;      // 数据库连接池的初始线程数量
    int m_max_size;       // 数据库连接池的最大线程数量
    int m_max_idletime;   // 数据库连接池各线程最大空闲时间
    int m_timeout;        // 数据库连接池获取连接的超时时间
    // 连接队列，用于存放连接池中的所有连接
    queue<Connection*> m_connection_queue;
    std::mutex m_queue_mutex;  // 队列锁，维护线程安全
    atomic<int> m_connection_cnt;  // 原子操作，保存现在拥有的连接数量
    std::condition_variable cv;  // 条件变量，用于连接生产者和消费者之间的通信

   private:
    ConnectionPool();    // 单例模式，构造函数私有
    bool deal_config();  // 处理配置文件，从配置文件加载配置项
    void produce_connection();  // 生产者生产一个连接
    void scan_connection_time(); // 定时器的处理函数
};

#endif