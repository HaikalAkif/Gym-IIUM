#include <iostream>
#include <conio.h>
#include <vector>
#include <fstream>
#include <string>
#include <ctime>

using namespace std;

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
                         {2,"Weigh Loss Challenges", 5.00},
                         {3,"Lifestyles Seminars",6.00},
                         {4,"Personal Training",10.00},
                         {5,"Pool",5.00},
                         {6,"Sauna",4.00}};

string getTime();

void Services();
void Add();
double Calc(char,vector<Cart>&);
void checkOut(double, vector<Cart>&);
void dailyFile(double);
void custFile(vector<Cart>&);
void collectionFile(vector<Cart>&, double);
void Review();

void dailyCollection();
void totalCollection();

void checkFile();

int main()
{

    while(true){
        
        system("cls");

        cout << "Gym da iium" << endl;
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


void totalCollection()
{
    ifstream paymentFile;
    double type1, type2, type3, type4, type5, totalCharge;

    paymentFile.open("Collection.txt");

    system("cls");

    if(paymentFile.is_open())
    {
        paymentFile >> type1 >> type2 >> type3 >> type4 >> type5 >> totalCharge;
        cout << "Total collections: " << totalCharge << endl;
        
    } else {
        cout << "ERROR! A file is currently missing!" << endl;
        cout << "Missing file: Collection.txt" << endl;
    }
    cout << "Press any key to continue: ";
    system("pause>nul");
}

void dailyCollection()
{
    ifstream daily;
    string temp1;
    double temp2;

    daily.open("dailyCollection.txt");
    system("cls");

    if(daily.is_open())
    {
        cout << "Date\tCollections" << endl;
        while(!daily.eof()){
            daily >> temp1 >> temp2;
            cout << temp1 << "\t" << temp2 << endl;
        }
    } else {
        cout << "ERROR! A file is currently missing!" << endl;
        cout << "Missing file: Collection.txt" << endl;
    }
    cout << "Press any key to continue: ";
    system("pause>nul");
    
}

void Services()
{
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

void Review()
{
    ifstream reviewFile;
    vector<string> lines;
    int type, qty;
    double payment;
    string notes;
    string temp;

    reviewFile.open("Customers.txt");
    system("cls");

    cout << "History of the customers' transactions" << endl;

    if(reviewFile.is_open()){
        while(!reviewFile.eof()){
            getline(reviewFile,temp);
            cout << temp << endl;
        }
    } else {
        cout << "ERROR! A file is currently missing!" << endl;
        cout << "Missing file: Customers.txt" << endl;
    }
    cout << "Press any key to continue: ";
    system("pause>nul");
    
}

void Add()
{
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
        cout << "Name: ";

        getline(cin,name);

        cout << "Matric No: ";
        cin >> matNo;
        cout << "Phone No: ";
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
        cout << "Repeat the order? (Y/y) to repeat: ";
        repeat = getch();

    }while(repeat == 'Y' || repeat == 'y');


}

void checkOut(double totalCharge,vector<Cart>& cart)
{
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

    dailyFile(totalCharge);
    custFile(cart);
    collectionFile(cart,totalCharge);

    cout << endl << "Press any key to continue: ";
    system("pause>nul");

    cart.clear();
}

void collectionFile(vector<Cart>& cart,double totalCharge)
{
    fstream cFile;
    double type[6] = {0,0,0,0,0,0};

    cFile.open("Collection.txt");

    if(cFile.is_open()){

        cFile >> type[0] >> type[1] >> type[3] >> type[4] >> type[5];

        for(int i = 0 ; i < cart.size(); i++){
            switch(cart[i].type){
                case 2: type[0] += cart[i].payment; break;
                case 3: type[1] += cart[i].payment; break;
                case 4: type[2] += cart[i].payment; break;
                case 5: type[3] += cart[i].payment; break;
                case 6: type[4] += cart[i].payment; break;
            }
        }
        type[5] += totalCharge;

        for(int i = 0; i < 6; i++){
            cFile << type[i] << " ";
        }
        cFile.close();
    
    } else {

        ofstream newCollection;
        newCollection.open("Collection.txt");
        if(newCollection.is_open()){

            for(int i = 0 ; i < cart.size(); i++){
                switch(cart[i].type){
                    case 2: type[0] += cart[i].payment; break;
                    case 3: type[1] += cart[i].payment; break;
                    case 4: type[2] += cart[i].payment; break;
                    case 5: type[3] += cart[i].payment; break;
                    case 6: type[4] += cart[i].payment; break;
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

void custFile(vector<Cart>& cart)
{
    fstream cust;

    cust.open("Customers.txt",fstream::app);

    if(cust.is_open()){
        for(int i = 0; i < cart.size(); i++){
            cust << cart[i].type << " " << cart[i].qty << " " << cart[i].payment << " " << cart[i].notes << endl;
        }
    } else {
        ofstream newCust;
        newCust.open("Customers.txt");
        for(int i = 0; i < cart.size(); i++){
            newCust << cart[i].type << " " << cart[i].qty << " " << cart[i].payment << " " << cart[i].notes << endl;
        }
        newCust.close();
    }
}

void dailyFile(double totalCharge)
{
    fstream outputFile;

    vector<string> date;
    vector<double> value;
    string temp1;
    double temp2;

    string str = getTime();

    outputFile.open("dailyCollection.txt");

    if(outputFile.is_open()){

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
    
    } else {
        
        ofstream newDaily;
        newDaily.open("dailyCollection.txt");
        
        newDaily << str << " " << totalCharge << endl;
        newDaily.close();
    }    
}

string getTime()
{
    time_t rawtime;
    struct tm * timeinfo;
    char buffer[80];

    time (&rawtime);
    timeinfo = localtime(&rawtime);

    strftime(buffer,sizeof(buffer),"%d-%m-%Y",timeinfo);
    string str(buffer);
    return str;
}

double Calc(char op, vector<Cart>& cart)
{
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

    // cout << type << endl;
    // cout << serv[type - 1].price << endl;
    // system("pause");

    double servicePayment = qty * serv[type - 1].price;

    Cart currentCart = {type,qty,notes,servicePayment};

    cart.push_back(currentCart);
    
    return servicePayment;
}