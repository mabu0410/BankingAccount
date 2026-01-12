#ifndef AUTH_CONTROLLER_H
#define AUTH_CONTROLLER_H

#include <string>
#include "services/UserService.h"

class AuthController {
private:
    UserService* userService;
    User* currentUser;

public:
    AuthController(UserService* service);
    
    bool registerUser();
    bool login();
    void logout();
    bool changePassword();
    void viewProfile();
    
    User* getCurrentUser();
    bool isLoggedIn();
};

#endif // AUTH_CONTROLLER_H
