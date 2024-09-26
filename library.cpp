#include <iostream>
#include <string>
#include <limits>
using namespace std;

class Books {
public:
    static int total_books;      // Total number of books
    static int total_quantity;   // Total quantity of all books

private:
    int code;                    // Book code (private)
    string name;                 // Book name (private)
    string author;               // Author name (private)
    int quantity;                // Quantity of the book (private)

public:
    // Constructor to increment the total number of books
    Books() {
        total_books++;
    }

    // Mutator method to set book data
    void setData(int code, const string& name, const string& author, int quantity) {
        this->code = code;          // Set book code
        this->name = name;          // Set book name
        this->author = author;      // Set author name
        this->quantity = quantity;  // Set quantity of the book
        total_quantity += quantity; // Increment total quantity of all books
    }

    // Accessor methods to get book data
    int getCode() const {
        return code;
    }

    string getName() const {
        return name;
    }

    string getAuthor() const {
        return author;
    }

    int getQuantity() const {
        return quantity;
    }

    // Method to display book details
    void display() const {
        cout << code << "\t\t" << name << "\t\t" << author << "\t\t" << quantity << endl;
    }

    // Static method to display total books and quantities
    static void displayTotals() { 
        cout << "\nTotal number of books: " << total_books << endl;
        cout << "Total quantity of all books: " << total_quantity << endl;
    }
};

// Initialize static variables
int Books::total_books = 0;
int Books::total_quantity = 0;

class Library {
private:
    Books* books;     // Dynamic array of books (private)
    int num_books;    // Number of books in the library (private)

public:
    // Constructor to initialize the Library
    Library() : books(nullptr), num_books(0) {}

    // Destructor to release memory
    ~Library() {
        delete[] books; 
    }

    // Method to input book data
    void getData() {
        cout << "Enter the number of books you need to store in Library: ";
        cin >> num_books;
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore newline

        // Allocate memory for books dynamically
        books = new Books[num_books];

        for (int i = 0; i < num_books; i++) {
            int code, quantity;
            string book_name, author;

            cout << "Enter Book code: ";
            cin >> code;
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore newline

            cout << "Enter Book Name: ";
            getline(cin, book_name); // Read book name

            cout << "Enter the Author Name: ";
            getline(cin, author); // Read author name

            cout << "Enter quantity: ";
            cin >> quantity;
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore newline

            // Set the book data using setData() method
            books[i].setData(code, book_name, author, quantity);
        }
    }

    // Method to display all books in the library
    void display() {
        cout << "Library Books\n";
        cout << "----------------------------------------------------------\n";
        cout << "Book Code \t Book Name\t\t Author \t Quantity\n";
        cout << "----------------------------------------------------------\n";
        for (int i = 0; i < num_books; i++) {
            books[i].display(); // Display each book
        }
        cout << "----------------------------------------------------------\n";

        Books::displayTotals(); // Display total books and quantities
    }

    // Method to fetch a specific book by various criteria
    void fetchBook() {
        string search_type;
        cout << "Search by (1) Book Code, (2) Book Name, (3) Author Name: ";
        getline(cin, search_type);

        if (search_type == "1") {
            int code;
            cout << "Enter Book Code: ";
            cin >> code;
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore newline

            for (int i = 0; i < num_books; i++) {
                if (books[i].getCode() == code) {
                    displayBook(books[i]);
                    return;
                }
            }
            cout << "Book not found" << endl;
        } else if (search_type == "2") {
            string book_name;
            cout << "Enter Book Name: ";
            getline(cin, book_name); // Read book name

            for (int i = 0; i < num_books; i++) {
                if (books[i].getName() == book_name) {
                    displayBook(books[i]);
                    return;
                }
            }
            cout << "Book not found" << endl;
        } else if (search_type == "3") {
            string author;
            cout << "Enter Author Name: ";
            getline(cin, author); // Read author name

            for (int i = 0; i < num_books; i++) {
                if (books[i].getAuthor() == author) {
                    displayBook(books[i]);
                    return;
                }
            }
            cout << "Book not found" << endl;
        }
    }

    // Method to display details of a specific book
    void displayBook(const Books& book) {
        cout << "Book Details\n";
        cout << "----------------------------------------------------------\n";
        cout << "Book Code \t Book Name \t\t Author \t Quantity\n";
        cout << "----------------------------------------------------------\n";
        book.display(); // Display the book
        cout << "----------------------------------------------------------\n";
    }
};

int main() {
    Library library; // Create a Library object
    library.getData(); // Get data for books
    library.display(); // Display all books
    library.fetchBook(); // Fetch a specific book by criteria
    return 0;
}
