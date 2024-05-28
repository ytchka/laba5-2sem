#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <fstream>
#include <deque>
#include <sstream>
#include <set>
#include <unordered_set>

using namespace std;

class Book {
public:
    string author;
    string title;
    string publisher;
    int year;
    int pages;

    Book() : author(""), title(""), publisher(""), year(0), pages(0) {}
    Book(string author, string title, string publisher, int year, int pages)
        : author(author), title(title), publisher(publisher), year(year), pages(pages) {}

    friend ostream& operator<<(ostream& out, const Book& book) {
        out << "Author: " << book.author << ", Title: " << book.title << ", Publisher: " << book.publisher
            << ", Year: " << book.year << ", Pages: " << book.pages << endl;
        return out;
    }
};

struct BookCompare {
    bool operator()(const Book& b1, const Book& b2) const {
        return b1.title < b2.title;
    }
};

struct BookHash {
    size_t operator()(const Book& b) const {
        size_t h1 = hash<string>()(b.title);
        size_t h2 = hash<string>()(b.author);
        return h1 ^ (h2 << 1);
    }
};

struct BookEqual {
    bool operator()(const Book& b1, const Book& b2) const {
        return b1.title == b2.title && b1.author == b2.author;
    }
};

int main() {
    vector<Book> books;
    ifstream input("input.txt");
    string line;

    while (getline(input, line)) {
        stringstream ss(line);
        string author, title, publisher;
        int year, pages;
        getline(ss, author, ',');
        getline(ss, title, ',');
        getline(ss, publisher, ',');
        ss >> year >> pages;
        books.emplace_back(author, title, publisher, year, pages);
    }
    input.close();

    set<Book, BookCompare> bookSet;
    unordered_set<Book, BookHash, BookEqual> bookUnorderedSet;

    for (const auto& book : books) {
        bookSet.insert(book);
        bookUnorderedSet.insert(book);
    }

    ofstream output("output.txt");
    output << "Set container:" << endl;
    for (const auto& book : bookSet) {
        output << book;
    }

    output << "Unordered set container:" << endl;
    for (const auto& book : bookUnorderedSet) {
        output << book;
    }

    output.close();

    return 0;
}