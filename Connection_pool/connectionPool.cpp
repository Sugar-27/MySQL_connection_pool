#include "connectionPool.h"

// 懒汉单例模式，只有调用get函数时才生成对象
ConnectionPool* ConnectionPool::get_pool() {
    static ConnectionPool m_pool;
    return &m_pool;
}

// 预处理配置文件
bool ConnectionPool::deal_config() {
    FILE* m_config = fopen("mysql.conf", "r");
    if (!m_config) {
        LOG("没有配置文件，请先配置好文件再次运行");
        return false;
    }
    while (!feof(m_config)) {
        char buf[1024] = {0};
        size_t len = sizeof buf;
        fgets(buf, sizeof buf, m_config);
        string _buf(buf);
        int idx = _buf.find('=');
        if (idx == -1)
            continue;
        string key = _buf.substr(0, idx);
        string val = _buf.substr(idx + 1, _buf.find('\n', idx) - idx - 1);
        // if (val.back() == '\n') val.pop_back();
        // cout << "key:" << key << endl;
        // cout << "value:" << val << endl;
        if (key == "ip")
            m_ip = val;
        else if (key == "port")
            m_port = atoi(val.c_str());
        else if (key == "username")
            m_user = val;
        else if (key == "password")
            m_password = val;
        else if (key == "dbname")
            m_dbname = val;
        else if (key == "initSize")
            m_init_size = atoi(val.c_str());
        else if (key == "maxSize")
            m_max_size = atoi(val.c_str());
        else if (key == "maxIdleTime")
            m_max_idletime = atoi(val.c_str());
        else if (key == "connectionTimeout")
            m_timeout = atoi(val.c_str());
    }
    return true;
}

// 数据库连接池的构造函数
ConnectionPool::ConnectionPool() : m_port(3306) {
    // 预处理，用配置文件对数据库连接池要连接的数据库属性进行配置，就不需要重新编译代码了
    if (!deal_config()) {
        LOG("未能完成连接池的初始化");
        return;
    }
    for (size_t i = 0; i < m_init_size; ++i) {
        Connection* p = new Connection();
        p->connect(m_ip, m_user, m_password, m_dbname, m_port);
        m_connection_queue.push(p);
        m_connection_cnt++;
    }
}

void ConnectionPool::print() {
    cout << m_ip << endl;
    cout << m_user << endl;
    cout << m_password << endl;
    cout << m_dbname << endl;
    cout <<  m_port << endl;
    cout <<  m_init_size << endl;
    cout <<  m_max_size << endl;
    cout <<  m_max_idletime << endl;
    cout <<  m_timeout << endl;
}