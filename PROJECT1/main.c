/*
NAME : Pavani Ramisetty
DATE : Sep 23 2025
DESCRIPTION : Address Book is a small application written in C language. It keeps track of names and telephone/mobile numbers and e-mail addresses. 
It is a console based application which uses standard I/O for adding and deleting contact names, phone numbers and e-mail addresses, 
searching names and associated numbers and email addresses, updating numbers and email addresses, and deleting contacts.
*/

#include <stdio.h>      // Standard I/O functions
#include "contact.h"    // Header file containing AddressBook structure and function declarations

int main() 
{
    int choice;                  // Variable to store user menu choice
    AddressBook addressBook;     // AddressBook structure variable
    //addressBook.contactCount = 0; // Already initialized in initialize()
    initialize(&addressBook);    // Initialize the address book

    do {
        // Display menu
        printf("\nAddress Book Menu:\n");
        printf("1. Create contact\n");
        printf("2. Search contact\n");
        printf("3. Edit contact\n");
        printf("4. Delete contact\n");
        printf("5. List all contacts\n");
        printf("6. Save contacts\n");		
        printf("7. Exit\n");
        printf("Enter your choice: ");
        scanf(" %d", &choice);   // Read user choice
        //getchar(); // optional to consume newline

        switch (choice) {
            case 1: {
                int n;   // Number of contacts to add
                printf("How many contacts do you want to add: ");
                scanf(" %d", &n);
                //getchar();

                // Loop to create multiple contacts
                for (int i = 0; i < n; i++) 
                {
                    printf("\n--- Enter Contact %d ---\n", i + 1);
                    createContact(&addressBook);  // Call function to create contact
                }
                break;
            }
            case 2:
                searchContact(&addressBook);  // Search a contact
                break;
            case 3:
                editContact(&addressBook);    // Edit existing contact
                break;
            case 4:
                deleteContact(&addressBook);  // Delete a contact
                break;
            case 5:          
                listContacts(&addressBook);   // List all saved contacts
                break;
            case 6:
                printf("Saving and Exiting...\n");
                saveContactsToFile(&addressBook); // Save contacts to file
                break;
            default:
                printf("Invalid choice. Please try again.\n"); // Handle wrong input
        }
    } while (choice != 7);   // Continue until user chooses Exit (7)
    
    return 0;  // Program ends
}
