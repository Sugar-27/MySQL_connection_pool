/* 遵循RAII标准，对MySQL连接进行封装*/

#include <mysql/mysql.h>
#include <ctime>
#include <string>
#include <iostream>

#define LOG(str) std::cout << __FILE__ << ":" << __LINE__ << " " << __TIMESTAMP__ << " : " << str << std::endl;

using std::string;
using std::cout;
using std::cin;
using std::endl;

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
   private:
    MYSQL* _conn;
};