# 📒 Address Book Management System in C
A robust and modular **command-line Address Book application** developed in C programming language. It allows users to efficiently manage contacts with features such as add, search, edit, delete, and persistent storage using CSV files. Designed with a real-world contact manager in mind, the system emphasizes clean user interaction, strong input validation, and file-based data management.
## 🧾 Project Description
Managing contacts manually or through outdated tools can be inefficient. This project offers a lightweight terminal-based alternative that supports all core contact operations with a focus on simplicity, data accuracy, and long-term usability.

The application follows a modular architecture with reusable components, input validations, and CSV-based file I/O that simulates real-world applications. Suitable for beginners learning file handling, structs, and modular C programming.
## 📌 Key Features

- ✅ Add New Contact with validation
- 🔍 Search by Name / Email / Phone (case-insensitive & partial match)
- 📝 Edit existing contact details
- 🗑️ Delete contacts with confirmation
- 📋 View all saved contacts in tabular format
- 📂 Save and Load contacts from a `.csv` file
- 🔐 Validates Name, Email, Phone with custom rules
- 🆘 Emergency contacts support (Ambulance, Police, etc.)
- ❌ Prevents duplicate contact entries (by phone/email)
- 🧼 Clean, modular codebase — easy to maintain and extend
- ## 📂 Project Structure
- AddressBook/
   
├── a.out # Compiled executable (generated after build)

├── main.c # Program entry point & menu handling

├── contact.c # Functions for adding, editing, deleting contacts

├── contact.h # Header file for contact-related declarations

├── file.c # Functions for saving/loading contacts from CSV

├── file.h # Header file for file operations

├── contacts.csv # Persistent contact data stored in CSV format

└── README.md # Project documentation (you’re reading it!)
# 🔐 Input Validation

- **Name**: Alphabet-only (no digits/symbols)
  - Example: `Anju`
- **Phone**: Exactly 10 digits, numeric only
  - Example: `9876543210`
- **Email**: One `@`, valid domain ending with `.com`
  - Example: `anju.k@domain.com`

> Invalid entries are rejected with clear error messages to ensure data integrity.

## 🎬 Screenshots / Demo
![Screenshot 2025-07-03 211955](https://github.com/user-attachments/assets/e225d319-5e59-4b40-8734-4eb47f1c6bd2)
![Screenshot 2025-07-03 212045](https://github.com/user-attachments/assets/dd01eb1c-a95d-4550-ba4e-9dcec021dab7)
![Screenshot 2025-07-03 212113](https://github.com/user-attachments/assets/b9edf2c8-acce-499f-bfa9-1226feb87d39)
![Screenshot 2025-07-03 212149](https://github.com/user-attachments/assets/3f802f16-93f5-46cf-b9c2-665c7135fe3a)
![Screenshot 2025-07-03 212221](https://github.com/user-attachments/assets/1d59b1a3-55ca-4ba1-89c5-23ff12426797)
![Screenshot 2025-07-03 213758](https://github.com/user-attachments/assets/53b03b5b-2fee-4a0c-9975-bc41cc776671)
## 🧠 How It Works

1. **Launch the Program** – Menu-driven interface appears.
2. **Choose an Option** – Add, Edit, Search, Delete, List, Emergency.
3. **Data is Validated** – Ensures all inputs are in proper format.
4. **Persistent Save** – All contacts are saved in `contacts.csv`.
5. **Load Existing Data** – Program auto-loads contacts from file.
## 📈 Future Enhancements
🌐 GUI using GTK or ncurses

🗄️ Switch to SQLite / MySQL backend

🔐 Password-protected user login

🧾 Export to Excel or JSON

🌍 Multilingual UI support

⏱️ Track creation & update timestamps
## 🖥️ How to Compile & Run

```bash
gcc *.c -o hotel_management
./hotel_management
## 👨‍💻 Developed By

**Vedha C R**  
💻 *C Programmer | Project Enthusiast*  
📫 **Email**: [vedhagowda59@gmail.com](mailto:vedhagowda59@gmail.com)  
🌐 **GitHub**: [https://github.com/VedhaCR59](https://github.com/VedhaCR59)  
🔗 **LinkedIn**: [https://www.linkedin.com/in/vedhacr](https://www.linkedin.com/in/vedhacr)

## 📄 License

This project is licensed under the **MIT License**.  
Feel free to **fork**, **contribute**, or **use it** in your own projects!
