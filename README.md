# Library Management System

A comprehensive C++ application designed to help small libraries transition from paper-based systems to digital management. This system provides complete functionality for tracking books, managing member accounts, processing transactions, and handling notifications.

## Overview

The Library Management System is built using Object-Oriented Design principles and implements several design patterns to ensure a maintainable, flexible, and scalable solution. The system was developed as part of the CS3307A Object-Oriented Analysis and Design course.

### Key Features

#### For Librarians:
- Add, update, and remove books in the library catalog
- Process check-outs and returns efficiently
- Register and manage library members
- Track overdue books automatically
- Generate notifications for important events
- Calculate and manage late fees

#### For Library Members:
- Search for books by title, author, or ISBN
- Check book availability status
- View account information and borrowed books
- Receive notifications about due dates, available books, and fines
- Track borrowing history

## Design Patterns

The system implements several design patterns to ensure flexibility, scalability, and maintainability:

### Singleton Pattern
The Library class uses the Singleton pattern to ensure there is only one central control point for the library system. This prevents conflicts and ensures consistent data management throughout the application.

```cpp
// Singleton implementation in Library class
class Library {
private:
    static Library* instance;
    Library() {} // Private constructor
    
public:
    static Library* getInstance() {
        if (instance == nullptr) {
            instance = new Library();
        }
        return instance;
    }
    // ...
};
```

### Observer Pattern
The notification system uses the Observer pattern to keep members informed about important events like due dates, available books, and fines. This creates a flexible notification system that can easily be extended.

```cpp
// Observer implementation
class Observer {
public:
    virtual void update(const std::string& message) = 0;
    virtual ~Observer() = default;
};

class Member : public Observer {
public:
    void update(const std::string& message) override {
        std::cout << "Notification for member " << name << ": " << message << std::endl;
    }
    // ...
};
```

## Class Structure

### Core Classes:
- **Library**: Central controller for the system (Singleton)
- **Book**: Contains information about each book (title, author, ISBN, availability)
- **Member**: Manages library user data and book checkouts (Observer)
- **Transaction**: Records book checkouts, returns, and due dates
- **Catalog**: Handles searching and browsing the book collection
- **Fine**: Calculates and manages late fees
- **Observer**: Interface for the Observer pattern
- **Subject**: Base class for subject in the Observer pattern

## Exception Handling

The system implements robust exception handling with custom exception classes:
- `LibraryException`: Base exception class for all library-related exceptions
- `BookNotFoundException`: Thrown when a book cannot be found
- `MemberNotFoundException`: Thrown when a member cannot be found
- `InvalidInputException`: Thrown when invalid input is provided

## Building and Running

### Prerequisites
- C++14 compatible compiler
- CMake (version 3.10 or higher)

### Build Instructions
1. Clone the repository
```bash
git clone https://github.com/yourusername/LibraryManagementSystem.git
cd LibraryManagementSystem
```

2. Create a build directory and navigate to it
```bash
mkdir build
cd build
```

3. Generate build files and compile
```bash
cmake ..
make
```

4. Run the application
```bash
./library_system
```

## Example Usage

```cpp
// Create and initialize the library
Library* library = Library::getInstance();

// Create books
auto book = std::make_shared<Book>("The Great Gatsby", "F. Scott Fitzgerald", "123456");
library->addBook(book);

// Register members
auto member = std::make_shared<Member>("John Doe", "M001");
library->registerMember(member);

// Check out a book
library->checkOutBook("123456", "M001");

// Return a book
library->returnBook("123456", "M001");
```

## Future Improvements

The system is designed to be extensible, with potential future enhancements including:
- Digital media catalog (e-books, audiobooks)
- Reservation system enhancements
- Additional notification methods
- User role management (librarians, administrators)
- Integration with external systems

## License

This project is licensed under the MIT License - see the LICENSE file for details.

## Acknowledgments

- Developed as part of CS3307A Object-Oriented Analysis and Design course
- Inspired by the needs of small community libraries
