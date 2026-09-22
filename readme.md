# VoidDB

**VoidDB** is a lightweight database engine built from scratch in **C++**.

The project is currently focused on implementing the fundamental concepts behind a database system — including tables, rows, query parsing, CRUD operations, and in-memory data management.

The goal is to gradually evolve VoidDB from a simple command-line database into a more complete database engine with **persistent storage, indexing, query optimization, and advanced data structures**.

---

## 🚀 Current Features

VoidDB currently supports:

* Creating tables
* Defining table columns
* Inserting rows
* Selecting rows
* Updating rows
* Deleting rows using an `id`
* Basic command parsing
* Multiple tables in memory
* Row and table abstraction using C++ classes
* Basic validation for column counts
* Basic error handling

---

## 🧪 Current Commands

VoidDB uses a simple command-line interface.

### Create Table

```text
create users id name age
```

Creates a table named `users` with the specified columns.

---

### Insert Data

```text
insert users 1 Prince 20
```

Adds a new row to the `users` table.

The number of values must match the number of columns.

---

### Select Data

```text
select users
```

Displays all rows stored in the selected table.

Example:

```text
1 Prince 20
2 Rahul 21
3 Aman 19
```

---

### Update Data

```text
update users 1 Prince 21
```

Updates the row whose `id` is `1`.

The `id` column is treated as the identifier and is not modified during an update.

---

### Delete Data

```text
delete users 1
```

Deletes the row with `id = 1`.

---

### Exit

```text
exit
```

Terminates the command-line session.

---

# 🏗️ Current Architecture

The current implementation consists of three primary layers.

```text
             User Input
                 │
                 ▼
        ┌─────────────────┐
        │ Command Parser  │
        │   praseing()    │
        └────────┬────────┘
                 │
                 ▼
        ┌─────────────────┐
        │ Query Functions │
        │                 │
        │ create()        │
        │ insert()        │
        │ select()        │
        │ update()        │
        │ del()           │
        └────────┬────────┘
                 │
                 ▼
        ┌─────────────────┐
        │      Table      │
        │                 │
        │ table_name      │
        │ columns         │
        │ data            │
        └────────┬────────┘
                 │
                 ▼
        ┌─────────────────┐
        │       rows      │
        │                 │
        │ vector<string>  │
        └─────────────────┘
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

---

## `table`

The `table` class represents a database table.

Each table contains:

```cpp
string table_name;
vector<string> columns;
vector<rows*> data;
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

These tokens are then passed to the corresponding query function.

---

# 🔄 Query Flow

A command follows this basic execution flow:

```text
User
 │
 │  insert users 1 Prince 20
 ▼
praseing()
 │
 ▼
Tokenized Command
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
      Find Table
          │
          ▼
       Find ID
          │
          ▼
      Modify Row
```

---

# 🧠 Data Structures Used

VoidDB currently makes heavy use of the C++ STL.

### `vector`

Used for:

* Table columns
* Rows
* Tables
* Parsed commands

Example:

```cpp
vector<string> columns;
vector<rows*> data;
vector<table*> tables;
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
Database Table
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

This is intentional for the current development stage. Persistent storage is planned as one of the major future upgrades.

---

# ⚠️ Current Limitations

VoidDB is still an early-stage database engine.

Current limitations include:

* Data is lost when the program exits
* No `.vdb` file format yet
* No SQL parser
* Commands use a simplified custom syntax
* No data types
* All values are currently stored as strings
* No primary-key validation
* No duplicate ID protection
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

# 🛣️ Future Upgrades

VoidDB will be developed incrementally.

## Phase 1 — Persistent Storage

The next major milestone is persistent storage.

Planned architecture:

```text
RAM
 │
 ▼
Database Engine
 │
 ▼
Storage Manager
 │
 ▼
.vdb File
```

Planned features:

* Custom `.vdb` file format
* Save tables to disk
* Load tables when starting VoidDB
* Binary file storage
* Row serialization
* Row deserialization

Target behavior:

```text
void_db> insert users 1 Prince 20
void_db> exit

        ↓

      users.vdb

        ↓

Start VoidDB again

        ↓

Data automatically restored
```

---

# Phase 2 — Better Query Engine

Improve the current command parser and executor.

Planned commands:

```text
CREATE
INSERT
SELECT
UPDATE
DELETE
```

with support for more structured syntax.

Example:

```sql
SELECT * FROM users;
```

```sql
SELECT name FROM users WHERE id = 1;
```

---

# Phase 3 — WHERE Conditions

Add conditional queries.

Example:

```sql
SELECT * FROM users WHERE age > 18;
```

```sql
DELETE FROM users WHERE id = 5;
```

```sql
UPDATE users SET age = 21 WHERE id = 1;
```

This will require expression parsing and evaluation.

---

# Phase 4 — Data Types

Currently values are stored as strings.

A future version will support types such as:

```text
INT
FLOAT
STRING
BOOL
```

Example:

```sql
CREATE TABLE users (
    id INT,
    name STRING,
    age INT
);
```

This will allow VoidDB to perform proper type validation and comparisons.

---

# Phase 5 — Indexing

Searching through every row currently requires a linear scan.

Future versions can introduce indexing.

Possible structure:

```text
            Index
              │
              ▼
        ┌─────────────┐
        │   B-Tree    │
        └──────┬──────┘
               │
               ▼
             Rows
```

Potential indexing structures:

* Hash tables
* Binary Search Trees
* B-Trees
* B+ Trees

This will improve query performance for large datasets.

---

# Phase 6 — Query Optimization

Introduce a basic query planner and optimizer.

Future architecture:

```text
Query
  │
  ▼
Parser
  │
  ▼
Query Planner
  │
  ▼
Query Optimizer
  │
  ▼
Execution Plan
  │
  ▼
Storage Engine
```

The objective is to make VoidDB capable of choosing more efficient ways to execute queries.

---

# Phase 7 — Storage Engine

The storage system can eventually evolve from simple file storage into a page-based storage engine.

Possible architecture:

```text
Database
   │
   ▼
Tables
   │
   ▼
Pages
   │
   ▼
Records
   │
   ▼
Disk
```

Potential features:

* Fixed-size pages
* Page IDs
* Record IDs
* Free-space management
* Buffer pool
* Disk manager

---

# Phase 8 — Transactions

Introduce transaction support.

Potential commands:

```sql
BEGIN;
```

```sql
COMMIT;
```

```sql
ROLLBACK;
```

Future goals include understanding:

* Atomicity
* Consistency
* Isolation
* Durability

---

# Phase 9 — Concurrency

A future version could allow multiple operations or clients to interact with the database safely.

Potential features:

* Locks
* Mutexes
* Concurrent reads
* Transaction isolation
* Thread-safe storage

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

# 🎯 Long-Term Vision

The long-term goal is to evolve VoidDB through the following stages:

```text
Simple CRUD
     │
     ▼
Query Executor
     │
     ▼
Persistent Storage
     │
     ▼
Query Parser
     │
     ▼
Data Types
     │
     ▼
WHERE / Expressions
     │
     ▼
Indexes
     │
     ▼
Storage Engine
     │
     ▼
Query Optimizer
     │
     ▼
Transactions
     │
     ▼
Concurrency
```

Eventually, the architecture could look like:

```text
                    VoidDB
                      │
        ┌─────────────┴─────────────┐
        │                           │
   Query Engine                Storage Engine
        │                           │
   ┌────┴────┐                ┌─────┴─────┐
   │         │                │           │
 Parser  Executor          Buffer       Disk
   │         │              Pool       Manager
   │         │                │           │
   └────┬────┘                └─────┬─────┘
        │                           │
        └───────────┬───────────────┘
                    │
                  Index
                    │
              B-Tree / Hash
```

---

# 📊 Development Status

| Component           | Status     |
| ------------------- | ---------- |
| C++ Core            | 🟢 Working |
| Table Creation      | 🟢 Working |
| Row Insertion       | 🟢 Working |
| Row Selection       | 🟢 Working |
| Row Update          | 🟢 Working |
| Row Deletion        | 🟢 Working |
| Basic Query Parsing | 🟢 Working |
| Multiple Tables     | 🟢 Working |
| Persistent Storage  | 🔴 Planned |
| `.vdb` Format       | 🔴 Planned |
| Data Types          | 🔴 Planned |
| WHERE Clause        | 🔴 Planned |
| Indexing            | 🔴 Planned |
| Query Optimizer     | 🔴 Planned |
| Transactions        | 🔴 Planned |
| Concurrency         | 🔴 Planned |

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
```

and gradually moving toward:

```text
Query Processing
       ↓
Persistent Storage
       ↓
Indexes
       ↓
Storage Engine
       ↓
Transactions
       ↓
Query Optimization
       ↓
Concurrency
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
