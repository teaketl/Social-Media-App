#ifndef SOCIALMEDIA_HPP
#define SOCIALMEDIA_HPP

#include <string>
#include "DynamicList.hpp"
#include "User.hpp"

class SocialMedia {
private:
    DynamicList<User*> users;
    
public:
    void addUser(User *user);
    void removeUser(User *user);
    DynamicList<User*> getUsers() const;
    void saveToFile(const std::string &filename);
    void loadFromFile(const std::string &filename);
    User *authenticate(const std::string &username, const std::string &password) const;
    bool isUserInFile(const std::string &filename, const std::string &username);
    void followUser(User *follower, User *userToFollow);
};

#endif
