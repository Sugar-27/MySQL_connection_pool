#ifndef CONNECTION_H
#define CONNECTION_H
#include <mysql/mysql.h>
#include <ctime>
#include <iostream>
#include <string>

/* 宏定义，用于打印日志 */
#define LOG(str)                                                              \
    std::cout << __FILE__ << ":" << __LINE__ << " " << __TIMESTAMP__ << " : " \
              << str << std::endl;

using std::cin;
using std::cout;
using std::endl;
using std::string;

/* 遵循RAII标准，对MySQL连接进行封装 */
class Connection {
   public:
    // 初始化连接
    Connection();
    // 析构连接
    ~Connection();
    // 连接数据库
    bool connect(string ip,
                 string user,
                 string password,
                 string dbname,
                 unsigned int port = 3306);
    // 更新操作 insert、delete、update
    bool update(string& sql);
    // 查询操作 select
    MYSQL_RES* query(string& sql);
    // 刷新一下起始的空闲时间点
    void refresh_alive_time() { _alive_time = clock(); }
    // 返回存活的时间
    clock_t get_alive_time() const {
        // 存活的时间即：当前的时间-起始的时间点
        return clock() - _alive_time;
    }

   private:
    MYSQL* _conn;
    clock_t _alive_time;  // 记录进入空闲状态后的起始时间点(应该在进入队列的时候更新时间点)  
};

#endif