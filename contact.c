#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "contact.h"
#include "file.h"
#include "populate.h"

// Function to display all contacts, sorted based on given criteria
void listContacts(AddressBook *addressBook, int sortCriteria)
{
    Contact temp; // Temporary variable for swapping

    // Bubble sort logic to arrange contacts based on chosen field
    for (int i = 0; i < addressBook->contactCount - 1; i++) {
        for (int j = 0; j < addressBook->contactCount - i - 1; j++) {
            int comp = 0; // Comparison result

            // Sorting criteria: 1 = Name, 2 = Phone, 3 = Email, 4 = No sort
            if (sortCriteria == 1) {
                comp = strcmp(addressBook->contacts[j].name, addressBook->contacts[j + 1].name);
            }
            else if (sortCriteria == 2) {
                comp = strcmp(addressBook->contacts[j].phone, addressBook->contacts[j + 1].phone);
            }
            else if (sortCriteria == 3) {
                comp = strcmp(addressBook->contacts[j].email, addressBook->contacts[j + 1].email);
            }
            else if (sortCriteria == 4) {
                comp = 0;   // No sorting applied
            }

            // Swap if current contact > next contact
            if (comp > 0) {
                temp = addressBook->contacts[j];
                addressBook->contacts[j] = addressBook->contacts[j + 1];
                addressBook->contacts[j + 1] = temp;
            }
        }
    }

    // Print header
    printf("-------------------------------------EHVC  MEMBER  DETAILS--------------------------------------\n");
    printf("+----------+--------------------+--------------------+------------------------------------------+\n");
    printf("| %-8s | %-18s | %-18s | %-40s |\n", "Index", "Name", "Phone", "Email");
    printf("+----------+--------------------+--------------------+------------------------------------------+\n");
// Print all contacts with index
    for (int i = 0; i < addressBook->contactCount; i++) {
    printf("| %-8d | %-18s | %-18s | %-40s |\n", i,
        addressBook->contacts[i].name,
        addressBook->contacts[i].phone,
        addressBook->contacts[i].email);
}
    printf("+----------+--------------------+--------------------+------------------------------------------+\n");

    // Print footer
    printf("----------------------------------EHVC  MEMBER  DETAILS----------------------------------------\n");
}


void initialize(AddressBook *addressBook) {
    addressBook->contactCount = 0;
    // Remove or comment out populateAddressBook(addressBook);
   loadContactsFromFile(addressBook);
}

void saveAndExit(AddressBook *addressBook) {
    saveContactsToFile(addressBook);
    exit(EXIT_SUCCESS);
}

// Function to create a new contact
void createContact(AddressBook *addressBook)
{
    char Name[50];   // Store name
    char num[100];   // Store phone number
    char Email[50];  // Store email

    // Read contact details from user
    printf("Enter the Name\n"); 
    scanf(" %[^\n]", Name);
    printf("Enter the phone number\n");
    scanf("%s", num);
    printf("Enter the email\n");
    scanf(" %[^\n]", Email);

    // Validate name, phone, and email before adding contact
    if (ValidateName(Name) == 1 && ValidatePhoneNumber(num, addressBook) == 1 && ValidateEmail(Email, addressBook) == 1) 
    {
        // Copy details into contact structure
        strcpy(addressBook->contacts[addressBook->contactCount].name, Name);
        strcpy(addressBook->contacts[addressBook->contactCount].phone, num);
        strcpy(addressBook->contacts[addressBook->contactCount].email, Email);

        // Increase count and confirm addition
        printf("Contact added successfully.\n");
        addressBook->contactCount++;

        // Display updated contact list
        listContacts(addressBook, 4);
    } 
    else 
    {
        // Invalid input message
        printf("Invalid input: Ensure Name, Phone, and Email are all valid and unique.\n");
    }
}


// Function to search for contacts by name, phone, or email
int searchContact(AddressBook *addressBook)
{
    // Check if there are any contacts
    if (addressBook->contactCount == 0) {
        printf("Address book is empty. Nothing to search.\n");
        return -1;
    }

    int choice;               // Search field choice
    char searchTerm[50];      // Stores user input search term
    int found = 0;            // Tracks if any contact is found

    // Ask user for search criteria
    printf("Search by:\n1. Name\n2. Phone\n3. Email\nEnter choice: ");
    scanf("%d", &choice);
    getchar();                // Remove trailing newline

    // Get the term to search for
    printf("Enter search term: ");
    scanf("%[^\n]", searchTerm);

    // Prepare to output results
    printf("Search results:\n");
    printf("Index         Name                Phone           Email\n");
    printf("--------------------------------------------------------------------\n");

    // Loop through contacts and check for a match
    for (int i = 0; i < addressBook->contactCount; i++) {
        int match = 0;

        // Compare based on user's choice
        switch (choice) {
            case 1:
                if (strcasecmp(addressBook->contacts[i].name, searchTerm) == 0)
                    match = 1;
                break;
            case 2:
                if (strcasecmp(addressBook->contacts[i].phone, searchTerm) == 0)
                    match = 1;
                break;
            case 3:
                if (strcasecmp(addressBook->contacts[i].email, searchTerm) == 0)
                    match = 1;
                break;
        }

        // If a match is found, print the contact
        if (match) {
            found = 1;
            printf("%-20d%-20s %-15s %-25s\n", i,
                addressBook->contacts[i].name,
                addressBook->contacts[i].phone,
                addressBook->contacts[i].email);

        }
    }

    // If no contact matched, print message
    if (!found) {
        printf("No contacts matched exactly.\n");
        return 0;
    }
}


// Function to edit an existing contact
void editContact(AddressBook *addressBook)
{
    char new_name[50];        // Buffer for updated name
    char new_number[20];      // Buffer for updated phone number
    char new_email[50];       // Buffer for updated email

    int ret = searchContact(addressBook); // Show contacts and search
    if (ret != 0) {
        int index;
        // Ask for the index of contact to edit
        printf("Enter the index of the contact to edit: ");
        scanf("%d", &index);

        if (index == -1) {
            // Invalid index entered
            printf("Contact not found.\n");
            return;
        }

        int choice, value;
        // Prompt for field to edit
        printf("Enter the choice : ");
        printf("1. Edit Name\n2. Edit Phone Number\n3. Edit Email\n");
        scanf("%d", &choice);

        // Edit the name
        if (choice == 1) {
            printf("Enter Updated Name\n");
            scanf(" %[^\n]", new_name);

            value = ValidateName(new_name); // Validate new name
            if (value == 1)
                strcpy(addressBook->contacts[index].name, new_name);
            else {
                printf("Enter valid name\n");
                return;
            }
        }

        // Edit the phone number
        if (choice == 2) {
            printf("Enter Updated phone_number\n");
            scanf(" %[^\n]", new_number);
            value = ValidatePhoneNumber(new_number, addressBook); // Validate new number
            if (value == 1)
                strcpy(addressBook->contacts[index].phone, new_number);
            else {
                printf("Enter valid phone number\n");
                return;
            }
        }

        // Edit the email
        if (choice == 3) {
            printf("Enter Updated Email\n");
            scanf(" %[^\n]", new_email);
            value = ValidateEmail(new_email, addressBook); // Validate new email
            if (value == 1)
                strcpy(addressBook->contacts[index].email, new_email);
            else {
                printf("Enter valid email\n");
                return;
            }
        }

        // Confirm and display updated contact list
        printf("Contact updated successfully.\n");
        listContacts(addressBook, 4);
    }
}


// Function to delete a contact from the address book
void deleteContact(AddressBook *addressBook)
{
    searchContact(addressBook); // Display contacts and allow user to search

    int index;
    printf("Enter the index of the contact to delete: ");
    scanf("%d", &index);

    if (index == -1) return; // If invalid index, exit

    // Shift contacts left to overwrite the deleted contact
    for (int i = index; i < addressBook->contactCount - 1; i++) {
        addressBook->contacts[i] = addressBook->contacts[i + 1];
    }

    addressBook->contactCount--; // Decrease the contact count

    printf("Contact deleted successfully.\n");
    listContacts(addressBook, 4); // Show updated contact list
}


// Function to validate phone number length, uniqueness, and digit-only characters
int ValidatePhoneNumber(const char *phone, AddressBook *addressBook) {
    int len = strlen(phone);           // Get length of the phone number

    if (len != 10) return 0;           // Check if length is exactly 10

    // Check for duplicate phone number in address book
    for (int i = 0; i < addressBook->contactCount; i++) {
        if (strcmp(phone, addressBook->contacts[i].phone) == 0) {
            return 0;                  // Phone number already exists
        }
    }

    // Check phone number contains only digits
    for (int i = 0; i < len; i++) {
        if (phone[i] < '0' || phone[i] > '9') 
            return 0;                  // Invalid character found
    }

    return 1;                         // Valid phone number
}

    
// Function to validate that name contains only alphabets or spaces
int ValidateName(const char *name) {
    int len = strlen(name);             // Get length of the name

    // Check each character
    for (int i = 0; i < len; i++) {
        if (!((name[i] >= 'A' && name[i] <= 'Z') ||   // Uppercase letters
              (name[i] >= 'a' && name[i] <= 'z') ||   // Lowercase letters
               name[i] == ' ')) {                      // Spaces allowed
            return 0;                                  // Invalid character found
        }
    }

    return 1; // Name is valid
}


int ValidateEmail(const char *email,AddressBook *AddressBook) {
     for(int i=0;i<AddressBook->contactCount;i++){
        if(strcmp(email,AddressBook->contacts[i].email)==0){
            return 0; // Email already exists
        }
    }
    const char *at = strchr(email, '@');
    if (!at) {
        return 0; // Must contain '@'
    }
    const char *dot = strrchr(email, '.');
    if (!dot) {
    return 0; // Must contain '.'
    }
    if (at > dot){
         return 0; // '.' must come after '@'
    }
    if (strlen(at + 1) < 2 || strlen(dot + 1) < 2){
         return 0; // Basic domain check
    }
    for(int i = 0; email[i]; i++) {
        if (!( (email[i] >= 'a' && email[i] <= 'z')||(email[i] >= '0' && email[i] <= '9')||(email[i] == '@')||(email[i] == '.'))) {
            return 0; // Invalid character found
        }
    }
    return 1; // Valid email
}

