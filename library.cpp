#include <iostream>
#include <string>
#include <limits>
using namespace std;

const int Max_books=100;

class Books{
    public:
        int code;
        string name;
        string author;
        int quantity;

        void setdata(int code,string name,string author,int quantity){
            this->code=code;
            this->name=name;
            this->author=author;
            this->quantity=quantity;
        }

        void display(){
            cout<<code<<"\t\t"<<name<<"\t\t"<<author<<"\t\t"<<quantity<<endl;
        }
};
class Library{
    private:
        Books books[Max_books];
        int num_books;
    public:
        void getdata(){
            cout<<"Enter the number of books you need to store in Library: ";
            cin>>num_books;
            cin.ignore(numeric_limits<streamsize>::max(),'\n');

            if(num_books>Max_books){
                cout<<"The number of books exceede the limit\n";
                num_books=Max_books;
            }
            for(int i=0;i<num_books;i++){
                int code,quantity;
                string book_name,author;

                cout<<"Enter Book code: ";
                cin>>code;
                cin.ignore(numeric_limits<streamsize>::max(),'\n');

                cout<<"Enter Book Name: ";
                getline(cin,book_name);

                cout<<"Enter the Author Name: ";
                getline(cin,author);

                cout<<"Enter quantity: ";
                cin>>quantity;
                cin.ignore(numeric_limits<streamsize>::max(),'\n');

                books[i].setdata(code,book_name,author,quantity);
            }
        } 
        void display(){
            cout<<"Library Books\n";
            cout<<"----------------------------------------------------------\n";
            cout<<"Book Code \t Book Name\t\t Author \t Quantity\n";
            cout<<"----------------------------------------------------------\n";
            for(int i=0;i<num_books;i++){
                books[i].display();
            }
            cout<< "----------------------------------------------------------\n";
        }  

};

int main() {
    Library library;
    library.getdata();
    library.display();
    return 0;
}