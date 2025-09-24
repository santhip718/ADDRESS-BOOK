#include <stdio.h>
#include "contact.h"

int main() {
    int choice;
    int sortchoice; 
    AddressBook addressBook;
    initialize(&addressBook); // Initialize the address book

    do {
        printf("\nAddress Book Menu:\n");
        printf("1. Create contact\n");
        printf("2. Search contact\n");
        printf("3. Edit contact\n");
        printf("4. Delete contact\n");
        printf("5. List all contacts\n");
    	printf("6. Save contacts\n");
        printf("7. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar(); // Clear newline from input buffer
        
        switch (choice) {
            case 1:
                createContact(&addressBook);
                break;
            case 2:
                searchContact(&addressBook);
                break;
            case 3:
                printf("Contacts before editing: %d\n", addressBook.contactCount);
                editContact(&addressBook);
                printf("Contacts after editing: %d\n", addressBook.contactCount);
                break;
            case 4:
                deleteContact(&addressBook);
                break;
            case 5:
                printf("Sort contacts by:\n");
                printf("1. Sort by Name\n");
                printf("2. Sort by Phone\n");
                printf("3. Sort by email\n");
                printf("4. print all the contacts\n");
                printf("Enter your choice: ");
                scanf("%d", &sortchoice);
                listContacts(&addressBook, sortchoice);
                break;
            case 6:
                printf("Saved\n");
                saveContactsToFile(&addressBook);
                break;
            default:
                printf("Exited.\n");
        }
    } while (choice != 7);
    
       return 0;
}
