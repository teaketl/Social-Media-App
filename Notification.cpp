#include "Notification.hpp"
#include "User.hpp"

// constructor
Notification::Notification(const std::string &message, User *user)
    : message(message), user(user) {}

// setters
void Notification::setMessage(const std::string &newMessage) {
    message = newMessage;
}

void Notification::setUser(User *newUser) {
    user = newUser;
}

// getters
std::string Notification::getMessage() const {
    return message;
}

User *Notification::getUser() const {
    return user;
}
