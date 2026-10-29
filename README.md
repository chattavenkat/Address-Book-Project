Project Description
The Address Book Management System is a menu-driven C application used to store and manage personal contact information. Each contact contains a name, mobile number, and email address.

The application can store up to 100 contacts and uses a CSV file (AddressBook.csv) to save contact details between program runs.
Features
- Create Contact — Add a new contact.
- Search Contact — Search by name, mobile number, or email address.
- Edit Contact — Update a contact's name, mobile number, or email address.
- Delete Contact — Delete a contact using its name, mobile number, or email address.
- List Contacts — Display all stored contacts.
- Sort Contacts — Sort contacts by name, mobile number, or email address.
- Input Validation — Validate contact details before saving.
- Duplicate Prevention — Prevent duplicate mobile numbers and email addresses when creating or editing contacts.
- CSV File Handling — Load previously saved contacts at startup and save contact details to AddressBook.csv.
Validation Rules
Name
- Must contain at least 3 characters.
- Should contain alphabetic characters and spaces.
- The current implementation allows up to 3 spaces.
- The program provides up to 3 attempts for input.
Mobile Number
- Must contain exactly 10 digits.
- The first digit must be between 6 and 9.
- Must contain digits only.
- Must be unique across contacts.
Email Address
- Must contain one @ symbol.
- Must contain one dot after the @ symbol.
- Must end with .com.
- Must not duplicate another contact's email address.
- The program provides up to 3 attempts for input.
Note: These are the validation rules implemented in the supplied code; email validation is intentionally limited and is not a complete check of every valid email format.

Menu Options
1. Create Contact
2. Search Contact
3. Edit Contact
4. Delete Contact
5. List All Contacts
6. Exit
The search, edit, and delete operations provide submenus for selecting the contact field to use.
Technologies and C Concepts Used
- Structures (struct)
- Arrays
- Pointers
- Functions
- Strings and string-handling functions
- Conditional statements and loops
- Searching and sorting
- Input validation
- File handling (fopen, fscanf, fprintf, fclose)
- CSV data storage
Project Files
The project uses multiple C source and header files. The supplied code references these files:
File	Purpose
contact.h	Defines the Contact and AddressBook structures, MAX_CONTACTS, and function declarations.
file.h	Declares the file-loading and file-saving functions.
File-handling source file (for example, file.c)	Saves contacts to and loads contacts from AddressBook.csv.
Main program source file	Runs the main menu and dispatches the selected operation.
Contact operations source file(s)	Implements creating, searching, editing, deleting, listing, and sorting contacts.


The exact source filenames may differ depending on how the project is organized.
Build and Run
Compile all required project .c files together, using your compiler and the actual filenames in your repository.

Example with GCC (replace the placeholders with your source filenames):
gcc main.c contact.c file.c -o address_book
If your contact operations are stored in a different file, include that file in the command as well. Do not compile header files separately.

Run on Linux or macOS:
./address_book
Run on Windows (Command Prompt):
address_book.exe
Important: The compile command is an example. Update it to match the .c files included in your repository.
Data Storage
Contact details are stored in AddressBook.csv in comma-separated format:
Name,MobileNumber,Email
Example Person,9876543210,example@example.com
The supplied file-handling code writes records without a header row, so the example above illustrates the general CSV format rather than the exact output produced by the current implementation. The program loads saved records from AddressBook.csv when it initializes and writes records when the save function is called.

Keep AddressBook.csv in the program's working directory so the application can find it.
Future Enhancements
- Improve email validation to support more valid email formats.
- Add safer input handling to prevent buffer overflows.
- Add case-insensitive sorting and more flexible search options.
- Improve CSV parsing to handle commas or quotation marks inside fields.
- Add automated tests and clearer error handling.
Author
Chatta Venkata Narasimha
Project: Address Book Management System in C
