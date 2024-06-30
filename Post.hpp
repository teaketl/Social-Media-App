#ifndef POST_HPP
#define POST_HPP

#include <string>

class User; // will be made later

class Post {
private:
    std::string content; // stuff in post
    User *author; // post maker
public:
    Post(const std::string &content, User *author); // constructor
    
    // setters
    void setContent(const std::string &newContent);
    void setAuthor(User *newAuthor);
    
    // getters
    std::string getContent() const;
    User *getAuthor() const;
};

#endif
