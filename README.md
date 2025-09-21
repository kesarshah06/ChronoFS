&nbsp;
# ChronoFS
ChronoFS — a version-controlled file system built in C++17, featuring snapshots, rollbacks, and efficient data structures for fast file management.


This program simulates a file system with version control capabilities, allowing users to create, modify, and track different versions of a file. The core functionality is built on a custom data structure that combines a hash map for file lookup with a tree-like structure for version management.

&nbsp;
---

&nbsp;

## How to Launch the Program 

This project is written in **C++17** and can be compiled using a C++17-compliant compiler like `g++` on most operating systems.

### Prerequisites

Before you begin, ensure you have a modern C++ compiler installed on your system.

  * **Linux:** `sudo apt-get install build-essential`
  * **macOS:** `xcode-select --install`
  * **Windows:** Install `MinGW` or use `WSL` (Windows Subsystem for Linux).

### Step-by-Step Instructions

1.  **Clone the repository:**
    Start by cloning the project to your local machine using Git.

    ```bash
    git clone https://github.com/kesarshah06/ChronoFS.git
    cd ChronoFS
    ```

2.  **Compile the source code:**
    Use `g++` to compile the main source file with the specified flags. This command will create an executable named `main`.

    ```bash
    g++ -std=c++17 -O2 -Wall main.cpp -o main
    ```

      * **Note:** If you are on Windows, the executable will be named `main.exe`.

3.  **Run the program:**
    Once compiled, you can launch the program from your terminal.

    ```bash
    ./main
    ```

    This will start the **File System shell**, where you can begin entering commands.

-----

&nbsp;


## Project Structure

```

COL_ASSIGNMENT/
│
├── main.cpp          # Entry point, integrates all modules
│
├── file.h            # File structure & related operations
├── filemap.h         # File-to-object mapping
├── filesystem.h      # Filesystem controller & shell
├── hashmap.h         # Custom hash map implementation
├── heaps.h           # Heap data structures
├── helper.h          # Helper/utility functions
└── version.h         # Version control logic

```
&nbsp;
----
&nbsp;

## File System Commands

The program provides a terminal-based interface with a variety of commands. The commands are case-insensitive.
Each command is listed below along with its **complexity**.

| Command                     | Description                                     | Example                  | Complexity   |            
| --------------------------- | ----------------------------------------------- | ------------------------ | ------------ |
| `CREATE <filename>`         | Create a new file                               | `CREATE f1`              | O(log n)     |      
| `DELETE <filename>`         | Delete file + all versions                      | `DELETE f1`              | O(m + log n) |     
| `RENAME <old> <new>`        | Rename file                                     | `RENAME f1 f2`           | O(log n)     |     
| `OPEN <filename>`           | Set a file as active                            | `OPEN f1`                | O(1)         |     
| `CLOSE`                     | Close active file                               | `CLOSE`                  | O(1)         |     
| `LS`                        | List all files                                  | `LS`                     | O(n)         |      
| `READ <filename>`           | Show active version content                     | `READ f1`                | O(1)         |     
| `INSERT <filename> <text>`  | Append text (creates new version if needed)     | `INSERT f1 hello`        | O(t  + log n) |
| `UPDATE <filename> <text>`  | Replace content (creates new version if needed) | `UPDATE f1 hi`           | O(t  + log n) |
| `SNAPSHOT <filename> <msg>` | Snapshot current version                        | `SNAPSHOT f1 first_save` | O(log n)     |    
| `ROLLBACK <filename> [id]`  | Revert to parent or version ID                  | `ROLLBACK f1 2`          | O(log n)     |    
| `HISTORY <filename>`        | Show version history                            | `HISTORY f1`             | O(m)         |     
| `PRINT <filename>`          | Print version tree                              | `PRINT f1`               | O(m)         |     
| `RECENT_FILES`              | List files by last modified                     | `RECENT_FILES`           | O(n log n)   |      
| `BIGGEST_TREES`             | List files by number of versions                | `BIGGEST_TREES`          | O(n log n)   |     
| `HELP`                      | Show all commands                               | `HELP`                   | O(1)         |     
| `EXIT`                      | Quit program                                    | `EXIT`                   | O(1)         |      


**Notes:**

* `n` = number of files, `m` = number of versions in a file, `t` = size of input string, `f` = total files in system.
* Commands are not case-sensitive (e.g., 'create', 'Create', 'CREATE' all work).

&nbsp;
---
&nbsp;

## Example Session

```
> CREATE f1
File with name f1 is created

> OPEN f1
File f1 is now open.

> INSERT Hi
The current active version is snapshotted and the content is inserted to the new version

> READ
Content of active version:  hi

> SNAPSHOT snapshot
The current active version is snapshotted

> UPDATE hello
The current active version is snapshotted and the content is updated to the new version

> HISTORY
ID :0 TIME :2025-09-10 10:48:00 MESSAGE :snapshot
ID : 1 is not snapshotted.

> CLOSE
File f1 is now closed.

> DELETE f1
File f1 deleted from filesystem

> EXIT
```
&nbsp;
---

&nbsp;
## Error Messages

The system provides clear error messages for invalid operations:

| Error Message                                                         | Cause                                                         |
| :-------------------------------------------------------------------- | :------------------------------------------------------------ |
| `The File System already contains this file`                                          | Attempting to create a file that already exists.              |
| `File with given name doesn't exist`                                               | Command issued on a file that doesn’t exist.                  |
| `No file is currently open`                                           | Using `READ`, `INSERT`, `UPDATE`, etc., without an open file. |
| `Active version has no parent`                        | Trying to rollback when there is no parent version.           |
| `Version with given id doesn't exist`                                      | Invalid version ID supplied during rollback.                  |
| `Empty string detected, type 'YES' to continue or input new content:` | Empty input provided to `INSERT` or `UPDATE`.                 |
| `INVALID COMMAND`                                              | Invalid or unrecognized command typed.                        |
| `Current active version is already snapshotted`                 | Trying to snapshot an already snapshotted version.            |
| `Target filename already exists`                 | Trying to rename a file with a filename that already exists.            |
| `THERE ARE ONLY <int> FILES IN THE FILE SYSTEM...`                 | During Biggest_trees/Recent_files when you want to output more files than the size of filesystem.            |


&nbsp;
---
&nbsp;
## Highlighting Key Features

### Open and Close Commands

The **`OPEN`** and **`CLOSE`** commands simplify your workflow by allowing you to work on a single file without repeatedly typing its name.

Instead of:

```
INSERT f1 hi
INSERT f1 hello
SNAPSHOT f1 snapshot
```

You can do:

```
OPEN f1
INSERT hi
INSERT hello
SNAPSHOT snapshot
CLOSE
```

### Empty String Handling

The code includes a check for empty strings in the `INSERT` and `UPDATE` functions. If the string is empty or whitespace-only, the program asks for confirmation with "YES" or for new content.

### File Integrity

* **`RENAME`** updates the key in the custom hash map efficiently.
* **`DELETE`** removes the file from all data structures (**FileMap**, **RecentHeap**, **BiggestTree**) and frees all memory, preventing leaks.
  
&nbsp;
---
&nbsp;

## Core Data Structures


The program's file system is organized like a forest of trees. The **Filesystem** manages the collection, each **File** is a tree of **Version** objects.

* **HashMap** → For fast file lookup.
* **Custom Heaps** → For `RECENT_FILES` (by modification time) and `BIGGEST_TREES` (by version count).
* **Tree Structure** → Each file is a version tree of `Version` nodes with `parent` and `children`.


### Data Structures
- **FileMap (HashMap)** → O(1) average lookup, stores files.  
- **RecentHeap** → Max-heap sorted by last modified time.  
- **BiggestTree** → Max-heap sorted by number of versions.  
- **Version Tree** → Each file is a tree of versions with parent + children pointers.

### Filesystem Structure

The filesystem is organized like a forest of version trees:

```

Filesystem
├─ FileMap → File
│    ├─ root → Version
│    ├─ active\_version → Version
│    └─ version\_map (VersionMap)
├─ RecentHeap → File
└─ BiggestTree → File

```
&nbsp;
---
&nbsp;

## IndexMap Optimization

The **IndexMap** is used inside heaps to maintain the **position of a file**.

* Without it, removing a file from a heap requires a **linear O(n) scan**.
* With IndexMap, file index lookup is **O(1)**, making removal **O(log n)** (just reheapify).

**Before (linear search):**

```cpp
for (int i = 0; i < heap.size(); i++) {
    if (heap[i] == f) { ... } // O(n)
}
```

**After (IndexMap):**

```cpp
if (!index.get(f->file_name, i)) return; // O(1)
heapifyDown(i);
heapifyUp(i); // O(log n)
```

This optimization significantly improves performance for `DELETE`, `RENAME`, and updates to heaps.

&nbsp;
---
&nbsp;
## Future Enhancements

* **Undo/Redo** stack for reversing recent actions.
* **Persistent Storage** for saving state across sessions.
* **GUI/Advanced UI** for visual version tree representation.
* **Multi-user Support** with permissions and authentication.

---

