#ifndef USER_HPP
#define USER_HPP

#include <string>
#include "DynamicList.hpp"
#include "Post.hpp"
#include "Notification.hpp"

class User {
private:
    std::string data; // file stuff
    std::string name;
    std::string username;
    std::string password;
    DynamicList<Post*> posts; // dynamic list of posts, notifs, following, followers, etc.
    DynamicList<Notification*> notifications;
    DynamicList<User*> following;
    DynamicList<User*> followers;
    DynamicList<User*> followRequests;
public:
    // constructor uses data from users file
    User(const std::string &data);
    
    // setters
    void setName(const std::string &newName);
    void setUsername(const std::string &newUsername);
    void setPassword(const std::string &newPassword);
    
    // getters
    std::string getName() const; // get name, username, password of user
    std::string getUsername() const;
    std::string getPassword() const;
    
    // others
    DynamicList<Post*> getPosts() const; // get all users' posts
    DynamicList<Notification*> getNotifications() const; // get users' notifs
    DynamicList<User*> getFollowing() const; // get following

    // for menu options
    void removeFollowRequest(User *request); // if user declines request to follow
    void createPost(const std::string &content);
    void receiveNotification(const std::string &message); // gives user message
    void viewNotifications();
    void updateProfile(const std::string &newName, const std::string &newUsername, const std::string &newPassword);
    void viewFollowing(); // see who you're following
    void viewPosts(); // look at your posts
    void addFollower(User *follower);
};

#endif
