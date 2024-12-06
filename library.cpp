#include <iostream>
#include <string>
#include <limits>
using namespace std;

// Base class for Genre demonstrating OCP
class Genre {
protected:
    string genre_name; // Name of the genre

public:
    // Constructor for Genre class
    Genre(const string& genre_name) : genre_name(genre_name) {}

    // Pure virtual function to demonstrate runtime polymorphism (Open for Extension)
    virtual void describe() const = 0;

    // Function to display the genre name
    void displayGenre() const {
        cout << "Genre: " << genre_name << endl;
    }
};

// Subclass for Fiction extending Genre (Example of extending functionality)
class Fiction : public Genre {
public:
    // Calling base class constructor with Fiction genre
    Fiction() : Genre("Fiction") {}

    // Overriding the describe function (Runtime Polymorphism)
    void describe() const override {
        cout << "This is a fiction genre, typically imaginative or invented." << endl;
    }
};

// Subclass for NonFiction extending Genre (Another example of extending functionality)
class NonFiction : public Genre {
public:
    // Calling base class constructor with Non-Fiction genre
    NonFiction() : Genre("Non-Fiction") {}

    // Overriding the describe function (Runtime Polymorphism)
    void describe() const override {
        cout << "This is a non-fiction genre, based on factual information." << endl;
    }
};

// Books class tracks book details and overall quantities
class Books {
public:
    // Static members to track total books and quantities
    static int total_books;
    static int total_quantity;

private:
    int code;         // Unique code for the book
    string name;      // Name of the book
    string author;    // Author of the book
    int quantity;     // Number of copies available

public:
    // Default constructor
    Books() {
        total_books++; // Increment total books on object creation
        code = 0;
        name = "Unknown";
        author = "Unknown";
        quantity = 0;
    }

    // Parameterized constructor
    Books(int code, const string& name, const string& author, int quantity) {
        this->code = code;
        this->name = name;
        this->author = author;
        this->quantity = quantity;
        total_quantity += quantity; // Add to total quantity
        total_books++;              // Increment total books
    }

    // Destructor
    ~Books() {
        cout << "Destructor called for book: " << name << endl;
    }

    // Setter for book details
    void setData(int code, const string& name, const string& author, int quantity) {
        this->code = code;
        this->name = name;
        this->author = author;
        this->quantity = quantity;
        total_quantity += quantity; // Add to total quantity
    }

    // Display function for book information
    void display() const {
        cout << code << "\t\t" << name << "\t\t" << author << "\t\t" << quantity << endl;
    }

    // Static function to display total books and quantities
    static void displayTotals() {
        cout << "\nTotal number of books: " << total_books << endl;
        cout << "Total quantity of all books: " << total_quantity << endl;
    }
};

// Initializing static members
int Books::total_books = 0;
int Books::total_quantity = 0;

// Library class using polymorphism for OCP
class Library {
private:
    Books* books;       // Dynamic array of books
    Genre** genres;     // Array of base class pointers for runtime polymorphism
    int num_books;      // Total number of books in the library

public:
    // Constructor for Library
    Library() : books(nullptr), genres(nullptr), num_books(0) {}

    // Destructor to clean up dynamic memory
    ~Library() {
        delete[] books; // Deleting dynamic books array
        for (int i = 0; i < num_books; ++i) {
            delete genres[i]; // Deleting derived genre objects
        }
        delete[] genres; // Deleting dynamic genres array
        cout << "Library destructor called, memory released." << endl;
    }

    // Function to gather data about books and genres
    void getData() {
        cout << "Enter the number of books you need to store in Library: ";
        cin >> num_books;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        books = new Books[num_books];    // Allocate dynamic array for books
        genres = new Genre*[num_books]; // Allocate dynamic array for genres

        for (int i = 0; i < num_books; i++) {
            int code, quantity, genre_choice;
            string book_name, author;

            // Input book details
            cout << "Enter Book code: ";
            cin >> code;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            cout << "Enter Book Name: ";
            getline(cin, book_name);

            cout << "Enter the Author Name: ";
            getline(cin, author);

            cout << "Enter quantity: ";
            cin >> quantity;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            books[i].setData(code, book_name, author, quantity);

            // Input and dynamically assign genre
            cout << "Select genre (1) Fiction (2) Non-Fiction: ";
            cin >> genre_choice;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            // Demonstrating OCP:
            // Library class remains unchanged when new genres are added.
            if (genre_choice == 1) {
                genres[i] = new Fiction(); // Dynamic polymorphism
            } else {
                genres[i] = new NonFiction(); // Dynamic polymorphism
            }
        }
    }

    // Function to display all books and their genres
    void display() {
        cout << "Library Books\n";
        cout << "----------------------------------------------------------\n";
        cout << "Book Code \t Book Name\t\t Author \t Quantity\t Genre\n";
        cout << "----------------------------------------------------------\n";
        for (int i = 0; i < num_books; i++) {
            books[i].display();          // Display book information
            genres[i]->displayGenre();   // Display genre name
            genres[i]->describe();       // Dynamic binding with virtual function
        }
        cout << "----------------------------------------------------------\n";

        Books::displayTotals(); // Display totals using static members
    }
};

int main() {
    Library library;

    // Getting library data and displaying the results
    library.getData();
    library.display();

    return 0;
}
