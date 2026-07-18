# The Alchemist

A terminal-based RPG written in C, where each dungeon is a math or physics problem to solve.

**Language:** C &nbsp;·&nbsp; **Platforms:** Windows, macOS, Linux &nbsp;·&nbsp; **Type:** Final Project

---

## Table of Contents

- [Overview](#overview)
- [Features](#features)
- [Dungeon Trials](#dungeon-trials)
- [Getting Started](#getting-started)
- [Controls](#controls)
- [Project Structure](#project-structure)
- [Technical Highlights](#technical-highlights)
- [Roadmap](#roadmap)
- [Authors](#authors)
- [License](#license)

---

## Overview

The Alchemist is a single-file, dependency-free C game that runs entirely in the terminal. It combines a narrative-driven RPG loop — character creation, a town hub, an inventory and economy, and save/load persistence — with five procedurally generated dungeon puzzles, each built around a real math or physics formula: geometry, kinematics, the Pythagorean theorem, Newton's second law, and sequence recognition.

It was built as a final project to demonstrate structured C programming: file I/O, structs and enums for game state, cross-platform terminal input handling, and modular game-loop design, wrapped in an ANSI-rendered terminal interface.

---

## Features

- Narrative intro sequence with typewriter-paced story text establishing the world and stakes
- Character creation with a custom name and a choice of three species, each with a passive bonus

  | Species | Role | Passive |
  | --- | --- | --- |
  | Elf | Mage | +10% Gold earned |
  | Human | Fighter | +10% EXP earned |
  | Giant | Tank | +10% damage reduction in dungeons |

- Town Hub with a General Store (buy/sell consumables, permanent stat upgrades), The Lodge (paid full-HP rest), a Library (in-world lore with paginated navigation), and an Amusement Park minigame unlocked at Level 2
- Progression systems including leveling, EXP thresholds, win streaks with bonus rewards, and a one-time revival mechanic on defeat
- Persistent saves, with full game state serialized to a local save file and restored on launch
- Cross-platform terminal engine with custom raw-input handling for arrow-key menus on both Windows (`conio.h`) and POSIX systems (`termios`), with no external dependencies

---

## Dungeon Trials

Each of the five dungeons is a boss encounter gated by a procedurally generated puzzle.

| # | Dungeon | Boss | Concept |
| --- | --- | --- | --- |
| 1 | The Geometry Gate | Polyhedra | Area and perimeter |
| 2 | Ether-Arc Field | Zephyr | Projectile motion (distance, velocity, time) |
| 3 | Bridge of Pythagoras | Triad Trolls | Pythagorean theorem |
| 4 | Tunnel of Boulders | Reiner | Force, mass, and acceleration |
| 5 | Magister's Cave | Boolean Beast | Number sequence recognition |

Wrong answers cost HP scaled to the player's level. Correct answers grant gold and EXP, with escalating bonuses at a five-win streak.

---

## Getting Started

### Prerequisites

- A C compiler (GCC or Clang)
- A terminal that supports ANSI escape codes

### Build

```bash
# Windows (MinGW)
gcc alchemist.c -o alchemist.exe -lm

# macOS / Linux
gcc alchemist.c -o alchemist -lm
```

### Run

```bash
# Windows
alchemist.exe

# macOS / Linux
./alchemist
```

Run the compiled binary directly in a terminal window. IDE-embedded consoles often do not support the arrow-key input or ANSI colors correctly.

---

## Controls

| Input | Action |
| --- | --- |
| Up / Down arrow | Navigate menus |
| Left / Right arrow | Turn pages in the Library |
| Enter | Confirm selection |

---

## Project Structure

```
Alchemist/
├── alchemist.c       Game source: menus, game loop, puzzles, save system
├── paradoxical.dat   Save file, generated on first save
└── README.md
```

---

## Technical Highlights

- State management via a `Player` struct tracking HP, gold, EXP, level, inventory, and status flags (e.g. dungeon seal, revival used) across the game loop
- File-backed persistence, with save/load implemented using `fopen`, `fscanf`, and `fprintf`
- Conditional compilation so a single codebase targets Windows and POSIX terminals via `#ifdef _WIN32`, abstracting input, screen-clear, and sleep behavior behind common macros
- Procedural puzzle generation, where each dungeon generates randomized values at runtime and validates answers with a tolerance check for floating-point results
- A custom UI layer with hand-built ANSI rendering for progress bars, loading animations, and a multi-page lore reader, with no third-party libraries

---

## Roadmap

- [ ] Add unit tests for puzzle answer validation
- [ ] Externalize lore and dungeon text into data files
- [ ] Add additional species or difficulty modes

---

## Authors

Add name(s), section, and instructor here.

## License

Add a license (e.g. MIT) if this repository is intended to be reused, or note that it is coursework not licensed for reuse.
