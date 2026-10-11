# Domino — Console Game in C

A classic Domino game for the terminal, written in C. Play against another person or against the computer, and save your match to continue it later. Made as a group project (Group IJR) in September 2025.

> The game interface (menus and messages) is in Brazilian Portuguese.

## Features

- Two game modes: **2 players** or **player vs. computer**
- Full 28-piece double-six set, shuffled and dealt (7 pieces each)
- Automatic first move: the player holding the highest double starts
- Buy pieces from the pile when you cannot play
- Save and load a match at any time
- Built-in rules screen

## How to play

On your turn you see the table, your hand (pieces are numbered) and these options:

| Key | Action |
|:---:|--------|
| `J` | Play a piece on the left or right end of the table |
| `C` | Buy a piece from the pile |
| `P` | Pass (only if you cannot play and the pile is empty) |
| `S` | Pause the match and go back to the main menu |

A piece can only be played if one of its sides matches the number at an end of the table. The first player to play all their pieces wins.

When you pause a match you can resume it, start a new one, or save it. Saved games are written to `pecas.dat`, `mesa.dat` and `jogo.dat` in the game folder.

## How to run

The game is for **Windows** (it uses the `cls` and `pause` commands).

**Easiest:** download `Dom_IJR_Projeto.exe` from the [Releases](../../releases) page and run it.

**From source** (Dev-C++, MinGW or any GCC on Windows): compile only `Dom_IJR_Projeto.cpp`, since it includes the other `.cpp` files.

```bash
g++ Dom_IJR_Projeto.cpp -o domino
```

## Project structure

The code follows the **Model-View-Controller** pattern:

| File | Role |
|------|------|
| `Dom_IJR_Model.cpp / .h` | Game data and rules: pieces, table, dealing, valid moves |
| `Dom_IJR_View.cpp / .h` | Everything shown on screen: menus, table, hand, messages |
| `Dom_IJR_Controller.cpp / .h` | Game flow: turns, user choices, computer player, save/load |
| `Dom_IJR_Projeto.cpp` | Entry point (`main`) |

**Computer player:** it plays the first piece that fits the table; if none fits, it buys from the pile; if the pile is empty, it passes.

## Authors

Group IJR

- Igor Elias Guimarães Serafim
- João Batistella da Costa
- Rafael Barros Infantini
