#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "contact.h"
#include<ctype.h>
//#include "file.h"

void listContacts(AddressBook *addressBook) 
{
    // Sort contacts based on the chosen criteria
    if(addressBook->contactCount==0)
    {
        printf("No Contact Found");
    }
    else{
        printf("Listing all contacts\n");
        printf("Name\tPhone Number\tEmail\n");
        for(int i=0;i<addressBook->contactCount;i++)
        {
            printf(" %s\t",addressBook->contacts[i].name);
            printf(" %s\t",addressBook->contacts[i].phone);
            printf(" %s\t",addressBook->contacts[i].email);
            printf("\n");
        }
    }


    
}

void initialize(AddressBook *addressBook) {
    // populateAddressBook(addressBook);
    addressBook->contactCount = 0;
    FILE *fptr = fopen("contacts.txt", "r");

    if (fptr == NULL) {
        printf("File is not present\n");
        return;
    }

    char data[1000];
    while(fscanf(fptr,"%[^\n]",data) == 1 )
    {
        char *name=strtok(data,",");
        char *phone=strtok(NULL,",");
        char *email=strtok(NULL,"\n");
        if(name && phone && email && addressBook->contactCount<100)
        {
            strcpy(addressBook->contacts[addressBook->contactCount].name,name);
            strcpy(addressBook->contacts[addressBook->contactCount].phone,phone);
            strcpy(addressBook->contacts[addressBook->contactCount].email,email);
            addressBook->contactCount++;
        }
        fseek(fptr,1,SEEK_CUR);

    }
    fclose(fptr);
    
    
    // Load contacts from file during initialization (After files)
    //loadContactsFromFile(addressBook);
}

void saveAndExit(AddressBook *addressBook) {
   saveContactsToFile(addressBook); // Save contacts to file
    
}

void saveContactsToFile(AddressBook *addressBook) {
   FILE *ptr = fopen("contacts.txt", "w");  
    if(ptr == NULL)
    {
        printf("Error: Could not open file\n");
        return;
    }

    
    for(int i = 0; i < addressBook->contactCount; i++)
    {
        fprintf(ptr,"%s,",addressBook->contacts[i].name);  
        fprintf(ptr,"%s,",addressBook->contacts[i].phone); 
        fprintf(ptr,"%s\n",addressBook->contacts[i].email); 
        putc('\n', ptr);  
    }

    fclose(ptr);
    printf("Contacts saved to file successfully\n"); 
}


void createContact(AddressBook *addressBook)
{
	/* Define the logic to create a Contacts */
    char inputName[50];
    char inputPhone[20];
    char inputEmail[50];
    int flag = 0,flag1=0,flag2=0;

    printf("Enter the name: ");
    getchar();  
    scanf("%[^\n]", inputName);

    
    for (int i = 0; i < addressBook->contactCount; i++) {
        if (strcmp(inputName, addressBook->contacts[i].name) == 0) {
            flag = 1;
            printf("Error: Name already exists\n");
            return;
        }
    }

    printf("Enter the phone number: ");
    getchar();  
    scanf("%[^\n]", inputPhone);

    
    if (strlen(inputPhone) != 10) {
        printf("Error: Enter 10 digits\n");
        flag1 = 1;
    }

    
    for (int i = 0; i < addressBook->contactCount; i++) {
        if (strcmp(inputPhone, addressBook->contacts[i].phone) == 0) {
            flag1 = 1;
            printf("Error: Phone number already exists\n");
            return;
        }
    }

    printf("Enter the email: ");
    getchar();  
    scanf("%[^\n]", inputEmail);

    
    if (strstr(inputEmail, "@") && strstr(inputEmail, ".com")) {
        // Check if the email already exists
        for (int i = 0; i < addressBook->contactCount; i++) {
            if (strncmp(inputEmail, addressBook->contacts[i].email,strlen(inputEmail)) == 0) {
                flag2 = 1;
                printf("Error: Email already exists\n");
                return;
            }
        }
    }
    else 
    {
        printf("Error: Invalid email format\n");
        return;
    }

    
    if (flag == 0 && flag1 == 0 && flag2==0) {
        int index = addressBook->contactCount;
        strcpy(addressBook->contacts[index].name, inputName);
        strcpy(addressBook->contacts[index].phone, inputPhone);
        strcpy(addressBook->contacts[index].email, inputEmail);
        addressBook->contactCount++;
        printf("Contact created successfully\n");
    }
}

void searchContact(AddressBook *addressBook) 
{
    /* Define the logic for search */
    int searchOption;
    printf("Select search option:\n 1. Name\n 2. Phone\n 3. Email\n: ");
    scanf("%d", &searchOption);
    getchar();  
    switch (searchOption) {
        case 1: {
            char searchName[50];
            int nameFound = 0;
            printf("Enter the name: ");

            scanf("%[^\n]",searchName);
            //int nameLength = strlen(searchName);
            
            for (int i = 0; i < addressBook->contactCount; i++) {
                if (strstr(addressBook->contacts[i].name,searchName)) {
                    printf("Contact found:\n");
                    printf("Name: %s\n", addressBook->contacts[i].name);
                    printf("Phone: %s\n", addressBook->contacts[i].phone);
                    printf("Email: %s\n", addressBook->contacts[i].email);
                    nameFound = 1;
                    //break;
                }
            }
            if (!nameFound) {
                printf("Contact not found\n");
            }
            break;
        }
        case 2: {
            char searchPhone[20];
            int phoneFound = 0;
            printf("Enter the phone number: ");
          
            scanf("%[^\n]",searchPhone);          
            //int phoneLength = strlen(searchPhone);
            
            for (int i = 0; i < addressBook->contactCount; i++) {
                if (strstr(addressBook->contacts[i].phone,searchPhone)) {
                    printf("Contact found:\n");
                    printf("Name: %s\n", addressBook->contacts[i].name);
                    printf("Phone: %s\n", addressBook->contacts[i].phone);
                    printf("Email: %s\n", addressBook->contacts[i].email);
                    phoneFound = 1;
                    //break;
                }
            }
            if (!phoneFound) {
                printf("Contact not found\n");
            }
            break;
        }
        case 3: {
            char searchEmail[50];
            int emailFound = 0;
            printf("Enter the email: ");
            scanf("%[^\n]", searchEmail);
            //int emailLength = strlen(searchEmail);
            
            for (int i = 0; i < addressBook->contactCount; i++) {
                if (strstr(addressBook->contacts[i].email,searchEmail)) {
                    printf("Contact found:\n");
                    printf("Name: %s\n", addressBook->contacts[i].name);
                    printf("Phone: %s\n", addressBook->contacts[i].phone);
                    printf("Email: %s\n", addressBook->contacts[i].email);
                    emailFound = 1;
                    //break;
                }
            }
            if (!emailFound) {
                printf("Contact not found\n");
            }
            break;
        }
        default:
            printf("Invalid option selected\n");
            break;
    }
    
}
void editContact(AddressBook *addressBook)
{
    int opt;
    printf("Enter the option\n 1. Name\n 2. Email\n");
    scanf("%d", &opt);
    getchar(); 
    char searchKey[50];
    int foundIndices[10];
    int foundCount = 0;

    switch (opt)
    {
        case 1: 
            printf("Enter the name: ");
            scanf("%[^\n]", searchKey);

            for (int i = 0; i < addressBook->contactCount; i++)
            {
                if (strstr(addressBook->contacts[i].name, searchKey))
                {
                    foundIndices[foundCount] = i;
                    foundCount++;
                    printf("%d. %s %s %s\n", foundCount, addressBook->contacts[i].name, addressBook->contacts[i].phone, addressBook->contacts[i].email);
                }
            }
            break;
        case 2: 
            printf("Enter the email: ");
            scanf("%[^\n]", searchKey);

           
            for (int i = 0; i < addressBook->contactCount; i++)
            {
                if (strstr(addressBook->contacts[i].email, searchKey))
                {
                    foundIndices[foundCount] = i;
                    foundCount++;
                    printf("%d. %s %s %s\n", foundCount, addressBook->contacts[i].name, addressBook->contacts[i].phone, addressBook->contacts[i].email);
                }
            }
            break;

        default:
            printf("Invalid option\n");
            return;
    }

    if (foundCount == 0)
    {
        printf("No contacts found.\n");
        return;
    }
    int choice;
    printf("Enter the choice of contact to edit (1 to %d): ", foundCount);
    scanf("%d", &choice);
    if (choice < 1 || choice > foundCount)
    {
        printf("Invalid choice.\n");
        return;
    }

    int selectedContact = foundIndices[choice - 1];
    int editOption;
    printf("Enter the option for editing the contact:\n1. Name\n2. Phone\n3. Email\n");
    scanf("%d", &editOption);
    getchar(); 
    switch (editOption)
    {
        case 1:
            {
                char newName[50];
                int nameExists = 0;
                do {
                    printf("Enter the new name: ");
                    scanf("%[^\n]", newName);
                    getchar(); 
                    
                    nameExists = 0;
                    for (int i = 0; i < addressBook->contactCount; i++)
                    {
                        if (strcmp(addressBook->contacts[i].name, newName) == 0)
                        {
                            nameExists = 1;
                            printf("Name already exists.\n");
                            break;
                        }
                    }
                } while (nameExists);

                strcpy(addressBook->contacts[selectedContact].name, newName);
                printf("Name updated successfully.\n");
            }
            break;

        case 2: 
            {
                char newPhone[50];
                int phoneValid = 0;
                do {
                    printf("Enter the new phone number: ");
                    scanf("%[^\n]", newPhone);
                    getchar(); 

                    
                    if (strlen(newPhone) == 10)
                    {
                        phoneValid = 1;
                        for (int i = 0; i < 10; i++)
                        {
                            if (!isdigit(newPhone[i]))
                            {
                                phoneValid = 0;
                                printf("Invalid phone number, should contain only digits.\n");
                                break;
                            }
                        }

                        
                        for (int i = 0; i < addressBook->contactCount; i++)
                        {
                            if (strcmp(addressBook->contacts[i].phone, newPhone) == 0)
                            {
                                phoneValid = 0;
                                printf("Phone number already exists.\n");
                                break;
                            }
                        }
                    }
                    else
                    {
                        printf("Invalid phone number length.\n");
                    }

                } while (!phoneValid);

                strcpy(addressBook->contacts[selectedContact].phone, newPhone);
                printf("Phone number updated successfully.\n");
            }
            break;

        case 3: 
            {
                char newEmail[50];
                int emailValid = 0;
                do {
                    printf("Enter the new email: ");
                    scanf("%[^\n]", newEmail);
                    getchar(); 

                    
                    if (strchr(newEmail, '@') && strchr(newEmail, '.'))
                    {
                        emailValid = 1;

                        
                        for (int i = 0; i < addressBook->contactCount; i++)
                        {
                            if (strcmp(addressBook->contacts[i].email, newEmail) == 0)
                            {
                                emailValid = 0;
                                printf("Email already exists.\n");
                                break;
                            }
                        }
                    }
                    else
                    {
                        printf("Invalid email format.\n");
                    }
                } while (!emailValid);

                strcpy(addressBook->contacts[selectedContact].email, newEmail);
                printf("Email updated successfully.\n");
            }
            break;

        default:
            printf("Invalid option for editing.\n");
            break;
    }
}
void deleteContact(AddressBook *addressBook) 
{
    int choice;
    int found = 0;  
    printf("\nChoose Option to Delete\n");
    printf("1. Name\n2. Phone Number\n3. Email ID\n");
    printf("Enter your choice: ");
    if (scanf("%d", &choice) != 1) {  
        printf("Invalid input.\n");
        return;
    }
    getchar(); 

    switch (choice) 
    {
        case 1: 
        {
            char name[50];
            printf("Enter the Name to Delete: ");
            scanf(" %[^\n]", name);  
            printf("Contacts:\n");
            for (int i = 0; i < addressBook->contactCount; i++) 
            {
                if (strstr(addressBook->contacts[i].name, name)) 
                {
                    printf("Index %d: Name: %s, Phone: %s, Email: %s\n", i, addressBook->contacts[i].name, addressBook->contacts[i].phone, addressBook->contacts[i].email);
                    found = 1;
                }
            }
            if (found) 
            {
                int index;
                printf("Enter the index of the contact to delete: ");
                if (scanf("%d", &index) != 1) {  
                    printf("Invalid input.\n");
                    return;
                }
                
                if (index >= 0 && index < addressBook->contactCount) 
                {
                    for (int i = index; i < addressBook->contactCount - 1; i++) 
                    {
                        addressBook->contacts[i] = addressBook->contacts[i + 1];
                    }
                    addressBook->contactCount--;  
                    printf("Contact deleted successfully.\n");
                } 
                else 
                {
                    printf("Invalid index.\n");
                }
            } 
            else 
            {
                printf("No contacts found with the given name.\n");
            }
            break;
        }

        case 2: 
        {
            char phone[20];
            printf("Enter the Phone Number to Delete: ");
            scanf(" %[^\n]", phone);  
            printf("Contacts:\n");
            for (int i = 0; i < addressBook->contactCount; i++) 
            {
                if (strcmp(addressBook->contacts[i].phone, phone) == 0) 
                {
                    printf("Index %d: Name: %s, Phone: %s, Email: %s\n", i, addressBook->contacts[i].name, addressBook->contacts[i].phone, addressBook->contacts[i].email);
                    found = 1;
                }
            }
            if (found) 
            {
                int index;
                printf("Enter the index of the contact to delete: ");
                if (scanf("%d", &index) != 1) {  
                    printf("Invalid input.\n");
                    return;
                }
                
                if (index >= 0 && index < addressBook->contactCount) 
                {
                    
                    for (int i = index; i < addressBook->contactCount - 1; i++) 
                    {
                        addressBook->contacts[i] = addressBook->contacts[i + 1];
                    }
                    addressBook->contactCount--;  
                    printf("Contact deleted successfully.\n");
                } 
                else 
                {
                    printf("Invalid index.\n");
                }
            } 
            else 
            {
                printf("No contacts found with the given phone number.\n");
            }
            break;
        }

        case 3:     
        {
            char email[50];
            printf("Enter the Email ID to Delete: ");
            scanf(" %[^\n]", email);  
    
            printf("Contacts:\n");
            for (int i = 0; i < addressBook->contactCount; i++) 
            {
                if (strcmp(addressBook->contacts[i].email, email) == 0) 
                {
                    printf("Index %d: Name: %s, Phone: %s, Email: %s\n", i, addressBook->contacts[i].name, addressBook->contacts[i].phone, addressBook->contacts[i].email);
                    found = 1;
                }
            }
            if (found) 
            {
                int index;
                printf("Enter the index of the contact to delete: ");
                if (scanf("%d", &index) != 1) {  
                    printf("Invalid input.\n");
                    return;
                }
        
                if (index >= 0 && index < addressBook->contactCount) 
                {
                    for (int i = index; i < addressBook->contactCount - 1; i++) 
                    {
                        addressBook->contacts[i] = addressBook->contacts[i + 1];
                    }
                    addressBook->contactCount--;  
                    printf("Contact deleted successfully.\n");
                } 
                else 
                {
                    printf("Invalid index.\n");
                }
             } 
            else 
            {
                printf("No contacts found with the given email ID.\n");
            }
            break;
        }

        default :
            printf("Invalid Choice\n");
            break;
    }
}
