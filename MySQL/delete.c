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

// Reads new entry from user and saves it into str.
size_t get_db_entry(char* str, size_t str_size, const char* msg, const char* error_msg) {
    size_t str_leng;
    while (1) {
        fputs(msg, stdout);
        fgets(str, str_size, stdin);
        str_leng = strlen(str);
        if (str_leng == str_size - 1 && str[str_leng - 1] != '\n') {
            puts(error_msg);
            clear_stdin();
            continue;
        }
        if (str[str_leng - 1] == '\n') {
            str[--str_leng] = '\0';
        }
        break;
    }
    return str_leng;
}

int main() {
    MYSQL* conn = mysql_init(NULL);
    if (conn == NULL) {
        die("Memory allocation error!\n");
    }

    if (mysql_real_connect(conn, HOST, USER, PASSWORD, DATABASE, PORT, NULL, 0) == NULL) {
        die("ERROR mysql_real_connect: %s\n", mysql_error(conn));
    }

    char email[EMAILSIZE];
    get_db_entry(email, EMAILSIZE, "Enter email of user to delete: ", "Email too long!\n");

    char query[QUERYSIZE] = "SELECT *\n"
                            "FROM Users\n"
                            "WHERE email LIKE '";
    strcat(query, email);
    strcat(query, "';");

    if (mysql_query(conn, query) != 0) {
        die("ERROR mysql_query: %s\n", mysql_error(conn));
    }
    
    MYSQL_RES* res = mysql_store_result(conn);
    if (res == NULL) {
        die("ERROR mysql_use_result: %s\n", mysql_error(conn));
    }

    if (mysql_num_rows(res) == 0) {
        printf("User not found!\n");
        mysql_free_result(res);
        mysql_close(conn);
        exit(EXIT_SUCCESS);
    }
    
    MYSQL_ROW row = mysql_fetch_row(res);
    if (row == NULL) {
        die("ERROR mysql_fetch_row: %s\n", mysql_error(conn));
    }

    printf(
        "User found!\n"
        "Email: %s\n"
        "Password: %s\n"
        "Address: %s\n",
        row[1], row[2], row[3]
    );
    mysql_free_result(res);

    printf("Do you want to delete user? [y/N]: ");
    int c = getchar();
    if (c != 'y' && c != 'Y') {
        printf("User not deleted!\n");
        exit(EXIT_SUCCESS);
    }

    strcpy(query, "DELETE FROM Users\n"
                  "WHERE email LIKE '");
    strcat(query, email);
    strcat(query, "';");

    if (mysql_query(conn, query) != 0) {
        die("ERROR mysql_query: %s\n", mysql_error(conn));
    }

    printf("User deleted successfully!\n");    

    mysql_close(conn);
    return EXIT_SUCCESS;
}