#include "User.hpp"
#include <stdexcept>
#include <sstream>
#include <fstream>
#include <iostream>

User::User(const std::string &data) : data(data) { // read through data to get user info
    std::istringstream iss(data);
    std::getline(iss, name, ',');       
    std::getline(iss, username, ',');  
    std::getline(iss, password, ',');
}

// set
void User::setName(const std::string &newName){
    name = newName;
}
void User::setUsername(const std::string &newUsername){
    username = newUsername;
}
void User::setPassword(const std::string &newPassword){
    password = newPassword;
}

// get
std::string User::getName() const {
    return name;
}

std::string User::getUsername() const {
    return username;
}

std::string User::getPassword() const {
    return password;
}

DynamicList<Post*> User::getPosts() const {
    return posts;
}

DynamicList<Notification*> User::getNotifications() const {
    return notifications;
}

DynamicList<User*> User::getFollowing() const {
    return following;
}

// Other methods
void User::createPost(const std::string &content) {
    Post *post = new Post(content, this); //create post 
    posts.add(post); //add to posts lst
}

void User::receiveNotification(const std::string &message) {
    Notification *notification = new Notification(message, this); //create notif for user
    notifications.add(notification); //add notif to notifs lsit
}


void User::updateProfile(const std::string &newName, const std::string &newUsername, const std::string &newPassword) {
    // check if username already exists
    for (User *existingUser : followers.getItems()) { // loop through
        if (existingUser->getUsername() == newUsername) {
            throw std::invalid_argument("Username taken, sorry!");
        }
    }
    std::ofstream file("initial_users.txt", std::ios::app); // append to file
    if (!file.is_open()) {
        throw std::runtime_error("Couldnt open file.");
    }

    std::string updatedData = newName + "," + newUsername + "," + newPassword;
    file << updatedData << std::endl; //put in file
    file.close();
}

void User::viewNotifications() {
    std::cout << "Notifications:\n";
    for (Notification *notification : notifications.getItems()) { //loops through a users' notifs 
        std::cout << notification->getMessage() << std::endl;
    }
}

void User::viewFollowing() {
    std::cout << "Following:\n";
    for (User *followedUser : following.getItems()) { //loops through following items and prints users
        std::cout << followedUser->getUsername() << std::endl;
    }
}

void User::viewPosts() {
    std::cout << "Posts:\n";
    for (Post* post : posts.getItems()) { //loop through items in list
        std::cout << "Content: " << post->getContent() << std::endl;
        std::cout << "User: " << post->getAuthor()->getUsername() << std::endl;
        std::cout << "****************\n";
    }
}

void User::addFollower(User *follower) { //add follower to followers list
    followers.add(follower);
}
