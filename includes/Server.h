#pragma once
#include <iostream>
#include "sqlCode.h"
#include "httplib.h"

enum class setting {notRunning, home, monitor, away};

class Server{
    public:
        void createServer();
        void start();
        void end();
    
        setting currentMode = setting::notRunning;
        bool loggedIn = false;
        httplib::Server svr;
};
