#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

struct Contact {
    string name;
    string phoneNumber;
    string email;
};

// Function to display all contacts
void displayContacts(const vector<Contact>& contacts) {
    if (contacts.empty()) {
        cout << "No contacts available." << endl;
        return;
    }

    for (size_t i = 0; i < contacts.size(); ++i) {
        cout << "Contact " << i + 1 << ":" << endl;
        cout << "Name: " << contacts[i].name << endl;
        cout << "Phone Number: " << contacts[i].phoneNumber << endl;
        cout << "Email: " << contacts[i].email << endl;
        cout << "-----------------------" << endl;
    }
}

// Function to add a new contact
void addContact(vector<Contact>& contacts) {
    Contact newContact;
    cout << "Enter name: ";
    cin.ignore();  // To clear the buffer before taking new input
    getline(cin, newContact.name);
    cout << "Enter phone number: ";
    getline(cin, newContact.phoneNumber);
    cout << "Enter email address: ";
    getline(cin, newContact.email);

    contacts.push_back(newContact);
    cout << "Contact added successfully!" << endl;
}

// Function to edit an existing contact
void editContact(vector<Contact>& contacts) {
    int index;
    displayContacts(contacts);
    cout << "Enter the contact number you want to edit: ";
    cin >> index;

    if (index < 1 || index > contacts.size()) {
        cout << "Invalid contact number." << endl;
        return;
    }

    index--;  // Adjust for zero-based index
    cout << "Editing Contact " << index + 1 << endl;
    cout << "Enter new name (leave blank to keep current): ";
    cin.ignore();
    string input;
    getline(cin, input);
    if (!input.empty()) contacts[index].name = input;

    cout << "Enter new phone number (leave blank to keep current): ";
    getline(cin, input);
    if (!input.empty()) contacts[index].phoneNumber = input;

    cout << "Enter new email address (leave blank to keep current): ";
    getline(cin, input);
    if (!input.empty()) contacts[index].email = input;

    cout << "Contact updated successfully!" << endl;
}

// Function to delete a contact
void deleteContact(vector<Contact>& contacts) {
    int index;
    displayContacts(contacts);
    cout << "Enter the contact number you want to delete: ";
    cin >> index;

    if (index < 1 || index > contacts.size()) {
        cout << "Invalid contact number." << endl;
        return;
    }

    contacts.erase(contacts.begin() + index - 1);
    cout << "Contact deleted successfully!" << endl;
}

// Function to load contacts from a file
void loadContactsFromFile(vector<Contact>& contacts, const string& filename) {
    ifstream file(filename);
    if (!file) {
        cout << "No existing contacts found." << endl;
        return;
    }

    Contact contact;
    while (getline(file, contact.name)) {
        getline(file, contact.phoneNumber);
        getline(file, contact.email);
        contacts.push_back(contact);
    }
    file.close();
    cout << "Contacts loaded from file." << endl;
}

// Function to save contacts to a file
void saveContactsToFile(const vector<Contact>& contacts, const string& filename) {
    ofstream file(filename);
    if (!file) {
        cout << "Error opening file for saving." << endl;
        return;
    }

    for (const auto& contact : contacts) {
        file << contact.name << endl;
        file << contact.phoneNumber << endl;
        file << contact.email << endl;
    }
    file.close();
    cout << "Contacts saved to file." << endl;
}

int main() {
    vector<Contact> contacts;
    string filename = "contacts.txt";

    // Load contacts from file at the start
    loadContactsFromFile(contacts, filename);

    int choice;
    do {
        cout << "\nContact Management System" << endl;
        cout << "1. View Contacts" << endl;
        cout << "2. Add Contact" << endl;
        cout << "3. Edit Contact" << endl;
        cout << "4. Delete Contact" << endl;
        cout << "5. Save and Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                displayContacts(contacts);
                break;
            case 2:
                addContact(contacts);
                break;
            case 3:
                editContact(contacts);
                break;
            case 4:
                deleteContact(contacts);
                break;
            case 5:
                saveContactsToFile(contacts, filename);
                cout << "Exiting program." << endl;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != 5);

    return 0;
}
