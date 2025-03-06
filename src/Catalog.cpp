#include "Catalog.h"
#include <algorithm>

void Catalog::addBook(std::shared_ptr<Book> book) {
    books.push_back(book);
}

void Catalog::removeBook(const std::string& ISBN) {
    books.erase(
            std::remove_if(books.begin(), books.end(),
                           [&ISBN](const std::shared_ptr<Book>& book) {
                               return book->getISBN() == ISBN;
                           }),
            books.end()
    );
}

std::vector<std::shared_ptr<Book>> Catalog::searchByTitle(const std::string& title) {
    std::vector<std::shared_ptr<Book>> results;
    std::copy_if(books.begin(), books.end(), std::back_inserter(results),
                 [&title](const std::shared_ptr<Book>& book) {
                     return book->getTitle().find(title) != std::string::npos;
                 });
    return results;
}

std::vector<std::shared_ptr<Book>> Catalog::searchByAuthor(const std::string& author) {
    std::vector<std::shared_ptr<Book>> results;
    std::copy_if(books.begin(), books.end(), std::back_inserter(results),
                 [&author](const std::shared_ptr<Book>& book) {
                     return book->getAuthor().find(author) != std::string::npos;
                 });
    return results;
}

std::vector<std::shared_ptr<Book>> Catalog::searchByISBN(const std::string& ISBN) {
    std::vector<std::shared_ptr<Book>> results;
    std::copy_if(books.begin(), books.end(), std::back_inserter(results),
                 [&ISBN](const std::shared_ptr<Book>& book) {
                     return book->getISBN() == ISBN;
                 });
    return results;
}

std::vector<std::shared_ptr<Book>> Catalog::getAllBooks() const {
    return books;
}
