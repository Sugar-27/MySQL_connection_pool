#include "connection.h"

// 初始化数据库连接
Connection::Connection() {
    _conn = mysql_init(nullptr);
    // LOG("初始化成功");
}

// 关闭数据库连接
Connection::~Connection() {
    if (!_conn)
        mysql_close(_conn);
}

// 连接数据库
bool Connection::connect(string ip,
                         string user,
                         string password,
                         string dbname,
                         unsigned int port) {
    MYSQL* p =
        mysql_real_connect(_conn, ip.c_str(), user.c_str(), password.c_str(),
                           dbname.c_str(), port, nullptr, 0);
    if (p == nullptr) LOG("连接失败");
    return p != nullptr;
}

// 更新数据库
bool Connection::update(string& sql) {
    if (mysql_query(_conn, sql.c_str())) {
        LOG("更新失败：" + sql);
        return false;
    }
    return true;
}

// 查询数据库
MYSQL_RES* Connection::query(string& sql) {
    if (mysql_query(_conn, sql.c_str())) {
        LOG("查询失败：" + sql);
        return nullptr;
    }
    return mysql_use_result(_conn);
}