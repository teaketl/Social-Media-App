#include "SocialMedia.hpp"
#include <fstream>
#include <stdexcept>
#include <sstream>
#include <iostream>

DynamicList<User*> SocialMedia::getUsers() const {
    return users;
}

void SocialMedia::addUser(User *user) {
    for (User *existingUser : users.getItems()) {
        if (existingUser->getUsername() == user->getUsername()) {
            throw std::invalid_argument("Username is taken!");
        }
    }
    users.add(user);
    
    std::ofstream outFile("initial_users.txt", std::ios::app); // append user to file
    if (!outFile.is_open()) {
        throw std::runtime_error("Can't open or append.");
    }
    outFile << user->getName() << "," << user->getUsername() << "," << user->getPassword() << "\n";
    outFile.close();
}

void SocialMedia::removeUser(User *user) {
    users.remove(user);
    
    // Update file
    std::ifstream inFile("initial_users.txt"); 
    if (!inFile.is_open()) {
        throw std::runtime_error("Cant open.");
    }

    std::ofstream outFile("temp_users.txt");
    if (!outFile.is_open()) {
        inFile.close();
        throw std::runtime_error("Cant open file.");
    }

    std::string line;
    std::string usernameToRemove = user->getUsername();
    while (std::getline(inFile, line)) {//read line by line
        // write all other users
        std::string username = line.substr(0, line.find(","));
        if (username != usernameToRemove) {
            outFile << line << "\n";
        }
    }

    inFile.close();
    outFile.close();

    // swap files
    remove("initial_users.txt");
    rename("temp_users.txt", "initial_users.txt");
}


void SocialMedia::saveToFile(const std::string &filename) {
    std::ofstream file(filename);
    if (!file.is_open()) { //not open
        throw std::runtime_error("Sorry, the file is not opening.");
    }

    for (User* user : users.getItems()) { //save to file as name, usernmae, pass
        file << user->getName() << "," << user->getUsername() << "," << user->getPassword() << "\n";
    }

    file.close();
}

void SocialMedia::loadFromFile(const std::string &filename) {
    std::ifstream file(filename);
    if (!file.is_open()) { // Open file
        throw std::runtime_error("Can't open file... maybe check if it exists..");
    }

    std::string line;
    while (std::getline(file, line)) { //read line by line and create user
        std::stringstream ss(line);
        std::string name, username, password;
        if (std::getline(ss, name, ',') && std::getline(ss, username, ',') && std::getline(ss, password)) {
            std::string userData = name + "," + username + "," + password;
            users.add(new User(userData));

        } else {
            std::cerr << "Invalid line: " << line << std::endl; //less than name, usernmae, pass
        }
    }

    file.close();
}

User *SocialMedia::authenticate(const std::string &username, const std::string &password) const {
    std::ifstream file("initial_users.txt"); // open file
    if (!file.is_open()) { // if not open
        std::cerr << "Error opening file." << std::endl;
        return nullptr;
    }

    std::string line;
    while (std::getline(file, line)) { // go through each line
        std::istringstream iss(line);
        std::string extractedName, extractedUsername, extractedPassword;

        // get name, username, password
        std::getline(iss, extractedName, ',');
        std::getline(iss, extractedUsername, ',');
        std::getline(iss, extractedPassword, ',');

        // check against userInput
        if (extractedUsername == username && extractedPassword == password) {
            file.close();
            User* authenticatedUser = new User(extractedName + "," + extractedUsername + "," + extractedPassword);
            return authenticatedUser;
        }
    }

    file.close();
    return nullptr; // failed authentification
}

bool SocialMedia::isUserInFile(const std::string &filename, const std::string &username) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Can't open:  " << filename << std::endl;
        return false;
    }

    std::string line;
    while (std::getline(file, line)) {
        // get username
        std::string extractedUsername = line.substr(1); //username index 1
        if (extractedUsername == username) {
            file.close();
            return true; // found username
        }
    }

    file.close();
    return false; // username not found in file
}

void SocialMedia::followUser(User *follower, User *userToFollow) {
    if (follower != nullptr && userToFollow != nullptr) { //do they exist?
        follower->getFollowing().add(userToFollow);// add to follower list
        userToFollow->addFollower(follower); // update the following
        std::cout << "Now following: " << userToFollow->getUsername() << std::endl;
    }
}
