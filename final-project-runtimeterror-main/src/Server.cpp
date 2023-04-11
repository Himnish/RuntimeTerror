
#include "server.h"

void Server::createServer(){
    sqlCode sqlConnection("10.0.2.2", "root", "");

    //server code based on demo of https://github.com/yhirose/cpp-httplib
    svr.Get("/start", [](const httplib::Request& req, httplib::Response& res) {
        res.set_content("Hello. Welcome to Runtime Terror. Your perfect improved home security system.", "text/plain");
    });
    
    
    //login
    svr.Post("/login", [&](const httplib::Request& req, httplib::Response& res) {
        int works = 1;
        if (!(req.has_param("username") && req.has_param("password"))){
            res.set_content("INVALID COMMAND", "text/plain");
            works = 0;
        }

        if (works == 1){
            std::string username = req.get_param_value("username");
            std::string password = req.get_param_value("password");
            
            if (!(sqlConnection.login(username, password))){
                res.set_content("INVALID CREDENTIALS", "text/plain");
                works = 0;
            }else{
                res.set_content("Logged in!", "text/plain");
                loggedIn = true;
            }
        }
    });
    
    
    //modes:
    svr.Post("/home", [&](const httplib::Request& req, httplib::Response& res) {
        if (loggedIn){
            currentMode = setting::home;
            res.set_content("home", "text/plain");
        }else{
            res.set_content("INVALID LOGIN", "text/plain");
        }
    });
    svr.Post("/monitor", [&](const httplib::Request& req, httplib::Response& res) {
        if (loggedIn){
            currentMode = setting::monitor;
            res.set_content("monitor", "text/plain");
        }else{
            res.set_content("INVALID LOGIN", "text/plain");
        }
    });
    svr.Post("/away", [&](const httplib::Request& req, httplib::Response& res) {
        if (loggedIn){
            currentMode = setting::away;
            res.set_content("away", "text/plain");
        }else{
            res.set_content("INVALID LOGIN", "text/plain");
        }
    });
    
    //get info:
    svr.Get("/files", [&](const httplib::Request& req, httplib::Response& res) {
        if (loggedIn){
            res.set_content(sqlConnection.getNames(), "text/plain");
        }else{
            res.set_content("INVALID LOGIN", "text/plain");
        }
    });
    
    svr.Get("/currentState", [&](const httplib::Request& req, httplib::Response& res) {
        std::string outStr = "";
        switch (currentMode){
            case setting::notRunning:
            outStr = "Not Running";
            break;
            case setting::home:
            outStr = "Home";
            break;
            case setting::monitor:
            outStr = "Monitor";
            break;
            case setting::away:
            outStr = "Away";
            break;
        }
        res.set_content(outStr, "text/plain");
    });

    //leave:
    svr.Post("/exit", [&](const httplib::Request& req, httplib::Response& res) {
        if (loggedIn){
            currentMode = setting::away;
            res.set_content("away", "text/plain");
        }else{
            res.set_content("INVALID LOGIN", "text/plain");
        }
    });
}

void Server::start(){
    svr.listen("localhost", 1234);
}

void Server::end(){
    svr.stop();
}
