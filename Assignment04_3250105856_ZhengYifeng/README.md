# Assignment 004 — Personal Diary

- Name: Zheng Yifeng
- Student ID: 3250105856
- Language: C++ (C++17)

## Files

```text
Assignment04_3250105856_ZhengYifeng/
├── README.md
├── Guide.md
├── code/
│   ├── Date.h
│   ├── Date.cpp
│   ├── Entry.h
│   ├── Diary.h
│   ├── Diary.cpp
│   ├── pdadd.cpp
│   ├── pdlist.cpp
│   ├── pdshow.cpp
│   ├── pdremove.cpp
│   ├── pd.sh
│   └── 遇到的问题.md
└── report/
    ├── Assignment04_3250105856_ZhengYifeng.tex
    └── Assignment04_3250105856_ZhengYifeng.pdf
```

| File | Purpose |
| --- | --- |
| `code/Date.h`, `code/Date.cpp` | Date parsing and checking (`YYYYMMDD`), conversion back to a string, and comparison |
| `code/Entry.h` | One diary entry: a date and its lines of text |
| `code/Diary.h`, `code/Diary.cpp` | All entries in date order; add, remove, find, list, load, and save |
| `code/pdadd.cpp` | `pdadd` program: adds or replaces the entry of a date |
| `code/pdlist.cpp` | `pdlist` program: lists all entries or the entries in a date range |
| `code/pdshow.cpp` | `pdshow` program: prints the content of one entry |
| `code/pdremove.cpp` | `pdremove` program: removes the entry of a date |
| `code/pd.sh` | Runs one of the four programs, or runs all tests with `test` |
| `code/遇到的问题.md` | Notes on problems met during development |
| `Guide.md` | Step-by-step study guide used while writing the programs |
| `README.md` | Build instructions, usage, design notes, and test instructions |
| `report/Assignment04_3250105856_ZhengYifeng.pdf` | Program report (`.tex` is its LaTeX source) |

## Environment

- Ubuntu 24.04 (Linux)
- g++ 13.3.0, C++17 (`Diary.cpp` uses `std::filesystem`)
- bash

## Build

Run these commands in the `code` directory. Each program is compiled with the shared source files into its own executable:

```bash
for p in pdadd pdlist pdshow pdremove; do
    g++ -std=c++17 -Wall -Wextra $p.cpp Date.cpp Diary.cpp -o $p
done
```

Delete the four executables before packing the submission.

## Usage

Dates are always written as `YYYYMMDD`, for example `20261105`. The programs can be run directly or through `pd.sh`:

```bash
bash pd.sh pdadd 20261105 < input.txt
bash pd.sh pdlist
bash pd.sh pdlist 20261101 20261130
bash pd.sh pdshow 20261105 > copy.txt
bash pd.sh pdshow 20261105 | bash pd.sh pdadd 20261106
bash pd.sh pdremove 20261105
```

| Command | Behavior | Exit code |
| --- | --- | --- |
| `pdadd <date>` | Reads lines from stdin until a line with a single `.` or EOF. An entry of the same date is replaced. | 0 on success, 1 on failure |
| `pdlist` | Lists all entries in date order, one line each: date, a tab, and the first line of the content. | 0 / 1 |
| `pdlist <start> <end>` | Lists only the entries between the two dates, including both ends. | 0 / 1 |
| `pdshow <date>` | Prints only the content of that entry, so the output can be redirected to `pdadd`. | 0 / 1 |
| `pdremove <date>` | Removes the entry of that date. | 0 on success, -1 on failure |

When typing an entry by hand, end it with a line containing only `.`, or press Ctrl+D on an empty line (Ctrl+Z then Enter on Windows).

Results are written to stdout. Error messages are written to stderr, so they do not mix with redirected output.

`pdremove` returns -1 on failure. The shell only keeps the lowest 8 bits of an exit code, so `echo $?` shows `255`.

`pd.sh` passes the remaining arguments and stdin to the chosen program and returns that program's exit code.

## Data File

All entries are stored in `diary.txt` in the current directory. If the file does not exist yet, the diary is treated as empty; it is created when an entry is first added.

Each entry is a date line, its content, and a line with a single `.`:

```text
20261105
First day
Second line
.
20261106
Second day
.
```

`pdadd` stops reading at such a line, so the content of an entry can never contain it. If the file has a bad date line or an entry without the final `.`, loading fails and the file is left unchanged.

## Design

- **Date** stores the year, month, and day. `parse` checks the format, the length of each month, and leap years. `operator<` lets `std::map` sort entries by date.
- **Entry** only holds data: a `Date` and a `vector<string>` of lines.
- **Diary** keeps entries in `std::map<Date, Entry>`, so they stay in date order and each date has at most one entry. `load` reads into a temporary map and only replaces the diary when the whole file is valid.
- Each program checks its arguments, loads the diary, and does its own job. `pdadd` and `pdremove` save the file at the end. `pdlist` and `pdshow` do not change the diary, so they do not write it back; this keeps a pipe such as `pdshow A | pdadd B` safe, because the two programs run at the same time.

## Testing

```bash
bash pd.sh test
```

The script compiles the four programs into a temporary directory and runs every test there, so the real `diary.txt` is not changed. Each test compares actual and expected output with `diff`, and the script stops at the first difference.

The tests cover:

1. The first run without a data file; input ended by `.` (the next line is ignored) and input ended by EOF.
2. Date order, a date range, and a range whose start and end are the same day.
3. Replacing the entry of the same date.
4. Copying an entry to another date with `>` and `<`, and with a pipe.
5. Removing an entry, then removing it again, which fails with exit code 255.
6. An invalid date, a missing argument, and a start date after the end date.

The error messages printed under groups 5 and 6 are expected. The script ends with:

```text
All tests passed.
```
