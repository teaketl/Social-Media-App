#include <iostream>
#include "SocialMedia.hpp"
#include "User.hpp"

// options once logged in
void loggedInUserMenu(User *loggedInUser, SocialMedia &socialMedia) {
    int choice;
    do {
        std::cout << "Select one of the following options:\n"
                  << "1. Edit Profile\n"
                  << "2. Create a Post\n"
                  << "3. Find users to follow\n"
                  << "4. View Notifications\n"
                  << "5. View followed users\n"
                  << "6. View your posts\n"
                  << "7. Logout\n"
                  << "Enter your choice: ";
        std::cin >> choice;

        switch (choice) {
            case 1: { // edit profile
                std::string newName, newUsername, newPassword;
                std::cout << "Enter new name: ";
                std::cin >> newName;
                std::cout << "Enter new username: ";
                std::cin >> newUsername;
                std::cout << "Enter new password: ";
                std::cin >> newPassword;
                loggedInUser->updateProfile(newName, newUsername, newPassword);
                break;
            }
            case 2: { // create a post
                std::string content;
                std::cout << "Enter post stuff: ";
                std::cin.ignore(); // buffer
                std::getline(std::cin, content);
                loggedInUser->createPost(content); //create post!
                break;
            }
            case 3: { // find users to follow
                std::string usernameToFollow;
                std::cout << "Enter username of the person you want to follow : ";
                std::cin >> usernameToFollow;
                User* userToFollow = socialMedia.authenticate(usernameToFollow, ""); // check if exists
                if (userToFollow != nullptr) {
                    socialMedia.followUser(loggedInUser, userToFollow);
                } else {
                    std::cout << "User " << usernameToFollow << " doesnt exist." << std::endl; 
                }
                break;
            }
            case 4: // view notifs
                loggedInUser->viewNotifications();
                break;
            case 5: // view ppl u follow
                loggedInUser->viewFollowing();
                break;
            case 6: // view posts
                loggedInUser->viewPosts();
                break;
            case 7: // Logout
                std::cout << "And you're logged out!! \n";
                break;
            default: // catch if someone enters something crazy
                std::cout << "try again...\n";
        }
    } while (choice != 7);
}

void loggedOutUserMenu(User*& loggedInUser, SocialMedia& socialMedia) {
    int choice;
    do {
        std::cout << "Select one of the following options:\n"
                  << "1. Login\n"
                  << "2. Sign up\n"
                  << "3. Exit or Continue to main menu if signing up.\n"
                  << "Choice: ";
        std::cin >> choice;

        switch (choice) {
            case 1: {
                std::string username, password;
                std::cout << "Enter username: ";
                std::cin >> username;
                std::cout << "Enter password: ";
                std::cin >> password; 
                loggedInUser = socialMedia.authenticate(username, password);//check if user entered the right info
                if (loggedInUser != nullptr) { 
                    std::cout << "User " << loggedInUser->getUsername() << " logged in successfully!\n";
                } else {
                    std::cout << "Incorrect. Try again. \n";
                }
                break;
            }
            case 2: { // Sign up
                std::string name, username, password;
                std::cout << "Enter your name: ";
                std::cin >> name;
                std::cout << "Choose a username: ";
                std::cin >> username;
                std::cout << "Choose a password: ";
                std::cin >> password;

                if (!socialMedia.isUserInFile("initial_users.txt", username)) {
                    User* newUser = new User(name + "," + username + "," + password); // Create as new user
                    try {
                        socialMedia.addUser(newUser);
                        std::cout << "User " << username << " is officially signed up! \n";
                        loggedInUser = newUser;
                    } catch (const std::invalid_argument& e) {
                        std::cerr << "Error: " << e.what() << std::endl;
                        delete newUser; // Don't add it
                    }
                } else {
                    std::cout << username << " has an owner. Try: " << username << "12232313\n"; // can't have the same username as an existing one
                }
                break;
            }
            case 3:
                std::cout << "Bye!! \n"; // Classic exit
                break;
            default:
                std::cout << "That's not an option... Kind of awkward..\n";
        }
    } while (choice != 3);
}

int main() {
    SocialMedia instagram;
    instagram.loadFromFile("initial_users.txt");
    User *loggedInUser = nullptr; //keep track of user logged in or not

    do {
        if (loggedInUser != nullptr) {
            loggedInUserMenu(loggedInUser, instagram);
            loggedInUser = nullptr; // reset to not logged in
        } else {
            loggedOutUserMenu(loggedInUser, instagram);
        }
    } while (loggedInUser != nullptr);

    instagram.saveToFile("initial_users.txt");

    return 0;
}
