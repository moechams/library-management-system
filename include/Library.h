#ifndef LIBRARY_H
#define LIBRARY_H

#include <vector>
#include <memory>
#include <stdexcept>
#include "Book.h"
#include "Member.h"
#include "Transaction.h"
#include "Subject.h"

// Custom exceptions
class LibraryException : public std::runtime_error {
public:
    explicit LibraryException(const std::string& message) : std::runtime_error(message) {}
};

class BookNotFoundException : public LibraryException {
public:
    explicit BookNotFoundException(const std::string& isbn)
            : LibraryException("Book with ISBN " + isbn + " not found") {}
};

class MemberNotFoundException : public LibraryException {
public:
    explicit MemberNotFoundException(const std::string& id)
            : LibraryException("Member with ID " + id + " not found") {}
};

class InvalidInputException : public LibraryException {
public:
    explicit InvalidInputException(const std::string& message)
            : LibraryException("Invalid input: " + message) {}
};

class Library : public Subject {
private:
    // Singleton instance
    static Library* instance;

    // Private constructor for Singleton
    Library() {}

    // Collection of books, members, and transactions
    std::vector<std::shared_ptr<Book>> books;
    std::vector<std::shared_ptr<Member>> members;
    std::vector<std::shared_ptr<Transaction>> transactions;

public:
    // Delete copy constructor and assignment operator
    Library(const Library&) = delete;
    Library& operator=(const Library&) = delete;

    // Singleton instance getter
    static Library* getInstance();

    // Book management
    void addBook(std::shared_ptr<Book> book);
    void removeBook(const std::string& ISBN);
    std::shared_ptr<Book> findBook(const std::string& ISBN);
    std::vector<std::shared_ptr<Book>> getAllBooks() const;

    // Member management
    void registerMember(std::shared_ptr<Member> member);
    void removeMember(const std::string& memberID);
    std::shared_ptr<Member> findMember(const std::string& memberID);
    std::vector<std::shared_ptr<Member>> getAllMembers() const;

    // Transaction management
    bool checkOutBook(const std::string& ISBN, const std::string& memberID);
    bool returnBook(const std::string& ISBN, const std::string& memberID);
    std::vector<std::shared_ptr<Transaction>> getTransactions() const;

    // Cleanup for singleton
    static void cleanup() {
        delete instance;
        instance = nullptr;
    }
};

#endif // LIBRARY_H
