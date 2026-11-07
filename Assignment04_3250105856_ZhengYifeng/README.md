# Assignment 004 — Personal Diary

- Name: Zheng Yifeng
- Student ID: 3250105856
- Language: C++ (C++17)

## Files

| File | Purpose |
| --- | --- |
| `code/Date.h`, `code/Date.cpp` | Date checking and comparison |
| `code/Entry.h` | One diary entry: a date and its lines |
| `code/Diary.h`, `code/Diary.cpp` | All entries; load and save `diary.txt` |
| `code/pdadd.cpp`, `pdlist.cpp`, `pdshow.cpp`, `pdremove.cpp` | The four programs |
| `code/pd.sh` | Runs a program by name, or runs the tests |
| `report/Assignment04_3250105856_ZhengYifeng.pdf` | Program report |

## Build

Run in the `code` directory:

```bash
for p in pdadd pdlist pdshow pdremove; do
    g++ -std=c++17 -Wall -Wextra $p.cpp Date.cpp Diary.cpp -o $p
done
```

## Usage

Dates are written as `YYYYMMDD`.

```bash
bash pd.sh pdadd 20261105 < input.txt
bash pd.sh pdlist
bash pd.sh pdlist 20261101 20261130
bash pd.sh pdshow 20261105
bash pd.sh pdremove 20261105
```

- `pdadd` reads lines until a line with a single `.` or EOF (Ctrl+D). An old entry of the same date is replaced.
- `pdlist` lists entries by date: the date and the first line. With two dates, it lists only the entries between them.
- `pdshow` prints the content of one entry.
- `pdremove` returns 0 on success and -1 on failure (shown as 255 in the shell).

All entries are saved in `diary.txt` in the current directory.

## Testing

```bash
bash pd.sh test
```

The script compiles the programs in a temporary directory and tests adding, listing, replacing, redirection and pipes, removing, and wrong input. It prints `All tests passed.` at the end.
