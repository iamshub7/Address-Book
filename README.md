Address Book

📌 Description

The Address Book is a console-based application developed in C language under the Advanced C Programming module. This project allows users to efficiently manage personal contact information including names, mobile numbers, and email addresses. It provides a menu-driven interface with input validation and persistent file storage.

This project was developed to demonstrate structured programming, file handling, and data validation in C.

⚙️ Features

Add, list, search, edit, and delete contacts.

Validate inputs for names, mobile numbers, and email addresses.

Save and load contacts from a CSV file for persistent storage.

Prevent duplicate entries.

Menu-driven console interface for easy usage.

🛠 Technologies Used

Language: C Programming

Modules Covered: File Handling, Structures, Functions, Validation

Compiler/IDE: GCC / Code::Blocks / DevC++

File Storage: CSV file (contact.csv)

📂 Project Structure
AddressBook/
 ├── main.c        # Main program with menu interface
 ├── contact.csv   # Persistent storage for contacts
 └── README.md     # Project documentation

▶️ Usage

Compile the program:

gcc main.c -o AddressBook


Run the program:

./AddressBook


Menu options:

1. Add Contact
2. List Contact
3. Search Contact
4. Delete Contact
5. Edit Contact
6. Save Contact
7. Exit


Follow on-screen prompts to manage contacts.

📚 Learning Outcomes

Structured programming in C using functions and structures

File handling for persistent storage

Input validation and error handling

Console-based user interface design

Managing data in arrays efficiently

🚧 Limitations

Limited to 100 contacts (array-based storage)

Console-based, no graphical interface

Email validation is basic (only lowercase letters, @, . allowed)

👨‍💻 Author

Shubham Shinde

📜 License

Open-source and available for educational purposes