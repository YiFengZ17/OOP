# Assignment 003 — Adventure

- Name: Zheng Yifeng
- Student ID: 3250105856
- Language: C++ (C++11 or later)

## Files

```text
Assignment03_3250105856_ZhengYifeng/
├── README.md
├── code/
│   ├── Adventure.h
│   ├── Adventure.cpp
│   ├── main.cpp
│   ├── test_input.txt
│   └── test_invalid_input.txt
└── report/
    ├── Assignment03_3250105856_ZhengYifeng.pdf
```

| File | Purpose |
| --- | --- |
| `code/Adventure.h` | Class declarations for rooms, the knight, and the castle |
| `code/Adventure.cpp` | Class implementations, map construction, and random occupant placement |
| `code/main.cpp` | Command parsing, room information, and the game loop |
| `code/test_input.txt` | Movement and exploration test input |
| `code/test_invalid_input.txt` | Invalid commands, unavailable exits, and end-of-input tests |
| `README.md` | Build instructions, design notes, and test instructions |
| `report/Assignment03_3250105856_ZhengYifeng.pdf` | Program report |

## Build and Run

Run these commands from the assignment directory. The executable is placed outside the submission directory:

```bash
mkdir -p ../Adventure03-build
g++ -std=c++11 -Wall -Wextra code/Adventure.cpp code/main.cpp -o ../Adventure03-build/adventure
../Adventure03-build/adventure
```

Enter `go` followed by an exit direction to move, for example:

```text
go east
go north
go down
```

Commands are case-sensitive. Directions include `east`, `west`, `north`, `south`, `up`, and `down`; the available directions depend on the exits displayed for the current room.

After the player enters the princess's room, she follows the knight. Returning to the lobby with her wins the game. Entering the monster's room loses the game. The program exits at end of file (EOF); during interactive use, press Ctrl+D on an empty line to end input.

## Design

- **Room** stores its ID, type, floor, occupant, and exits. A hash table maps directions to neighboring room IDs.
- **Knight** stores the current position, whether the princess is following, and the path history.
- **Castle** manages all rooms, creates bidirectional edges, and randomly places the princess and monster.
- The **game loop** displays the current room, handles occupant events, reads and validates commands, and then moves the knight.

The room type also determines its displayed name, so a separate name string is unnecessary.

## Map

The castle contains 9 rooms of 8 types on floors `-1`, `1`, and `2`. Floor `-1` is the basement; there is no floor `0`.

| ID | Type | Floor | Exits and Destination IDs |
| --- | --- | --- | --- |
| 0 | Lobby | 1 | east → 1, north → 2, west → 3 |
| 1 | Corridor | 1 | west → 0, north → 5 |
| 2 | Library | 1 | south → 0, down → 7 |
| 3 | DiningHall | 1 | east → 0 |
| 4 | Tower | 2 | down → 5 |
| 5 | Armory | 1 | south → 1, up → 4, down → 6 |
| 6 | Dungeon | -1 | up → 5, east → 8, west → 7 |
| 7 | SecretChamber | -1 | east → 6, up → 2 |
| 8 | Corridor | -1 | west → 6 |

Every connection allows travel in both directions. The two corridors share a room type, but their actual exits depend on their positions in the map.

## Random Placement and Solvability

The princess and monster occupy different rooms, neither of which is the lobby. The princess's position is chosen first, followed by the monster's position.

After choosing a monster position, breadth-first search (BFS) starts from the lobby and skips the monster's room. If the princess cannot be reached, the monster's position is chosen again. Since every connection is bidirectional, the player can also return to the lobby along the safe route after finding the princess.

This guarantees that a winning route exists, although the player can still lose by entering the monster's room while exploring.

## Testing

### Movement and Exploration

```bash
../Adventure03-build/adventure < code/test_input.txt
```

The input schedules these round trips in order:

```text
0 → 3 → 0
0 → 2 → 0
0 → 1 → 0
0 → 1 → 5 → 1 → 0
0 → 1 → 5 → 4 → 5 → 1 → 0
0 → 2 → 7 → 2 → 0
0 → 2 → 7 → 6 → 7 → 2 → 0
0 → 2 → 7 → 6 → 8 → 6 → 7 → 2 → 0
```

All moves follow valid map exits. The game ends immediately after a win or loss, so later input is not processed and a single run may not execute every route.

Occupant positions are randomized each time the program runs, so identical input can produce different results. This file provides exploration test data, not a guaranteed winning route or a single fixed expected output. Run it repeatedly to observe different outcomes.

Check that:

- Each room entry displays the name, exit count, and exit directions.
- Meeting the princess for the first time triggers dialogue and makes her follow the knight.
- Returning to the lobby with the princess wins; returning without her does not.
- Meeting the monster ends the game immediately.

### Input Validation

```bash
../Adventure03-build/adventure < code/test_invalid_input.txt
```

The file includes an empty line, an unknown command, a missing direction, extra arguments, an uppercase command, an unknown direction, and exits that do not exist in the lobby.

Expected results:

- The first five lines produce messages beginning with `Invalid command.`.
- The next four lines produce `There is no exit in that direction.`.
- The knight stays in the lobby, and the program prints `Input ended. Goodbye!` when the input is exhausted.

Test input files contain only actual input, without explanatory comments.
