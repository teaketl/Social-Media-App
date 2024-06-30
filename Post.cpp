#include "Post.hpp"
#include "User.hpp"

//construct
Post::Post(const std::string &content, User *author)
    : content(content), author(author) {}

// setters
void Post::setContent(const std::string &newContent) {
    content = newContent;
}

void Post::setAuthor(User *newAuthor) {
    author = newAuthor;
}

// getters
std::string Post::getContent() const {
    return content;
}

User *Post::getAuthor() const {
    return author;
}
