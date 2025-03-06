#ifndef BOOK_H
#define BOOK_H

#include <string>

class Book {
private:
    std::string title;
    std::string author;
    std::string ISBN;
    bool isAvailable;

public:
    Book(std::string title, std::string author, std::string ISBN);

    // Getters
    std::string getTitle() const;
    std::string getAuthor() const;
    std::string getISBN() const;
    bool getAvailability() const;

    // Setters
    void setAvailability(bool status);

    // Utility methods
    std::string getDetails() const;
};

#endif // BOOK_H
