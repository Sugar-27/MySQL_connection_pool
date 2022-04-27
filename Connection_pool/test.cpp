#include <unistd.h>
#include "connection.h"
#include "connectionPool.h"

using std::cin;
using std::cout;
using std::endl;
using std::string;

// #define press_single
#define press_fout_thread

int main() {
    // 单线程测试
    // SQL语句，只测试插入
    string sql(
        "INSERT INTO user (name, age, sex) VALUES ('Test_user2', 1, "
        "'female');");
    // cout << sql << endl;
    /* 获取一个连接对这个连接进行插入测试
    Connection* test = new Connection();
    if (test->connect("localhost", "root", "root", "chat")) {
        if (test->update(sql)) {
            cout << "更新成功\n";
        } else {
            cout << "更新失败\n";
        }
    } else {
        cout << "连接失败\n";
    }
    sql = "SELECT * FROM user";
    test.query(sql);
    */

    /* 建立连接池，使用一个连接测试连接池是否好用
    ConnectionPool* tmp = ConnectionPool::get_pool();
    string stat;
    while (std::cin >> stat) {
        if (stat == "quit")
            break;
        std::shared_ptr<Connection> p = tmp->get_connection();
        p->update(sql);
    }
    */
#ifdef press_single
    // 压力测试
    // 模拟user_cnt个人对连接池进行访问
    int user_cnt = 1000;
    clock_t begin = clock();
    for (int i = 0; i < 1000; ++i) {
        // usleep(10);
        Connection conn;
        conn.connect("localhost", "root", "root", "chat");
        conn.update(sql);
        // ConnectionPool* pool = ConnectionPool::get_pool();
        // std::shared_ptr<Connection> p = pool->get_connection();
        // p->update(sql);
    }
    cout << clock() - begin << "ms" << endl;
#endif
#ifdef press_fout_thread

    clock_t begin = clock();
    // ConnectionPool* pool = ConnectionPool::get_pool();
    thread t1([&]() {
        for (int i = 0; i < 250; ++i) {
            // usleep(10);
            Connection conn;
            conn.connect("localhost", "root", "root", "chat");
            conn.update(sql);
            // ConnectionPool* pool = ConnectionPool::get_pool();
            // std::shared_ptr<Connection> p = pool->get_connection();
            // p->update(sql);
        }
    });
    thread t2([&]() {
        for (int i = 0; i < 250; ++i) {
            // usleep(10);
            Connection conn;
            conn.connect("localhost", "root", "root", "chat");
            conn.update(sql);
            // ConnectionPool* pool = ConnectionPool::get_pool();
            // std::shared_ptr<Connection> p = pool->get_connection();
            // p->update(sql);
        }
    });
    thread t3([&]() {
        for (int i = 0; i < 250; ++i) {
            // usleep(10);
            Connection conn;
            conn.connect("localhost", "root", "root", "chat");
            conn.update(sql);
            // ConnectionPool* pool = ConnectionPool::get_pool();
            // std::shared_ptr<Connection> p = pool->get_connection();
            // p->update(sql);
        }
    });
    thread t4([&]() {
        for (int i = 0; i < 250; ++i) {
            // usleep(10);
            Connection conn;
            conn.connect("localhost", "root", "root", "chat");
            conn.update(sql);
            // ConnectionPool* pool = ConnectionPool::get_pool();
            // std::shared_ptr<Connection> p = pool->get_connection();
            // p->update(sql);
        }
    });
    t1.join();
    t2.join();
    t3.join();
    t4.join();

    cout << clock() - begin << "ms" << endl;
    // cout << "1111" << endl;

#endif
    printf("结束\n");
    return 0;
}