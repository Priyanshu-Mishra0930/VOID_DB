# VoidDB

**VoidDB** is a lightweight database engine built from scratch in **C++**.

The goal is to understand how database systems work internally by implementing their core concepts step by step.

---

## 🚀 Features

* Table creation
* Custom schemas
* Data types: `int`, `text`, `float`
* Mandatory `id` column
* Duplicate table/column validation
* Data type validation
* Insert, Select, Update, Delete
* Duplicate ID protection
* Query parsing and validation
* Multiple tables
* Typed row storage
* In-memory data management

---

## 🧪 Commands

### Create

```text
create users id int name text age int
```

### Insert

```text
insert users 1 Prince 20
```

### Select

```text
select users
```

### Update

```text
update users 1 Prince 21
```

### Delete

```text
delete users 1
```

### Exit

```text
exit
```

---

## 🏗️ Architecture

```text
User Input
    ↓
Parsing
    ↓
Validation
    ↓
Query Execution
    ↓
Table
 ├── Columns
 └── Rows
      └── Values
```

### Core Classes

```text
table
 ├── table_name
 ├── vector<column>
 └── vector<rows>

column
 ├── column_name
 └── data_type

rows
 └── vector<value>

value
 ├── type
 ├── raw text data
 └── converted data
```

---

## 🧠 Data Types

| Type    | Code |
| ------- | ---: |
| `int`   |    1 |
| `text`  |    2 |
| `float` |    3 |

Example:

```text
create users id int name text marks float
```

Values are validated against their corresponding column types during `INSERT` and `UPDATE`.

VoidDB converts validated values into their corresponding internal representation through the `value` class.

---

## 📊 Development Status

| Component                  | Status |
| -------------------------- | ------ |
| Table Creation             | 🟢     |
| Schema Validation          | 🟢     |
| Data Type Validation       | 🟢     |
| Typed Value Storage        | 🟢     |
| Insert                     | 🟢     |
| Select                     | 🟢     |
| Update                     | 🟢     |
| Delete                     | 🟢     |
| Duplicate ID Protection    | 🟢     |
| Query Parsing              | 🟢     |
| Query Validation           | 🟢     |
| Multiple Tables            | 🟢     |
| Persistent Storage         | ⚪      |
| WHERE / Conditions         | ⚪      |
| Indexing                   | ⚪      |
| Query Optimization         | ⚪      |
| Transactions               | ⚪      |
| Concurrency                | ⚪      |
| Client–Server Architecture | ⚪      |

---

## 📦 Current Storage

VoidDB currently uses **in-memory storage**.

```text
Program Start
     ↓
Tables + Rows in RAM
     ↓
Queries
     ↓
Program Exit
     ↓
Data Lost
```

Persistent storage is planned as the next major milestone.

---

## 🧠 DSA Integration

VoidDB is also being used to apply DSA concepts to a real system.

Planned areas include:

```text
Hash Tables → Fast Lookup
Trees       → Indexing
B-Tree/B+   → Database Indexes
Queues      → Buffer Processing
Stacks      → Query Processing
Searching   → Query Execution
Sorting     → Query Operations
```

The long-term goal is to replace simple linear operations with appropriate data structures as the database engine grows.

---

## 🔄 Development Roadmap

```text
Basic CRUD                    ✅
Query Parsing                 ✅
Query Validation              ✅
SELECT Headers                ✅
ID Uniqueness                 ✅
Data Types                    ✅
Typed Value Storage           ✅
Persistent Storage             ⬜
Better Parser                 ⬜
WHERE / Conditions             ⬜
Indexing                       ⬜
Query Executor                 ⬜
Query Optimization             ⬜
Transactions                   ⬜
Concurrency                    ⬜
Client–Server Architecture     ⬜
```

---

## 💻 Build

```bash
g++ -std=c++17 main.c++ -o voiddb
```

Run:

```bash
./voiddb
```

Windows:

```bash
voiddb.exe
```

---

## 📌 Philosophy

VoidDB is not just a CRUD project.

It is being built from the ground up to understand the internals of database systems.

```text
Classes
   ↓
Tables
   ↓
Schemas
   ↓
Typed Values
   ↓
Rows
   ↓
Queries
   ↓
Database Engine
```

Every feature is being implemented incrementally instead of relying on existing database libraries.

---

## 👨‍💻 Author

**Prince**

Computer Science & Engineering Student

**Interests:** C++, Backend Development, DSA, Database Systems, Systems Programming

---

## ⭐ VoidDB

> **From vectors and classes to a database engine.**

Built from scratch in C++.
