#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

class Book
{
private:
    int bookID;
    char title[50];
    char author[50];
    bool issued;

public:
    void addBook();
    void displayBook() const;
    int getBookID() const;
    bool isIssued() const;
    void issueBook();
    void returnBook();
    bool searchTitle(const char[]) const;
    bool searchAuthor(const char[]) const;
};

void Book::addBook()
{
    cout << "\nEnter Book ID: ";
    cin >> bookID;

    cin.ignore();

    cout << "Enter Book Title: ";
    cin.getline(title, 50);

    cout << "Enter Author Name: ";
    cin.getline(author, 50);

    issued = false;

    cout << "\nBook Added Successfully!\n";
}

void Book::displayBook() const
{
    cout << "\nBook ID     : " << bookID;
    cout << "\nTitle       : " << title;
    cout << "\nAuthor      : " << author;
    cout << "\nStatus      : ";

    if (issued)
        cout << "Issued";
    else
        cout << "Available";

    cout << endl;
}

int Book::getBookID() const
{
    return bookID;
}

bool Book::isIssued() const
{
    return issued;
}

void Book::issueBook()
{
    if (!issued)
    {
        issued = true;
        cout << "\nBook Issued Successfully!\n";
    }
    else
    {
        cout << "\nBook Already Issued!\n";
    }
}

void Book::returnBook()
{
    if (issued)
    {
        issued = false;
        cout << "\nBook Returned Successfully!\n";
    }
    else
    {
        cout << "\nBook Was Not Issued!\n";
    }
}

bool Book::searchTitle(const char t[]) const
{
    return strcmp(title, t) == 0;
}

bool Book::searchAuthor(const char a[]) const
{
    return strcmp(author, a) == 0;
}

void writeBook()
{
    Book bk;

    ofstream outFile("library.dat", ios::binary | ios::app);

    bk.addBook();

    outFile.write(reinterpret_cast<char *>(&bk), sizeof(Book));

    outFile.close();
}

void displayAllBooks()
{
    Book bk;

    ifstream inFile("library.dat", ios::binary);

    while (inFile.read(reinterpret_cast<char *>(&bk), sizeof(Book)))
    {
        bk.displayBook();
    }

    inFile.close();
}

void searchByTitle()
{
    Book bk;
    char title[50];
    bool found = false;

    cin.ignore();

    cout << "\nEnter Title to Search: ";
    cin.getline(title, 50);

    ifstream inFile("library.dat", ios::binary);

    while (inFile.read(reinterpret_cast<char *>(&bk), sizeof(Book)))
    {
        if (bk.searchTitle(title))
        {
            bk.displayBook();
            found = true;
        }
    }

    inFile.close();

    if (!found)
        cout << "\nBook Not Found!\n";
}

void searchByAuthor()
{
    Book bk;
    char author[50];
    bool found = false;

    cin.ignore();

    cout << "\nEnter Author Name: ";
    cin.getline(author, 50);

    ifstream inFile("library.dat", ios::binary);

    while (inFile.read(reinterpret_cast<char *>(&bk), sizeof(Book)))
    {
        if (bk.searchAuthor(author))
        {
            bk.displayBook();
            found = true;
        }
    }

    inFile.close();

    if (!found)
        cout << "\nNo Books Found!\n";
}

void modifyBook(int id, int option)
{
    Book bk;

    fstream file("library.dat", ios::binary | ios::in | ios::out);

    bool found = false;

    while (!file.eof() && !found)
    {
        streampos pos = file.tellg();

        file.read(reinterpret_cast<char *>(&bk), sizeof(Book));

        if (bk.getBookID() == id)
        {
            if (option == 1)
                bk.issueBook();
            else
                bk.returnBook();

            file.seekp(pos);

            file.write(reinterpret_cast<char *>(&bk), sizeof(Book));

            found = true;
        }
    }

    file.close();

    if (!found)
        cout << "\nBook Not Found!\n";
}

int main()
{
    int choice, id;

    do
    {
        cout << "\n\n====== LIBRARY MANAGEMENT SYSTEM ======";
        cout << "\n1. Add Book";
        cout << "\n2. Display All Books";
        cout << "\n3. Search by Title";
        cout << "\n4. Search by Author";
        cout << "\n5. Issue Book";
        cout << "\n6. Return Book";
        cout << "\n7. Exit";

        cout << "\nEnter Your Choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            writeBook();
            break;

        case 2:
            displayAllBooks();
            break;

        case 3:
            searchByTitle();
            break;

        case 4:
            searchByAuthor();
            break;

        case 5:
            cout << "\nEnter Book ID to Issue: ";
            cin >> id;
            modifyBook(id, 1);
            break;

        case 6:
            cout << "\nEnter Book ID to Return: ";
            cin >> id;
            modifyBook(id, 2);
            break;

        case 7:
            cout << "\nThank You!\n";
            break;

        default:
            cout << "\nInvalid Choice!\n";
        }

    } while (choice != 7);

    return 0;
}
