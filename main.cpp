#include <iostream>
#include <iomanip>
#include <conio.h>
#include <vector>
#include <fstream>
#include <string>
#include <ctime>
#include "utils.h"

using namespace std;
using namespace utils;

struct Service {
    int type;
    string name;
    double price;
};

struct Cart {
    int type;
    int qty;
    string notes;
    double payment;
};

const Service serv[6] = {{1,"Entry fee", 5.00}, // We include an entry fee for every order
                         {2,"Weight Loss Challenges", 5.00},
                         {3,"Lifestyles Seminars",6.00},
                         {4,"Personal Training",10.00},
                         {5,"Pool\t\t",5.00},
                         {6,"Sauna\t\t",4.00}};

string getTime();
void Services();
void Add();
void Review();
double Calc(char,vector<Cart>&);
void checkOut(double, vector<Cart>&);
void OUTFile(double);
void OUTFile(vector<Cart>&);
void OUTFile(vector<Cart>&, double);
void dailyCollection();
void totalCollection();
void checkFile();

int main(){
    fontColor(13);
    setfont();
    while(true){
        system("cls");

        cout << "IIUM Gym Management" << endl;
        fontColor(10);
        cout << "1. Services Order" << endl;
        cout << "2. Our Daily collection " << endl;
        cout << "3. Display total collection by service type" << endl;
        cout << "4. Exit" << endl;
        
        cout << endl << "Enter menu: ";
        
        char op  = getch();

        switch(op){
            case '1': Services(); break;
            case '2': dailyCollection(); break;
            case '3': totalCollection(); break;
            case '4': system("cls"); exit(0);
        }
    }//using while loop to keep the program running until user choose to exit
}

void Services(){ 
    fontColor(11);
    setfont();
    char op;
    do{
        system("cls");

        cout << "1. Add services" << endl;
        cout << "2. Review services" << endl;
        cout << "3. Back to main menu" << endl;
        cout << endl << "Enter menu: ";
        op = getch(); 

        switch(op){
            case '1': Add(); break;
            case '2': Review();
        }
    }while(op != '3');
}

void Add(){
    fontColor(11);
    setfont();
    ShowConsoleCursor(false); // Hide cursor
    string name;
    int matNo;
    int phoneNo;
    int serviceType;
    char op, repeat;
    double totalCharge = 0;

    vector<Cart> cart; // vector to store the cart

    do{
        system("cls");
        cout << "Enter the following" << endl;
        cout << "Full Name: ";
        cin.ignore(); // ignore the newline character
        getline(cin,name); // getline to get the whole name
        cout << "Matric Number: ";
        cin >> matNo;
        cout << "Phone Number: ";
        cin >> phoneNo;

        do{
            system("cls");
            
            cout << endl << "Service currently provided\tCart: " << cart.size() << endl; // display the current cart size
            cout << "\nType\tService\t\t\tPrice(RM)" << endl; // display the service type and price
            for(int i = 1; i < 6; i++){
                cout << serv[i].type - 1 << "\t" << serv[i].name << "\t" << fixed << setprecision(2) << serv[i].price << endl;
            }
            cout << "6 \tCheckout" << endl; 
            cout << endl;
            cout << "Choose type: ";
            op = getch();
            fontColor(11);

            if(op == '1' || op == '2' || op == '3' || op == '4' || op == '5'){
                totalCharge += Calc(op,cart); // add the total charge
            }

        }while(op != '6');

        checkOut(totalCharge,cart);

        system("cls");
        fontColor(11);
        cout << "Press (Y/y) to repeat the order or any key to continue: "; // ask user to repeat the order
        repeat = getch();

    }while(repeat == 'Y' || repeat == 'y');
}

void Review(){
    fontColor(11);
    setfont();
    ifstream reviewFile;
    string input[4];

    vector<string> temp;
    vector<string> temp1;
    vector<string> temp2;
    vector<string> temp3;

    reviewFile.open("Customers.txt");
    system("cls");

    if(reviewFile.is_open()){
        cout << "History of the customers' transactions" << endl; 
        cout << "\nService type\tQuantity\tPayment\t\tNotes" << endl; 
        while(!reviewFile.eof()){
            reviewFile >> input[0] >> input[1] >> input[2] >> input[3];
            temp.push_back(input[0]);
            temp1.push_back(input[1]);
            temp2.push_back(input[2]);
            temp3.push_back(input[3]);
        }

        for(int i = 0; i < temp.size() - 1; i++){
            cout << temp[i] << "\t\t" << temp1[i] << "\t\t" << temp2[i] << "\t\t" << temp3[i] << endl;
        }
    } 
    else{
        cout << "ERROR! A file is currently missing!" << endl;
        cout << "Missing file: Customers.txt" << endl;
    }
    cout << "Press any key to continue: ";
    system("pause>nul");
}

void checkOut(double totalCharge,vector<Cart>& cart){
    system("cls");
    fontColor(11);
    setfont();
    cout << "Services\t\t\tQty\tPrice (RM)" << endl;

    for(unsigned int i = 0; i < cart.size(); i++){

        for(int j = 2; j <= 6; j++){
            if(cart[i].type == j) cout << serv[j - 1].name;
        }
        cout << "\t\t" << cart[i].qty << "\t" << cart[i].payment << endl; // display the cart
    }
    cout << endl << "Including entry fee: RM" << fixed << setprecision(2) << serv[0].price << endl;
    totalCharge += serv[0].price; // add the entry fee to the total charge
    cout << "Grand payment: RM" << fixed << setprecision(2) << totalCharge << endl; // display the grand total

    OUTFile(totalCharge);
    OUTFile(cart);
    OUTFile(cart,totalCharge);
	
	fontColor(11);
    cout << endl << "Press any key to continue: ";
    system("pause>nul"); // pause the program until user press any key

    cart.clear();
}

void OUTFile(vector<Cart>& cart,double totalCharge){ // total collection by services outfile
    fontColor(10);
    setfont();
    ifstream cFile; // check
    string tempp;
    double tempD;

    cFile.open("Collection.txt");

    if(cFile.is_open()){

        int type[6];

        for(int i = 0 ; i < cart.size(); i++){
            switch(cart[i].type){ // check the type of the service
                case 2: *(type + 0) += cart[i].payment; break;
                case 3: *(type + 1) += cart[i].payment; break;
                case 4: *(type + 2) += cart[i].payment; break;
                case 5: *(type + 3) += cart[i].payment; break;
                case 6: *(type + 4) += cart[i].payment; break;
            }
        }
        type[5] += totalCharge; // add the total charge to the last element of the array

        ofstream outFile; 
        outFile.open("Collection.txt");

        for(int i = 0; i < 6; i++){
            outFile << type[i] << " ";
        }
        cFile.close();
        outFile.close();

    } else {

        ofstream newCollection;
        double type[6] = {0,0,0,0,0,0}; // initialize the array
        newCollection.open("Collection.txt");
        if(newCollection.is_open()){
            for(int i = 0 ; i < cart.size(); i++){
                switch(cart[i].type){ // check the type of the service
                    case 2: *(type + 0) += cart[i].payment; break;
                    case 3: *(type + 1) += cart[i].payment; break;
                    case 4: *(type + 2) += cart[i].payment; break;
                    case 5: *(type + 3) += cart[i].payment; break;
                    case 6: *(type + 4) += cart[i].payment; break;
                }
            }
            type[5] += totalCharge;

            for(int i = 0; i < 6; i++){
                newCollection << type[i] << " ";
            }
            newCollection.close();
        }
    }
    
}

void OUTFile(vector<Cart>&cart){ // customers outfile
    fontColor(11);
    setfont();
    ofstream cust;

    cust.open("Customers.txt",fstream::app); 

    for(int i = 0; i < cart.size(); i++){
        cust << cart[i].type << " " << cart[i].qty << " " << cart[i].payment << " " << cart[i].notes << endl; // write the data to the file
    }
    cust.close();
}

void OUTFile(double totalCharge){ // daily collection outfile
    fontColor(11);
    setfont();
    ifstream cFile;

    vector<string> date;
    vector<double> value;
    string temp1;
    double temp2;
    string tempp;

    string str = getTime();

    cFile.open("dailyCollection.txt"); // check

    if(cFile.is_open()){ // if the file is already exist
        
        while(!cFile.eof()){
            cFile >> temp1 >> temp2;
            date.push_back(temp1);
            value.push_back(temp2);
        }

        for(int i = 0; i < date.size() - 1; i++){
            if(date[i] == str)
                value[i] += totalCharge;
        }

        fstream outFile1;
        ofstream outFile;

        outFile.open("dailyCollection.txt"); // overwrite the file
        outFile1.open("dailyCollection.txt",fstream::app); // append the new data to the file

        for(int i = 0; i < date.size() - 1; i++){
            if(date[i] == str)
                outFile << date[i] << " " << value[i] << endl;
            else if(date[i] != str)
                outFile1 << date[i] << " " << value[i] << endl;
        }
        cFile.close();
        outFile1.close();
        outFile.close();
    } else {

        ofstream newDaily;
        newDaily.open("dailyCollection.txt");
        
        newDaily << str << " " << totalCharge << endl; // write the date and the total charge to the file
        newDaily.close();
    }
}

string getTime(){ // get the current time
    fontColor(11);
    setfont();
    time_t rawtime;
    struct tm * timeinfo; // struct to store the time
    char buffer[80];

    time (&rawtime);
    timeinfo = localtime(&rawtime);

    strftime(buffer,sizeof(buffer),"%d-%m-%Y",timeinfo);
    string str(buffer); // convert the time to string
    return str;
}

double Calc(char op, vector<Cart>& cart){
    fontColor(11);
    setfont();
    int qty;
    int type;
    string notes;

    system("cls");

    cout << "Enter Quantity: ";
    cin >> qty;

    type = (int)op - 48 + 1;

    cout << "Enter notes: "; // get the notes from the user
    cin.ignore();
    getline(cin,notes); //get the full sentece means include the space button

    double servicePayment = qty * serv[type - 1].price;

    Cart currentCart = {type,qty,notes,servicePayment};

    cart.push_back(currentCart);
    
    return servicePayment;
}

void dailyCollection(){ //read daily collection
    fontColor(11);
    setfont();
    ifstream daily;
    string temp[2] = {"",""};
    vector<string> temp1;
    vector<double> temp2;
    string temporary;
    double collectionTemp;
    int i = 0;

    daily.open("dailyCollection.txt");
    system("cls");

    if(daily.is_open()){
        cout << "Date\t\t   Collections" << endl;

        while(!daily.eof()){
            daily >> temporary >> collectionTemp;
            temp1.push_back(temporary);
            temp2.push_back(collectionTemp);
        }
        for(int i = 0; i < temp1.size() - 1; i++){
            cout << fixed << setprecision(2) << temp1[i] << "\t\t" << temp2[i] << endl;
        }

    }
    else{
        cout << "ERROR! A file is currently missing!" << endl;
        cout << "Missing file: dailyCollection.txt" << endl;
    }
    cout << "Press any key to continue: ";
    system("pause>nul");
}

void totalCollection(){ // read total collection
    fontColor(11);
    setfont();
    ifstream paymentFile;
    double type[6];

    paymentFile.open("Collection.txt");

    system("cls");

    if(paymentFile.is_open()){
        for(int i = 0; i < 6; i++){
            paymentFile >> type[i];
            if(i < 5)
                cout << fixed << setprecision(2) << serv[i + 1].name << "\t: " << type[i] << endl;
        }
        cout << "Total collections: " << type[5] << endl;    
    } 
    else {
        cout << "ERROR! A file is currently missing!" << endl;
        cout << "Missing file: Collection.txt" << endl;
    }
    cout << "Press any key to continue: ";
    system("pause>nul");
}