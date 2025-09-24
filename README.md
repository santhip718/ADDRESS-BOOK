# ADDRESS-BOOK
A console-based Address Book application in C that enables users to create, search, edit, delete, list, save, and load contacts from a CSV file. This project demonstrates core C programming concepts including file I/O operations, structs, dynamic data handling, and validation.
# Address Book Application in C

## Project Overview
This is a command-line based Address Book application written in C. It allows users to manage contacts efficiently supporting create, read, update, delete (CRUD) operations along with file-based persistence using CSV.

## Features
- Add new contacts with name, phone number, and email.
- Search contacts by name, phone, or email.
- Edit and delete contacts.
- List contacts with sorting options by name, phone, or email.
- Save contacts to a CSV file.
- Load contacts from CSV on startup.
- Validates all inputs (name, phone, email).
- Prevents duplicate phone numbers and emails.

## Getting Started

### Prerequisites
- GCC compiler or any C compiler.
- Terminal or command prompt access.

### Installation & Usage
1. Clone the repository:
git clone <repository_URL>

text
2. Navigate to the project folder:
cd <project_folder>

text
3. Compile all source files:
gcc *.c -o AddressBookApp

text
4. Run the executable:
./AddressBookApp

text
5. Follow the on-screen menu to manage your address book.

## Project Structure
- `main.c`: Entry point and user interface.
- `contact.c/h`: Contact management functions and data structures.
- `file.c/h`: File read/write operations.
- `populate.c/h`: Populates with dummy data for testing.
- `contacts.csv`: Data storage file.
- `documents.txt`: Project notes and documentation.

## Contribution
Contributions are welcome! Please fork the repo and submit pull requests.
