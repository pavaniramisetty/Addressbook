#ifndef CONTACT_H      // Prevent multiple inclusion of this header file
#define CONTACT_H

#define MAX_CONTACTS 100   // Maximum number of contacts allowed

// Structure to store individual contact details
typedef struct {
    char name[50];   // Name of contact
    char phone[20];  // Phone number of contact
    char email[50];  // Email address of contact
} Contact;

// Structure to represent the AddressBook
typedef struct {
    Contact contacts[100];  // Array of contacts
    int contactCount;       // Current number of contacts
} AddressBook;

// Function declarations for address book operations
void createContact(AddressBook *addressBook);     // Create a new contact
void searchContact(AddressBook *addressBook);     // Search for a contact
void editContact(AddressBook *addressBook);       // Edit an existing contact
void deleteContact(AddressBook *addressBook);     // Delete a contact
void listContacts(AddressBook *addressBook);      // List all contacts
void initialize(AddressBook *addressBook);        // Initialize the address book
void saveContactsToFile(AddressBook *AddressBook); // Save contacts to a file

// Validation functions
int name_validate(char name[]);   // Validate contact name
int phone_validate(char phone[]); // Validate phone number
int email_validate(char email[]); // Validate email address

#endif // CONTACT_H
