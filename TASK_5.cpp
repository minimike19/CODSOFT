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

double Fine_calculations(time_t Book_checkoutDate, time_t Book_returnDate) {
    const double Rate = 3.0;
    double TimeDifference = difftime(Book_returnDate, Book_checkoutDate);
    int dueDays_Count = static_cast<int>(TimeDifference / (60 * 60 * 24)) - 14;
    if (dueDays_Count > 0) {
        return Rate * dueDays_Count;
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
    void Insert_book_fn(const string& Book_Title, const string& Book_Author, const string& Book_ISBN) {
        books.push_back({Book_Title, Book_Author, Book_ISBN});
    }

    void Book_Search_fn(const string& searchQuery) {
        bool Book_found = false;
        for (const auto& book : books) {
            if (book.Book_Title == searchQuery || book.Book_Author == searchQuery || book.Book_ISBN == searchQuery) {
                cout << "Book is found in the Library System:" <<endl;
                cout << "Title of the book: " << book.Book_Title << endl;
                cout <<"Author of the book: "<< book.Book_Author<< endl;
                cout << "ISBN : "<< book.Book_ISBN << endl;
                cout << "Availability: " << (book.Book_Availability ? "Available" : "Checked out") << endl;
                Book_found = true;
            }
        }
        if (!Book_found) {
            cout << "No book was found according to your request."<<endl;;
        }
    }

    void Book_Checkout_fn(const string& Borrower_ID, const string& Book_ISBN) {
        bool bookAvailable = false;
        for (auto& book : books) {
            if (book.Book_ISBN == Book_ISBN && book.Book_Availability) {
                book.Book_Availability = false;
                bookAvailable = true;
                Transaction newTransaction = {Borrower_ID, Book_ISBN, time(0), 0};
                transactions.push_back(newTransaction);
                cout << "Book was checked out successfully!"<< endl;
                return;
            }
        }
        if (!bookAvailable) {
            cout << "Book is not available for checkout." <<endl;;
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

                double fine = Fine_calculations(transaction.Book_checkoutDate, transaction.Book_returnDate);
                if (fine > 0) {
                    cout << "Book was returned. Fine amount due for the book: " << fine << endl;
                } else {
                    cout << "Book was returned. No fine due" <<endl;
                }
                return;
            }
        }
        cout << "No matching transaction was found in the system."<< endl;;
    }

    void Insert_borrower_fn(const string& Borrower_Name, const string& Borrower_ID) {
        borrowers.push_back({Borrower_Name, Borrower_ID});
    }

    void DisplayBooks_available() {
        cout << "Available books:\n";
        for (const auto& book : books) {
            if (book.Book_Availability) {
                cout << "Title of the book: " << book.Book_Title << endl;
				cout<< "Author of the book: " << book.Book_Author << endl;
				cout<< "ISBN: " << book.Book_ISBN << endl;
            }
        }
    }
};

int main() {
    LibrarySystem library;
    int choice;
    string Book_Title, Book_Author, Book_ISBN, Borrower_ID, Borrower_Name;

    library.Insert_book_fn("Gitanjali", "Rabindranath Tagore", "9780143065883");
    library.Insert_book_fn("Malgudi Days", "R.K. Narayan", "9788185986104");
    library.Insert_book_fn("Godan", "Munshi Premchand", "9780140449860");

    library.Insert_borrower_fn("Sarvesh Joshi", "BR001");
    library.Insert_borrower_fn("Aditya Kulkarni", "BR002");
    library.Insert_borrower_fn("Nitya Deshpande", "BR002");

    do {
        cout << "Library Management System" << endl;
        cout << "1. Add Book in the Library System" <<endl;
        cout << "2. Search Book in the Library System" << endl;
        cout << "3. Checkout Book from the system" << endl;
        cout << "4. Return Book from the system" << endl;
        cout << "5. Add Borrower in the Borrowers List" <<endl;
        cout << "6. Display Available Books in the Library System" <<endl;
        cout << "7. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter the title of the book: ";
                cin.ignore();
                getline(cin, Book_Title);
                cout << "Enter the name of the author: ";
                getline(cin, Book_Author);
                cout << "Enter ISBN of the book: ";
                getline(cin, Book_ISBN);
                library.Insert_book_fn(Book_Title, Book_Author, Book_ISBN);
                cout << "Book was added successfully" << endl;
                break;

            case 2:
                cout << "Enter the title of the book: ";
                cin.ignore();
                getline(cin, Book_Title);
                library.Book_Search_fn(Book_Title);
                break;

            case 3:
                cout << "Enter your ID: ";
                cin >> Borrower_ID;
                cout << "Enter ISBN of the book: ";
                cin >> Book_ISBN;
                library.Book_Checkout_fn(Borrower_ID, Book_ISBN);
                break;

            case 4:
                cout << "Enter your ID: ";
                cin >> Borrower_ID;
                cout << "Enter ISBN of the book ";
                cin >> Book_ISBN;
                library.returnBook(Borrower_ID, Book_ISBN);
                break;

            case 5:
                cout << "Enter your name: ";
                cin.ignore();
                getline(cin, Borrower_Name);
                cout << "Enter your ID: ";
                getline(cin, Borrower_ID);
                library.Insert_borrower_fn(Borrower_Name, Borrower_ID);
                cout << "Borrower was added successfully." <<endl;
                break;

            case 6:
                library.DisplayBooks_available();
                break;

            case 7:
                cout << "Exiting the system..."<< endl;
                break;

            default:
                cout << "Invalid choice. Please try again.\n";
                break;
        }
    } while (choice != 7);

    return 0;
}
