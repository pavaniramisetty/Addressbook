#include "contact.h"   // Include header file for AddressBook and Contact structures

// Dummy contact data for initial population
static Contact dummyContacts[] = {
    {"John Doe", "1234567890", "john@example.com"},      // Contact 1
    {"Alice Smith", "0987654321", "alice@example.com"},  // Contact 2
    {"Bob Johnson", "1112223333", "bob@company.com"},    // Contact 3
    {"Carol White", "4445556666", "carol@company.com"},  // Contact 4
    {"David Brown", "7778889999", "david@example.com"},  // Contact 5
    {"Eve Davis", "6665554444", "eve@example.com"},      // Contact 6
    {"Frank Miller", "3334445555", "frank@example.com"}, // Contact 7
    {"Grace Wilson", "2223334444", "grace@example.com"}, // Contact 8
    {"Hannah Clark", "5556667777", "hannah@example.com"},// Contact 9
    {"Ian Lewis", "8889990000", "ian@example.com"}       // Contact 10
};

// Function to populate the address book with dummy contacts
void populateAddressBook(AddressBook* addressBook)
{
    int numDummyContacts = sizeof(dummyContacts) / sizeof(dummyContacts[0]); // Calculate total dummy contacts
    // Loop through dummy contacts and add to address book (if space available)
    for (int i = 0; i < numDummyContacts && addressBook->contactCount < MAX_CONTACTS; ++i) {
        addressBook->contacts[addressBook->contactCount++] = dummyContacts[i]; // Add contact and increment count
    }
}
