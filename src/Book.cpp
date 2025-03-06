#include "Book.h"

Book::Book(std::string title, std::string author, std::string ISBN)
        : title(title), author(author), ISBN(ISBN), isAvailable(true) {
}

std::string Book::getTitle() const {
    return title;
}

std::string Book::getAuthor() const {
    return author;
}

std::string Book::getISBN() const {
    return ISBN;
}

bool Book::getAvailability() const {
    return isAvailable;
}

void Book::setAvailability(bool status) {
    isAvailable = status;
}

std::string Book::getDetails() const {
    return "Title: " + title +
           "\nAuthor: " + author +
           "\nISBN: " + ISBN +
           "\nAvailable: " + (isAvailable ? "Yes" : "No");
}
