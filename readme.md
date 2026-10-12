<div align="center">

# ⚡ VoidDB

### A Database Engine Built from Scratch in C++

**From vectors and classes to a database engine.**

[![Language](https://img.shields.io/badge/Language-C++17-blue?style=for-the-badge\&logo=cplusplus\&logoColor=white)](https://isocpp.org/)
[![Storage](https://img.shields.io/badge/Persistent%20Storage-Complete-2ea44f?style=for-the-badge)](#-features)
[![Status](https://img.shields.io/badge/Project-Active-8a2be2?style=for-the-badge)](#-roadmap)

</div>

---

## 🧠 About

**VoidDB** is a lightweight database engine developed from scratch in C++ to explore how databases work internally.

The project focuses on query processing, data structures, typed storage, and persistence without relying on external database libraries for its core functionality.

## ✨ Features

| Feature         | Description                                   |
| --------------- | --------------------------------------------- |
| 🗂️ Tables      | Custom schemas and multiple tables            |
| 🔢 Data Types   | `INT`, `TEXT`, `FLOAT`                        |
| ⚙️ CRUD         | Insert, Select, Update, Delete                |
| 🛡️ Validation  | Schema, data types, and duplicate IDs         |
| 🧩 Query Engine | Query parsing and validation                  |
| 💾 Persistence  | File-based storage and automatic saving       |
| 🔄 Recovery     | Corruption detection and valid-table recovery |

## 🏗️ Architecture

```text
       USER INPUT
            │
            ▼
      QUERY PARSER
            │
            ▼
       VALIDATION
            │
            ▼
      QUERY EXECUTOR
            │
            ▼
        DATABASE
            │
      ┌─────┴─────┐
      ▼           ▼
    TABLES      STORAGE
      │         voiddb.vdb
   ┌──┴───┐
   ▼      ▼
COLUMNS  ROWS
           │
           ▼
         VALUES
```

**Core Classes:** `table` · `column` · `rows` · `value`

## 💻 Example

```text
create users id int name text age int
insert users 1 Prince 20
select users
update users 1 Prince 21
delete users 1
```

### Supported Data Types

| Type    | Code |
| :------ | :--: |
| `INT`   |   1  |
| `TEXT`  |   2  |
| `FLOAT` |   3  |

## 💾 Persistent Storage

VoidDB stores data in `voiddb.vdb` and restores it when the program starts.

```text
       DATABASE FILE
             │
             ▼
      LOAD INTO MEMORY
             │
             ▼
       EXECUTE QUERIES
             │
             ▼
       SAVE CHANGES
```

**Current milestone:** Persistence, storage validation, and corruption recovery are complete. Performance optimization is intentionally deferred until further DSA progress.

## 🗺️ Roadmap

* [x] Core CRUD operations
* [x] Query parsing and validation
* [x] Typed value storage
* [x] Multiple tables
* [x] Persistent storage
* [x] Corruption detection and recovery
* [ ] `WHERE` conditions
* [ ] Indexing and query optimization
* [ ] Transactions
* [ ] Concurrency
* [ ] Client–server architecture

## 🧩 DSA in Practice

VoidDB is also a practical environment for applying DSA concepts.

* **Hash Tables** — Faster lookups
* **Trees & B-Trees** — Database indexing
* **Searching & Sorting** — Query execution
* **Stacks & Queues** — Processing concepts

## 🔨 Build & Run

**Compile:**

```bash
g++ -std=c++17 main.c++ -o voiddb
```

**Windows:**

```powershell
.\voiddb.exe
```

**Linux:**

```bash
./voiddb
```

## 👨‍💻 Author

**Prince**
Computer Science & Engineering Student

*C++ · Backend Development · DSA · Database Systems*

---

<div align="center">

### ⚡ VoidDB

*Built from scratch. Driven by curiosity.*

</div>
