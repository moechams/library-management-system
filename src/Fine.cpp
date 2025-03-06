#include "Fine.h"
#include <sstream>
#include <iomanip>

Fine::Fine(std::shared_ptr<Member> member)
        : member(member), amount(0.0) {
}

void Fine::calculateFine(int daysOverdue) {
    amount = daysOverdue * DAILY_RATE;
}

bool Fine::payFine(double payment) {
    if (payment >= amount) {
        amount = 0;
        return true;
    }
    amount -= payment;
    return false;
}

double Fine::getAmount() const {
    return amount;
}

std::shared_ptr<Member> Fine::getMember() const {
    return member;
}

std::string Fine::getDetails() const {
    std::stringstream ss;
    ss << "Fine Details:\n";
    ss << "Member: " << member->getName() << " (ID: " << member->getID() << ")\n";
    ss << "Amount Due: $" << std::fixed << std::setprecision(2) << amount << "\n";
    return ss.str();
}
