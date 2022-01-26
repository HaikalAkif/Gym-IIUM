#include <iostream>
#include <conio.h>
#include <iomanip>
#include <fstream>

using namespace std;

// void cust();           tidak diperlukan since int main kat bawah
// void cust(int);
// void admin();
// void showCustomers();
// void readRecords();
// void saveRecords();

struct newCust {
    string name, pass;
    int matNo, IC, phone;
    char gender;
};

struct customerData {
    string name, pass;
    int matNo;
};// Global Array

void cust() { //new customer
    system("cls");
    newCust customer;
    newCust* custPtr;
    string name, pass;
    int matNo, IC, phone;
    char gender;

    // ifstream inFile;
    fstream outFile;

    // inFile.open("cust.txt");
    outFile.open("customer.txt", fstream::app);

    if(!outFile.fail()){

        cout << "Enter your full name: "; //ligmaballs
        cin >> custPtr->name;
        cout << "Enter your matric number: ";
        cin >> customer.matNo;
        cout << "Create a password: ";
        cin >> customer.pass;
        cout << "Enter your phone number: ";
        cin >> customer.phone;
        cout << "1. Male\n2. Female\n";
        cout << "Choose your gender(M/F): ";
        cin >> customer.gender;
        cout << endl;

        outFile << customer.name << " " << customer.matNo << " " << customer.pass << " " << customer.phone << " " << customer.gender << endl;
        // outFile << "please write this";
        
        // system("pause");

    } else {
        cout << "Error opening the file!" << endl;
    }
    outFile.close();

}

void login(){
    system("cls");
    string name, pass;
    int matNo;

    cout << "Please Fill The Detail Below\n" << endl;
    cout << "Name: ";
    cin >> name;
    cout << "Matric Number: ";
    cin >> matNo;
    cout << "Password: ";
    cin >> pass;
    cout << "Thank you for your cooperation. Please tick your attendance later... \n" << endl;
    system("pause");

    // getch();
}

// void admin(){ //gymnasium staff
//     system("cls");

//     ifstream inFile;

//     inFile.open("staff.txt");
// }

void homepage(){ //homepage for customer
    system("cls");
    cout << "-------------------------------------------" << endl;
    cout << "-\t         WELCOME      \t-" << endl;
    cout << "-\t    To IIUM Gymnasium    \t-" << endl;
    cout << "-------------------------------------------" << endl;

    

    system("pause");


}

// void booking(){ // booking interface for customer
//     system("cls");
// }

// void saveRecords() {
// }

// void showCustomers() {
//     system("cls");
//     cout << setw(30) << left << "Name" << setw(10) << "Matric No" << endl;

//     for (int i = 0; i < 10; i++)
//     {
//         if (customerlist[i].matNo != 0) {
//             cout << setw(30) << left << customerlist[i].name 
//                 << setw(10) << left << customerlist[i].matNo << endl;
//         }
//     }
// }

int main() {
    system("title Gymnasium Management System");
    // system("color 70");
    int choice, ID, phone;
    string name;
    
    while(true){

        //readRecords();

        cout << "*************************************************************" << endl;
        cout << "\n\t\t IIUM Gymnasium Management System\n" << endl;
        cout << "\t1. New Customer Registration" << endl;
        cout << "\t2. Log in as Customer" << endl;
        cout << "\t3. Log in as Staff" << endl;
        cout << "\t4. Show Customers" << endl;
        cout << "\t5. Exit\n" << endl;
        cout << "*************************************************************\n" << endl;
        cout << "\t\tEnter your choice: ";
        cin >> choice;

        // if (choice == 1 || choice == 2 || choice == 3 || choice == 4){
        //     system("cls");
        //     // system("color 90");
        //     switch (choice)
        //     {
        //     case 1:
        //         cust();
        //         break;
        //     case 2:
        //         login();
        //         homepage();
        //         break;
        //     // case 3:
        //     //     admin();
        //     //     break;
        //     // case 4:
        //     //     showCustomers();
        //     //     break;
        //     }
        // }
        // // User choose to exit the program
        // if (choice == 5){
        //     exit(0);
        // }
        // // User entered an unexisted option
        // if (choice < 1 || choice > 5){
        //     cout << "Sorry! You Entered an invalid option." << endl;
        // }

        switch(choice){
            case 1: cust(); break;
            case 2: login(); homepage();break;
            // case 3: admin(); break;
            // case 4: showCustomer(); break;
            case 5: exit(0);
            default: cout << "Sorry! You Entered an invalid option." << endl;
        }

        // saveRecords();
    }
    getch();
}