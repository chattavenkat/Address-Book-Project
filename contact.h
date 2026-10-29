/*
Name :- Chatta Venkata Narasimha
Batch No :- 26015B
Date :- 29/08/2026
PROJECT :- ADDRESS BOOk

DESCRIPTION :- 
    This is a Personal Digital Book used to store the basic details of a person like NAME, PHONE NUMBER, and EMAIL ID.
In this program, we can store up to 100 contacts. The program provides a menu with the
following options:
    1. Create contact
    2. Search contact
    3. Edit contact
    4. Delete contact
    5. List all contacts
    6. Exit
    By selecting the required option, the user can proceed further based on their choice.
Each operation provides an option to exit and return back to the main menu if the user does not want to continue. The system has 
input validation features for NAME, PHONE NUMBER, and EMAIL ID. The name should contain valid characters, the phone number should 
contain 10 digits and start with a number between 6 and 9, and the email should follow the specified email format. The system also 
provides a feature to store only unique contact details. Duplicate PHONE NUMBERS and EMAIL IDs are not allowed while creating or 
editing a contact.

    The SEARCH option allows the user to search contacts using NAME, PHONE NUMBER,
or EMAIL ID. 
    The EDIT option allows the user to modify the NAME, PHONE NUMBER, or EMAIL ID
of an existing contact.
    The DELETE option allows the user to delete a contact using NAME, PHONE NUMBER,
or EMAIL ID.
    The LIST option displays all the stored contacts. The contacts can also be sorted
based on NAME, PHONE NUMBER, or EMAIL ID.
    The program also uses FILE HANDLING to save the contact details into a CSV file. When
the program starts, the previously saved contacts are loaded from the file. Therefore, the 
contact details are maintained even after the program is closed.

This project demonstrates important C programming concepts such as STRUCTURES,
ARRAYS, POINTERS, FUNCTIONS, STRINGS, FILE HANDLING, SEARCHING, SORTING,
and INPUT VALIDATION.
*/
#ifndef CONTACT_H
#define CONTACT_H

#define MAX_CONTACTS 100

typedef struct {
    char name[50];
    char phone[20];
    char email[50];
} Contact;

typedef struct {
    Contact contacts[MAX_CONTACTS];
    int contactCount;
} AddressBook;

void createContact(AddressBook *addressBook);
void searchContact(AddressBook *addressBook);
void editContact(AddressBook *addressBook);
void editName(AddressBook *addressBook);
void editMobileNumber(AddressBook *addressBook);
void editEmail(AddressBook *addressBook);
void deleteContact(AddressBook *addressBook);
void listContacts(AddressBook *addressBook, int sortCriteria);
void initialize(AddressBook *addressBook);
void saveContactsToFile(AddressBook *AddressBook);

#endif
