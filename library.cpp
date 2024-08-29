#include <iostream>
#include <string>
#include <limits>
using namespace std;

class Books {
public:
    static int total_books;      
    static int total_quantity;   

    int code;
    string name;
    string author;
    int quantity;

    Books() {
        total_books++;
    }

    void setdata(int code, string name, string author, int quantity) {
        this->code = code;
        this->name = name;
        this->author = author;
        this->quantity = quantity;
        total_quantity += quantity;  
    }

    void display() {
        cout << code << "\t\t" << name << "\t\t" << author << "\t\t" << quantity << endl;
    }

    static void display_totals() { // I used the static method here to display total books and quantity
        cout << "\nTotal number of books: " << total_books << endl;
        cout << "Total quantity of all books: " << total_quantity << endl;
    }
};


int Books::total_books = 0;
int Books::total_quantity = 0;

class Library {
private:
    Books* books;
    int num_books;

public:
    Library() : books(nullptr), num_books(0) {}

    ~Library() {
        delete[] books; 
    }

    void getdata() {
        cout << "Enter the number of books you need to store in Library: ";
        cin >> num_books;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        books = new Books[num_books];

        for (int i = 0; i < num_books; i++) {
            int code, quantity;
            string book_name, author;

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

            books[i].setdata(code, book_name, author, quantity);
        }
    }

    void display() {
        cout << "Library Books\n";
        cout << "----------------------------------------------------------\n";
        cout << "Book Code \t Book Name\t\t Author \t Quantity\n";
        cout << "----------------------------------------------------------\n";
        for (int i = 0; i < num_books; i++) {
            books[i].display();
        }
        cout << "----------------------------------------------------------\n";

        Books::display_totals(); 
    }

    void fetch_book() {
        string search_type;
        cout << "Search by (1) Book Code, (2) Book Name, (3) Author Name: ";
        getline(cin, search_type);

        if (search_type == "1") {
            int code;
            cout << "Enter Book Code: ";
            cin >> code;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            for (int i = 0; i < num_books; i++) {
                if (books[i].code == code) {
                    display_book(books[i]);
                    return;
                };
            }
            cout << "Book not Found";
        } else if (search_type == "2") {
            string Book_name;
            cout << "Enter Book Name: ";
            getline(cin, Book_name);

            for (int i = 0; i < num_books; i++) {
                if (books[i].name == Book_name) {
                    display_book(books[i]);
                    return;
                }
            }
            cout << "Book not found";
        } else if (search_type == "3") {
            string author;
            cout << "Enter Author Name: ";
            getline(cin, author);

            for (int i = 0; i < num_books; i++) {
                if (author == books[i].author) {
                    display_book(books[i]);
                    return;
                }
            }
            cout << "Book not found";
        }
    }

    void display_book(Books& books) {
        cout << "Book Details\n";
        cout << "----------------------------------------------------------\n";
        cout << "Book Code \t Book Name \t\t Author \t Quantity\n";
        cout << "----------------------------------------------------------\n";
        books.display();
        cout << "----------------------------------------------------------\n";
    }
};

int main() {
    Library library;
    library.getdata();
    library.display();
    library.fetch_book();
    return 0;
}
