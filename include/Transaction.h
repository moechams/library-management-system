#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <memory>
#include <ctime>
#include "Book.h"
#include "Member.h"

class Transaction {
private:
    std::shared_ptr<Book> book;
    std::shared_ptr<Member> member;
    std::time_t checkOutDate;
    std::time_t dueDate;

public:
    Transaction(std::shared_ptr<Book> book, std::shared_ptr<Member> member);

    // Getters
    std::shared_ptr<Book> getBook() const;
    std::shared_ptr<Member> getMember() const;
    std::time_t getCheckOutDate() const;
    std::time_t getDueDate() const;

    // Utility methods
    int getDaysOverdue() const;
    std::string getDetails() const;
};

#endif // TRANSACTION_H
