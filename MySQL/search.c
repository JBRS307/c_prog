#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <mysql/mysql.h>

#define HOST "localhost"
#define USER "jbrs"
#define PASSWORD "1234"
#define PORT 3306
#define DATABASE "ecommerce"

#define EMAILSIZE 32
#define QUERYSIZE 2048

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

void clear_stdin() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int main() {
    MYSQL* conn = mysql_init(NULL);
    if (conn == NULL) {
        die("Memory allocation error!\n");
    }

    if (mysql_real_connect(conn, HOST, USER, PASSWORD, DATABASE, PORT, NULL, 0) == NULL) {
        die("ERROR mysql_real_connect: %s\n", mysql_error(conn));
    }

    size_t email_leng;
    char email[EMAILSIZE];
    while (1) {
        printf("Enter email to search: ");
        fgets(email, EMAILSIZE, stdin);
        email_leng = strlen(email);
        if (email_leng == EMAILSIZE - 1 && email[email_leng - 1] != '\n') {
            clear_stdin();
            printf("Invalid email!\n");
            continue;
        }
        if (email[email_leng - 1] == '\n') {
            email[--email_leng] = '\0';
        }
        break;
    }

    char query[QUERYSIZE] = "SELECT *\n"
                            "FROM Users\n"
                            "WHERE email LIKE '";
    
    strcat(query, email);
    strcat(query, "';");

    printf("SQL query:\n%s\n", query);

    if (mysql_query(conn, query) != 0) {
        die("ERROR mysql_query: %s\n", mysql_error(conn));
    }

    MYSQL_RES* res = mysql_use_result(conn);
    if (res == NULL) {
        die("ERROR mysql_use_result: %s\n", mysql_error(conn));
    }

    MYSQL_ROW row;
    while ((row = mysql_fetch_row(res)) != NULL) {
        printf("Email address: %s\n"
               "Password: %s\n"
               "Address: %s\n", row[1], row[2], row[3]);
    }

    mysql_free_result(res);
    mysql_close(conn);

    return EXIT_SUCCESS;
}