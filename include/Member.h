#ifndef MEMBER_H
#define MEMBER_H

#include <string>
#include <vector>
#include <memory>
#include "Observer.h"
#include "Book.h"

class Member : public Observer {
private:
    std::string name;
    std::string ID;
    std::vector<std::shared_ptr<Book>> checkedOutBooks;

public:
    Member(std::string name, std::string ID);

    // Getters
    std::string getName() const;
    std::string getID() const;
    std::vector<std::shared_ptr<Book>> getCheckedOutBooks() const;

    // Book management
    void borrowBook(std::shared_ptr<Book> book);
    void returnBook(std::shared_ptr<Book> book);
    bool hasBook(const std::string& ISBN) const;

    // Observer interface implementation
    void update(const std::string& message) override;

    // Utility methods
    std::string getDetails() const;
};

#endif // MEMBER_H
