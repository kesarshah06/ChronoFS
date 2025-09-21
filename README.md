
# ChronoFS

ChronoFS is a **version-controlled file system in C++17** with snapshots, rollbacks, and efficient data structures for fast file management. It simulates a file system with version control, using a custom **hash map + version tree** design.

---

##  How to Run

**Prerequisites:** A C++17 compiler.

* **Linux:** `sudo apt-get install build-essential`
* **macOS:** `xcode-select --install`
* **Windows:** Install `MinGW` or use WSL.

**Steps:**

```bash
git clone https://github.com/kesarshah06/ChronoFS.git
cd ChronoFS
g++ -std=c++17 -O2 -Wall main.cpp -o main
./main   # (main.exe on Windows)
```

---

##  Project Structure

```
COL_ASSIGNMENT/
├── main.cpp        # Entry point
├── file.h          # File structure
├── filemap.h       # File-object mapping
├── filesystem.h    # Controller & shell
├── hashmap.h       # Custom hash map
├── heaps.h         # Heap structures
├── helper.h        # Utilities
└── version.h       # Version logic
```

---

##  Commands

| Command              | Description            | Example        | Complexity |
| -------------------- | ---------------------- | -------------- | ---------- |
| `CREATE <f>`         | Create file            | `CREATE f1`    | O(log n)   |
| `DELETE <f>`         | Delete file + versions | `DELETE f1`    | O(m+log n) |
| `RENAME <old> <new>` | Rename file            | `RENAME f1 f2` | O(log n)   |
| `OPEN <f>` / `CLOSE` | Work on active file    | `OPEN f1`      | O(1)       |
| `READ`               | Read active version    | `READ`         | O(1)       |
| `INSERT <txt>`       | Append text            | `INSERT hi`    | O(t+log n) |
| `UPDATE <txt>`       | Replace text           | `UPDATE hello` | O(t+log n) |
| `SNAPSHOT <msg>`     | Save snapshot          | `SNAPSHOT v1`  | O(log n)   |
| `ROLLBACK [id]`      | Revert to version      | `ROLLBACK 2`   | O(log n)   |
| `HISTORY`            | Show version history   | `HISTORY`      | O(m)       |
| `PRINT`              | Print version tree     | `PRINT f1`     | O(m)       |
| `RECENT_FILES`       | Files by last modified | -              | O(n log n) |
| `BIGGEST_TREES`      | Files by version count | -              | O(n log n) |
| `HELP` / `EXIT`      | Help or quit           | -              | O(1)       |

---

##  Example Session

```
> CREATE f1
> OPEN f1
> INSERT hi
> SNAPSHOT v1
> UPDATE hello
> HISTORY
> CLOSE
> DELETE f1
> EXIT
```

---

## Error Handling

* `File already exists` – duplicate create.
* `No file is currently open` – using `READ/INSERT` etc. without `OPEN`.
* `Invalid version ID` – rollback to non-existent version.
* `Current active version is already snapshotted` – duplicate snapshot.
* `Target filename already exists` – renaming to existing file.

---

##  Key Features

* **OPEN/CLOSE** simplify workflows (no need to retype filename).
* **Empty string handling** prompts confirmation.
* **Efficient heaps + IndexMap** for O(log n) updates in `RECENT_FILES` & `BIGGEST_TREES`.
* **Memory safety**: delete frees file + versions from all structures.

---

##  Data Structures

* **HashMap** – fast file lookup.
* **RecentHeap** – by last modified.
* **BiggestTree** – by version count.
* **Version Tree** – parent-child version graph.

---

##  Future Enhancements

* Undo/Redo stack
* Persistent storage
* GUI for version tree
* Multi-user support

---

