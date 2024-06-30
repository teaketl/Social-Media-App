#ifndef NOTIFICATION_HPP
#define NOTIFICATION_HPP

#include <string>

class User; //for later

class Notification {
private:
    std::string message;
    User *user;
    
public:
    // constructor
    Notification(const std::string &message, User *user);
    // setters
    void setMessage(const std::string &newMessage);
    void setUser(User *newUser);
    // getters
    std::string getMessage() const;
    User *getUser() const;
};

#endif
