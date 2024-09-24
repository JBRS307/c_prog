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

#define QUERYSIZE 8192
#define EMAIL_SIZE 32
#define PASSWORD_SIZE 32

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
    char query[QUERYSIZE];
    query[0] = '\0';

    char email[EMAIL_SIZE];
    char password[PASSWORD_SIZE];
    char* address = NULL;
    size_t address_size = 0;

    MYSQL* conn = mysql_init(NULL);
    if (conn == NULL) {
        die("ERROR on mysql_init: %s\n", mysql_error(conn));
    }

    if (mysql_real_connect(conn, HOST, USER, PASSWORD, DATABASE, PORT, NULL, 0) == NULL) {
        die("ERROR mysql_real_connect: %s\n", mysql_error(conn));
    }
    printf("Connected to database\n");


    size_t email_leng;
    while (1) {
        printf("Enter email: ");
        fgets(email, EMAIL_SIZE, stdin);
        email_leng = strlen(email);
        if (email_leng == EMAIL_SIZE - 1 && email[email_leng - 1] != '\n') {
            clear_stdin();
            printf("Invalid email!\n");
            continue;
        }
        if (email[email_leng - 1] == '\n') {
            email[--email_leng] = '\0';
        }
        break;
    }

    size_t password_leng;
    while (1) {
        printf("Enter password: ");
        fgets(password, PASSWORD_SIZE, stdin);
        password_leng = strlen(password);
        if (password_leng == PASSWORD_SIZE - 1 && password[password_leng - 1] != '\n') {
            clear_stdin();
            printf("Invalid password!\n");
            continue;
        }
        if (password[password_leng - 1] == '\n') {
            password[--password_leng] = '\0';
        }
        break;
    }

    printf("Enter address: ");
    if (getline(&address, &address_size, stdin) < 0) {
        perror_die("ERROR getline");
    }
    size_t address_leng = strlen(address);
    if (address[address_leng - 1] == '\n') {
        address[--address_leng] = '\0';
    }
    
    strcpy(query, "INSERT INTO Users (email, password, address)\n"
                  "VALUES ('");
    strcat(query, email);
    strcat(query, "', '");
    strcat(query, password);
    strcat(query, "', '");
    strcat(query, address);
    strcat(query, "');");

    printf("SQL query:\n%s\n", query);
    if (mysql_query(conn, query) < 0) {
        die("ERROR mysql_query: %s", mysql_error(conn));
    }
    printf("Row added successfully!\n");

    free(address);
    mysql_close(conn);

    return EXIT_SUCCESS;
}