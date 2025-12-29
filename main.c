/////////////////////////////////////////////////////////////************************************////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////* * * * * * ADDRESS BOOK * * * * * *////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////************************************////////////////////////////////////////////////////////////////////////
// ======================================================================================================================================================================
// PROJECT NAME : ADDRESS BOOK                                                                                                                                          =
// NAME : SHUBHAM S.                                                                                                                                                    =
//                                                                                                                                                   =
//                                                                                                  =
// MODULE : ADV. C PROGRAMMING                                                                                                                                          =
// LANGUAGE : C - PROGRAMMING                                                                                                                                           =
// ======================================================================================================================================================================
/*
This ADDRESS BOOK is a console-based application developed in C language under the module Advanced C Programming. This project enables users to efficiently manage 
personal contact information such as names, mobile numbers, and email addresses.
With a user-friendly menu-driven interface, the system allow you to :-
-> Add, List, Search, Edit, Delete, Save contacts.
-> Ensuring validated inputs.
-> Save and load contacts from a file to maintain persistent data.
*/
// ***** MENU CONTENTS ***** //
/* 
1. ADD CONTACT
2. LIST CONTACT
3. SEARCH CONTACT
4. DELETE CONTACT
5. EDIT CONTACT
6. SAVE CONTACT
7. EXIT
*/
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////*** PROGRAM CODE ***////////////////////////////////////////////////////////////////////////////

#include<stdio.h> //std input-output functions
#include<string.h> //string handling
#include<ctype.h> //character classification

// ====================
// STRUCTURE DEFINITIONS
// ====================

//structure to store individual contact details
struct contact_data
{
    char name[25]; //stores name of the contact[ARRAY]
    char mobile_number[25]; //stores contact's mobile number[ARRAY]
    char email_ID[25]; //stores email ID[ARRAY]
};

//structure to store the whole address book
struct addressbook
{
    struct contact_data contact_list[100]; //ARRAY OF 100 conatcts
    int contact_count; //holds current/total number of contacts added
};

//====================
//VALIDATION FUNCTIONS
//====================

int is_valid_name(const char *name) 
{
    if (strlen(name) == 0) 
    {
        return 0;
    }
    for (int i = 0; name[i]; i++)
    {
        if (!isalpha(name[i]) && name[i] != ' ')
        {
            return 0;
        }
    }
    return 1;
}

int is_valid_mobile(const char *mobile_number) 
{
    if (strlen(mobile_number) != 10) 
    {
        return 0;
    }
    for (int i = 0; mobile_number[i]; i++)
    {
        if (!isdigit(mobile_number[i]))
        { 
            return 0;
        }
    }
    return 1;
}

int is_valid_email(const char *email_ID) 
{
    int at_count = 0;
    char *at_ptr = NULL;
    char *dot_ptr = NULL;

    for (int i = 0; email_ID[i]; i++) 
    {
        if (!islower(email_ID[i]) && !isdigit(email_ID[i]) && email_ID[i] != '.' && email_ID[i] != '_' && email_ID[i] != '@')
        {
            return 0;
        }
        if (email_ID[i] == '@') 
        {
            at_count++;
            at_ptr = &((char*)email_ID)[i];
        }
    }

    if (at_count != 1) return 0;
    dot_ptr = strrchr(email_ID, '.');
    if (!dot_ptr || at_ptr > dot_ptr || dot_ptr == at_ptr + 1)
    {
        return 0;
    }

    if (at_ptr == email_ID || *(at_ptr + 1) == '.' || *(at_ptr - 1) == '.')
    {
        return 0;
    }

    return 1;
}

void input_contact(struct contact_data *new_contact) 
{
    do {
        printf("Enter name: ");
        scanf("%s", new_contact->name);
        if (!is_valid_name(new_contact->name)) 
        {
            printf("Invalid name. Try again.\n");
        }
    } while (!is_valid_name(new_contact->name));

    do {
        printf("Enter mobile: ");
        scanf("%s", new_contact->mobile_number);
        if (!is_valid_mobile(new_contact->mobile_number))
        { 
            printf("Invalid mobile. Try again.\n");
        }
    } while (!is_valid_mobile(new_contact->mobile_number));

    do {
        printf("Enter email: ");
        scanf("%s", new_contact->email_ID);
        if (!is_valid_email(new_contact->email_ID)) 
        {
            printf("Invalid email. Try again.\n");
        }
    } while (!is_valid_email(new_contact->email_ID));
}



int add_contact(struct addressbook *create); //Func prototype
void list_contact(struct addressbook *create); //Func prototype
int search_contact(struct addressbook *create); //Func prototype
int delete_contact(struct addressbook *create); //Func prototype
int edit_contact(struct addressbook *create); //Func prototype
int save_contact(struct addressbook *create); //Func prototype
int load_contact(struct addressbook *create); //Func prototype


// ====================
// FUNCTION DEFINITIONS
// ====================

// *****ADD CONTACT*****

//add contact function definition
int add_contact(struct addressbook *create)
{
    // Check if address book is full
    if (create->contact_count >= 100)
    {
        printf("Address Book is full.\n");
        return 1; //exit if no space left
    }

    struct contact_data temp_contact; // Temporary contact structure to hold new contact info

    // Input and validate name
    printf("Enter contact name: ");
    getchar(); // Clear newline
    scanf("%[^\n]", temp_contact.name);

    //check if name is empty
    if (temp_contact.name[0] == '\0')
    {
        printf("Name cannot be empty.\n");
        return 1;
    }

    // Input and validate mobile number
    printf("Enter the mobile number: ");
    scanf("%s", temp_contact.mobile_number); //read mobile number as string
    int len = strlen(temp_contact.mobile_number); //get length of mobile number

    //Validate length is exactly 10 digits
    if (len != 10)
    {
        printf("Mobile number must be exactly 10 digits.\n");
        return 1;
    }
    //Validate that all characters are digits
    for (int i = 0; i < len; i++)
    {
        if (temp_contact.mobile_number[i] < '0' || temp_contact.mobile_number[i] > '9')
        {
            printf("Mobile number must contain only digits.\n");
            return 1;
        }
    }

    // Input and validate email
    printf("Enter the email ID: ");
    scanf("%s", temp_contact.email_ID); //read email ID as string
    int at = 0, dot = 0; //count '@' and '.'
    for (int i = 0; temp_contact.email_ID[i] != '\0'; i++)
    {
        char c = temp_contact.email_ID[i];

        //alow only lowercase letters, '@', '.'
        if ((c < 'a' || c > 'z') && c != '@' && c != '.')
        {
            printf("Email should only have lowercase letters, '@', and '.'\n");
            return 1;
        }
        //count number of '@' and '.'
        if (c == '@') at++;
        if (c == '.') dot++;
    }
    //check that exactly one '@' and '.' are present
    if (at != 1 || dot != 1)
    {
        printf("Email must contain one '@' and one '.'\n");
        return 1;
    }
    //pointers to check email format positions
    char *exist_at = strchr(temp_contact.email_ID, '@'); //find '@'
    char *exist_dot = strchr(temp_contact.email_ID, '.'); //find '.'

    //check valid email structure
    if (!exist_at || !exist_dot || exist_at == temp_contact.email_ID || exist_dot <= exist_at + 1 || *(exist_dot + 1) == '\0')
    {
        printf("Invalid email format.\n");
        return 1;
    }

    // Check for duplicates
    for (int i = 0; i < create->contact_count; i++)
    {
        //if name, number and email id all match - it's a duplicate
        if (strcmp(create->contact_list[i].name, temp_contact.name) == 0 &&
            strcmp(create->contact_list[i].mobile_number, temp_contact.mobile_number) == 0 &&
            strcmp(create->contact_list[i].email_ID, temp_contact.email_ID) == 0)
        {
            printf("This contact already exists.\n");
            return 1;
        }
    }

    // Save new contact to address book
    create->contact_list[create->contact_count] = temp_contact; //store contact in address book
    create->contact_count++; //increement contact count

    printf("Contact added successfully.\n");
    return 0;
}

// *****LIST CONTACTS*****

void list_contact(struct addressbook *create)
{
    if(create->contact_count==0) //check if contact list is empty
    {
        printf("No contacts available\n"); //inform user no contacts to list
        return;
    }
    else
    {
        printf("List of contact details\n"); //heading
        for(int i=0;i<create->contact_count;i++) //loop through all stored contacts 
        {
        printf("\nContact %d:\n", i + 1); //list contact n then increement by 1, i.e. i=0 is Contact1 , i=1 is Contact2, i=2 is Contact3,..... so on
        printf("Name : %s\n", create->contact_list[i].name);
        printf("Mobile Number : %s\n", create->contact_list[i].mobile_number);
        printf("Email ID : %s\n", create->contact_list[i].email_ID);
        }
        printf("Total no. of contacts : %d\n", create->contact_count); //display total count
    }
}  

int search_contact(struct addressbook *create)
{
    int choice; //user's choice
    char search_term[25]; //Buffer to store search input
    int found=0; //flag to track if match is found

     //Display search MENU
     printf("Search contact by: \n");
     printf("1. Name\n");
     printf("2. Mobile Number\n");
     printf("3. Email ID\n");
     printf("Enter your choice (1, 2 or 3): ");
     scanf("%d", &choice); //Read user's choice

     //Input search term based on choice
     switch(choice)
     {
        case 1:
        //prompt user to enter name to search
        printf("Enter the name to search : ");
        getchar(); // clear leftover newline from previous input
        scanf("%[^\n]", search_term); //read full name including spaces

        //loop to analyze the contact list and search from name
        for(int i=0;i<create->contact_count;i++) //loop through all contacts/contact list
        {
            //compare entered name 
            if(strcmp(create->contact_list[i].name, search_term)==0) //compare names
            {
                //if match found, printf contact details
                printf("Contact found : \n");
                printf("Name : %s\n", create->contact_list[i].name);
                printf("Mobile Number : %s\n", create->contact_list[i].mobile_number);
                printf("Email ID : %s\n", create->contact_list[i].email_ID);
                found=1; //set found flag to true
            }
        }
        break; //exit case 1 block

        case 2:
        //prompt user to enter the mobile number to search
        printf("Enter the mobile number to search: ");
        scanf("%s", search_term); //read the mobile number

        //loop through all contacts to find matching mobile number
        for(int i = 0; i < create->contact_count; i++)
        {
            //compare entered number with each contact's mobile number
            if(strcmp(create->contact_list[i].mobile_number, search_term) == 0)
            {
                //if match found, print contact details
                printf("Contact found:\n");
                printf("Name: %s\n", create->contact_list[i].name);
                printf("Mobile Number: %s\n", create->contact_list[i].mobile_number);
                printf("Email ID: %s\n", create->contact_list[i].email_ID);
                found = 1; //set flag found to true
            }
        }
        break; //exit case 2 block

        case 3:
        //Prompt user to enter the email_ID to search
        printf("Enter the email ID to search: ");
        scanf("%s", search_term); //read the email_ID 

        //loop through all contacts to find matching email ID
        for(int i = 0; i < create->contact_count; i++)
        {
            //Compare entered email with each contacts's email ID
            if(strcmp(create->contact_list[i].email_ID, search_term) == 0)
            {
                //if match found, print contact details
                printf("Contact found:\n");
                printf("Name: %s\n", create->contact_list[i].name);
                printf("Mobile Number: %s\n", create->contact_list[i].mobile_number);
                printf("Email ID: %s\n", create->contact_list[i].email_ID);
                found = 1; //set found flag to true 
            }
        }
        break; //Exit case 3 block 

        default:
            printf("Invalid search option.\n");
     }

     //After case block is complete, check if any contact found
     if (!found)
     {
         printf("No matching contact found.\n");
     }

     return 0; //return from func after search
}

// *****DELETE CONTACT*****
int delete_contact(struct addressbook *create)
{
    int i, j, choice, found = 0;
    char input[50]; //buffer to store

    //check if there are no contacts in the address book
    if (create->contact_count == 0)
    {
        printf("No contacts available to delete.\n");
        return 1; // Exit early if address book is empty
    }

    // Ask user how they want to delete (by name, mobile, or email)
    printf("Delete contact by:\n");
    printf("1. Name\n");
    printf("2. Mobile Number\n");
    printf("3. Email ID\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);
    getchar(); // Clear buffer

    // Prompt user to enter the value to search (name/number/email)
    printf("Enter the value to search: ");
    scanf("%[^\n]", input); //read full line including spaces

    // Loop through all contacts to search for a match
    for (i = 0; i < create->contact_count; i++)
    {
        int match = 0; // Flag to track match for each contact

        if (choice == 1)
        {
            // Compare entered name with current contact's name
            if (strcmp(create->contact_list[i].name, input) == 0)
                match = 1;
        }
        else if (choice == 2)
        {
            // Compare entered mobile number
            if (strcmp(create->contact_list[i].mobile_number, input) == 0)
                match = 1;
        }
        else if (choice == 3)
        {
            // Compare entered email ID
            if (strcmp(create->contact_list[i].email_ID, input) == 0)
                match = 1;
        }
        else
        {
            printf("Invalid choice.\n");
            return 1;
        }

        // If a matching contact is found
        if (match)
        {
            found = 1; // Set flag indicating match found

            // Shift contacts to delete matched one
            for (j = i; j < create->contact_count - 1; j++)
            {
                create->contact_list[j] = create->contact_list[j + 1];
            }

            create->contact_count--; // Decrease contact count after deletion


            printf("Contact deleted successfully.\n");
            break; //exit loop
        }
    }

    // If no match was found during search
    if (!found)
    {
        printf("Contact not found.\n");
    }

    return 0; //return from func
}

// *****EDIT CONTACT*****
int edit_contact(struct addressbook *create)
{
    int choice, i, found = 0; 
    char input[50]; // Input buffer to search for the contact

    // Check if address book is empty
    if (create->contact_count == 0)
    {
        printf("No contacts available to edit.\n");
        return 1; //exit func
    }

    // Prompt user how they want to search the contact to be edited
    printf("Edit contact by:\n");
    printf("1. Name\n");
    printf("2. Mobile Number\n");
    printf("3. Email ID\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);
    getchar(); // Clear buffer

    printf("Enter the value to search: ");
    scanf("%[^\n]", input); // Accept input with spaces 

    // Loop through all existing contacts to search for a match
    for (i = 0; i < create->contact_count; i++)
    {
        int match = 0; //reset match flag for each contact 

        if (choice == 1 && strcmp(create->contact_list[i].name, input) == 0)
            match = 1;
        else if (choice == 2 && strcmp(create->contact_list[i].mobile_number, input) == 0)
            match = 1;
        else if (choice == 3 && strcmp(create->contact_list[i].email_ID, input) == 0)
            match = 1;

        //If a matching contact is found
        if (match)
        {
            found = 1; //set flag to indicate contact found

            printf("Enter new name: ");
            getchar(); //clear leftover newline 
            scanf("%[^\n]", create->contact_list[i].name); // Accept new name (with spaces)

            printf("Enter new mobile number: ");
            scanf("%s", create->contact_list[i].mobile_number); // Accept new number

            printf("Enter new email ID: ");
            scanf("%s", create->contact_list[i].email_ID); // Accept new email

            printf("Contact edited successfully.\n");
            break; //exit loop
        }
    }

    if (!found)
    {
        printf("Contact not found.\n");
    }

    return 0; //return to main program
}

// *****SAVE CONTACT***** 
int save_contact(struct addressbook *create)
{
    FILE *file_ptr=fopen("contact.csv","w");//open file in write mode
    if(file_ptr==NULL) //check if file opened successfully
    {
        printf("Error opening file for writing\n");
        return 1;
    }
    fprintf(file_ptr, "%d\n",create->contact_count); //write total contact count to file
        for(int i=0; i<create->contact_count; i++)
        {
            fprintf(file_ptr,"%s,",create->contact_list[i].name);
            fprintf(file_ptr, "%s,", create->contact_list[i].mobile_number);
            fprintf(file_ptr, "%s\n", create->contact_list[i].email_ID);
        }
        fclose(file_ptr); //close file pointer
        printf("Contacts saved successfully to contact.csv\n");
        return 0; //success
}

// *****LOAD CONTACT*****
int load_contact(struct addressbook *create)
{
    // Open the file "addressbook.txt" in read mode to load previously saved contacts
    FILE *file_ptr=fopen("contact.csv","r"); //open file in read mode

    // Check if the file was successfully opened
    if(file_ptr==NULL)
    {
        return 1;//return error code
    }
    int count;
    if(fscanf(file_ptr, "%d\n", &count) != 1)
    {
        fclose(file_ptr);
        return 1;
    }
     create->contact_count = 0; // Reset contact count before loading

    // Read each line from the file until end of file or 100 contacts are loaded
    // Each line is expected to be in the format: name,mobile_number,email_ID\n 
    for(int i=0; i<count; i++)
    {
        if(fscanf(file_ptr, "%24[^,],%24[^,],%24[^\n]\n",
                  create->contact_list[i].name,
                  create->contact_list[i].mobile_number,
                  create->contact_list[i].email_ID) == 3)
        // Increase contact count after successfully reading a contact
       { 
                    create->contact_count++;
       } 
    }
    // Close the file after reading
    fclose(file_ptr);
    // Inform the user about successful loading and total contacts loaded
    printf("Contacts loaded successfully! Total: %d\n", create->contact_count);
    return 0; //return success
}

// ====================
// MAIN FUNCTION
// ====================

int main()
{  

    struct addressbook create; //create an addressbook instance named 'create'
    create.contact_count=0; //initialize count t0 0
    int option; //variable to store user option

    // Print manual
    printf("\nAddress Book Management System Manual:\n");
    printf("1. Add Contact: Enter the name, mobile number, and email address of the contact you want to add.\n");
    printf("2. List Contacts: Displays all the contacts in the address book.\n");
    printf("3. Search Contact: Enter the name of the contact you want to search for.\n");
    printf("4. Delete Contact: Enter the name of the contact you want to delete.\n");
    printf("5. Edit Contact: Enter the name of the contact you want to edit, and then provide the new details.\n");
    printf("6. Save Contacts: Saves all contacts to a CSV file named 'contact.csv'.\n");
    printf("7. Exit: Exits the program.\n");

    // Load contacts from file at the start
    load_contact(&create);

    do
    {
        //display menu options
        printf("\n==== Display menu ====\n");

        printf("1.Add Contact : \n");
        printf("2.List Contact : \n");
        printf("3.Search Contact : \n");
        printf("4.Delete Contact : \n");
        printf("5.Edit Contact : \n");
        printf("6.Save Contact : \n");
        printf("7.Exit\n");
        printf("Enter your option : ");
        scanf("%d", &option); //accepting/reading user input for menu selection

        //handling/taking user's choice
        switch(option)
        {
            case 1 :
                printf("Add contact : \n"); 
                add_contact(&create); //call add_contact
                printf("Contact added\n");
                break;
            case 2 :
                printf("List contact : \n");
                list_contact(&create); //call list_contact
                printf("Contact listed\n");
                break;
            case 3 :
                printf("Search contact : \n");    
                search_contact(&create); //call search_contact
                printf("Searched contact\n");
                break;
            case 4 :
                printf("Delete contact : \n");
                delete_contact(&create); //call delete_contact
                printf("Contact deleted\n");
                break;
            case 5 :
                printf("Edit contact : \n");
                edit_contact(&create); //call edit_contact
                printf("Edited contact\n");
                break;
            case 6 :
                printf("Save contact : \n");
                save_contact(&create); //call save_contact
                printf("Contact saved\n");
                break;
            case 7 :
                printf("Exiting Menu!\n");
                break;
            default :
                printf("Enter the correct option"); //Invalid Input
        }
    }while(option!=7); //continue menu loop until user selects Exit
    return 0;
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//                                                                                                                                                               /////
//  PROJECT SUCESSFULLY COMPLETED !!!!!!!                                                                                                                        /////
//                                                                                                                                                               /////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
