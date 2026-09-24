# VoidDB

**VoidDB** is a lightweight database engine built from scratch in **C++**.

The project is currently focused on implementing the fundamental concepts behind a database system — including tables, rows, query parsing, validation, CRUD operations, and in-memory data management.

---

## 🚀 Current Features

VoidDB currently supports:

* Creating tables
* Defining table columns
* Mandatory `id` column
* Duplicate table-name validation
* Duplicate column validation
* Inserting rows
* Selecting rows
* Updating rows
* Deleting rows using an `id`
* Basic command parsing
* Command validation
* Argument-count validation
* Table-existence validation
* Multiple tables in memory
* Row and table abstraction using C++ classes
* Generic row storage using `vector<string>`
* ID preservation during updates
* Basic error handling

---

## 🧪 Current Commands

VoidDB uses a simple command-line interface.

### Create Table

```text
create users id name age
```

Creates a table named `users` with the specified columns.

The `id` column is mandatory.

VoidDB rejects:

* Duplicate table names
* Missing `id` column
* Duplicate column names

### Insert Data

```text
insert users 1 Prince 20
```

Adds a new row to the `users` table.

The number of values must match the number of columns.

### Select Data

```text
select users
```

Displays all rows stored in the selected table.

Current output:

```text
1 Prince 20
2 Rahul 21
3 Aman 19
```

### Update Data

```text
update users 1 Prince 21
```

Updates the row whose `id` is `1`.

The `id` column is treated as the identifier and is not modified during an update.

### Delete Data

```text
delete users 1
```

Deletes the row with `id = 1`.

### Exit

```text
exit
```

Terminates the command-line session.

---

# 🏗️ Current Architecture

The current implementation consists of four logical stages followed by the in-memory database model.

```text
                 User Input
                     │
                     ▼
              Command Parser
                 praseing()
                     │
                     ▼
              Query Validation
                 validate()
                     │
                     ▼
              Query Functions
       ┌─────────────┼─────────────┐
       │             │             │
    create()      insert()      select()
       │             │             │
       └─────────────┼─────────────┘
                     │
              update() / del()
                     │
                     ▼
                  Table
                     │
                     ▼
                   rows
```

---

# 🧩 Core Components

## `rows`

The `rows` class represents an individual row in a table.

It currently provides functionality for:

* Storing row data
* Displaying row data
* Getting the row ID
* Updating row values
* Preserving the ID during updates

Important methods:

```cpp
display()
getid()
setdata()
```

The class also maintains a static row counter:

```cpp
static int count;
```

Rows currently store their values as:

```cpp
vector<string> data;
```

---

## `table`

The `table` class represents a database table.

Each table contains:

```cpp
string table_name;
vector<string> columns;
vector<rows> data;
```

This allows VoidDB to maintain multiple tables and their associated rows.

---

## Query Parsing

User commands are converted into tokens using the `praseing()` function.

For example:

```text
insert users 1 Prince 20
```

becomes:

```text
["insert", "users", "1", "Prince", "20"]
```

These tokens are passed through validation and then to the corresponding query function.

---

## Query Validation

VoidDB contains a dedicated `validate()` function.

The validation layer currently checks:

* Whether the command is valid
* Whether the required arguments are present
* Whether the table already exists during `create`
* Whether the `id` column is present during `create`
* Whether duplicate columns exist
* Whether the target table exists for non-create commands

The validation flow is:

```text
Command
   │
   ▼
Parsing
   │
   ▼
validate()
   │
   ├── Invalid → Error → Next command
   │
   └── Valid
          │
          ▼
       Execute
```

---

# 🔄 Query Flow

A command follows this general execution flow:

```text
User

  │
  │ insert users 1 Prince 20
  ▼

praseing()

  │
  ▼

Tokenized Command

  │
  ▼

validate()

  │
  ▼

insert()

  │
  ▼

Find Table

  │
  ▼

Validate Column Count

  │
  ▼

Create Row

  │
  ▼

Add Row To Table
```

Similarly, an update operation follows:

```text
update users 1 Prince 21

        │
        ▼

     Validate
        │
        ▼
    Find Table
        │
        ▼
      Find ID
        │
        ▼
     Modify Row
        │
        ▼
 Preserve ID
```

---

# 🧠 Data Structures Used

VoidDB currently makes use of the C++ STL.

### `vector`

Used for:

* Table columns
* Rows
* Tables
* Parsed commands

Examples:

```cpp
vector<string> columns;
vector<rows> data;
vector<table> tables;
```

### `string`

Used for:

* Table names
* Column names
* Stored values
* User commands

### Classes

Object-oriented programming is used to represent:

```text
Database
   ↓
Table
   ↓
Rows
```

---

# 📦 Current Storage Model

At the moment, VoidDB uses **in-memory storage**.

```text
Program Starts
      │
      ▼
Tables Created
      │
      ▼
Rows Stored In RAM
      │
      ▼
Queries Executed
      │
      ▼
Program Ends
      │
      ▼
Data Lost
```

There is currently **no persistent database file**.

---

# ⚠️ Current Limitations

VoidDB is still an early-stage database engine.

Current limitations include:

* Data is lost when the program exits
* No `.vdb` file format yet
* No SQL parser
* Commands use simplified custom syntax
* No data types
* All values are currently stored as strings
* No duplicate ID protection yet
* No `WHERE` conditions
* No sorting
* No filtering
* No indexing
* No joins
* No transactions
* No concurrency
* No query optimization
* Limited error handling

---

# 🧠 DSA Integration

One of the main goals of VoidDB is to apply **Data Structures and Algorithms to a real project**.

Potential DSA usage throughout the project:

```text
Stack
 │
 └── Expression / Query Processing

Hash Table
 │
 └── Fast Lookup

Linked List
 │
 └── Record / Page Management

Tree
 │
 └── Indexing

B-Tree / B+ Tree
 │
 └── Database Index

Queue
 │
 └── Buffer / Request Processing
```

This makes VoidDB more than just a CRUD program — it is intended to become a practical implementation of database and DSA concepts.

---

# 📊 Development Status

# 📊 Development Status

| Component | Status |
|---|---|
| C++ Core | 🟢 Working |
| Table Creation | 🟢 Working |
| Row Insertion | 🟢 Working |
| Row Selection | 🟢 Working |
| Row Update | 🟢 Working |
| Row Deletion | 🟢 Working |
| Basic Query Parsing | 🟢 Working |
| Query Validation | 🟢 Working |
| Schema Validation | 🟢 Working |
| Multiple Tables | 🟢 Working |
| Query Processing | 🟡 In Development |
| Data Management | 🟡 In Development |
| Storage System | ⚪ Planned |
| Indexing System | ⚪ Planned |
| Query Optimization | ⚪ Planned |
| Transaction Management | ⚪ Planned |
| Concurrency | ⚪ Planned |

---

# 💻 Building

Clone the repository:

```bash
git clone <repository-url>
cd VoidDB
```

Compile with C++17:

```bash
g++ -std=c++17 main.cpp -o voiddb
```

Run:

```bash
./voiddb
```

On Windows:

```bash
voiddb.exe
```

---

# 🧪 Example Session

```text
void_db> create users id name age
void_db> created

void_db> insert users 1 Prince 20
void_db> inserted

void_db> insert users 2 Rahul 21
void_db> inserted

void_db> select users
1 Prince 20
2 Rahul 21

void_db> update users 1 Prince 21
void_db> updated

void_db> delete users 2
void_db> deleted
```

---

# 📌 Project Philosophy

VoidDB is not being built simply to create another CRUD application.

The purpose is to understand what happens **inside a database**.

Starting with:

```text
Classes
   ↓
Vectors
   ↓
Rows
   ↓
Tables
   ↓
Queries
   ↓
Validation
```

Every major feature is intended to be implemented from the ground up.

---

# 👨‍💻 Author

**Prince**

Computer Science & Engineering Student

### Interests

* C++
* Backend Development
* Data Structures & Algorithms
* Database Systems
* Systems Programming

---

## ⭐ VoidDB

> **From vectors and classes to a database engine.**

Built from scratch in C++.
