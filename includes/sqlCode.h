#pragma once
#include <string>
using std::string;
#include <mysql/mysql.h>
#include <stdexcept>
#include <iostream>

class sqlCode{
    public:
        sqlCode(const char *host_name, const char *user_name, const char *password);
        ~sqlCode();
        bool makeAccount(string user, string pass); //returns true if valid new account, false if account already exists
        bool login(string user, string pass); //returns true if account is valid, false if account doesn't match
        void insertName(std::string name, std::string time);
        std::string getNames();
        void deleteTable(std::string tableName);
    private:
        MYSQL *conn;
};
