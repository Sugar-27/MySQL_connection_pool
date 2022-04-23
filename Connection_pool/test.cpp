#include "connection.h"

using std::string;
using std::cout;
using std::cin;
using std::endl;

int main() {
    Connection test;
    string sql("INSERT INTO user (name, age, sex) VALUES ('Test_user2', 1, 'female')");
    // cout << sql << endl;
    if (test.connect("localhost", "root", "root", "chat")) {
        if (test.update(sql)) {
            cout << "更新成功\n";
        } else {
            cout << "更新失败\n";
        }
    } else {
        cout << "连接失败\n";   
    }
    sql = "SELECT a FROM user";
    test.query(sql);

    return 0;
}