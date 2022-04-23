#ifndef CONNECTIONPOOL_H
#define CONNECTIONPOOL_H

#include <atomic>
#include <cstring>
#include <iostream>
#include <mutex>
#include <queue>
#include <string>
#include <thread>
#include "connection.h"

using std::atomic;
using std::queue;
using std::string;

class ConnectionPool {
   public:
    static ConnectionPool* get_pool();
    void print();
    ~ConnectionPool() = default;

   private:
    ConnectionPool();
    bool deal_config();
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
    atomic<int> m_connection_cnt;  // 原子操作，保存现在拥有的连接数量
};

#endif