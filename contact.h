#ifndef CONTACT_H
#define CONTACT_H 
#include<stdio.h>

// Maximum number of contacts the addressbook can store
#define MAX_CONTACTS 100

typedef struct Contact{
    char name[50];
    char phone[20];
    char email[50];
    int isEmergency;
    int isfavourite;
} Contact;

typedef struct {
    // array holdong all contacts
    Contact contacts[MAX_CONTACTS];
    // Number of currently stored contacts
    int contactCount;
} AddressBook;

void listFavouriteContacts(AddressBook *addressBook);
void listEmergencyContacts(AddressBook *addressBook);
void undoDelete(AddressBook *addressBook);
void createContact(AddressBook *addressBook);
void searchContact(AddressBook *addressBook);
void editContact(AddressBook *addressBook);
void deleteContact(AddressBook *addressBook);
void listContacts(AddressBook *addressBook);
void initialize(AddressBook *addressBook);
void saveContactsToFile(AddressBook *addressBook);
void loadContactsFromFile(AddressBook *addressBook);
int is_valid_phone(char* number);
int is_valid_email(char* email);
void edit(Contact *c, AddressBook *addressBook);
int is_duplicate_field(const char *value, AddressBook *addressBook, int fieldType);
int findMatchingContacts(AddressBook *addressBook, int fieldType, const char *value, int indexArray[]);

#endif
