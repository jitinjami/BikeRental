//
//  main.cpp
//  BikeRental
//
//  Created by Jitin Jami on 27/12/20.
//

#include <iostream>
#include <cstdlib>
#include <string>
#include <fstream>

using namespace std;

class Bike
{
    friend class ListOfBikes; //Linking to bike LinkedList
private:
public:
    string Brand; //Brand of Bike
    string Model; //Mode lof bike
    int BikeId; //Bike ID
    Bike *nextBike; //Points to the next bike
    Bike (){}
    Bike (string b, string m, int bi): Brand(b), Model(m), BikeId(bi){} //Constructor
};

class BikeList //Bike LinkedList, will ony contain available bikes
{
private:
    Bike* head; //First bike
public:
    BikeList() //Constructor
    {
        head = NULL;
    }
    Bike* FirstBike(){return head;} //Returns head

    void InsertBike(Bike* BikeToBeInserted) //Adds bike to list
    {
        BikeToBeInserted->nextBike = head;
        head = BikeToBeInserted;
    }

    Bike* SearchBike(int BikeIdOfBikeToBeSearched) //Searches for bike
    {
        if(head == NULL)
        {
            return NULL;
        }

        Bike* SearchIndex = head;
        while(SearchIndex != NULL)
        {
            if(SearchIndex->BikeId == BikeIdOfBikeToBeSearched)
            {
                return SearchIndex;
            }
            SearchIndex = SearchIndex->nextBike;
        }
        return NULL;
    }

    void DeleteBike(Bike* BikeToBeDeleted) //Deletes Bike
    {
        if(head==BikeToBeDeleted)
        {
            if(head->nextBike == NULL)
            {
                head = NULL;
                delete BikeToBeDeleted;
                return;
            }
            head = head->nextBike;
            delete BikeToBeDeleted;
            return;
        }

        Bike* SearchDelete = head;
        while(SearchDelete->nextBike != BikeToBeDeleted)
        {
            SearchDelete = SearchDelete->nextBike;
        }

        SearchDelete->nextBike = BikeToBeDeleted->nextBike;
        delete BikeToBeDeleted;
        return;
    }

    void DisplayBike() //Displays list of bikes on the list
    {
        Bike* BikeToBeDisplayed = head;
        cout << "List of Bikes avalable: " << endl;
        while(BikeToBeDisplayed != NULL)
        {
            cout << BikeToBeDisplayed->BikeId << ". " << BikeToBeDisplayed->Brand << " - " << BikeToBeDisplayed->Model<<endl;
            BikeToBeDisplayed = BikeToBeDisplayed->nextBike;
        }
        delete BikeToBeDisplayed;
    }
};

class Customer
{
    friend class ListOfCustomers; //Linking to customer linkedlist
private:
public:
    string LastName; //Last name of customer
    string FirstName; //First name of customer
    string PhoneNumber; //Phone no
    int YearOfBirth; //Year of birth
    string Address[4]; // 1 = House number, 2 = Street Name, 3 = City, 4 = Pincode
    int LicenseCheck; // 0 = No, 1 = Yes, else = error
    //Details of bike reserved
    string BikeModelReserved;
    string BikeBrandReserved;
    int BikeReervationID;

    Customer(){}; //Constructor

    Customer *nextCustomer; // Points to the next Customer
    //Operator overloading for cout and cin
    friend istream &operator >> (istream &InputStream, Customer &a);
    friend ostream &operator << (ostream &OutputStream, Customer &a);

};

istream &operator >> (istream &InputStream, Customer &a) //insertion operator
{
    int check;
    cout << "Enter the details of the customer as prompted" << endl;
    cout << "Last name: " << endl;
    cin >> a.LastName;
    cout << "First name: " << endl;
    cin >> a.FirstName;
    cout << "Phone number: " << endl;
    cin >> a.PhoneNumber;
    cout << "Year of birth in YYYY format: " << endl;
    cin >> a.YearOfBirth;
    cout << "Address Input" << endl;
    cout << "House number: " << endl;
    cin >> a.Address[0];
    cout << "Street Name: " << endl;
    cin >> a.Address[1];
    cout << "City: " << endl;
    cin >> a.Address[2];
    cout << "Pin Code: " << endl;
    cin >> a.Address[3];
    cout << "Does the customer hold a class A license? [0] = No, [1] = Yes " << endl;
    cin >> check;
    if(check == 0)
    {
        a.LicenseCheck = 0;
    }
    else if(check == 1)
    {
        a.LicenseCheck = 1;
    }
    else
    {
        a.LicenseCheck = 2;
    }
    return InputStream;
}

ostream &operator << (ostream &OutputStream, Customer &a) //Output operator
{
    cout << "------------ Customer Details ------------" << endl;
    cout << "Last Name: " << a.LastName << endl;
    cout << "First Name: " << a.FirstName << endl;
    cout << "Phone Number: " << a.PhoneNumber << endl;
    cout << "Address: " << endl;
    cout << "House number: " << a.Address[0] << endl;
    cout << "Street: " << a.Address[1] << endl;
    cout << "City: " << a.Address[2] << endl;
    cout << "Pin Code: " << a.Address[3] << endl;
    cout << "Details of bike reserved-" << endl;
    cout << "Brand of Bike Reserved: " << a.BikeBrandReserved << endl;
    cout << "Model of Bike Reserved: " << a.BikeModelReserved << endl;
    cout << "Reservation number: " << a.BikeReervationID << endl;
    return OutputStream;
}

class CustomerList //Customer linked list. Will only contain active reservations
{
private:
    Customer* head; //First element
public:
    CustomerList() //Constructor
    {
        head = NULL;
    }

    Customer* FirstCustomer(){return head;} //Returns first element

    void InsertCustomer(Customer *CustomerToBeInserted) //Inserts customer
    {
        CustomerToBeInserted->nextCustomer = head;
        head = CustomerToBeInserted;
    }

    Customer* CustomerSearch(string SearchFName, string SearchLName) //Searches for customer
    {
        if (head == NULL)
        {
            return NULL;
        }

        Customer* SearchIndex = head;
        while(SearchIndex != NULL)
        {
            if(SearchIndex->FirstName == SearchFName && SearchIndex->LastName == SearchLName)
            {
                return SearchIndex;
            }
            SearchIndex = SearchIndex->nextCustomer;
        }
        return NULL;
    }

    void CustomerDelete(Customer* CustomerToBeDeleted) //Deletes customer
    {
        if(head == NULL)
        {
            return;
        }

        if (head == CustomerToBeDeleted)
        {
            if(head->nextCustomer == NULL)
            {
                head = NULL;
                delete CustomerToBeDeleted;
                return;
            }
            head = head->nextCustomer;
            delete CustomerToBeDeleted;
            return;
        }

        Customer* SearchDelete = head;
        while(SearchDelete->nextCustomer != CustomerToBeDeleted)
        {
            SearchDelete = SearchDelete->nextCustomer;
        }
        SearchDelete->nextCustomer = CustomerToBeDeleted->nextCustomer;
        delete CustomerToBeDeleted;
        return;
    }
};

int main()
{
    int s1 = 0, s2 = 0;
    cout << "Welcome to Bike Management System" << endl;
    cout << "Enter - " << endl;
    cout << "[1] to make a new files 'BikesAvailable.txt' with available bikes and empty 'ReservationList.txt'. " << endl;
    cout << "[2] if the files already exist." << endl;

    cin >> s1;

    switch(s1)
    {
        case 1:
        {
            //Populating the 2 text files and creating new files
            ofstream BikeFile("BikesAvailable.txt");
            ofstream ReservationFile("ReservationList.txt");
            BikeFile << 1 << "\t\t" << "Suzuki" <<"\t\t" << "Bandit" << endl;
            BikeFile << 2 << "\t\t" << "Honda" <<"\t\t"<<"TransAlp" << endl;
            BikeFile << 3 << "\t\t" << "BMW" <<"\t\t"<<"F-650-GS" << endl;
            BikeFile << 4 << "\t\t"<<"Kawasaki" <<"\t\t"<<"ZZR1400" << endl;

            ReservationFile << "LastName\t\tFirstName\t\tPhoneNumber\t\tYearOfBirth\t\tHouseNo\t\tStreet\t\tCity\t\tCode\t\tBike Brand\t\tBike Model\t\tBike ID" << endl;
            cout << "BikesAvailable.txt and ReservationList.txt have been created" << endl;

            cout << endl;
        }
        case 2:
        {
            CustomerList cl;
            BikeList bl;
            Customer* c;
            Bike* b;
            //input file stream for both text files
            ifstream BikeFile("BikesAvailable.txt");
            ifstream ReservationFile("ReservationList.txt");
            //bike related
            string BrandName;
            string ModelName;
            int bikeid;
            //customer related
            string CustomerFirstName;
            string CustomerLastName;
            string CustomerPhoneNumber;
            int CustomerYear;
            string CustomerAddress[4];
            string CustomerBikeBrand;
            string CustomerBikeModel;
            int CustomerBikeReervationID;

            //taking data from the text files and uploading to linked lists
            while(BikeFile >> bikeid >> BrandName >> ModelName)
            {
                b = new Bike(BrandName,ModelName,bikeid);
                bl.InsertBike(b);
            }

            while(ReservationFile >> CustomerLastName >> CustomerFirstName >> CustomerPhoneNumber>> CustomerYear >> CustomerAddress[0] >> CustomerAddress[1] >> CustomerAddress[2] >> CustomerAddress[3] >> CustomerBikeBrand >> CustomerBikeModel >> CustomerBikeReervationID)
            {
                c = new Customer();
                c->LastName = CustomerLastName;
                c->FirstName = CustomerFirstName;
                c->PhoneNumber = CustomerPhoneNumber;
                c->YearOfBirth = CustomerYear;
                c->Address[0] = CustomerAddress[0];
                c->Address[1] = CustomerAddress[1];
                c->Address[2] = CustomerAddress[2];
                c->Address[3] = CustomerAddress[3];
                c->BikeBrandReserved = CustomerBikeBrand;
                c->BikeModelReserved = CustomerBikeModel;
                c->BikeReervationID = CustomerBikeReervationID;
                cl.InsertCustomer(c);
            }
            //actions
            do
            {
                cout << "Main Menu" << endl;
                cout << "Enter the number to choose the respective option." << endl;
                cout << "[0] Make Reservation" << endl; //Make reservation
                cout << "[1] Hand Over Bike" << endl; //Take bike back from customer
                cout << "[2] Cancel Reservation" << endl; //Cancel an existing reservation
                cout << "[3] Display all available bikes" << endl;
                cout << "[4] Display reservations" << endl;
                cout << "[5] Save and Exit system" << endl;

                cin >> s2;

                switch (s2)
                {
                    case 0: //Make reservation
                    {
                        c = new Customer();
                        int ReserveCheck;
                        int BikeChoice;
                        bl.DisplayBike();
                        cout << "Enter the bike id of bike you would like to reserve" << endl;
                        cin >> BikeChoice;
                        if(BikeChoice>0 && BikeChoice<5 && bl.SearchBike(BikeChoice) != NULL)
                        {
                            c->BikeBrandReserved = bl.SearchBike(BikeChoice)->Brand;
                            c->BikeModelReserved = bl.SearchBike(BikeChoice)->Model;
                            c->BikeReervationID = bl.SearchBike(BikeChoice)->BikeId;
                            ReserveCheck = 1;
                        }
                        else if(BikeChoice>0 && BikeChoice<5 && bl.SearchBike(BikeChoice) == NULL)
                        {
                            cout << "The bike is not available." << endl;
                            ReserveCheck = 0;
                            break;
                        }
                        else
                        {
                            cout << "Please enter correct bike id." << endl;
                            ReserveCheck = 0;
                            break;
                        }
                        cout << endl;
                        try
                        {
                            cin >> *c;
                            if(c->YearOfBirth <= 999 || c->YearOfBirth > 9999)
                            {
                                throw 1;
                            }
                            if(c->Address[3].length() != 5)
                            {
                                throw 2;
                            }
                        }
                        catch(int error)
                        {
                            if (error == 1)
                            {
                                cout << "Enter a valid year in 4 digits." << endl;
                                cout << "Reservation cancelled" << endl;
                            }
                            else if (error == 2)
                            {
                                cout << "Enter a 5 digit pincode" << endl;
                                cout << "Reservation cancelled" << endl;
                            }
                        }

                        if(c->LicenseCheck == 1)
                        {
                            cl.InsertCustomer(c);
                            bl.DeleteBike(bl.SearchBike(BikeChoice));
                            ReserveCheck = 1;
                            cout << "Your bike has been reserved. Following are the details." << endl;
                            cout << *c;
                        }
                        else if (c->LicenseCheck == 0)
                        {
                            cout << "Since you don't posses a valid class A license, the reservation can't be made" << endl;
                            ReserveCheck = 0;
                        }
                        else
                        {
                            cout << "Please enter 0 for No and 1 for Yes, when prompted about possesion of class A license." << endl;
                            ReserveCheck = 0;
                        }
                        cout << endl;
                        //Over-writing files with new data
                        if (ReserveCheck == 1)
                        {
                            ofstream ReservationFile("ReservationList.txt");
                            ofstream BikeFile("BikesAvailable.txt");

                            Customer* c_temp = cl.FirstCustomer();
                            ReservationFile << "LastName\t\tFirstName\t\tPhoneNumber\t\tYearOfBirth\t\tHouseNo\t\tStreet\t\tCity\t\tCode\t\tBike Brand\t\tBike Model\t\tBike ID" << endl;
                            while(c_temp != NULL)
                            {
                                ReservationFile << c_temp->LastName << "\t\t" << c_temp->FirstName << "\t\t" << c_temp->PhoneNumber << "\t\t" << c_temp->YearOfBirth << "\t\t" << c_temp->Address[0] << "\t\t" << c_temp->Address[1] << "\t\t" << c_temp->Address[2] << "\t\t" << c_temp->Address[3] << "\t\t" << c_temp->BikeBrandReserved << "\t\t" << c_temp->BikeModelReserved << "\t\t" << c_temp->BikeReervationID << endl;
                                c_temp = c_temp->nextCustomer;
                            }
                            delete c_temp;

                            Bike* b_temp = bl.FirstBike();
                            while(b_temp != NULL)
                            {
                                BikeFile << b_temp->BikeId << "\t\t" << b_temp->Brand << "\t\t" << b_temp->Model << endl;
                                b_temp = b_temp->nextBike;
                            }
                            delete b_temp;
                            ReservationFile.close();
                            BikeFile.close();
                        }
                    }
                        break;
                    case 1:
                    {
                        cout << "Handing over" << endl;
                        int HandCheck;
                        cout << "Please enter last name." << endl;
                        cin >> CustomerLastName;
                        cout << "Please enter first name." << endl;
                        cin >> CustomerFirstName;

                        if(cl.CustomerSearch(CustomerFirstName, CustomerLastName) != NULL)
                        {
                            Customer *c_temp = cl.CustomerSearch(CustomerFirstName, CustomerLastName);

                            cl.CustomerDelete(c_temp);

                            b = new Bike(c_temp->BikeBrandReserved, c_temp->BikeModelReserved, c_temp->BikeReervationID);
                            bl.InsertBike(b);
                            cout << "The Bike '" << b->Brand << " - " << b->Model << "' has been added back to inventory." << endl;
                            HandCheck = 1;
                        }
                        else
                        {
                            cout << "The person doesn't have any ongoing reservations." << endl;
                            HandCheck = 0;
                        }
                        //Over-writing files with new data
                        if(HandCheck == 1)
                        {
                            ofstream ReservationFile("ReservationList.txt");
                            ofstream BikeFile("BikesAvailable.txt");

                            Customer* c_temp = cl.FirstCustomer();
                            ReservationFile << "LastName\t\tFirstName\t\tPhoneNumber\t\tYearOfBirth\t\tHouseNo\t\tStreet\t\tCity\t\tCode\t\tBike Brand\t\tBike Model\t\tBike ID" << endl;
                            while(c_temp != NULL)
                            {
                                ReservationFile << c_temp->LastName << "\t\t" << c_temp->FirstName << "\t\t" << c_temp->PhoneNumber << "\t\t" << c_temp->YearOfBirth << "\t\t" << c_temp->Address[0] << "\t\t" << c_temp->Address[1] << "\t\t" << c_temp->Address[2] << "\t\t" << c_temp->Address[3] << "\t\t" << c_temp->BikeBrandReserved << "\t\t" << c_temp->BikeModelReserved << "\t\t" << c_temp->BikeReervationID << endl;
                                c_temp = c_temp->nextCustomer;
                            }
                            delete c_temp;

                            Bike* b_temp = bl.FirstBike();
                            while(b_temp != NULL)
                            {
                                BikeFile << b_temp->BikeId << "\t\t" << b_temp->Brand << "\t\t" << b_temp->Model << endl;
                                b_temp = b_temp->nextBike;
                            }
                            delete b_temp;
                            ReservationFile.close();
                            BikeFile.close();
                        }
                    }
                        break;
                    case 2:
                    {
                        int CancelCheck;
                        cout << "Cancelling" << endl;
                        cout << "Please enter last name." << endl;
                        cin >> CustomerLastName;
                        cout << "Please enter first name." << endl;
                        cin >> CustomerFirstName;

                        if(cl.CustomerSearch(CustomerFirstName, CustomerLastName) != NULL)
                        {
                            Customer *c_temp = cl.CustomerSearch(CustomerFirstName, CustomerLastName);

                            cl.CustomerDelete(c_temp);

                            b = new Bike(c_temp->BikeBrandReserved, c_temp->BikeModelReserved, c_temp->BikeReervationID);
                            bl.InsertBike(b);
                            cout << "The reservation for Bike '" << b->Brand << " - " << b->Model << "' under the name " << c_temp->LastName << ", " << c_temp->FirstName <<"has been cancelled." << endl;
                            CancelCheck = 1;
                        }
                        else
                        {
                            cout << "The person doesn't have any ongoing reservations." << endl;
                            CancelCheck = 0;
                        }
                        //Over-writing files with new data
                        if(CancelCheck == 1)
                        {
                            ofstream ReservationFile("ReservationList.txt");
                            ofstream BikeFile("BikesAvailable.txt");

                            Customer* c_temp = cl.FirstCustomer();
                            ReservationFile << "LastName\t\tFirstName\t\tPhoneNumber\t\tYearOfBirth\t\tHouseNo\t\tStreet\t\tCity\t\tCode\t\tBike Brand\t\tBike Model\t\tBike ID" << endl;
                            while(c_temp != NULL)
                            {
                                ReservationFile << c_temp->LastName << "\t\t" << c_temp->FirstName << "\t\t" << c_temp->PhoneNumber << "\t\t" << c_temp->YearOfBirth << "\t\t" << c_temp->Address[0] << "\t\t" << c_temp->Address[1] << "\t\t" << c_temp->Address[2] << "\t\t" << c_temp->Address[3] << "\t\t" << c_temp->BikeBrandReserved << "\t\t" << c_temp->BikeModelReserved << "\t\t" << c_temp->BikeReervationID << endl;
                                c_temp = c_temp->nextCustomer;
                            }
                            delete c_temp;

                            Bike* b_temp = bl.FirstBike();
                            while(b_temp != NULL)
                            {
                                BikeFile << b_temp->BikeId << "\t\t" << b_temp->Brand << "\t\t" << b_temp->Model << endl;
                                b_temp = b_temp->nextBike;
                            }
                            delete b_temp;
                            ReservationFile.close();
                            BikeFile.close();
                        }

                    }
                        break;
                    case 3:
                    {
                        bl.DisplayBike();
                    }
                        break;
                    case 4:
                    {
                        cout << "Please enter last name." << endl;
                        cin >> CustomerLastName;
                        cout << "Please enter first name." << endl;
                        cin >> CustomerFirstName;
                        if(cl.CustomerSearch(CustomerFirstName, CustomerLastName) != NULL)
                        {
                            cout << *cl.CustomerSearch(CustomerFirstName, CustomerLastName);
                        }
                        else
                        {
                            cout << "The person doesn't have any active reservation." << endl;
                        }
                    }
                        break;
                    case 5:
                    {
                        //Over-writing files with data and exiting
                        ofstream ReservationFile("ReservationList.txt");
                        ofstream BikeFile("BikesAvailable.txt");

                        Customer* c_temp = cl.FirstCustomer();
                        ReservationFile << "LastName\t\tFirstName\t\tPhoneNumber\t\tYearOfBirth\t\tHouseNo\t\tStreet\t\tCity\t\tCode\t\tBike Brand\t\tBike Model\t\tBike ID" << endl;
                        while(c_temp != NULL)
                        {
                            ReservationFile << c_temp->LastName << "\t\t" << c_temp->FirstName << "\t\t" << c_temp->PhoneNumber << "\t\t" << c_temp->YearOfBirth << "\t\t" << c_temp->Address[0] << "\t\t" << c_temp->Address[1] << "\t\t" << c_temp->Address[2] << "\t\t" << c_temp->Address[3] << "\t\t" << c_temp->BikeBrandReserved << "\t\t" << c_temp->BikeModelReserved << "\t\t" << c_temp->BikeReervationID << endl;
                            c_temp = c_temp->nextCustomer;
                        }
                        delete c_temp;

                        Bike* b_temp = bl.FirstBike();
                        while(b_temp != NULL)
                        {
                            BikeFile << b_temp->BikeId << "\t\t" << b_temp->Brand << "\t\t" << b_temp->Model << endl;
                            b_temp = b_temp->nextBike;
                        }
                        delete b_temp;
                        ReservationFile.close();
                        BikeFile.close();
                    }
                        break;
                    default:
                    {
                        cout << "Please enter a value between 0 and 5." << endl;
                    }
                        break;
                }
            }while(s2!=5);
        }
            break;
        default:
        {
            cout << "Please enter an appropriate value (0 or 1)." << endl;
        }
            break;
    }
    return 0;
}
