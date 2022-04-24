#include "connection.h"
#include "connectionPool.h"

using std::cin;
using std::cout;
using std::endl;
using std::string;

int main() {
    string sql(
        "INSERT INTO user (name, age, sex) VALUES ('Test_user2', 1, 'female')");
    cout << sql << endl;
    // Connection* test = new Connection();
    // if (test->connect("localhost", "root", "root", "chat")) {
    //     if (test->update(sql)) {
    //         cout << "更新成功\n";
    //     } else {
    //         cout << "更新失败\n";
    //     }
    // } else {
    //     cout << "连接失败\n";
    // }
    // sql = "SELECT * FROM user";
    // test.query(sql);

    // 建立连接池，使用一个连接测试连接池是否好用
    ConnectionPool* tmp = ConnectionPool::get_pool();
    for (int i = 0; i < 5; ++i) {
        std::shared_ptr<Connection> p = tmp->get_connection();
        p->update(sql);
    }
    printf("结束\n");
    return 0;
}