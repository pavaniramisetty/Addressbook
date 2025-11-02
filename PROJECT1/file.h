#ifndef FILE_H // Prevent multiple inclusion of this header file
#define FILE_H

#include "contact.h" // Include the contact structure and definitions

void saveContactsToFile(AddressBook *addressBook); // Function to save all contacts into a file
void loadContactsFromFile(AddressBook *addressBook); // Function to load contacts from a file

#endif // End of FILE_H
