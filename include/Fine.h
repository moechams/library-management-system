#ifndef FINE_H
#define FINE_H

#include <memory>
#include "Member.h"

class Fine {
private:
    std::shared_ptr<Member> member;
    double amount;
    const double DAILY_RATE = 0.50; // 50 cents per day

public:
    // Constructor
    explicit Fine(std::shared_ptr<Member> member);

    // Fine management
    void calculateFine(int daysOverdue);
    bool payFine(double payment);

    // Getters
    double getAmount() const;
    std::shared_ptr<Member> getMember() const;

    // Utility method
    std::string getDetails() const;
};

#endif // FINE_H
