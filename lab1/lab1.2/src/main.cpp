#include <iostream>
#include <string>
#include <vector>

using namespace std;

// Structure for Address
struct Address {
    string street;
    int houseNumber;
    int flatNumber;
};

// Structure for Resident
struct Resident {
    string fullName;
    Address address; // Nested structure
    char gender;     // 'm' for male, 'f' for female
    int age;
};

int main() {
    int numResidents; 
    cout << "--- Part 2: Structures and Arrays ---" << endl;
    cout << "Enter the number of residents: ";
    cin >> numResidents;

    // Dynamically allocated array using vector
    vector<Resident> residents(numResidents); 

    // Data input loop
    for (int i = 0; i < numResidents; i++) {
        cout << "\nResident N=" << i + 1 << endl;
        
        cout << "Full Name: ";
        cin.ignore(); // Clear newline character from the buffer
        getline(cin, residents[i].fullName);
        
        cout << "Street: ";
        getline(cin, residents[i].address.street);
        
        cout << "House Number: ";
        cin >> residents[i].address.houseNumber;
        
        cout << "Flat Number: ";
        cin >> residents[i].address.flatNumber;
        
        cout << "Gender (m/f): ";
        cin >> residents[i].gender;
        
        cout << "Age: ";
        cin >> residents[i].age;
    }

    // Output entered data for verification
    cout << "\n--- Housing Department Database (Input Verification) ---" << endl;
    for (int i = 0; i < numResidents; i++) {
        cout << "Name: " << residents[i].fullName 
             << " | Address: " << residents[i].address.street 
             << ", House " << residents[i].address.houseNumber 
             << ", Flat " << residents[i].address.flatNumber 
             << " | Gender: " << residents[i].gender 
             << " | Age: " << residents[i].age << endl;
    }

    // Search based on Variant 15 condition
    string targetStreet;
    int targetHouse;
    
    cout << "\n--- Search ---" << endl;
    cout << "Enter street to search: ";
    cin.ignore();
    getline(cin, targetStreet);
    cout << "Enter house number to search: ";
    cin >> targetHouse;

    int matchCount = 0; // Counter for matching residents

    // Iterate through all residents
    for (int i = 0; i < numResidents; i++) {
        // Check if address matches (street and house number)
        if (residents[i].address.street == targetStreet && residents[i].address.houseNumber == targetHouse) {
            // Check gender (female) and age (>30)
            if (residents[i].gender == 'f' && residents[i].age > 30) {
                matchCount++;
            }
        }
    }

    // Output search result
    if (matchCount > 0) {
        cout << "Number of women over 30 in the specified house: " << matchCount << endl;
    } else {
        cout << "No matching residents found in the specified house." << endl;
    }

    return 0;
}
