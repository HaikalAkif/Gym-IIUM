#include <iostream>
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

const Service serv[6] = {{1,"Entry fee", 5.00},
                         {2,"Weight Loss Challenges", 5.00},
                         {3,"Lifestyles Seminars",6.00},
                         {4,"Personal Training",10.00},
                         {5,"Pool",5.00},
                         {6,"Sauna",4.00}};

string getTime();

void Services();
void Add();
double Calc(char,vector<Cart>&);
void checkOut(double, vector<Cart>&);
void OUTFile(double);
void OUTFile(vector<Cart>&);
void OUTFile(vector<Cart>&, double);
void Review();

void dailyCollection();
void totalCollection();

void checkFile();

int main()
{
    
    while(true){
        
        system("cls");

        cout << "IIUM Gym Management" << endl;
        cout << "1. Services" << endl;
        cout << "2. Daily collection " << endl;
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
    }
}

void totalCollection(){
    ifstream paymentFile;
    double type[6];

    paymentFile.open("Collection.txt");

    system("cls");

    if(paymentFile.is_open()){
        for(int i = 0; i < 6; i++){
            paymentFile >> type[i];
            if(i < 5)
                cout << serv[i + 1].name << "\t: " << type[i] << endl;
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

void dailyCollection(){
    ifstream daily;
    string temp[2];

    daily.open("dailyCollection.txt");
    system("cls");

    if(daily.is_open()){
        cout << "Date\t\tCollections" << endl;
        while(!daily.eof()){
            for(int i = 0; i < 2; i++){
                daily >> temp[i];
                cout << temp[i] << "\t\t";
            }
            cout << endl;
        }
    }
    else{
        cout << "ERROR! A file is currently missing!" << endl;
        cout << "Missing file: Collection.txt" << endl;
    }
    cout << "Press any key to continue: ";
    system("pause>nul");
}

void Services(){
    char op;

    do{

        system("cls");

        cout << "1. Add services" << endl;
        cout << "2. Review services" << endl;
        cout << "3. Back" << endl;
        cout << endl << "Enter menu: ";
        op = getch();

        switch(op){
            case '1': Add(); break;
            case '2': Review();
        }

    }while(op != '3');
}

void Review(){
    ifstream reviewFile;
    string input[4];

    reviewFile.open("Customers.txt");
    system("cls");


    if(reviewFile.is_open()){
        cout << "History of the customers' transactions" << endl;
        cout << "\nService type\tQuantity\tPayment\tNotes" << endl;
        while(!reviewFile.eof()){
            for(int i = 0; i < 4; i++){
                reviewFile >> input[i];
                cout << input[i] << "\t";
            }
            cout << endl;
        }
    } 
    else{
        cout << "ERROR! A file is currently missing!" << endl;
        cout << "Missing file: Customers.txt" << endl;
    }
    cout << "Press any key to continue: ";
    system("pause>nul");
}

void Add(){
    string name;
    int matNo;
    int phoneNo;
    int serviceType;
    char op, repeat;
    double totalCharge = 0;

    vector<Cart> cart;

    do{
        system("cls");
        cout << "Enter the following" << endl;
        cout << "Full Name: ";

        getline(cin,name);

        cout << "Matric Number: ";
        cin >> matNo;
        cout << "Phone Number: ";
        cin >> phoneNo;

        do{

            system("cls");
            cout << endl << "Service currently provided\tCart: " << cart.size() << endl;
            cout << "Type\tService\tPrice(RM)" << endl;
            for(int i = 1; i < 6; i++){
                cout << serv[i].type - 1 << "\t" << serv[i].name << "\t" << serv[i].price << endl;
            }
            cout << "6. Checkout" << endl;
            cout << "Choose type: ";
            op = getch();

            if(op == '1' || op == '2' || op == '3' || op == '4' || op == '5'){
                totalCharge += Calc(op,cart);
            }

        }while(op != '6');

        checkOut(totalCharge,cart);

        system("cls");
        cout << "Repeat the order? (Y/y) to repeat\nPress any key to continue: ";
        repeat = getch();

    }while(repeat == 'Y' || repeat == 'y');
}

void checkOut(double totalCharge,vector<Cart>& cart){
    system("cls");
    cout << "Services\t\tQty\tPrice (RM)" << endl;

    for(unsigned int i = 0; i < cart.size(); i++){

        for(int j = 2; j <= 6; j++){
            if(cart[i].type == j) cout << serv[j - 1].name;
        }
        cout << "\t\t" << cart[i].qty << "\t" << cart[i].payment << endl;
    }
    cout << endl << "Including entry fee: RM" << serv[0].price << endl;
    totalCharge += serv[0].price;
    cout << "Grand payment: RM" << totalCharge << endl;

    OUTFile(totalCharge);
    OUTFile(cart);
    OUTFile(cart,totalCharge);

    cout << endl << "Press any key to continue: ";
    system("pause>nul");

    cart.clear();
}

void OUTFile(vector<Cart>& cart,double totalCharge){

    fstream cFile;
    double type[6] = {0,0,0,0,0,0};
    string tempp;

    cFile.open("Collection.txt");

    if(cFile.is_open()){
        getline(cFile,tempp);
        if(tempp != ""){
            for(int i = 0; i < 6; i++){
                cFile >> type[i];
            }
            for(int i = 0 ; i < cart.size(); i++){
                switch(cart[i].type){
                    case 2: *(type + 0) += cart[i].payment; break;
                    case 3: *(type + 1) += cart[i].payment; break;
                    case 4: *(type + 2) += cart[i].payment; break;
                    case 5: *(type + 3) += cart[i].payment; break;
                    case 6: *(type + 4) += cart[i].payment; break;
                }
            }
            type[5] += totalCharge;

            for(int i = 0; i < 6; i++){
                cFile << type[i] << " ";
            }
            cFile.close();

        }
        else{
            ofstream newCollection;
            newCollection.open("Collection.txt");
            if(newCollection.is_open()){
                for(int i = 0 ; i < cart.size(); i++){
                    switch(cart[i].type){
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
}

void OUTFile(vector<Cart>&cart)
{

    ofstream cust;

    cust.open("Customers.txt",fstream::app);

    for(int i = 0; i < cart.size(); i++){
        cust << cart[i].qty << " " << cart[i].qty << " " << cart[i].payment << " " << cart[i].notes << endl;
    }
    cust.close();
}

void OUTFile(double totalCharge){

    fstream outputFile;

    vector<string> date;
    vector<double> value;
    string temp1;
    double temp2;
    string tempp;

    string str = getTime();

    outputFile.open("dailyCollection.txt",fstream::app);

    if(outputFile.is_open()){
        getline(outputFile,tempp);
        if(tempp != ""){
            while(!outputFile.eof()){
                outputFile >> temp1 >> temp2;
                date.push_back(temp1);
                value.push_back(temp2);
            }
            for(unsigned int i = 0; i < date.size(); i++){
                if(date[i] == str){
                    value[i] += totalCharge;
                    break;
                }
            }
            for(unsigned int i = 0; i < date.size(); i++){
                outputFile << date[i] << " " << value[i] << endl;
            }
            outputFile.close();
        }
        else {
            
            ofstream newDaily;
            newDaily.open("dailyCollection.txt");
            
            newDaily << str << " " << totalCharge << endl;
            newDaily.close();
        }    
    } 
}

string getTime(){
    time_t rawtime;
    struct tm * timeinfo;
    char buffer[80];

    time (&rawtime);
    timeinfo = localtime(&rawtime);

    strftime(buffer,sizeof(buffer),"%d-%m-%Y",timeinfo);
    string str(buffer);
    return str;
}

double Calc(char op, vector<Cart>& cart){
    int qty;
    int type;
    string notes;

    system("cls");

    cout << "Enter Quantity: ";
    cin >> qty;


    type = (int)op - 48 + 1;

    cout << "Enter notes: ";
    cin.ignore();
    getline(cin,notes);

    double servicePayment = qty * serv[type - 1].price;

    Cart currentCart = {type,qty,notes,servicePayment};

    cart.push_back(currentCart);
    
    return servicePayment;
}
