#include "Member.h"
#include <iostream>
#include <algorithm>

Member::Member(std::string name, std::string ID)
        : name(name), ID(ID) {
}

std::string Member::getName() const {
    return name;
}

std::string Member::getID() const {
    return ID;
}

std::vector<std::shared_ptr<Book>> Member::getCheckedOutBooks() const {
    return checkedOutBooks;
}

void Member::borrowBook(std::shared_ptr<Book> book) {
    if (book) {
        checkedOutBooks.push_back(book);
    }
}

void Member::returnBook(std::shared_ptr<Book> book) {
    if (book) {
        auto it = std::find(checkedOutBooks.begin(), checkedOutBooks.end(), book);
        if (it != checkedOutBooks.end()) {
            checkedOutBooks.erase(it);
        }
    }
}

bool Member::hasBook(const std::string& ISBN) const {
    return std::any_of(checkedOutBooks.begin(), checkedOutBooks.end(),
                       [&ISBN](const std::shared_ptr<Book>& book) {
                           return book->getISBN() == ISBN;
                       });
}

void Member::update(const std::string& message) {
    std::cout << "Notification for member " << name << ": " << message << std::endl;
}

std::string Member::getDetails() const {
    std::string details = "Member Details:\n";
    details += "Name: " + name + "\n";
    details += "ID: " + ID + "\n";
    details += "Books checked out: " + std::to_string(checkedOutBooks.size()) + "\n";

    if (!checkedOutBooks.empty()) {
        details += "Checked out books:\n";
        for (const auto& book : checkedOutBooks) {
            details += "- " + book->getTitle() + "\n";
        }
    }

    return details;
}
