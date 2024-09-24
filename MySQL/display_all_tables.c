#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include "mysql/mysql.h"

#define HOST "localhost"
#define USER "jbrs"
#define PASSWORD "1234" // Who is gonna hack into that anyway?
#define PORT 3306
#define DATABASE "mysql"

void die(const char* fmt, ...) {
    va_list args;
    va_start(args, fmt);
    vfprintf(stderr, fmt, args);
    va_end(args);
    exit(EXIT_FAILURE);
}

void perror_die(const char* msg) {
    perror(msg);
    exit(EXIT_FAILURE);
}

int main() {
    MYSQL* conn;
    MYSQL_RES* res;
    MYSQL_ROW row;

    conn = mysql_init(NULL);
    if (conn == NULL) {
        die("Memory allocation error!\n");
    }

    if (mysql_real_connect(conn, HOST, USER, PASSWORD, DATABASE, PORT, NULL, 0) == NULL) {
        die("ERROR on mysql_real_connect\n");
    }

    if (mysql_query(conn, "SHOW TABLES") != 0) {
        die("ERROR on mysql_query\n");
    }

    res = mysql_use_result(conn);
    if (res == NULL) {
        die("ERROR on mysql_use_result\n");
    }

    printf("Tables in mysql database:\n");
    while ((row = mysql_fetch_row(res)) != NULL) {
        printf("%s\n", row[0]);
    }
    mysql_free_result(res);
    mysql_close(conn);

    return EXIT_SUCCESS;
}