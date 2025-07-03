#include "contact.h"

Contact lastDeletedContact;
int isDeletedAvailable = 0;
int lastDeletedIndex = -1;

int main() 
{
    int choice;
    AddressBook addressBook;
	// Initialize the AddressBook
    initialize(&addressBook);

    do 
    {
	printf("\nAddress Book Menu:\n");
	printf("1. Create contact\n");
	printf("2. Search contact\n");
	printf("3. Edit contact\n");
	printf("4. Delete contact\n");
	printf("5. List all contacts\n");
	printf("6. List all Emergency contacts\n");
	printf("7. List all Favourite contacts\n");
	printf("8. Recycle bin\n");
	printf("9. Exit\n");
	printf("Enter your choice: ");
	scanf("%d", &choice);

	switch (choice) 
	{
	    case 1:
		// Add new contact
		createContact(&addressBook);
		break;
	    case 2:
		// Search contacts
		searchContact(&addressBook);
		break;
	    case 3:
		// Modify existing contact
		editContact(&addressBook);
		break;
	    case 4:
		// Delete a contact
		deleteContact(&addressBook);
		break;
	    case 5:
		// List all contacts
		listContacts(&addressBook);
		break;
		case 6:
		// Show emergency contacts
		listEmergencyContacts(&addressBook);
		break;
		case 7:
		// Show favourites
		listFavouriteContacts(&addressBook);
		break;
		case 8:
		// Undo delete if possible
		undoDelete(&addressBook);
		break;
	    case 9:
		// Save on exit
		printf("Saving and Exiting...\n");
		saveContactsToFile(&addressBook);
		break;
	    default:
		// Input out of range
		printf("Invalid choice. Please try again.\n");
	}
    } while (choice != 9);

	// Cleanup any resources before exiting
    //cleanup();
    return 0;
}
