#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;
struct Expense {
    string item;
    int price;
};

bool compareByPrice(Expense a,Expense b){
    return a.price > b.price;
}



int getValidInt(){
    int val;
    while(!(cin >> val)){
        cin.clear();
        cin.ignore(10000,'\n');
        cout<< "Invalid Input. Enter a number: ";
    }
    return val;
}





void listadder(Expense e){
    ofstream outFile("expense.txt", ios::app);
    if(outFile.is_open()){
        outFile << e.item << "|" << e.price << "\n";
        outFile.close();
    }
}

vector<Expense> listreader(){
    string line;
    Expense t;
    vector<Expense> list;
    ifstream inputFile("expense.txt");
    if(inputFile.is_open()){
        while(getline(inputFile, line)){
            
            int x = line.find('|');
            if (x != -1){
            
            t.item = line.substr(0,x);
            string price1 = line.substr(x+1);
            t.price = stoi(price1);
            list.push_back(t);
            
            }
        }
    }
    return list;
}

void deleteitem(){
    vector<Expense> expenses;
    expenses = listreader();
    if (expenses.empty()){
        cout << "Nothing to delete. \n";
        return;
    }
    for(int i = 0;i < expenses.size();i++){
        cout << i+1 << ". Item: " <<  expenses[i].item << " Price: " << expenses[i].price << "\n";
    }
    int poll;
    cout << "Which item to delete: \n";
    poll = getValidInt();
    if(poll < 1 || poll > expenses.size()){
        cout << "Invalid Choice. \n";
        return;
    }

    ofstream outFile("expense.txt");
     if(outFile.is_open()){
    for (int i = 0;i < expenses.size();i++){
        if(i == poll - 1){continue;}
    

            outFile <<  expenses[i].item  << "|" << expenses[i].price <<  "\n";
        

    }
}
    
}

int main(){
    cout << "Welcome to the expense calculator\n";
while(true){
    cout << "\n1. Add new expenses\n";
    cout << "2. See total damage\n";
    cout << "3. Clear all expense history\n";
    cout << "4. Delete an item\n";
    cout << "5. View High to Low Purchase history: \n";
    cout << "6. EXIT\n \n";
    

    
    int inp = 0;
    inp = getValidInt();
    if(inp == 1){
    Expense e;
    int i;
    cout << "How many items to want to add: \n";
    i = getValidInt();
    while (i>0){cout << "Type Item and price \n";
        cin.ignore();
        cout << "Item Name: \n";
        getline(cin,e.item);
        cout << "Enter Price: \n";
        e.price = getValidInt();
        while(e.price < 0){cout << "Error: Input , Integer values only! Enter again: ";
        e.price = getValidInt();}

        listadder(e);
        i = i - 1;}}
   
    else if(inp == 2){ int final = 0;
        vector<Expense> expenses = listreader();
        if(expenses.empty()){
            cout << "No expenses found \n";
            continue;
        }
        
        int highest = expenses[0].price;
        int it = 0;
        
        for (int i = 0; i < expenses.size(); i++){
            cout << i+1 <<". " << "Item: " << expenses[i].item << " | Price: " << expenses[i].price << "\n";
            final = final + expenses[i].price;
            if(highest < expenses[i].price){
                highest = expenses[i].price;
                it = i;
            }


        }

        cout << "The total damage is: " << final << "\n";
        cout << "Highest Cost of item: " << highest << " Item: " << expenses[it].item << "\n";

    
     }

    else if(inp == 3){
        ofstream outFile("expense.txt", ios::trunc);
     }

    else if(inp == 4){
        deleteitem();
    }
    else if(inp ==5){
        vector<Expense> expenses = listreader();
        if(expenses.empty()){
            cout << "No items to sort. \n";
            continue;
        }
        sort(expenses.begin(),expenses.end(),compareByPrice);
        for(int i =0; i <expenses.size();i++){
            cout << i+1 << ". Item: " << expenses[i].item << " | Price: " << expenses[i].price;
        }
    }
    else if(inp ==6){return 0;}

    }
}