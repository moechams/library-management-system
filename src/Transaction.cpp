#include "Transaction.h"
#include <sstream>
#include <iomanip>

Transaction::Transaction(std::shared_ptr<Book> book, std::shared_ptr<Member> member)
        : book(book), member(member) {
    checkOutDate = std::time(nullptr);
    // Set due date to 14 days from checkout
    dueDate = checkOutDate + (14 * 24 * 60 * 60);
}

std::shared_ptr<Book> Transaction::getBook() const {
    return book;
}

std::shared_ptr<Member> Transaction::getMember() const {
    return member;
}

std::time_t Transaction::getCheckOutDate() const {
    return checkOutDate;
}

std::time_t Transaction::getDueDate() const {
    return dueDate;
}

int Transaction::getDaysOverdue() const {
    std::time_t now = std::time(nullptr);
    if (now > dueDate) {
        return (now - dueDate) / (24 * 60 * 60);
    }
    return 0;
}

std::string Transaction::getDetails() const {
    std::stringstream ss;
    ss << "Transaction Details:\n";
    ss << "Book: " << book->getTitle() << "\n";
    ss << "Member: " << member->getName() << " (ID: " << member->getID() << ")\n";

    auto formatTime = [](std::time_t time) {
        char buffer[26];
        ctime_r(&time, buffer);
        std::string str(buffer);
        return str.substr(0, str.length() - 1);
    };

    ss << "Check-out Date: " << formatTime(checkOutDate) << "\n";
    ss << "Due Date: " << formatTime(dueDate) << "\n";

    int daysOverdue = getDaysOverdue();
    if (daysOverdue > 0) {
        ss << "Days Overdue: " << daysOverdue << "\n";
    }

    return ss.str();
}
