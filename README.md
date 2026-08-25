# 🐠 Smart Aquarium & Automatic Feeding System

<p align="center">
  <img src="https://img.shields.io/badge/Language-C%20(C99)-blue?style=for-the-badge&logo=c" />
  <img src="https://img.shields.io/badge/Platform-Windows-0078D6?style=for-the-badge&logo=windows" />
  <img src="https://img.shields.io/badge/Version-1.0.0-brightgreen?style=for-the-badge" />
  <img src="https://img.shields.io/badge/Status-Stable-success?style=for-the-badge" />
  <img src="https://img.shields.io/badge/License-MIT-yellow?style=for-the-badge" />
</p>

---

## 📖 About The Project

**Smart Aquarium & Automatic Feeding System** is a command-line based aquarium management simulation written in pure C (C99 standard). The system allows users to monitor and control three core aquarium parameters — water temperature, food stock, and filter contamination — through an interactive terminal menu with full input validation.

This project was developed by **Timur Kabatash** as a foundational C programming exercise before beginning studies in **Mechatronics Engineering at Warsaw University of Technology (WUT)** in October 2026. The primary goals were to practice low-level logic, build a structured CLI interface, and correctly manage program state across a persistent loop.

---

## ✨ Features

| Feature | Description |
|---|---|
| 📊 **Status Dashboard** | Displays current water temperature (°C), food stock (grams), and filter dirt level (%) |
| 🍽️ **Feeding Module** | Deducts 1g of food per feed; applies a non-linear dirt accumulation formula |
| 🌡️ **Thermal Control** | Target-based heating and cooling with hardware safety limit enforcement |
| 🔧 **Filter Cleaning** | Three-tier maintenance system: Quick, Deep, and Extreme clean modes |
| 🛡️ **Defensive Input Validation** | All `scanf` calls are guarded; invalid input flushes the buffer via `while(getchar() != '\n')` to prevent infinite loops |

---

## 🔬 Technical Specifications

| Property | Detail |
|---|---|
| **Language** | Pure C — C99 Standard |
| **Architecture** | Single-file, modular `switch-case` state machine inside a persistent `while(1)` loop |
| **Platform** | Windows only (`windows.h`, `system("cls")`, `system("COLOR E0")`) |
| **IDE / Editors** | Code::Blocks, Visual Studio Code |
| **Dependencies** | `stdio.h`, `stdlib.h`, `windows.h`, `locale.h` |

> ⚠️ **Platform Note:** This program uses `windows.h` and Windows-specific `system()` calls (`cls`, `COLOR`, `pause`). It will **not** compile or run correctly on Linux or macOS without modification.

---

## 📁 Project Structure

```
SmartAquarium/
│
├── main.c          # Full implementation — all logic in a single file
└── README.md
```

> The monolithic single-file structure is intentional for v1.0. Modular refactoring into `.h`/`.c` header files is planned for future versions (see Roadmap).

---

## ⚙️ Global State Variables

The program manages three global variables that represent the aquarium's live state:

| Variable | Type | Default | Description |
|---|---|---|---|
| `temp` | `int` | `24` | Water temperature in °C |
| `food` | `int` | `10` | Remaining food stock in grams |
| `dirt` | `float` | `20.0` | Filter contamination level (0.0% – 100.0%) |

> These are declared globally so that `system_status()` can read them directly. In a future refactor, these would be encapsulated in a `struct AquariumState`.

---

## 🚀 How to Run

### Prerequisites

- GCC compiler (MinGW recommended on Windows)
- Windows OS

### Compile

```bash
gcc main.c -o SmartAquarium
```

### Run

```bash
# Windows
SmartAquarium.exe
```

---

## 🖥️ Menu Overview

```
==================================================
  SMART AQUARIUM & AUTOMATIC FEEDING SYSTEM v1.0
  Developed by: Timur Kabatash
==================================================

1 - View Aquarium Status
2 - Feed Fish
3 - Heat / Cool Water
4 - Filter Cleaning Level
5 - Exit System
```

---

## 🧠 Core Logic — Verified Against Source Code

### Option 1 — View Status (`case 1`)

Calls `system_status()` which prints the current values of `temp`, `food`, and `dirt` to the terminal.

---

### Option 2 — Feed Fish (`case 2`)

- Checks if `food > 0` before feeding. If stock is empty, prints a warning and does nothing.
- On successful feed:
  - `food = food - 1` → decrements stock by **1 gram**
  - `dirt = (dirt + 5.0f) * 1.20f` → applies a **non-linear (exponential-like) dirt accumulation**: adds 5 to dirt first, then multiplies the total by 1.20. This means the dirtier the tank already is, the faster it accumulates.
  - Dirt is capped at **100.0%** via `if (dirt > 100.0f) dirt = 100.0f`.

> 💡 **Design Note:** The feeding formula `(dirt + 5.0f) * 1.20` is intentionally non-linear. A tank that is already dirty will get dirty much faster with each feeding — this is a realistic and deliberate behavior.

---

### Option 3 — Thermal Control (`case 3`)

The user first selects **Cooling (1)** or **Heating (2)**, then enters a target temperature.

**Cooling rules (verified from source):**
- Target must be **strictly less than** current `temp`
- Target must be **greater than 10°C** (i.e., `newTemp <= 10` is rejected — so 10°C itself is blocked)
- Valid range: `11°C ≤ newTemp < temp`

**Heating rules (verified from source):**
- Target must be **strictly greater than** current `temp`
- Target must be **less than 35°C** (i.e., `newTemp >= 35` is rejected — so 35°C itself is blocked)
- Valid range: `temp < newTemp ≤ 34°C`

> ⚠️ **Known Code Note:** Variables `decision` and `newTemp` are declared inside `case 3` of the `switch` block without an enclosing `{}` scope. In C99 this compiles, but some compilers emit a warning. A future refactor should wrap the case body in braces or move declarations before the `switch`.

---

### Option 4 — Filter Cleaning (`case 4`)

Three cleaning modes, each verified against the source:

| Mode | Formula | Effect |
|---|---|---|
| **1 — Quick Clean** | `dirt = dirt / 2` | Reduces contamination by exactly **50%** |
| **2 — Deep Clean** | `dirt = dirt * 0.30` | Retains only 30% of current dirt → removes **70%** |
| **3 — Extreme Clean** | `dirt = 0.0f` | Full reset to **0% contamination** |

> Deep Clean also includes a floor guard: `if (dirt <= 0.0f) dirt = 0.0f` — though mathematically unnecessary for positive values, it prevents any floating-point underflow edge cases.

---

### Option 5 — Exit (`case 5`)

Prints a farewell message and calls `return 0` to terminate cleanly. The trailing `break` after `return 0` is unreachable but harmless.

---

## 🗺️ Roadmap

- [ ] Refactor into multi-file architecture (`.h` / `.c` header modules)
- [ ] Wrap `case 3` and `case 4` variable declarations in proper `{}` scopes
- [ ] Replace global variables with a `struct AquariumState`
- [ ] Simulate hardware sensor input via serial streams
- [ ] Add real-time execution loops and interrupt simulations
- [ ] Cross-platform support (remove Windows-only API dependencies)
- [ ] Persistent save/load of aquarium state via file I/O
- [ ] Unit tests for each subsystem module

---

## 👤 Developer

**Timur Kabatash**
- 🎓 Incoming Mechatronics Engineering student — Warsaw University of Technology (WUT), October 2026
- 💻 This project is the first C-language milestone, built before university studies begin

---

## 📄 License

This project is licensed under the **MIT License** — see below for details.

```
MIT License

Copyright (c) 2026 Kabatash.

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
```

---
<p align="center">Made with ❤️ in C — before the real engineering begins.</p>
