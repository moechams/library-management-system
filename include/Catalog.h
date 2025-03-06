#ifndef CATALOG_H
#define CATALOG_H

#include <vector>
#include <memory>
#include "Book.h"

class Catalog {
private:
    std::vector<std::shared_ptr<Book>> books;

public:
    // Book management
    void addBook(std::shared_ptr<Book> book);
    void removeBook(const std::string& ISBN);

    // Search methods
    std::vector<std::shared_ptr<Book>> searchByTitle(const std::string& title);
    std::vector<std::shared_ptr<Book>> searchByAuthor(const std::string& author);
    std::vector<std::shared_ptr<Book>> searchByISBN(const std::string& ISBN);

    // Utility methods
    std::vector<std::shared_ptr<Book>> getAllBooks() const;
};

#endif // CATALOG_H
