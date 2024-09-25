#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdarg.h>
#include <string.h>
#include <mysql/mysql.h>

#define HOST "localhost"
#define USER "jbrs"
#define PASSWORD "1234"
#define PORT 3306
#define DATABASE "ecommerce"

#define EMAILSIZE 32
#define PASSWDSIZE 32
#define QUERYSIZE 2048

#define EMAIL "email"
#define PASSWD "password"
#define ADDRESS "address"

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
    get_db_entry(email, EMAILSIZE, "Enter email of user to update: ", "Email too long!");

    char query[QUERYSIZE] = "SELECT *\n"
                            "FROM Users\n"
                            "WHERE email LIKE '";
    strcat(query, email);
    strcat(query, "';");

    if (mysql_query(conn, query) != 0) {
        die("ERROR mysql_query: %s\n", mysql_error(conn));
    }

    MYSQL_RES* res;
    if ((res = mysql_store_result(conn)) == NULL) {
        die("ERROR mysql_store_result: %s\n", mysql_error(conn));
    }

    if (mysql_num_rows(res) == 0) {
        printf("No results for given email!\n");
        mysql_free_result(res);
        mysql_close(conn);
        exit(EXIT_SUCCESS);
    }

    MYSQL_ROW row = mysql_fetch_row(res);
    if (row == NULL) {
        die("ERROR mysql_fetch_row: %s\n", mysql_error(conn));
    }

    printf(
        "Current email: %s\n"
        "Current password: %s\n"
        "Current address: %s\n",
        row[0], row[1], row[2]
    );

    mysql_free_result(res);

    char new_email[EMAILSIZE];
    char new_passwd[PASSWDSIZE];
    char* new_address = NULL;
    size_t new_address_size = 0;

    get_db_entry(new_email, EMAILSIZE,
                 "Enter new email: ", "Email too long!");
    get_db_entry(new_passwd, PASSWDSIZE,
                 "Enter new password: ", "Password too long!");

    printf("Enter new address: ");
    if (getline(&new_address, &new_address_size, stdin) < 0) {
        perror_die("ERROR getline");
    }
    size_t new_address_leng = strlen(new_address);
    if (new_address[new_address_leng - 1] == '\n') {
        new_address[--new_address_leng] = '\0';
    }

    if (*new_email == '\0' && *new_passwd == '\0' && *new_address == '\0') {
        printf("No new data given!\n");
        mysql_close(conn);
        exit(EXIT_SUCCESS);
    }
    
    bool comma = false;
    query[0] = '\0';
    strcpy(query, "UPDATE Users\n"
                  "SET\n");
    if (*new_email != '\0') {
        strcat(query, EMAIL);
        strcat(query, " = '");
        strcat(query, new_email);
        strcat(query, "'");
        comma = true;
    }
    if (*new_passwd != '\0') {
        if (comma) {
            strcat(query, ",\n");
        }
        strcat(query, PASSWD);
        strcat(query, " = '");
        strcat(query, new_passwd);
        strcat(query, "'");
        comma = true;
    }
    if (*new_address != '\0') {
        if (comma) {
            strcat(query, ",\n");
        }
        strcat(query, ADDRESS);
        strcat(query, " = '");
        strcat(query, new_address);
        strcat(query, "'");
    }
    strcat(query, "\nWHERE email LIKE '");
    strcat(query, email);
    strcat(query, "';");

    printf("Update SQL query:\n%s\n", query);

    if (mysql_query(conn, query) != 0) {
        die("ERROR mysql_query: %s\n", mysql_error(conn));
    }
    printf("Data updated successfully!\n");

    free(new_address);
    mysql_close(conn);
    return EXIT_SUCCESS;
}