#include <iostream>
#include <fstream>
#include <string>

using namespace std;

class Room {
private:
    int roomNumber;
    bool booked;
    string customerName;

public:
    Room() {
        roomNumber = 0;
        booked = false;
        customerName = "";
    }

    void setRoom(int num, bool status, string name) {
        roomNumber = num;
        booked = status;
        customerName = name;
    }

    int getRoomNumber() {
        return roomNumber;
    }

    bool isBooked() {
        return booked;
    }

    string getCustomerName() {
        return customerName;
    }

    void bookRoom(string name) {
        booked = true;
        customerName = name;
    }

    void checkoutRoom() {
        booked = false;
        customerName = "";
    }
};

class Hotel {
private:
    Room rooms[10];

public:
    Hotel() {
        loadData();

        for (int i = 0; i < 10; i++) {
            if (rooms[i].getRoomNumber() == 0)
                rooms[i].setRoom(i + 1, false, "");
        }
    }

    void bookRoom() {
        int roomNo;
        string name;

        cout << "Enter Room Number (1-10): ";
        cin >> roomNo;

        if (roomNo < 1 || roomNo > 10) {
            cout << "Invalid Room Number!\n";
            return;
        }

        if (rooms[roomNo - 1].isBooked()) {
            cout << "Room already booked!\n";
            return;
        }

        cin.ignore();

        cout << "Enter Customer Name: ";
        getline(cin, name);

        rooms[roomNo - 1].bookRoom(name);

        saveData();

        cout << "Room booked successfully.\n";
    }

    void checkout() {
        int roomNo;

        cout << "Enter Room Number: ";
        cin >> roomNo;

        if (roomNo < 1 || roomNo > 10) {
            cout << "Invalid Room Number!\n";
            return;
        }

        if (!rooms[roomNo - 1].isBooked()) {
            cout << "Room is already empty.\n";
            return;
        }

        rooms[roomNo - 1].checkoutRoom();

        saveData();

        cout << "Checkout completed.\n";
    }

    void searchCustomer() {
        string name;

        cin.ignore();

        cout << "Enter Customer Name: ";
        getline(cin, name);

        bool found = false;

        for (int i = 0; i < 10; i++) {
            if (rooms[i].getCustomerName() == name) {
                cout << "Customer found in Room "
                     << rooms[i].getRoomNumber() << endl;
                found = true;
            }
        }

        if (!found)
            cout << "Customer not found.\n";
    }

    void displayRooms() {

        cout << "\nRoom Status\n";
        cout << "-------------------------\n";

        for (int i = 0; i < 10; i++) {

            cout << "Room "
                 << rooms[i].getRoomNumber()
                 << " : ";

            if (rooms[i].isBooked())
                cout << "Booked (" << rooms[i].getCustomerName() << ")";
            else
                cout << "Available";

            cout << endl;
        }
    }

    void saveData() {

        ofstream file("hotel.txt");

        for (int i = 0; i < 10; i++) {

            file << rooms[i].getRoomNumber() << endl;
            file << rooms[i].isBooked() << endl;
            file << rooms[i].getCustomerName() << endl;
        }

        file.close();
    }

    void loadData() {

        ifstream file("hotel.txt");

        if (!file)
            return;

        int roomNo;
        bool booked;
        string name;

        for (int i = 0; i < 10; i++) {

            file >> roomNo;
            file >> booked;

            file.ignore();

            getline(file, name);

            rooms[i].setRoom(roomNo, booked, name);
        }

        file.close();
    }
};

int main() {

    Hotel hotel;

    int choice;

    do {

        cout << "\n===== HOTEL MANAGEMENT SYSTEM =====\n";
        cout << "1. Book Room\n";
        cout << "2. Checkout\n";
        cout << "3. Search Customer\n";
        cout << "4. Display Rooms\n";
        cout << "5. Exit\n";
        cout << "Enter Choice: ";

        cin >> choice;

        switch (choice) {

        case 1:
            hotel.bookRoom();
            break;

        case 2:
            hotel.checkout();
            break;

        case 3:
            hotel.searchCustomer();
            break;

        case 4:
            hotel.displayRooms();
            break;

        case 5:
            cout << "Thank You!\n";
            break;

        default:
            cout << "Invalid Choice!\n";
        }

    } while (choice != 5);

    return 0;
}