#include "Library.h"
#include <algorithm>
#include <iostream>

// Initialize the static instance pointer
Library* Library::instance = nullptr;

Library* Library::getInstance() {
    if (instance == nullptr) {
        instance = new Library();
    }
    return instance;
}

void Library::addBook(std::shared_ptr<Book> book) {
    if (!book) {
        throw InvalidInputException("Cannot add null book");
    }

    if (book->getISBN().empty() || book->getTitle().empty()) {
        throw InvalidInputException("Book must have valid ISBN and title");
    }

    // Check for duplicate ISBN
    try {
        findBook(book->getISBN());
        throw InvalidInputException("Book with this ISBN already exists");
    } catch (const BookNotFoundException&) {
        books.push_back(book);
        notifyObservers("New book added: " + book->getTitle());
    }
}

void Library::removeBook(const std::string& ISBN) {
    if (ISBN.empty()) {
        throw InvalidInputException("ISBN cannot be empty");
    }

    auto it = std::find_if(books.begin(), books.end(),
                           [&ISBN](const std::shared_ptr<Book>& book) {
                               return book->getISBN() == ISBN;
                           });

    if (it != books.end()) {
        std::string title = (*it)->getTitle();
        books.erase(it);
        notifyObservers("Book removed: " + title);
    } else {
        throw BookNotFoundException(ISBN);
    }
}

std::shared_ptr<Book> Library::findBook(const std::string& ISBN) {
    if (ISBN.empty()) {
        throw InvalidInputException("ISBN cannot be empty");
    }

    auto it = std::find_if(books.begin(), books.end(),
                           [&ISBN](const std::shared_ptr<Book>& book) {
                               return book->getISBN() == ISBN;
                           });

    if (it == books.end()) {
        throw BookNotFoundException(ISBN);
    }
    return *it;
}

std::vector<std::shared_ptr<Book>> Library::getAllBooks() const {
    return books;
}

void Library::registerMember(std::shared_ptr<Member> member) {
    if (!member) {
        throw InvalidInputException("Cannot register null member");
    }

    if (member->getID().empty()) {
        throw InvalidInputException("Member must have valid ID");
    }

    // Check for existing member
    auto it = std::find_if(members.begin(), members.end(),
                           [&member](const std::shared_ptr<Member>& m) {
                               return m->getID() == member->getID();
                           });

    if (it != members.end()) {
        throw InvalidInputException("Member with this ID already exists");
    }

    members.push_back(member);
    addObserver(member);
    notifyObservers("New member registered: " + member->getName());
}

void Library::removeMember(const std::string& memberID) {
    if (memberID.empty()) {
        throw InvalidInputException("Member ID cannot be empty");
    }

    auto it = std::find_if(members.begin(), members.end(),
                           [&memberID](const std::shared_ptr<Member>& member) {
                               return member->getID() == memberID;
                           });

    if (it != members.end()) {
        removeObserver(*it);
        std::string name = (*it)->getName();
        members.erase(it);
        notifyObservers("Member removed: " + name);
    } else {
        throw MemberNotFoundException(memberID);
    }
}

std::shared_ptr<Member> Library::findMember(const std::string& memberID) {
    if (memberID.empty()) {
        throw InvalidInputException("Member ID cannot be empty");
    }

    auto it = std::find_if(members.begin(), members.end(),
                           [&memberID](const std::shared_ptr<Member>& member) {
                               return member->getID() == memberID;
                           });

    if (it == members.end()) {
        throw MemberNotFoundException(memberID);
    }
    return *it;
}

std::vector<std::shared_ptr<Member>> Library::getAllMembers() const {
    return members;
}

bool Library::checkOutBook(const std::string& ISBN, const std::string& memberID) {
    try {
        auto book = findBook(ISBN);
        auto member = findMember(memberID);

        if (!book->getAvailability()) {
            throw LibraryException("Book is not available for checkout");
        }

        book->setAvailability(false);
        auto transaction = std::make_shared<Transaction>(book, member);
        transactions.push_back(transaction);
        member->borrowBook(book);

        notifyObservers("Book '" + book->getTitle() + "' has been checked out by " +
                        member->getName());

        return true;
    } catch (const LibraryException& e) {
        std::cerr << "Checkout failed: " << e.what() << std::endl;
        return false;
    }
}

bool Library::returnBook(const std::string& ISBN, const std::string& memberID) {
    try {
        auto book = findBook(ISBN);
        auto member = findMember(memberID);

        if (book->getAvailability()) {
            throw LibraryException("Book is already returned");
        }

        // Find the transaction
        auto transIt = std::find_if(transactions.begin(), transactions.end(),
                                    [&](const std::shared_ptr<Transaction>& t) {
                                        return t->getBook()->getISBN() == ISBN &&
                                               t->getMember()->getID() == memberID;
                                    });

        if (transIt != transactions.end()) {
            int daysOverdue = (*transIt)->getDaysOverdue();
            if (daysOverdue > 0) {
                std::string fineMessage = "Fine incurred for overdue book: $" +
                                          std::to_string(daysOverdue * 0.50);
                notifyObservers(fineMessage);
            }
        }

        book->setAvailability(true);
        member->returnBook(book);

        notifyObservers("Book '" + book->getTitle() + "' has been returned by " +
                        member->getName());
        return true;
    } catch (const LibraryException& e) {
        std::cerr << "Return failed: " << e.what() << std::endl;
        return false;
    }
}

std::vector<std::shared_ptr<Transaction>> Library::getTransactions() const {
    return transactions;
}
