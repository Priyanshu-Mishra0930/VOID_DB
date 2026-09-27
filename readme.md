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
 └── vector<string>
```

> Row values are currently stored as strings after datatype validation. Typed row storage will be implemented later.

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

---

## 📊 Development Status

| Component            | Status |
| -------------------- | ------ |
| Table Creation       | 🟢     |
| Schema Validation    | 🟢     |
| Data Type Validation | 🟢     |
| Insert               | 🟢     |
| Select               | 🟢     |
| Update               | 🟢     |
| Delete               | 🟢     |
| Query Parsing        | 🟢     |
| Multiple Tables      | 🟢     |
| Persistent Storage   | ⚪      |
| Indexing             | ⚪      |
| Query Optimization   | ⚪      |
| Transactions         | ⚪      |
| Concurrency          | ⚪      |

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

Persistent storage is planned.

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
Rows
  ↓
Queries
  ↓
Database Engine
```

---

## 👨‍💻 Author

**Prince**
Computer Science & Engineering Student

**Interests:** C++, Backend Development, DSA, Database Systems, Systems Programming

---

### ⭐ VoidDB

> **From vectors and classes to a database engine.**

Built from scratch in C++.
