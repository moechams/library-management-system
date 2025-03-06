#ifndef SUBJECT_H
#define SUBJECT_H

#include <vector>
#include <memory>
#include "Observer.h"

class Subject {
protected:
    std::vector<std::shared_ptr<Observer>> observers;

public:
    virtual ~Subject() = default;

    virtual void addObserver(std::shared_ptr<Observer> observer) {
        observers.push_back(observer);
    }

    virtual void removeObserver(std::shared_ptr<Observer> observer) {
        observers.erase(
                std::remove(observers.begin(), observers.end(), observer),
                observers.end()
        );
    }

    virtual void notifyObservers(const std::string& message) {
        for (const auto& observer : observers) {
            observer->update(message);
        }
    }
};

#endif // SUBJECT_H
