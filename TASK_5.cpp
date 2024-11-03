//Task 5
//LIBRARY MANAGEMENT SYSTEM
//Develop a system to manage books, borrowers, and transactions in a library.


#include <iostream>
#include <string>
#include <vector>
#include <ctime>
using namespace std;

struct Book {
    string Book_Title;
    string Book_Author;
    string Book_ISBN;
    bool Book_Availability = true;
};

struct Borrower {
    string Borrower_Name;
    string Borrower_ID;
};

struct Transaction {
    string Borrower_ID;
    string Book_ISBN;
    time_t Book_checkoutDate;
    time_t Book_returnDate;
    bool ReturnStatus = false;
};

double calculateFine(time_t Book_checkoutDate, time_t Book_returnDate) {
    const double finePerDay = 1.0;
    double diffInSeconds = difftime(Book_returnDate, Book_checkoutDate);
    int daysOverdue = static_cast<int>(diffInSeconds / (60 * 60 * 24)) - 14;
    if (daysOverdue > 0) {
        return finePerDay * daysOverdue;
    } else {
        return 0.0;
    }
}

class LibrarySystem {
private:
    vector<Book> books;
    vector<Borrower> borrowers;
    vector<Transaction> transactions;

public:
    void addBook(const string& Book_Title, const string& Book_Author, const string& Book_ISBN) {
        books.push_back({Book_Title, Book_Author, Book_ISBN});
    }

    void searchBook(const string& searchQuery) {
        bool found = false;
        for (const auto& book : books) {
            if (book.Book_Title == searchQuery || book.Book_Author == searchQuery || book.Book_ISBN == searchQuery) {
                cout << "Book found: \n";
                cout << "Title: " << book.Book_Title << ", Author: " << book.Book_Author << ", ISBN: " << book.Book_ISBN 
                     << ", Availability: " << (book.Book_Availability ? "Available" : "Checked out") << endl;
                found = true;
            }
        }
        if (!found) {
            cout << "No book was found according to your reguest.\n";
        }
    }

    void checkoutBook(const string& Borrower_ID, const string& Book_ISBN) {
        bool bookAvailable = false;
        for (auto& book : books) {
            if (book.Book_ISBN == Book_ISBN && book.Book_Availability) {
                book.Book_Availability = false;
                bookAvailable = true;
                Transaction newTransaction = {Borrower_ID, Book_ISBN, time(0), 0};
                transactions.push_back(newTransaction);
                cout << "Book checked out successfully!\n";
                return;
            }
        }
        if (!bookAvailable) {
            cout << "Book is not available for checkout.\n";
        }
    }

    void returnBook(const string& Borrower_ID, const string& Book_ISBN) {
        for (auto& transaction : transactions) {
            if (transaction.Borrower_ID == Borrower_ID && transaction.Book_ISBN == Book_ISBN && !transaction.ReturnStatus) {
                transaction.Book_returnDate = time(0);
                transaction.ReturnStatus = true;

                for (auto& book : books) {
                    if (book.Book_ISBN == Book_ISBN) {
                        book.Book_Availability = true;
                    }
                }

                double fine = calculateFine(transaction.Book_checkoutDate, transaction.Book_returnDate);
                if (fine > 0) {
                    cout << "Book returned. Fine amount due for the book: " << fine << " units\n";
                } else {
                    cout << "Book returned. No fine due.\n";
                }
                return;
            }
        }
        cout << "No matching transaction found for return.\n";
    }

    void addBorrower(const string& Borrower_Name, const string& Borrower_ID) {
        borrowers.push_back({Borrower_Name, Borrower_ID});
    }

    void displayAvailableBooks() {
        cout << "Available books:\n";
        for (const auto& book : books) {
            if (book.Book_Availability) {
                cout << "Title: " << book.Book_Title << ", Author: " << book.Book_Author << ", ISBN: " << book.Book_ISBN << endl;
            }
        }
    }
};

int main() {
    LibrarySystem library;
    int choice;
    string Book_Title, Book_Author, Book_ISBN, Borrower_ID, Borrower_Name;

    library.addBook("The Great Gatsby", "F. Scott Fitzgerald", "9780743273565");
    library.addBook("1984", "George Orwell", "9780451524935");
    library.addBorrower("Alice", "BR001");
    library.addBorrower("Bob", "BR002");

    do {
        cout << "\nLibrary Management System\n";
        cout << "1. Add Book in the Library System\n";
        cout << "2. Search Book in the Library System\n";
        cout << "3. Checkout Book\n";
        cout << "4. Return Book\n";
        cout << "5. Add Borrower in the Borrowers List\n";
        cout << "6. Display Available Books in the Library System\n";
        cout << "7. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter book title: ";
                cin.ignore();
                getline(cin, Book_Title);
                cout << "Enter book author: ";
                getline(cin, Book_Author);
                cout << "Enter book ISBN: ";
                getline(cin, Book_ISBN);
                library.addBook(Book_Title, Book_Author, Book_ISBN);
                cout << "Book added successfully.\n";
                break;

            case 2:
                cout << "Enter Book title, author, or ISBN to search: ";
                cin.ignore();
                getline(cin, Book_Title);
                library.searchBook(Book_Title);
                break;

            case 3:
                cout << "Enter borrower ID: ";
                cin >> Borrower_ID;
                cout << "Enter book ISBN: ";
                cin >> Book_ISBN;
                library.checkoutBook(Borrower_ID, Book_ISBN);
                break;

            case 4:
                cout << "Enter borrower ID: ";
                cin >> Borrower_ID;
                cout << "Enter book ISBN: ";
                cin >> Book_ISBN;
                library.returnBook(Borrower_ID, Book_ISBN);
                break;

            case 5:
                cout << "Enter borrower name: ";
                cin.ignore();
                getline(cin, Borrower_Name);
                cout << "Enter borrower ID: ";
                getline(cin, Borrower_ID);
                library.addBorrower(Borrower_Name, Borrower_ID);
                cout << "Borrower added successfully.\n";
                break;

            case 6:
                library.displayAvailableBooks();
                break;

            case 7:
                cout << "Exiting the system...\n";
                break;

            default:
                cout << "Invalid choice. Please try again.\n";
                break;
        }
    } while (choice != 7);

    return 0;
}
