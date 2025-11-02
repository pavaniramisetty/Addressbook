#include <stdio.h>   // Standard I/O header
#include "file.h"    // Custom header containing AddressBook structure and MAX_CONTACTS

// Function to save contacts into a CSV file
void saveContactsToFile(AddressBook *addressBook)
{
    FILE *fptr = fopen("contacts.csv", "w");  // Open file in write mode
    if (fptr == NULL) 
    {
        printf("Error: Could not open file for writing!\n");  // Error if file can't be opened
        return;
    }

    fprintf(fptr, "%d\n", addressBook->contactCount);  // Write total contact count at top

    // Write all contacts with numbering (1. Name, Phone, Email)
    for (int i = 0; i < addressBook->contactCount; i++) 
    {
        fprintf(fptr, "%d.%s,%s,%s\n",
                i + 1,
                addressBook->contacts[i].name,
                addressBook->contacts[i].phone,
                addressBook->contacts[i].email);
    }

    fclose(fptr);  // Close file after saving
}

// Function to load contacts from a CSV file
void loadContactsFromFile(AddressBook *addressBook) 
{
    FILE *fptr = fopen("contacts.csv", "r");  // Open file in read mode
    if (fptr == NULL) 
    {
        printf("No previous contacts found.\n");  // If no file exists, start with 0 contacts
        addressBook->contactCount = 0;
        return;
    }

    int totalContacts = 0;
    fscanf(fptr, "%d\n", &totalContacts);  // Read total contact count from first line

    addressBook->contactCount = 0;  // Reset count before loading

    // Loop through file and load contacts (up to MAX_CONTACTS)
    for (int i = 0; i < totalContacts && i < MAX_CONTACTS; i++) 
    {
        fscanf(fptr, "%*d.");  // Skip numbering before dot (like "1.")

        // Read Name, Phone, Email separated by commas
        if (fscanf(fptr, "%[^,],%[^,],%[^\n]\n",
                   addressBook->contacts[i].name,
                   addressBook->contacts[i].phone,
                   addressBook->contacts[i].email) == 3) 
        {
            addressBook->contactCount++;  // Increment if valid contact read
        }
    }

    fclose(fptr);  // Close file after reading
}
