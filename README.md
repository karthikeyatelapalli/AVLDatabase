# AVL Database Management System

This project implements a basic database management system (DBMS) using an AVL tree structure. The database supports operations like record insertion, deletion, searching, range queries, and finding nearest records, all in \( O(\log n) \) time. The AVL tree ensures balance through rotations, maintaining efficient performance.

---

## **Features**

1. **Efficient AVL Tree Implementation**:
   - Self-balancing AVL tree structure ensures \( O(\log n) \) operations for insertion, deletion, and searching.

2. **Database Operations**:
   - **Insert**: Add records to the database.
   - **Delete**: Remove records by key and value.
   - **Search**: Find a specific record using a key-value pair.
   - **Range Query**: Retrieve all records within a specific range of values.
   - **K-Nearest Records**: Find the \( k \)-nearest records to a given key.

3. **In-Order Traversal**:
   - Retrieves all records in sorted order based on their values.

4. **Tests and Assertions**:
   - Includes a comprehensive set of tests in the driver file to validate all core functionalities.

---

## **How to Build and Run**

### **Requirements**
- C++ Compiler (e.g., `g++`).
- Files:
  - `AVL_Database.cpp`
  - `AVL_Database.hpp`
  - `db_driver.cpp`

### **Steps**
1. Compile the program:
   ```bash
   g++ db_driver.cpp AVL_Database.cpp -o avl_database
