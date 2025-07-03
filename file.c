#include <stdio.h>
#include "file.h"
#include "contact.h"

#define FILENAME "contacts.csv"

void saveContactsToFile(AddressBook *addressBook) 
{
    // Open file for writing (write mode)
    FILE *fp = fopen("contacts.csv", "w");
    if(!fp)
    {
        // Handle file open failure
        printf("Error: Could not open file for writing.\n");
        return;
    }
    // Write number of contacts as header
    fprintf(fp, "#%d\n", addressBook->contactCount);
    // Write each contact in CSV format (name,phone,email)
    for(int i = 0; i < addressBook->contactCount; i++)
    {
        fprintf(fp, "%s,%s,%s,%d,%d\n", addressBook->contacts[i].name, addressBook->contacts[i].phone, addressBook->contacts[i].email, addressBook->contacts[i].isEmergency, addressBook->contacts[i].isfavourite);
    }
    // Close file after writing
    fclose(fp);
    printf("Contacts saved successfully to %s\n", FILENAME);
}

void loadContactsFromFile(AddressBook *addressBook) 
{
    // Open file for reading
    FILE *fp = fopen("contacts.csv", "r");
    if(!fp)
    {
        printf("No existing contacts file found. Starting fresh\n");
        return;
    }
    // Read total count first
    fscanf(fp, "#%d\n", &addressBook->contactCount);
    // Read each contact assuming CSV format (up to newline)
    for(int i = 0; i < addressBook->contactCount; i++)
    {
        fscanf(fp, "%[^,],%[^,],%[^,],%d,%d\n", addressBook->contacts[i].name, addressBook->contacts[i].phone, addressBook->contacts[i].email, &addressBook->contacts[i].isEmergency, &addressBook->contacts[i].isfavourite);
    }
    // close the file after reading
    fclose(fp);
    printf("%d Contacts loaded successfully from %s.\n",addressBook->contactCount, FILENAME);
}
