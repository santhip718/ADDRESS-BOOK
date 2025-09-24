#include <stdio.h>
#include<string.h>
#include "file.h"

// Save all contacts to a CSV file
void saveContactsToFile(AddressBook *addressBook) {
    FILE *file = fopen("contacts.csv", "w");  // Open file in write mode
    if (!file) {
        printf("Could not open contacts.csv for writing.\n");
        return;
    }

    // Write each contact as a CSV line: name, phone, email
    for (int i = 0; i < addressBook->contactCount; i++) {
        fprintf(file, "%s,%s,%s\n",
            addressBook->contacts[i].name,
            addressBook->contacts[i].phone,
            addressBook->contacts[i].email);
    }

    fclose(file);  // Close the file
    printf("Saved %d contacts to contacts.csv\n", addressBook->contactCount);
}

// Load contacts from CSV file into address book
void loadContactsFromFile(AddressBook *addressBook) {
    FILE *p = fopen("contacts.csv", "r");
    if (!p) return; // File not found
    addressBook->contactCount=0;
    while ( fscanf(p, "%[^,],%[^,],%[^\n]\n",
            addressBook->contacts[addressBook->contactCount].name,
            addressBook->contacts[addressBook->contactCount].phone,
            addressBook->contacts[addressBook->contactCount].email
            ) == 3 ) {
            addressBook->contactCount++;
        }
    fclose(p);
}
