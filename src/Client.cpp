#include "../includes/httplib.h"
#include <iostream>
#include "sqlCode"


int main(void)
{

  httplib::Client cli("127.0.0.1", 1234);
//////////////////////////////////////////////////////////////////////////////////

string userName;
string userPassword;
int loginAttempt = 0;


while (loginAttempt < 5)
{
    cout << "Please enter your user name: ";
    cin >> userName;
    cout << "Please enter your user password: ";
    cin >> userPassword;

    if (login == true)
    {
        cout << "Welcome" + name + "!\n";
        break;
    }
    else
    {
        cout << "Invalid login attempt. Please try again.\n" << '\n';
        loginAttempt++;
    }
}

if (loginAttempt == 5)
{
        cout << "Too many login attempts! The program will now terminate.";
        return 0;
}

cout << "Thank you for logging in.\n";

//////////////////////////////////////////////////////////////////////////////////

  if (auto res = cli.Get("/hi")) {
    if (res->status == 200) {
      std::cout << res->body << std::endl;
    }
  } else {
    auto err = res.error();
  }


std::string body;

auto res = cli.Get(
  "/stream", Headers(),
  [&](const Response &response) {
    EXPECT_EQ(200, response.status);
    return true; // return 'false' if you want to cancel the request.
  },
  [&](const char *data, size_t data_length) {
    body.append(data, data_length);
    return true; // return 'false' if you want to cancel the request.
  });

  
}