#include <iostream> 
#include <vector>
#include <string>

using namespace std; 

class Book {
public: 
    string title; 
    string auth; 
    int pg; 
    bool stat; 

    // Constructor
    Book(string t = "None", string a = "None", int p = 0, bool s = false){
        title = t; 
        auth = a; 
        pg = p; 
        stat = s; 
    }
};

// Print book
void pBook(Book b){
    cout << "Title:  " << b.title << endl; 
    cout << "Author:  " << b.auth << endl; 
    cout << "Page count:  " << b.pg << endl; 
    cout << "Read status:  "; 

    if(b.stat == true){
        cout << "Read" << endl;
    }
    else{
        cout << "Not read" << endl; 
    }
}

class Lib {
public: 
    vector<Book> books; 

    // Constructor - empty library
    Lib(){}

    // Method - add book 
    void add(const Book & b){
        books.push_back(b);
    }

    // Method - delete book (by title)
    void del() {
        bool found = false;
        string s;

        while (found == false) {
            cout << "Enter title to delete: ";
            getline(cin, s);

            for (int i = 0; i < books.size(); ++i) {
                if (books[i].title == s) {
                    books.erase(books.begin() + i);
                    cout << "Book deleted." << endl;
                    found = true;
                    break;
                }
            }

            if (found == false) {
                cout << "No book found with that title. Try again." << endl;
            }
        }
    }

    // Method - edit book (by number)
    void edit(int n){
        int res; 
        bool val = false; 

        cout << "-- What would you like to edit? --" << endl; 
        cout << "1. Title" << endl; 
        cout << "2. Author" << endl; 
        cout << "3. Page count" << endl;
        cout << "4. Read status (y/n)" << endl; 
        cin>>res; 

        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        while(val == false){
            if(res == 1){
                string t; 

                cout << "New title:  "; 
                getline(cin, t);

                books[n-1].title = t; 

                val = true;
            }
            else if(res == 2){
                string a; 

                cout << "New author:  ";
                getline(cin, a);

                books[n-1].auth = a; 

                val = true; 
            }
            else if(res == 3){
                string temp; 
                int p;
                bool valres = false; 

                while(valres == false) { 
                    cout << "New page count:  "; 
                    getline(cin, temp);

                    try{
                        p = stoi(temp);
                        valres = true; 
                    }
                    catch(const invalid_argument& e){
                        cout << "Invalid entry. Must be a positive integer. " << endl; 
                    }
                }

                books[n-1].pg = p; 
                val = true; 
            }
            else if(res == 4){
                string b; 
                bool valres2 = false; 

                while(valres2 == false) { 
                    cout << "New status:  "; 
                    getline(cin, b);

                    if(b == "y"){
                        books[n-1].stat = true; 
                        valres2 = true; 
                    }
                    else if(b == "n"){
                        books[n-1].stat = false; 
                        valres2 = true; 
                    }
                    else{
                        cout << "Invalid entry. Must be 'y' or 'n'. " << endl; 
                    }
                }

                val = true; 
            }
            else{
                cout << "Invalid entry. Must be a number from 1 to 4. " << endl; 
            }
        }
    }

    // Method - visualize library 

    void vis(){
        cout << " ---- YOUR LIBRARY ---- " << endl; 
        cout << endl; 
        
        if(books.size() == 0){
            cout << "Empty library :( ...  Add some books! " << endl; 
            cout << endl; 
        }
        for(int i = 0; i < books.size(); i++){
            cout << " -- " << i+1 << " -- " << endl; 
            pBook(books[i]); 
            cout << endl; 
        }
    }
};

// Book creator (user input)
Book dynamBook(){
    string t; 
    string a; 
    string count; 
    int p; 
    string stat; 
    bool s; 
    bool val1 = false; 
    bool val2 = false; 

    cout << "Insert title of book:  "; 
    getline(cin, t); 
    
    cout << "Insert author of book:  "; 
    getline(cin, a);

    while(val1 == false){
        cout << "Have you read this book before?  "; 
        getline(cin, stat);

        if(stat == "Y" || stat == "y"){
            s = true; 
            val1 = true;  
        }
        else if(stat == "N" || stat == "n"){
            s = false; 
            val1 = true; 
        }
        else{
            cout << "Invalid entry, please try again. " << endl; 
        }
    }

    while(val2 == false){
        cout << "Insert page count:  ";
        getline(cin, count); 

        try{
            p = stoi(count);
            if(p > 0){
                val2 = true; 
            }
            else{
                cout << "Page number must be a positive integer. " << endl; 
            }
        }
        catch(const invalid_argument& e){
            cout << "Invalid entry. Must be a positive integer. " << endl; 
        }
    }

    Book b(t, a, p, s); 
    return b; 
}

int main(){
    cout << " ---- Welcome to your virtual library manager! ---- " << endl; 

    Lib userLib;
    bool val = false; 

    while(val == false){
        string res; 

        cout << "What would you like to do?" << endl; 
        cout << "1. Visualize library" << endl; 
        cout << "2. Add book" << endl; 
        cout << "3. Edit book" << endl; 
        cout << "4. Delete book" << endl; 
        cout << "5. Exit" << endl; 
        getline(cin, res);
        
        if(res == "1"){
            userLib.vis(); 
        }
        else if(res == "2"){
            userLib.books.push_back(dynamBook()); 
        }
        else if(res == "3"){
            int n;
            bool val = false; 

            userLib.vis(); 
            cout << endl;

            while(val == false){
                cout << "Insert book number to edit:  "; 
                cin >> n; 

                if(n > userLib.books.size()){
                    cout << "Invalid entry. " << endl; 
                }
                else{
                    userLib.edit(n); 
                    val = true; 
                }
            }
        }
        else if(res == "4"){
            userLib.del(); 
        }
        else if(res == "5"){
            cout << "Goodbye! " << endl; 
            return 0; 
        }
    }
}