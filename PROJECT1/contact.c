#include <stdio.h> // Standard input-output functions
#include <stdlib.h> // For exit(), malloc(), free(), etc.
#include <string.h> // For string handling functions (strcpy, strcmp, strlen)
#include <ctype.h> // For character checking functions (isalpha, isdigit, islower)
#include "contact.h" // Header file containing AddressBook and function prototypes
#include "file.h" // Header file for file handling functions
#include "populate.h" // Header file for populating dummy contacts

// Function to list all contacts
void listContacts(AddressBook *addressBook) 
{
    printf("\n--- Contact List ---\n"); // Print header
    for (int i = 0; i < addressBook->contactCount; i++) // Loop through contacts
    {
        printf("%d. %s %s %s\n", // Print contact details
               i + 1,
               addressBook->contacts[i].name,
               addressBook->contacts[i].phone,
               addressBook->contacts[i].email);
    }
    printf("--------------------\n"); // Print footer
}

// Initialize address book
void initialize(AddressBook *addressBook) {
    addressBook->contactCount = 0; // Start with no contacts
    //populateAddressBook(addressBook); // Optional dummy data
    loadContactsFromFile(addressBook); // Load from file if available
}

// Save and exit program
void saveAndExit(AddressBook *addressBook) 
{
    saveContactsToFile(addressBook); // Save contacts to file
    exit(EXIT_SUCCESS); // Exit successfully
}

// Validate name
int name_validate(char name[]) // Returns 1 if valid else 0
{
  int len = strlen(name), i; // Get length
  if(len == 0) // Empty invalid
    return 0;
  for(i = 0; i < len; i++) // Loop through characters
  {
    if(!(isalpha(name[i]) || name[i] == ' ')) // Allow alphabets and spaces
    {
      return 0; // Invalid char
    }
  }
  return 1; // Valid
}

// Validate phone number
int phone_validate(char phone[])
{
  int len = strlen(phone), i, count = 0; // Get length and digit count
  for(i = 0; i < len; i++) // Loop through phone digits
  {
   if(isdigit(phone[i]) && !(isalpha(phone[i]))) // Only digits allowed
   {
    count++; // Count digits
   }
  }
  if(len == count && len == 10) // Must be exactly 10 digits
  {
    return 1; // Valid
  }
  else
  {
    return 0; // Invalid
  }
}
int email_validate(char email[])  // Validate email 
{
    int len = strlen(email);

    // Must end with ".com"
    if (len < 5 || strcmp(email + len - 4, ".com") != 0)
        return 0;

    // Check ".com" appears only once
    char *firstDotCom = strstr(email, ".com");
    char *lastDotCom  = email + len - 4;
    if (firstDotCom != lastDotCom)
        return 0;   // another ".com" found before the last one

    char *at = strchr(email, '@'); // must contain @
    if (!at) 
        return 0;

    if (at == email) // if nothing is present before @
        return 0; 

    if (strchr(at + 1, '@') != NULL)
        return 0;   // more than one @

    // Validate each character
    for (int i = 0; i < len; i++) 
    {
        if (email[i] == ' ') 
            return 0;  // no spaces

        // only lowercase letters, digits, @, _, .
        if (!(islower(email[i]) || isdigit(email[i]) || email[i] == '@' || email[i] == '_' || email[i] == '.'))
            return 0;

        // first char cannot be digit, '_' or '.'
        if (i == 0 && (isdigit(email[i]) || email[i] == '_' || email[i] == '.'))
            return 0;

        // consecutive dots not allowed
        if (i > 0 && email[i] == '.' && email[i - 1] == '.')
            return 0;
    }

    // Domain (after @) must not be empty or start with '.'
    char *domain = at + 1;
    if (domain[0] == '.')
        return 0;  // empty domain

    // Domain can only have lowercase letters before ".com"
    int domainLen = (lastDotCom - domain); // part between @ and .com
    for (int i = 0; i < domainLen; i++) 
    {
        if (!islower(domain[i]))
            return 0;  // only lowercase letters allowed
    }

    return 1; // valid email-id
}

// Check unique phone
int isPhoneUnique(AddressBook *addressBook, char phone[]) {
    for (int i = 0; i < addressBook->contactCount; i++) {
        if (strcmp(addressBook->contacts[i].phone, phone) == 0)
            return 0; // Duplicate
    }
    return 1; // Unique
}

// Check unique email
int isEmailUnique(AddressBook *addressBook, char email[]) {
    for (int i = 0; i < addressBook->contactCount; i++) {
        if (strcmp(addressBook->contacts[i].email, email) == 0)
            return 0; // Duplicate
    }
    return 1; // Unique
}

// Create a new contact
void createContact(AddressBook *addressBook)
{
    char name[20]; // Temp storage
    char phone[11];
    char email[30];

    // Validate name
    do{
     printf("Enter the name :");
     scanf(" %[^\n]", name);
     if (name_validate(name))
      break; // Valid
     else 
     printf("Enter the valid name\n"); // Invalid
    }while(1);

    // Validate phone
    do{
     printf("Enter the phone number :");
     scanf(" %[^\n]", phone);
     if (!phone_validate(phone)) // Invalid
        printf("Enter the valid phone number\n");
     else if (!isPhoneUnique(addressBook, phone)) // Duplicate
        printf("This phone number already exists! Enter a unique phone number.\n");
     else break; // Valid
    }while(1);

    // Validate email
    do{
     printf("Enter the mail id :");
     scanf(" %[^\n]", email);
     if (!email_validate(email)) // Invalid
        printf("Enter the valid mailid\n");
     else if (!isEmailUnique(addressBook, email)) // Duplicate
        printf("This email id already exists! Enter a unique email id.\n");
     else break; // Valid
    }while(1);

    // Store into address book
    strcpy(addressBook->contacts[addressBook->contactCount].name, name);
    strcpy(addressBook->contacts[addressBook->contactCount].phone, phone);
    strcpy(addressBook->contacts[addressBook->contactCount].email, email);
    addressBook->contactCount++; // Increase count
}

// Search contacts
void searchContact(AddressBook *addressBook) 
{
    if (addressBook->contactCount == 0) { // No contacts
        printf("No contacts available to search!\n");
        return;
    }
    int choice; // Search option
    char search[50]; // Search string
    int found = 0; // Match flag
    do {
        printf("\n--- Search Menu ---\n"); // Menu
        printf("1. Search by Name\n");
        printf("2. Search by Phone Number\n");
        printf("3. Search by Email ID\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        switch (choice)
        {
            case 1: { // By name
                printf("Enter the name to search: ");
                scanf(" %[^\n]", search);
                int matchedIndices[50], matchCount = 0; // Store matches
                for (int i = 0; i < addressBook->contactCount; i++) {
                    if (strcmp(addressBook->contacts[i].name, search) == 0)
                        matchedIndices[matchCount++] = i;
                }
                if (matchCount == 0)
                    printf("Name not found!\n");
                else if (matchCount == 1) { // One match
                    int idx = matchedIndices[0];
                    printf("\nContact Found:\nName : %s\nPhone: %s\nEmail: %s\n",
                        addressBook->contacts[idx].name,
                        addressBook->contacts[idx].phone,
                        addressBook->contacts[idx].email);
                } else { // Multiple matches
                    printf("\nMultiple contacts found:\n");
                    for (int j = 0; j < matchCount; j++) {
                        int idx = matchedIndices[j];
                        printf("%d. %s | %s | %s\n", j + 1,
                               addressBook->contacts[idx].name,
                               addressBook->contacts[idx].phone,
                               addressBook->contacts[idx].email);
                    }
                    printf("\nEnter phone or email to refine: ");
                    char refine[50];
                    scanf(" %[^\n]", refine);
                    int refinedFound = 0;
                    for (int j = 0; j < matchCount; j++) {
                        int idx = matchedIndices[j];
                        if (strcmp(addressBook->contacts[idx].phone, refine) == 0 ||
                            strcmp(addressBook->contacts[idx].email, refine) == 0) {
                            printf("\nExact Contact Found:\nName : %s\nPhone: %s\nEmail: %s\n",
                                addressBook->contacts[idx].name,
                                addressBook->contacts[idx].phone,
                                addressBook->contacts[idx].email);
                            refinedFound = 1;
                            break;
                        }
                    }
                    if (!refinedFound) printf("No contact matched refinement!\n");
                }
                break;
            }
            case 2: { // By phone
                printf("Enter the phone number to search: ");
                scanf(" %[^\n]", search);
                for (int i = 0; i < addressBook->contactCount; i++) {
                    if (strcmp(addressBook->contacts[i].phone, search) == 0) {
                        printf("\nContact Found:\nName : %s\nPhone: %s\nEmail: %s\n",
                            addressBook->contacts[i].name,
                            addressBook->contacts[i].phone,
                            addressBook->contacts[i].email);
                        found = 1; break;
                    }
                }
                if (!found) printf("Phone number not found!\n");
                found = 0;
                break;
            }
            case 3: { // By email
                printf("Enter the email ID to search: ");
                scanf(" %[^\n]", search);
                for (int i = 0; i < addressBook->contactCount; i++) {
                    if (strcmp(addressBook->contacts[i].email, search) == 0) {
                        printf("\nContact Found:\nName : %s\nPhone: %s\nEmail: %s\n",
                            addressBook->contacts[i].name,
                            addressBook->contacts[i].phone,
                            addressBook->contacts[i].email);
                        found = 1; break;
                    }
                }
                if (!found) printf("Email not found!\n");
                found = 0;
                break;
            }
            case 4: printf("Exiting search menu...\n"); break;
            default: printf("Invalid choice! Please try again.\n");
        }
    } while (choice != 4);
}

// Edit contact
void editContact(AddressBook *addressBook)
{
  if (addressBook->contactCount == 0) { // No contacts
    printf("No contacts available to edit!\n");
    return;
  }
  int choice, idx; // Menu option and index
  char temp[50]; // Temporary storage
  do {
        printf("\n--- Edit Contact Menu ---\n");
        printf("1. Edit Name\n2. Edit Phone Number\n3. Edit Email\n4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1: // Edit name
                listContacts(addressBook);
                printf("Select contact index: ");
                scanf("%d", &idx);
                idx--;
                if (idx < 0 || idx > addressBook->contactCount) {
                    printf("Invalid index!\n"); break;
                }
                printf("Enter new name: ");
                scanf(" %[^\n]", temp);
                if (name_validate(temp)) {
                    strcpy(addressBook->contacts[idx].name, temp);
                    printf("Name updated!\n");
                } else printf("Invalid name!\n");
                break;
            case 2: // Edit phone
                listContacts(addressBook);
                printf("Select contact index: ");
                scanf("%d", &idx);
                idx--;
                if (idx < 0 || idx > addressBook->contactCount) {
                    printf("Invalid index!\n"); break;
                }
                do {
                    printf("Enter new phone: ");
                    scanf(" %[^\n]", temp);
                    if (!phone_validate(temp))
                        printf("Invalid phone! Try again.\n");
                    else if (!isPhoneUnique(addressBook, temp) &&
                             strcmp(addressBook->contacts[idx].phone, temp) != 0)
                        printf("Phone already exists! Try again.\n");
                    else {
                        strcpy(addressBook->contacts[idx].phone, temp);
                        printf("Phone updated!\n"); break;
                    }
                } while (1);
                break;
            case 3: // Edit email
                listContacts(addressBook);
                printf("Select contact index: ");
                scanf("%d", &idx);
                idx--;
                if (idx < 0 || idx > addressBook->contactCount) {
                    printf("Invalid index!\n"); break;
                }
                do {
                    printf("Enter new email: ");
                    scanf(" %[^\n]", temp);
                    if (!email_validate(temp))
                        printf("Invalid email! Try again.\n");
                    else if (!isEmailUnique(addressBook, temp) &&
                             strcmp(addressBook->contacts[idx].email, temp) != 0)
                        printf("Email already exists! Try again.\n");
                    else {
                        strcpy(addressBook->contacts[idx].email, temp);
                        printf("Email updated!\n"); break;
                    }
                } while (1);
                break;
            case 4: printf("Exiting edit menu...\n"); break;
            default: printf("Invalid choice! Try again.\n");
        }
    } while (choice != 4);
}

// Delete contact
void deleteContact(AddressBook *addressBook)
{
    if (addressBook->contactCount == 0) { // No contacts
        printf("No contacts available to delete!\n");
        return;
    }
    int choice; // Menu option
    char search[50]; // Search string
    int found = 0; // Found flag
    do {
        printf("\n--- Delete Contact Menu ---\n");
        printf("1. Delete by Name\n2. Delete by Phone Number\n3. Delete by Email ID\n4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1: { // By name
                printf("Enter the name to delete: ");
                scanf(" %[^\n]", search);
                int matchedIndices[50], matchCount = 0;
                for (int i = 0; i < addressBook->contactCount; i++) {
                    if (strcmp(addressBook->contacts[i].name, search) == 0)
                        matchedIndices[matchCount++] = i;
                }
                if (matchCount == 0)
                    printf("Name not found!\n");
                else if (matchCount == 1) { // One match
                    int idx = matchedIndices[0];
                    printf("Deleting: %s | %s | %s\n",
                           addressBook->contacts[idx].name,
                           addressBook->contacts[idx].phone,
                           addressBook->contacts[idx].email);
                    for (int j = idx; j < addressBook->contactCount - 1; j++)
                        addressBook->contacts[j] = addressBook->contacts[j + 1]; // Shift
                    addressBook->contactCount--;
                    printf("Contact deleted!\n");
                } else { // Multiple matches
                    printf("\nMultiple contacts found:\n");
                    for (int j = 0; j < matchCount; j++) {
                        int idx = matchedIndices[j];
                        printf("%d. %s | %s | %s\n", j + 1,
                               addressBook->contacts[idx].name,
                               addressBook->contacts[idx].phone,
                               addressBook->contacts[idx].email);
                    }
                    printf("\nEnter phone/email to refine: ");
                    char refine[50];
                    scanf(" %[^\n]", refine);
                    int refinedIndex = -1;
                    for (int j = 0; j < matchCount; j++) {
                        int idx = matchedIndices[j];
                        if (strcmp(addressBook->contacts[idx].phone, refine) == 0 ||
                            strcmp(addressBook->contacts[idx].email, refine) == 0) {
                            refinedIndex = idx; break;
                        }
                    }
                    if (refinedIndex != -1) {
                        printf("Deleting: %s | %s | %s\n",
                               addressBook->contacts[refinedIndex].name,
                               addressBook->contacts[refinedIndex].phone,
                               addressBook->contacts[refinedIndex].email);
                        for (int j = refinedIndex; j < addressBook->contactCount - 1; j++)
                            addressBook->contacts[j] = addressBook->contacts[j + 1]; // Shift
                        addressBook->contactCount--;
                        printf("Contact deleted!\n");
                    } else printf("No contact matched refinement!\n");
                }
                break;
            }
            case 2: { // By phone
                printf("Enter phone to delete: ");
                scanf(" %[^\n]", search);
                int idx = -1;
                for (int i = 0; i < addressBook->contactCount; i++) {
                    if (strcmp(addressBook->contacts[i].phone, search) == 0) {
                        idx = i; break;
                    }
                }
                if (idx == -1) printf("Phone not found!\n");
                else {
                    printf("Deleting: %s | %s | %s\n",
                           addressBook->contacts[idx].name,
                           addressBook->contacts[idx].phone,
                           addressBook->contacts[idx].email);
                    for (int j = idx; j < addressBook->contactCount - 1; j++)
                        addressBook->contacts[j] = addressBook->contacts[j + 1];
                    addressBook->contactCount--;
                    printf("Contact deleted!\n");
                }
                break;
            }
            case 3: { // By email
                printf("Enter email to delete: ");
                scanf(" %[^\n]", search);
                int idx = -1;
                for (int i = 0; i < addressBook->contactCount; i++) {
                    if (strcmp(addressBook->contacts[i].email, search) == 0) {
                        idx = i; break;
                    }
                }
                if (idx == -1) printf("Email not found!\n");
                else {
                    printf("Deleting: %s | %s | %s\n",
                           addressBook->contacts[idx].name,
                           addressBook->contacts[idx].phone,
                           addressBook->contacts[idx].email);

                    for (int j = idx; j < addressBook->contactCount - 1; j++) {
                        addressBook->contacts[j] = addressBook->contacts[j + 1];
                    }
                    addressBook->contactCount--;
                    printf("Contact deleted successfully!\n");
                }
                break;
            }

            case 4:
                printf("Exiting delete menu...\n"); //exit delete menu
                break;

            default:
                printf("Invalid choice! Try again.\n"); //invalid input
        }
    } while (choice != 4); // Repeat until user exits


}
