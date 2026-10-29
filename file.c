#include <stdio.h>
#include "file.h"

void saveContactsToFile(AddressBook *addressBook) {
    FILE* fp = fopen("AddressBook.csv", "w");
    if(fp == NULL){
        printf("Unable to open AddressBook file\n\n");
        return;
    }
    for(int i = 0; i < addressBook->contactCount; i++){
        fprintf(fp, "%s,", addressBook->contacts[i].name);
        fprintf(fp, "%s,", addressBook->contacts[i].phone);
        fprintf(fp, "%s\n", addressBook->contacts[i].email);
    }
    fclose(fp);
}

void loadContactsFromFile(AddressBook *addressBook) {
    FILE* fp = fopen("AddressBook.csv", "r");
    if(fp == NULL){
        printf("File Doesn't Exists\n");
        return;
    }
    int i = 0;
    while(i < MAX_CONTACTS && (fscanf(fp, "%49[^,],%19[^,],%49[^\n]\n", 
        addressBook->contacts[i].name, 
        addressBook->contacts[i].phone, 
        addressBook->contacts[i].email) == 3)){
        i++;
    }
    addressBook->contactCount = i;
    fclose(fp);
}
