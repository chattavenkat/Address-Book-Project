#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "contact.h"
#include "file.h"
#include "populate.h"

void listContacts(AddressBook *addressBook, int sortCriteria) 
{
    // Sort contacts based on the chosen criteria
    Contact temp;
    for(int i = 0; i < addressBook->contactCount - 1; i++){
        for(int j = 0; j < addressBook->contactCount - i - 1; j++){
            int flag = 0;
            switch(sortCriteria){
                case 1:
                    if(strcmp(addressBook->contacts[j].name, addressBook->contacts[j + 1].name) > 0){
                        flag = 1;
                    }
                    break;
                case 2:
                    if(strcmp(addressBook->contacts[j].phone, addressBook->contacts[j + 1].phone) > 0){
                        flag = 1;
                    }
                    break;
                case 3:
                    if(strcmp(addressBook->contacts[j].email, addressBook->contacts[j + 1].email) > 0){
                        flag = 1;
                    }
                    break;
            }
            if(flag == 1){
                temp = addressBook->contacts[j];
                addressBook->contacts[j] = addressBook->contacts[j + 1];
                addressBook->contacts[j + 1]= temp;
            }
        }
    }
    printf("================================================ Contacts ==========================================================\n");
    printf("%-15s%-30s%-30s%-30s\n", "SI. No", "Contact Name", "Mobile Number", "Email");
    for(int i = 0; i < addressBook->contactCount; i++){
        printf("%-15d", i + 1);
        printf("%-30s", addressBook->contacts[i].name);
        printf("%-30s", addressBook->contacts[i].phone);
        printf("%-30s\n", addressBook->contacts[i].email);
    }
    printf("===================================================================================================================\n");
}
void initialize(AddressBook *addressBook) {
    addressBook->contactCount = 0;
    //populateAddressBook(addressBook);
    
    // Load contacts from file during initialization (After files)
    loadContactsFromFile(addressBook);
}
void saveAndExit(AddressBook *addressBook) {
    saveContactsToFile(addressBook); // Save contacts to file
    exit(EXIT_SUCCESS); // Exit the program
}
void createContact(AddressBook *addressBook)
{
	/* Define the logic to create a Contacts */
    if(addressBook -> contactCount >= MAX_CONTACTS){
        printf("\nStorage limit Exicedes.....\n");
        return;
    }
    Contact *c = &addressBook->contacts[addressBook->contactCount];
    int attempts = 0, name_flag = 0, ph_flag = 0, email_flag = 0, space = 0;
    // Contact Name 
    while(attempts < 3){
        printf("Enter a name : ");
        scanf(" %[^\n]", c->name);
        int flag = 1, i = 0;
        int len = strlen(c->name);
        if(len >= 3){ // checking the above 3 character names
            while(c->name[i] != '\0'){
                if(isalpha(c->name[i])){ // checking not a alphabets, above 3 spaces
                    flag = 1;
                }else if(isspace(c->name[i])){
                    space++;
                    if(space > 3){// maximum 3 spaces
                        flag = 0;
                        printf("Invalid ! Name contains more than 3 spaces\n\n");
                        break;
                    }
                }else{
                    flag = 0;
                    printf("Invalid! Name should contain only alphabets\n\n");
                    break;
                }
                i++;
            }
            if(flag == 1){
                //printf("%s\n", str);
                name_flag = 1;
                break;
            }
        }else{
            printf("Invalid! Name must contain at least 3 characters\n\n");
        }
        attempts++;
        if(attempts < 3){
            printf("%d Remaining attempts\n\n", 3 - attempts);
        }
    }
    if(name_flag != 1){
        printf("Maximum Attempts Exceeds\n\n");
        return;
    }
    // Mobile Number
    attempts = 0;
    while(attempts < 3){
        printf("Enter a Phone Number : ");
        scanf(" %[^\n]", c->phone);
        int len = strlen(c->phone);
        if(len != 10){
            printf("Invalid, Please enter only 10 digits\n\n");
        }else if(c->phone[0] < '6' || c->phone[0] > '9'){
            printf("Invalid! First digit must be between 6 and 9\n\n");
        }else{
            int flag = 1;
            for(int i = 0; c->phone[i] != '\0'; i++){
                if(!isdigit(c->phone[i])){
                    flag = 0;
                    break;
                }
            }
            if(flag == 0){
                printf("Invalid, phone number contains non-digit characters\n\n");
            }else{
                ph_flag = 1;
                for(int i = 0; i < addressBook->contactCount; i++){
                    if(strcmp(addressBook->contacts[i].phone, c->phone) == 0){
                        ph_flag = 0;
                        break;
                    }
                }
                if(ph_flag){
                    break;      
                }else{
                    printf("Mobile Number Already Exists!!\n\n");
                }
            }
        }
        attempts++;
        if(attempts < 3){
            printf("%d Remaining attempts\n\n", 3 - attempts);
        }
    }
    if(ph_flag != 1){
        printf("Maximum Attempts Exceeds\n\n");
        return;
    }
    // Contact Email
    attempts = 0;
    while(attempts < 3){
        printf("Enter a Email ID : ");
        scanf(" %[^\n]", c->email);
        int len = strlen(c->email);
        int at_count = 0, dot_count = 0, at = -1, dot = -1, flag = 1;
        for(int i = 0; i < len; i++){
            //not a alphabets and numbers or not a @ or not a . it will be error
            if(!(isalnum(c->email[i]) || c->email[i] == '@' || c->email[i] == '.')){
                flag = 0;
                printf("Inavlid Symbols\n\n");
                break;
            }
        }
        //checking the how many @ symbols in the email
        for(int i = 0; i < len; i++){
            if(c->email[i] == '@'){
                at_count++;
                at = i;
            }
        }
        // checking the after @ how many dots in the email
        for(int i = at + 1; i < len; i++){
            if(c->email[i] == '.'){
                dot = i;
                dot_count++;
            }
        }
        int last_len = len - 4; // checking for .com
        if(flag){
            for(int i = 0; i < addressBook->contactCount; i++){
                if(strcmp(addressBook->contacts[i].email, c->email) == 0){
                    flag = 0;
                    printf("Email is Already Exits ! Please Enter a unique Email\n\n");
                    break;
                }
            }
            if(at == 0){
                flag = 0;
                printf("Missing the user name\n\n");
            }else if(at_count != 1){
                if(at_count == 0){
                    flag = 0;
                    printf("Missing @ from the email \n\n");
                }else if(at_count > 1){
                    flag = 0;
                    printf("Multiple @ from the email\n\n");
                }
            }else if(dot_count != 1){
                if(dot_count == 0){
                    flag = 0;
                    printf("Missing  .  after @ \n\n");
                }else if(dot_count > 1){
                    flag = 0;
                    printf("Multiple . after @\n\n");
                }
            }else if(dot - at <= 1) {
                flag = 0;
                printf("b / w @ and . no charcter \n\n");
            }else if (len < 4 || strcmp(c->email + len - 4, ".com") != 0){
                printf("Missing or Extra characters after the .com\n\n");
                    flag = 0;
            }
        }
        if(flag == 1){
            email_flag = 1;
            break;
        }
        attempts++;
        if(attempts < 3){
            printf("%d Remaining attempts\n\n", 3 - attempts);
        }
    }
    if(email_flag != 1){
        printf("Maximum Attempts Exceeds\n\n");
        return;
    }
    if(name_flag == 1 && ph_flag == 1 && email_flag == 1){
        addressBook->contactCount++;
        printf("Contact Created Successfully\n\n");
    }
}
void searchContact(AddressBook *addressBook) 
{
    /* Define the logic for search */
    int op;
    int flag  = 1;
    while(flag){
        printf("1. Search Name\n2. Search Mobile Number\n3. Search Email\n4. Exit\n");
        printf("Please Choose option : ");
        if (scanf("%d", &op) != 1){
            printf("Invalid input. Please enter a number.\n");
            while (getchar() != '\n');
            return;
        }
        switch(op){
            case 1:
                char c_name[50];
                int n_flag = 0;
                printf("Enter a Searching name : ");
                scanf(" %[^\n]", c_name);
                printf("%-15s%-30s%-30s%-30s\n", "SI. No", "Contact Name", "Mobile Number", "Email");
                for(int i = 0; i < addressBook->contactCount; i++){
                    if(strcasestr(addressBook->contacts[i].name, c_name) != NULL){ // if(strcmp(c[i].name, c_name) == 0)
                        n_flag++;
                        printf("%-15d%-30s%-30s%-30s\n", i + 1, addressBook->contacts[i].name, addressBook->contacts[i].phone, addressBook->contacts[i].email);
                    }
                }
                if(n_flag == 0){
                    printf("Your Searching Name is not in the contact details\n\n");
                }
                break;
            case 2:
                char c_ph[20];
                int p_flag = 0;
                printf("Enter a Searching Mobile Number : ");
                scanf(" %[^\n]", c_ph);
                printf("%-15s%-30s%-30s%-30s\n", "SI. No", "Contact Name", "Mobile Number", "Email");
                for(int i = 0; i < addressBook->contactCount; i++){
                    if(strstr(addressBook->contacts[i].phone, c_ph) != NULL){ //if(strcmp(c[i].ph, c_ph) == 0)
                        p_flag++;
                        printf("%-15d%-30s%-30s%-30s\n", i + 1, addressBook->contacts[i].name, addressBook->contacts[i].phone, addressBook->contacts[i].email);
                    }
                }
                if(p_flag == 0){
                    printf("Your Searching Mobile Number is not in the contact details\n\n");
                }
                break;
            case 3:
                char c_email[50];
                int e_flag = 0;
                printf("Enter Searching Email: ");
                scanf(" %[^\n]", c_email);
                printf("%-15s%-30s%-30s%-30s\n", "SI. No", "Contact Name", "Mobile Number", "Email");
                for(int i = 0; i < addressBook->contactCount; i++){
                    if(strstr(addressBook->contacts[i].email, c_email) != NULL){ //if(strcmp(c[i].email, c_email) == 0)
                        e_flag++;
                        printf("%-15d%-30s%-30s%-30s\n", i + 1, addressBook->contacts[i].name, addressBook->contacts[i].phone, addressBook->contacts[i].email);
                    }
                }
                if(e_flag == 0){
                    printf("Your Searching Email is not in the contact details\n\n");
                }
                break;
            case 4:
                flag = 0;
                break;
            default:
                printf("Invalid Choice. Please try again.\n\n");
                break;
        }
        if(flag != 0){
            printf("Do You want to continue for searching (1. Yes 0. No) : ");
            scanf("%d", &flag);
        }
    } 
}
void editContact(AddressBook *addressBook)
{
	/* Define the logic for Editcontact */
    int op, flag = 1;
    while(flag){
        printf("1. Edit Name\n2. Edit Mobile Number\n3. Edit Email\n4. Exit\n");
        printf("Please Choose option : ");
        if (scanf("%d", &op) != 1){
            printf("Invalid input. Please enter a number.\n");
            while (getchar() != '\n');
            return;
        }
        switch(op){
            case 1:
                editName(addressBook);
                break;
            case 2:
                editMobileNumber(addressBook);
                break;
            case 3:
                editEmail(addressBook);
                break;
            case 4:
                flag = 0;
                break;
            default:
                printf("Invalid choice. Please try again.\n\n");
                break;
        }
        if(flag != 0){
            printf("Do You want to continue for searching (1. Yes 0. No) : ");
            scanf("%d", &flag);
        }
    }
}
void editName(AddressBook *addressBook){
    // Editing name 
    char c_name[50];
    printf("Enter a Searching name : ");
    scanf(" %[^\n]", c_name);
    int count = 0; //Matching Names Count;
    int match_name[20];
    printf("%-15s%-30s%-30s%-30s\n", "SI. No", "Contact Name", "Mobile Number", "Email");
    for(int i = 0; i < addressBook->contactCount; i++){
        if(strcasestr(addressBook->contacts[i].name, c_name) != NULL){ // if(strstr(c[i].name, c_name) == 0L)
            match_name[count] = i;
            count++;
            printf("%-15d%-30s%-30s%-30s\n", i + 1, addressBook->contacts[i].name, addressBook->contacts[i].phone, addressBook->contacts[i].email);
        }
    }
    int choice, index;
    if(count == 1){
        index = match_name[0];
    }else{
        printf("Enter a which index you want to editing name : ");
        scanf("%d",&choice);
        if(choice < 1 || choice > count)   {
            printf("Invalid choice\n");
            return;
        }
        index = match_name[choice - 1];
    }
    int attempts = 0, name_flag = 0;
    if(index != -1){
        // Name Validation
        char edit_name[50];
        while(attempts < 3){
            printf("Enter a Editing name : ");
            scanf(" %[^\n]", edit_name);
            int flag = 1, i = 0, space = 0;
            int len = strlen(edit_name);
            if(len >= 3){ // checking the above 3 character names
                while(edit_name[i] != '\0'){
                    if(isalpha(edit_name[i])){ // checking not a alphabets, above 3 spaces
                        flag = 1;
                    }else if(isspace(edit_name[i])){
                        space++;
                        if(space > 3){// maximum 3 spaces
                            flag = 0;
                            printf("Invalid ! Name contains more than 3 spaces\n\n");
                            break;
                        }
                    }else{
                        flag = 0;
                        printf("Invalid input ! name is included in the numric / speacial characters\n\n");
                        break;
                    }
                    i++;
                }
                if(flag == 1){
                    //printf("%s\n", str);
                    name_flag = 1;
                    break;
                }
            }else{
                printf("Invalid input ! name is below 3 characters\n\n");
            }
            attempts++;
            if(attempts < 3){
                printf("%d Remaining attempts\n\n", 3 - attempts);
            }
        }
        if(name_flag != 1){
            printf("Maximum Attempts Exceeds\n\n");
            return;
        }else{
            strcpy(addressBook->contacts[index].name, edit_name);
            printf("Editing name Successfully\n\n");
        }
    }else{
        printf("Your Searching Name is not in the contact details\n\n");
    }
}
void editMobileNumber(AddressBook *addressBook){
    //Editing Mobile Number
    char c_ph[20];
    int index = -1;
    printf("Enter a Searching Mobile Number : ");
    scanf(" %[^\n]", c_ph);
    for(int i = 0; i < addressBook->contactCount; i++){
        if(strcmp(addressBook->contacts[i].phone, c_ph) == 0){ //if(strstr(c[i].ph, c_ph) != NULL)
            index = i;
        }
    }
    if(index != -1){
        //Mobile Validation
        int attempts = 0, ph_flag = 0;
        char edit_ph[20];
        while(attempts < 3){
            printf("Enter a Phone Number : ");
            scanf(" %[^\n]", edit_ph);
            int len = strlen(edit_ph);
            if(len != 10){
                printf("Invalid, Please enter only 10 digits\n\n");
            }else if(edit_ph[0] < '6' || edit_ph[0] > '9'){
                printf("Invalid, first digit must be between 6 and 9\n\n");
            }else{
                int flag = 1;
                for(int i = 0; edit_ph[i] != '\0'; i++){
                    if(!isdigit(edit_ph[i])){
                        flag = 0;
                        break;
                    }
                }
                if(flag == 0){
                    printf("Invalid, phone number contains non-digit characters\n\n");
                }else{
                    ph_flag = 1;
                    for(int i = 0; i < addressBook->contactCount; i++){
                        if(i != index && strcmp(addressBook->contacts[i].phone, edit_ph) == 0){
                            ph_flag = 0;
                            break;
                        }
                    }
                    if(ph_flag){
                        break;      
                    }else{
                        printf("Mobile Number Already Exists!!\n\n");
                    }
                }
            }
            attempts++;
            if(attempts < 3){
                printf("%d Remaining attempts\n\n", 3 - attempts);
            }
        }
        if(ph_flag != 1){
            printf("Maximum Attempts Exceeds\n\n");
            return;
        }else{
            strcpy(addressBook->contacts[index].phone, edit_ph);
            printf("Editing Mobile Number Successfully\n\n");
        }
    }else{
        printf("Your Searching Mobile Number is not in the contact details\n\n");
    }
}
void editEmail(AddressBook *addressBook){
    //Editing Email Id
    char c_email[50];
    int index = -1;
    printf("Enter a Searching Email : ");
    scanf(" %[^\n]", c_email);
    for(int i = 0; i < addressBook->contactCount; i++){
        if(strcmp(addressBook->contacts[i].email, c_email) == 0){ //if(strstr(c[i].email, c_email) != NULL)
            index = i; 
        }
    }
    if(index != -1){
        // Contact Email
        char edit_email[50];
        int attempts = 0, email_flag = 0;
        while(attempts < 3){
            printf("Enter a Edit Email ID : ");
            scanf(" %[^\n]", edit_email);
            int len = strlen(edit_email);
            int at_count = 0, dot_count = 0, at = -1, dot = -1, flag = 1;
            for(int i = 0; i < len; i++){
                //not a alphabets and numbers or not a @ or not a . it will be error
                if(!(isalnum(edit_email[i]) || edit_email[i] == '@' || edit_email[i] == '.')){
                    flag = 0;
                    printf("Inavlid Symbols\n\n");
                    break;
                }
            }
            //checking the how many @ symbols in the email
            for(int i = 0; i < len; i++){
                if(edit_email[i] == '@'){
                    at_count++;
                    at = i;
                }
            }
            // checking the after @ how many dots in the email
            for(int i = at + 1; i < len; i++){
                if(edit_email[i] == '.'){
                    dot_count++;
                    dot = i;
                }
            }
            int last_len = len - 4; // checking for .com
            if(flag){
                for(int i = 0; i < addressBook->contactCount; i++){
                    if(i != index && strcmp(addressBook->contacts[i].email, edit_email) == 0){
                        flag = 0;
                        printf("Email is Already Exits ! Please Enter a unique Email\n\n");
                        break;
                    }
                }
                if(at == 0){
                    flag = 0;
                    printf("Missing the user name\n\n");
                }else if(at_count != 1){
                    if(at_count == 0){
                        flag = 0;
                        printf("Missing @ from the email \n\n");
                    }else if(at_count > 1){
                        flag = 0;
                        printf("Multiple @ from the email\n\n");
                    }
                }else if(dot_count != 1){
                    if(dot_count == 0){
                        flag = 0;
                        printf("Missing  .  after @ \n\n");
                    }else if(dot_count > 1){
                        flag = 0;
                        printf("Multiple . after @\n\n");
                    }
                }else if(dot - at <= 1) {
                    flag = 0;
                    printf("b / w @ and . no charcter \n\n");
                }else if (len < 4 || strcmp(edit_email + len - 4, ".com") != 0){
                    printf("Missing or Extra characters after the .com\n\n");
                        flag = 0;
                }
            }
            if(flag == 1){
                //printf("%s\n", email);
                email_flag = 1;
                break;
            }
            attempts++;
            if(attempts < 3){
                printf("%d Remaining attempts\n\n", 3 - attempts);
            }
        }
        if(email_flag != 1){
            printf("Maximum Attempts Exceeds\n\n");
            return;
        }else{
            strcpy(addressBook->contacts[index].email, edit_email);
            printf("Editing Email is Successfully\n\n");
        }
    }else{
        printf("Your Searching Email is not in the contact details\n\n");
    }
}
void deleteContact(AddressBook *addressBook){
	/* Define the logic for deletecontact */
   int op, flag = 1, index;
    while(flag){
        printf("1. Delete Name\n2. Delete Mobile Number\n3. Delete Email\n4. Exit\n");
        printf("Please Choose option : ");
        if (scanf("%d", &op) != 1){
            printf("Invalid input. Please enter a number.\n");
            while (getchar() != '\n');
            return;
        }
        switch(op){
            case 1:
                char c_name[50];
                printf("Enter a Deleting name : ");
                scanf(" %[^\n]", c_name);
                int count = 0; //Matching Names Count;
                int match_name[20];
                printf("%-15s%-30s%-30s%-30s\n", "SI. No", "Contact Name", "Mobile Number", "Email");
                for(int i = 0; i < addressBook->contactCount; i++){
                    if(strstr(addressBook->contacts[i].name, c_name) != NULL){ // if(strcmp(c[i].name, c_name) == 0)
                        match_name[count] = i;
                        count++;
                        printf("%-15d%-30s%-30s%-30s\n", i + 1, addressBook->contacts[i].name, addressBook->contacts[i].phone, addressBook->contacts[i].email);
                    }
                }
                int choice, index;
                if(count == 1){
                    index = match_name[0];
                }else if(count != 0 && count != 1){
                    printf("Enter a which index you want to deleting name : ");
                    scanf("%d",&choice);
                    if(choice < 1 || choice > count)   {
                        printf("Invalid choice\n");
                        return;
                    }
                    index = match_name[choice - 1];
                }else{
                    printf("There is No data\n\n");
                    return;
                }
                if(index != -1){
                    printf("Deleted Name Successfully\n\n");
                    for(int i = index; i < addressBook->contactCount - 1; i++){
                        strcpy(addressBook->contacts[i].name, addressBook->contacts[i + 1].name);
                        strcpy(addressBook->contacts[i].phone, addressBook->contacts[i + 1].phone);
                        strcpy(addressBook->contacts[i].email, addressBook->contacts[i + 1].email);
                    }
                    addressBook->contactCount--;
                }else{
                    printf("Your Deleting Name is not in the contact details\n\n");
                }
                break;
            case 2:
                char c_ph[20];
                index = -1;
                printf("Enter a Deleting Mobile Number : ");
                scanf(" %[^\n]", c_ph);
                for(int i = 0; i < addressBook->contactCount; i++){
                    if(strcmp(addressBook->contacts[i].phone, c_ph) == 0){ //if(strstr(c[i].ph, c_ph) != NULL)
                        index = i;
                        printf("Deleted Mobile Number Successfully\n\n");
                    }
                }
                if(index != -1){
                    for(int i = index; i < addressBook->contactCount - 1; i++){
                        strcpy(addressBook->contacts[i].name, addressBook->contacts[i + 1].name);
                        strcpy(addressBook->contacts[i].phone, addressBook->contacts[i + 1].phone);
                        strcpy(addressBook->contacts[i].email, addressBook->contacts[i + 1].email);
                    }
                    addressBook->contactCount--;
                }else{
                    printf("Your Deleting Mobile Number is not in the contact details\n\n");
                }
                break;
            case 3:
                char c_email[50];
                index = -1;
                printf("Enter a Deleting Email : ");
                scanf(" %[^\n]", c_email);
                for(int i = 0; i < addressBook->contactCount; i++){
                    if(strcmp(addressBook->contacts[i].email, c_email) == 0){ //if(strstr(c[i].email, c_email) != NULL)
                        index = i;
                        printf("Deleted Email Successfully\n\n");
                    }
                }
                if(index != -1){
                    for(int i = index; i < addressBook->contactCount - 1; i++){
                        strcpy(addressBook->contacts[i].name, addressBook->contacts[i + 1].name);
                        strcpy(addressBook->contacts[i].phone, addressBook->contacts[i + 1].phone);
                        strcpy(addressBook->contacts[i].email, addressBook->contacts[i + 1].email);
                    }
                    addressBook->contactCount--;
                }else{
                    printf("Your Deleting Email is not in the contact details\n\n");
                }
                break;
            case 4:
                flag = 0;
                break;
            default:
                printf("Invalid choice. Please try again.\n\n");
        }
        if(flag != 0){
            printf("Do You Want to you continue (1. Yes, 0. No) : ");
            scanf("%d", &flag);
        }
    }
}