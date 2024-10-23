#include <iostream>
#include <string>
#include <limits>
using namespace std;

class Genre {
protected:
    string genre_name;

public:
    Genre(const string& genre_name) : genre_name(genre_name) {}

    void displayGenre() const {
        cout << "Genre: " << genre_name << endl;
    }

    virtual void describe() const {
        cout << "This is a general genre." << endl;
    }
};

class Fiction : public Genre {
public:
    Fiction() : Genre("Fiction") {}

    void describe() const {
        cout << "This is a fiction genre, typically imaginative or invented." << endl;
    }
};

class NonFiction : public Genre {
public:
    NonFiction() : Genre("Non-Fiction") {}

    void describe() const {
        cout << "This is a non-fiction genre, based on factual information." << endl;
    }
};

class Books {
public:
    static int total_books;
    static int total_quantity;

private:
    int code;
    string name;
    string author;
    int quantity;

public:
    Books() {
        total_books++;
        code = 0;
        name = "Unknown";
        author = "Unknown";
        quantity = 0;
    }

    Books(int code, const string& name, const string& author, int quantity) {
        this->code = code;
        this->name = name;
        this->author = author;
        this->quantity = quantity;
        total_quantity += quantity;
        total_books++;
    }

    ~Books() {
        cout << "Destructor called for book: " << name << endl;
    }

    void setData(int code, const string& name, const string& author, int quantity) {
        this->code = code;
        this->name = name;
        this->author = author;
        this->quantity = quantity;
        total_quantity += quantity;
    }

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

    void display() const {
        cout << code << "\t\t" << name << "\t\t" << author << "\t\t" << quantity << endl;
    }

    static void displayTotals() {
        cout << "\nTotal number of books: " << total_books << endl;
        cout << "Total quantity of all books: " << total_quantity << endl;
    }
};

int Books::total_books = 0;
int Books::total_quantity = 0;

class Library {
private:
    Books* books;
    Genre** genres;
    int num_books;

public:
    Library() : books(nullptr), genres(nullptr), num_books(0) {}

    ~Library() {
        delete[] books;
        for (int i = 0; i < num_books; ++i) {
            delete genres[i];
        }
        delete[] genres;
        cout << "Library destructor called, memory released." << endl;
    }

    void getData() {
        cout << "Enter the number of books you need to store in Library: ";
        cin >> num_books;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        books = new Books[num_books];
        genres = new Genre*[num_books];

        for (int i = 0; i < num_books; i++) {
            int code, quantity, genre_choice;
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

            books[i].setData(code, book_name, author, quantity);

            cout << "Select genre (1) Fiction (2) Non-Fiction: ";
            cin >> genre_choice;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            if (genre_choice == 1) {
                genres[i] = new Fiction();
            } else {
                genres[i] = new NonFiction();
            }
        }
    }

    void display() {
        cout << "Library Books\n";
        cout << "----------------------------------------------------------\n";
        cout << "Book Code \t Book Name\t\t Author \t Quantity\t Genre\n";
        cout << "----------------------------------------------------------\n";
        for (int i = 0; i < num_books; i++) {
            books[i].display();
            genres[i]->displayGenre();
        }
        cout << "----------------------------------------------------------\n";

        Books::displayTotals();
    }
};

int main() {
    Library library;

    library.getData();
    library.display();

    return 0;
}
