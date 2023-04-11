#include "sqlCode.h"
#include <string>
#include <regex>
using std::string;

//Much of this code is based on from: https://github.com/mortinger91/header-only-cpp-mysql
sqlCode::sqlCode(const char *host_name, const char *user_name, const char *password){
    conn = mysql_init (NULL);  
    if (conn == NULL)
    { 
        throw std::runtime_error("SQL DID NOT CONNECT!");
    }
    if (mysql_real_connect (conn, host_name, user_name, password, 
        NULL, 3306, NULL, 0) == NULL)
    {
        throw std::runtime_error("SQL DID NOT CONNECT!");
    }
}

sqlCode::~sqlCode(){
    mysql_close (conn);
}

bool sqlCode::makeAccount(string user, string pass){
    //check if user already there
    std::string query = "SELECT * FROM learninginfo.users WHERE Users = (SELECT Users FROM learninginfo.users WHERE Users = \""  + user + "\");"; //SELECT Password FROM `users` WHERE Users = (SELECT Users FROM `users` WHERE Users = "username");
    const char* newQuery = &query[0];
    mysql_query (conn, newQuery);
    MYSQL_RES *result;
    result = mysql_store_result (conn);
    MYSQL_ROW row;
    int out = 0;
    while ((row = mysql_fetch_row (result)) != NULL)
    {
        out += 1;
    }
    if (out != 0){
        return false;
    }
    
    query = "INSERT INTO learninginfo.users (`Users`, `Password`) VALUES ('" + user + "', MD5('" + pass + "'))"; //SELECT Password FROM `users` WHERE Users = (SELECT Users FROM `users` WHERE Users = "username");
    const char* selectQuery = &query[0];
    mysql_query (conn, selectQuery);
    //INSERT INTO `users` (`Users`, `Password`) VALUES ('', MD5(''))

    //create user/pass
    return true;
}
bool sqlCode::login(string user, string pass){
    std::string query = "SELECT * FROM learninginfo.users WHERE Users = (SELECT Users FROM learninginfo.users WHERE Users = \""  + user + "\" AND Password = MD5 (\"" + pass + "\"));"; //SELECT Password FROM `users` WHERE Users = (SELECT Users FROM `users` WHERE Users = "username");
    std::cout << "Query" << query << std::endl;
    const char* newQuery = &query[0];
    mysql_query (conn, newQuery);
    MYSQL_RES *result;
    result = mysql_store_result (conn);
    MYSQL_ROW row;
    int out = 0;
    while ((row = mysql_fetch_row (result)) != NULL)
    {
        out += 1;
    }
    if (out == 1){
        return true;
    }
    return false;
}

void sqlCode::insertName(std::string name, std::string time){
    name = name + "      ";
    time = time + "~";
    std::string query = "INSERT INTO learninginfo.faces (`info`, `time`) VALUES ('" + name + "', '" + time + "')";
    std::cout << query << std::endl;
    const char* selectQuery = &query[0];
    mysql_query (conn, selectQuery);
}

std::string sqlCode::getNames(){
    std::string query = "SELECT * FROM learninginfo.faces";
    const char* newQuery = &query[0];
    mysql_query (conn, newQuery);
    MYSQL_RES *result;
    result = mysql_store_result (conn);
    MYSQL_ROW row;

    std::string out = "";
    while ((row = mysql_fetch_row (result)) != NULL)
    {
        char tmp = '!';
        //std::cout << row[0] << std::endl;
        int i = 0;
        while (tmp != '~'){
            tmp = *(row[0]+i);
            out += tmp;
            i++;
        }
        out += "\n";
    }
    out = std::regex_replace(out, std::regex("~"), "");

    return out;

}

void sqlCode::deleteTable(std::string table){
    std::string query = "TRUNCATE learninginfo." + table;
    std::cout << query << std::endl;
    const char* selectQuery = &query[0];
    mysql_query (conn, selectQuery);
}
//videos and text. 
