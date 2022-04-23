#include <mysql/mysql.h>
#include <stdio.h>
#include <stdlib.h>

int main(void) {
    MYSQL conn;

    mysql_init(&conn);
    if (mysql_real_connect(&conn, "localhost", "root", "root", "chat", 3306,
                           NULL, 0)) {
        if (mysql_query(&conn, "INSERT INTO user (name, age, sex) VALUES ('Test_user', 1, 'male')") != 0)
        {
            printf("mysql_real_query failed: %s\n", mysql_error(&conn));
            exit(0);
        }   
        mysql_close(&conn); 
        exit(0);
    } else {
        printf("mysql_real_connect failed: %s\n", mysql_error(&conn));
    }
    return 0;
}