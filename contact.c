#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "contact.h"
#include "file.h"
#include "populate.h"

extern Contact lastDeletedContact;
extern int isDeletedAvailable;
extern int lastDeletedIndex;

// Display all contacts in alphabetical order by name
void listContacts(AddressBook *addressBook) 
{
    if(addressBook -> contactCount == 0)
    {
        printf("No contacts to display\n"); 
        return;
    }
    // Bubble sort by name (case-insensitive)
    for(int i = 0; i < addressBook->contactCount - 1; i++)
    {
        for(int j = 0; j < addressBook->contactCount - i - 1; j++)
        {
            if(strcasecmp(addressBook->contacts[j].name, addressBook->contacts[j + 1].name) > 0)
            {
                Contact temp = addressBook->contacts[j];
                addressBook->contacts[j] = addressBook->contacts[j+1];
                addressBook->contacts[j+1] = temp;
            }
        }
    }
    // Print table header
    printf("\n%-5s | %-20s | %-15s | %-30s\n", "S.No", "Name", "Phone", "Email");
    printf("----------------------------------------------------------------------\n");
    // Print contact list
    for(int i = 0; i < addressBook->contactCount; i++)
    {
        printf("%-5d | %-20s | %-15s | %-30s\n", i+1,
        addressBook -> contacts[i].name,
        addressBook -> contacts[i].phone,
        addressBook -> contacts[i].email);
    }
}

void initialize(AddressBook *addressBook) 
{
    addressBook->contactCount = 0;
    //Load hardcoded dummy contacts (for testing)
    //populateAddressBook(addressBook);

    // Load contacts from file during initialization (After files)
    loadContactsFromFile(addressBook);
}

// Save all contacts and exit the program
void saveAndExit(AddressBook *addressBook) 
{
    // Save contacts to file
    saveContactsToFile(addressBook);
    // Exit the program
    exit(EXIT_SUCCESS);
}

// Function to create and add a new contact to the address book
void createContact(AddressBook *addressBook)
{
    char number[11];
    char name[30];
    char email[30];
    int flag;
    Contact newContact;

    if(addressBook->contactCount >= MAX_CONTACTS)
    {
        printf("Address Book is full! Cannot add more contacts.\n");
        return;
    }
    printf("Enter the Name:\n");
    // Reads name with spaces
    scanf(" %[^\n]", name);                                                               
    printf("\n");
    //Phone number input and validation
    do
    {
        flag=0;
        printf("Enter the mobile number:\n");
        scanf("%s", number);
        printf("\n");
        if(!is_valid_phone(number))
        { 
            flag = 1; 
            continue;
        }
        int len = strlen(number);
        if(len == 10)
        {
        // Check for duplicate mobile number
            if(is_duplicate_field(number, addressBook, 1))
            {
                printf("Mobile number already exists!\n");
                flag = 1;
            }
            else
            {
                newContact.isEmergency = 0;
            }
        }
        else if(len == 3 || len == 4)
        {
            char emergencyChoice;
            printf("It this an emergency contact? (Y/N): ");
            scanf(" %c", &emergencyChoice);
            if(emergencyChoice == 'Y' || emergencyChoice == 'y')
            {
                newContact.isEmergency = 1;
                // Emergency contact uses default name
                strcpy(name, "Emergency");
            }
            else
            {
                flag = 1;
                printf("Only emergency contacts can have 3 or 4 digit numbers\n");
            }
        }
        else
        {
            flag = 1;
        }
    }while(flag == 1);

    // Email entry and validation
    if(newContact.isEmergency == 0)
    {
        do
        {
            flag=0;
            printf("Enter the Email ID:\n");
            scanf("%s", email);
            printf("\n");
            if(!is_valid_email(email))
            {
                flag=1;
            }
            else if(is_duplicate_field(number, addressBook, 2))
            {
                printf("Email already exists!\n");
                flag = 1;
            }
        }while(flag == 1);
        strcpy(newContact.email, email);
    }
    else
    {
        // Skip email for emergency
        strcpy(newContact.email, "-");
        printf("Email skipped for emergency contact.\n");
    }
    // Finalize contact details
    strcpy(newContact.name, name);
    strcpy(newContact.phone, number);
    if(newContact.isEmergency)
    {
        printf("Emtergency Contact saved successfully!\n");
    }
    else
    {
        printf("Contact created successfully!\n");
    }
    // Favourite choice
    char favChoice;
    printf("Do you want to mark this contact as Favourite? (Y/N): ");
    scanf(" %c", &favChoice);
    if(favChoice == 'Y' || favChoice == 'y')
    {
        newContact.isfavourite = 1;
        printf("\nContact added to favourites!\n");
    }
    else
    {
        newContact.isfavourite = 0;
    }
    // Add contact to address book
    addressBook->contacts[addressBook->contactCount]=newContact;
    addressBook->contactCount++;
}
// Validates mobile number (only 10-digit, 3-digit, or 4-digit numbers)
int is_valid_phone(char *number)
{
    int len = strlen(number);
    if(len != 10 && len != 3 && len != 4)
    {
        printf("Invalid mobile number! Enter again\n");
        return 0;
    }
    for(int i = 0; i < len; i++)
    {
        if(!isdigit(number[i]))
        {
            printf("Invalid mobile number! Enter again\n");
            return 0;
        }
    }
    return 1;             
}
// Validates email format based on custom rules
int is_valid_email(char *email)
{
    if(!islower(email[0]))
    {
        printf("Invalid Email ID! Enter again\n");
        return 0;
    }

    char *isatpresent = strchr(email, '@');
    if(isatpresent == NULL)
    {
        printf("Invalid Email ID! Enter again\n");
        return 0;
    }
    // Validate username part (before '@')
    for(int i = 1; email + i < isatpresent; i++)
    {
        if(!islower(email[i])  && !isdigit(email[i]))
        {
            printf("Invalid Email ID! Enter again\n");
            return 0;
        }
    }

    char *isdotpresent = strchr(isatpresent, '.');
    if(isdotpresent == NULL)
    {
        printf("Invalid Email ID! Enter again\n");
        return 0;
    }
    if(isdotpresent <= isatpresent+1)
    {
        printf("Invalid Email ID! Enter again\n");
        return 0;
    }
    // Validate domain part (between @ and .)
    for(int i = 1;  isatpresent + i < isdotpresent; i++)
    {
        if(!islower(isatpresent[i]) && !isdigit(isatpresent[i]))
        {
            printf("Invalid Email ID! Enter again\n");
            return 0;
        }
    }
    // Allow only .com domain
    if(strcmp(isdotpresent, ".com") != 0)
    {
        printf("Invalid Email ID! Enter again\n");
        return 0;
    }
    return 1;
}

// Function to search for a contact in the address book based on name, mobile number, or email
void searchContact(AddressBook *addressBook) 
{
    int searchoption, maxCount;
    char input[30];
    int indexArray[100];
    printf("choose option to search contact\n");
    printf("1. Name\n2. Mobile Number\n3. Email ID\n");
    scanf("%d", &searchoption);
    if(searchoption < 1 || searchoption > 3)
    {
        printf("Invalid choice!Please try again.\n");
        return;
    }
    // Prompt user to enter the search value (name, number, or email)
    printf("Enter the info to search:\n");
    scanf(" %[^\n]", input);
    // Validate the input if the user chose phone or email search
    if((searchoption == 2 && !is_valid_phone(input))|| (searchoption == 3 && !is_valid_email(input)))
    {
        printf("Invalid input format.\n");
        return;
    }
    // Find all matching contacts based on selected field (name/phone/email)
    // Stores indices of matches in indexArray
    maxCount = findMatchingContacts(addressBook, searchoption, input, indexArray);
    if(maxCount == 0)
    {
        printf("No matching contacts found.\n");
        return;
    }
}

// Allows user to edit a contact by searching via Name, Phone, or Email
void editContact(AddressBook *addressBook)
{
    int indexArray[100], maxCount, selectIndex;
    int searchoption;
    char input[30];
    printf("choose option to search contact to edit\n");
    printf("1. Name\n2. Mobile Number\n3. Email ID\n");
    scanf("%d", &searchoption);
    if(searchoption < 1 || searchoption > 3)
    {
        printf("Invalid choice!Please try again.\n");
        return;
    }
    printf("Enter the value to search:\n");
    scanf(" %[^\n]", input);
    // Validate input format if searching by phone or email
    if((searchoption == 2 && !is_valid_phone(input)) || (searchoption == 3 && !is_valid_email(input)))
    {
        printf("Invalid input format.\n");
        return;
    }
    // Find matching contacts based on user input
    maxCount = findMatchingContacts(addressBook, searchoption, input, indexArray);
    // No matches found
    if(maxCount == 0)
    {
        printf("No matching contacts found.\n");
        return;
    }
    // If multiple matches found, ask user to choose one
    if(maxCount > 1)
    {
        printf("\nMultiple contacts found. choose one to edit (1 to %d):\n", maxCount);
        scanf("%d", &selectIndex);
        if(selectIndex < 1 || selectIndex > maxCount)
        {
            printf("Invalid selection\n");
            return;
        }
        // Map user’s choice to actual index in contacts array
        selectIndex = indexArray[selectIndex-1];
    }
    else
    {
        selectIndex = indexArray[0];
    }
    // Call edit helper to modify the selected contact
    edit(&addressBook->contacts[selectIndex], addressBook);
}
// Edits a specific field of a given contact (name, phone, or email)
void edit(Contact *c, AddressBook *addressBook)
{
    int editoption, flag=0;
    char name[50];
    char number[11];
    char email[40];

    // Ask user which field they want to edit
    printf("Choose option to edit\n"); 
    printf("1. Name\n");
    printf("2. Mobile Number\n");
    printf("3. Email ID\n");
    printf("4. Mark?Unmark Favourite\n");
    scanf("%d", &editoption);

    switch(editoption)
    {
        // Edit name directly
        case 1:
        printf("Enter the new name to edit\n");
        scanf(" %[^\n]", name);
        strcpy(c->name, name);
        printf("Contact updated Successfully!\n");
        break;

        //Edit mobile number
        case 2:
        do
        {
            flag = 0;
            printf("Enter the new mobile number to edit:\n");
            scanf("%s", number);

            int len = strlen(number);
            // Validate number format
            if (!is_valid_phone(number))
            {
                continue;
            }

            // if mobile number is 10-digit then it is regular contact
            if (len == 10)
            {
                if (!is_duplicate_field(number, addressBook, 1))
                {
                    c->isEmergency = 0;
                    strcpy(c->phone, number);
                    printf("Contact updated successfully!\n");
                    flag = 1;
                }
                else
                {
                    printf("This phone number already exists!\n");
                }
            }
            // If number is 3 or 4 digits — check for emergency
            else if (len == 3 || len == 4)
            {
                char choice;
                printf("Is this an emergency contact? (Y/N): ");
                scanf(" %c", &choice);

                if (choice == 'Y' || choice == 'y')
                {
                    if (!is_duplicate_field(number, addressBook, 1))
                    {
                        c->isEmergency = 1;
                        strcpy(c->phone, number);
                        // set default name for emergency
                        strcpy(c->name, "Emergency");
                        // clear email
                        strcpy(c->email, "-");
                        printf("Emergency contact updated successfully!\n");
                        flag = 1;
                    }
                    else
                    {
                        printf("This phone number already exists!\n");
                    }
                }
                else
                {
                    printf("Only emergency contacts can have 3 or 4 digit numbers.\n");
                }
            }
            else 
            {
                printf("Invalid number length.\n");
            }

        } while (flag == 0);
        break;

        // Edit Email ID 
        case 3:
        do
        {
            flag=0;
            printf("Enter the new email to edit\n");
            scanf("%s", email);
            // Validate email format
            if(is_valid_email(email))
            {
                // Check for duplicates
                if(!is_duplicate_field(email, addressBook, 2))
                {
                    strcpy(c->email, email);
                    printf("Contact updated Successfully!\n");
                    flag=1;
                }
            }
        }while(flag == 0);
        break;

        //add or remove the contact from favourites
        case 4:
        printf("Current Favourite status: %s\n", c->isfavourite ? "Yes" : "No");
        printf("Do you want to mark this as Favourite? (1 = Yes, 0 = No): ");
        int favInput;
        scanf("%d", &favInput);
        if (favInput == 0 || favInput == 1)
        {
            c->isfavourite = favInput;
            printf("Favourite status updated successfully!\n");
        }
        else
        {
            printf("Invalid input. Favourite status unchanged.\n");
        }
        break;

        default:
        printf("Invalid edit option\n");
        break;
    }
    // Print updated contact info
    printf("\nYour edited contact is:\n");
    printf("%-20s | %-15s | %-30s\n", "Name", "Phone", "Email");
    printf("-------------------------------------------------------------\n");
    printf("%-20s | %-15s | %-30s\n", c->name, c->phone, c->email);
}
// Checks if a phone number or email already exists in the address book
int is_duplicate_field(const char *value, AddressBook *addressBook, int fieldType)
{
    for(int i=0; i<addressBook->contactCount; i++)
    {
        // fieldType == 1 -> Phone, fieldType == 2 -> Email
        if((fieldType == 1 && strcmp(addressBook->contacts[i].phone, value) == 0) ||
            (fieldType == 2 && strcmp(addressBook->contacts[i].email, value) == 0))
        {
            if(fieldType == 1)
            printf("This Number already exists!\n");
            else
            printf("This Email already exists!\n");
            return 1;
            // Duplicate found
        }
        return 0;
    }
}
void deleteContact(AddressBook *addressBook)
{
    int indexArray[100], maxCount, selectIndex;
    int deleteoption;
    char input[30], choice;
    // Ask user how they want to search for the contact to delete
    printf("Choose option to delete contact\n");
    printf("1. Name\n2. Mobile Number\n3. Email ID\n");
    scanf("%d", &deleteoption);
    // Take input value for search
    printf("Enter the info to search:\n");
    scanf(" %[^\n]", input);
    // Validate delete option
    if(deleteoption < 1 || deleteoption > 3)
    {
        printf("Invalid choice!Please try again.\n");
        return;
    }
    // Validate input format for phone and email
    if((deleteoption == 2 && !is_valid_phone(input))||
       (deleteoption == 3 && !is_valid_email(input)))
       {
        printf("Invalid input format.\n");
        return;
       }
    // Find matching contacts using helper function
    maxCount = findMatchingContacts(addressBook, deleteoption, input, indexArray);
    // No matches found
    if(maxCount == 0)
    {
        printf("No matching contacts found.\n");
        return;
    }
    // If multiple matches found, ask user to choose which one
    if(maxCount > 1)
    {
        printf("\nMultiple contacts found. choose one to edit (1 to %d):\n", maxCount);
        scanf("%d", &selectIndex);
        if(selectIndex < 1 || selectIndex > maxCount)
        {
            printf("Invalid selection\n");
            return;
        }
        // Convert choice to actual contact index
        selectIndex = indexArray[selectIndex-1];
    }
    else
    {
        // Only one match found
        selectIndex = indexArray[0];
    }
    // Confirm deletion from user
    printf("\nAre you sure to delete contact? (Y/N):\n");
    scanf(" %c", &choice);
    if(choice == 'Y' || choice == 'y')
    {
        // Backup the contact for undo
        lastDeletedContact = addressBook->contacts[selectIndex];
        lastDeletedIndex = selectIndex;
        isDeletedAvailable = 1;
        // Shift contacts to remove the selected on
        for(int i = selectIndex; i < addressBook->contactCount - 1; i++)
        {
            addressBook->contacts[i] = addressBook->contacts[i + 1];
        }
        addressBook->contactCount--;
        printf("Contact deleted successfully.\n");
        // Prompt for immediate undo
        printf("\nDo you want to undo the deletion? (Y/N):\n");
        char undoChoice;
        scanf(" %c", &undoChoice);
        if(undoChoice == 'Y' || undoChoice == 'y')
        {
            undoDelete(addressBook);
        }
        else
        {
            //user can still have an option to restore later
            printf("You can still Restore later from the Recycle bin.\n");
        }
    }
    else
    {
        printf("Delete Cancelled\n");
    }
}
int findMatchingContacts(AddressBook *addressBook, int fieldType, const char *value, int indexArray[])
{
    int maxCount = 0;
    // Loop through all contacts
    for(int i = 0; i < addressBook->contactCount; i++)
    {
        int match = 0;
        // Check match based on field type
        // Case-insensitive name match
        if(fieldType == 1 && strcasestr(addressBook->contacts[i].name, value))
        match = 1;
        // Phone number match (case-sensitive, exact substring)
        else if(fieldType == 2 && strstr(addressBook->contacts[i].phone, value))
        match = 1;
        // Case-insensitive email match
        else if(fieldType == 3 && strcasestr(addressBook->contacts[i].email, value))
        match = 1;
        if(match)
        {
            // Print header only once
            if(maxCount == 0)
            {
                printf("\nMatching Contact(s) for \"%s\":\n\n", value);
                printf("%-5s | %-20s | %-15s | %-30s\n", "S.No", "Name", "Phone", "Email");
                printf("------------------------------------------------------------------------\n");
            }
            // Display matching contact
            printf("%-5d | %-20s | %-15s | %-30s\n", i+1,
            addressBook -> contacts[i].name,
            addressBook -> contacts[i].phone,
            addressBook -> contacts[i].email);
            // Store index of the matching contact
            indexArray[maxCount++] = i;
        }
    }
    // Return how many contacts matched the search
    return maxCount;
}
// Restores the most recently deleted contact if available
void undoDelete(AddressBook *addressBook)
{
    if (isDeletedAvailable)
    {
        printf("\nContact(s) in Recycle Bin:\n");
        printf("%-20s | %-15s | %-30s\n", "Name", "Phone", "Email");
        printf("-------------------------------------------------------------\n");
        printf("%-20s | %-15s | %-30s\n", lastDeletedContact.name, lastDeletedContact.phone, lastDeletedContact.email);

        // Ask user if they want to restore it
        char choice;
        printf("\nDo you want to restore this contact? (Y/N): ");
        scanf(" %c", &choice);

        if (choice == 'Y' || choice == 'y')
        {
            // If address book is full
            if (addressBook->contactCount >= MAX_CONTACTS)
            {
                printf("Cannot restore: Address book is full.\n");
                return;
            }

            for (int i = addressBook->contactCount; i > lastDeletedIndex; i--)
            {
                addressBook->contacts[i] = addressBook->contacts[i - 1];
            }

            // Restore the contact
            addressBook->contacts[lastDeletedIndex] = lastDeletedContact;
            addressBook->contactCount++;

            isDeletedAvailable = 0;
            lastDeletedIndex = -1;

            printf("Undo successful! Contact restored.\n");
        }
        else
        {
            printf("Contact not restored. You can undo later again.\n");
        }
    }
    else
    {
        printf("No recently deleted contact to undo.\n");
    }
}
// Lists all contacts marked as emergency contacts
void listEmergencyContacts(AddressBook *addressBook)
{
    int found = 0;
    printf("\n----Emergency contacts----\n");
    printf("\n-------------------------------------------------------------\n");
    printf("| %-4s | %-20s | %-15s | %-20s\n", "S.No", "Name", "Phone", "Email");
    printf("\n-------------------------------------------------------------\n");
    int serial = 1;
    // Loop through address book and print emergency contacts
    for(int i = 0; i < addressBook->contactCount; i++)
    {
        if(addressBook->contacts[i].isEmergency == 1)
        {
            printf("| %-4d | %-20s | %-15s | %-20s\n",
                serial,
                addressBook->contacts[i].name,
                addressBook->contacts[i].phone,
                addressBook->contacts[i].email);
                serial++;
                found = 1;
        }
    }
    printf("-------------------------------------------------------------\n");
    // If no emergency contacts found
    if(!found)
    {
        printf("| %-62s\n", "No emergency contacts found");
    }
}
// Lists all contacts marked as favourites
void listFavouriteContacts(AddressBook *addressBook)
{
    int found = 0;
    int serial = 1;
    printf("\n----Favourite contacts----\n");
    printf("\n-----------------------------------------------------------------\n");
    printf("| %-4s | %-20s | %-15s | %-20s\n", "S.No", "Name", "Phone", "Email");
    printf("------------------------------------------------------------------\n");
    // Loop through address book and print favourite contacts
    for(int i = 0; i < addressBook->contactCount; i++)
    {
        if(addressBook->contacts[i].isfavourite == 1)
        {
            printf("| %-4d | %-20s | %-15s | %-20s\n",
                serial++,
                addressBook->contacts[i].name,
                addressBook->contacts[i].phone,
                addressBook->contacts[i].email);
                found = 1;
        }
    }
    printf("------------------------------------------------------------------\n");
    // If no favourite contacts foun
    if(!found)
    {
        printf("| %-62s\n", "No Favourite contacts found");
    }
}
