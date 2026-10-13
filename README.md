# Minesweeper – C++ & Qt

A graphical Minesweeper game developed with **C++ and the Qt framework**. The project demonstrates object-oriented programming, GUI development, event handling, and game logic.

## Features

- **Interactive Game Board:** Reveal individual cells and discover hidden mines.
- **Mine Detection:** Numbers indicate how many mines are located in neighboring cells.
- **Automatic Cell Revealing:** Empty cells reveal connected areas automatically.
- **Flagging System:** Mark suspected mines with a right-click and remove flags with a middle-click.
- **Game Timer:** Track the time spent playing.
- **Pause Function:** Pause and resume the game.
- **Game Status:** Display the number of mines and placed flags.
- **Win and Loss Detection:** Automatically check the game result.
- **Statistics:** Track games played, wins, losses, and best times.
- **Settings and Help:** Configure the game and access instructions through separate dialog windows.

## Technologies

- C++
- Qt Framework
- Qt Widgets
- Object-Oriented Programming

## How It Works

The application is organized into multiple classes:

- **Cell:** Stores the state of an individual cell, including whether it contains a mine, has been revealed, or is flagged.
- **Board:** Manages the game board, mine placement, neighboring mine counts, cell interactions, and win/loss conditions.
- **CellButton:** Extends `QPushButton` to support middle-click interactions.
- **MainWindow:** Controls the game flow, user input, timer, and graphical interface.
- **SettingsDialog:** Provides game configuration options.
- **StatisticsDialog:** Displays game statistics.
- **HelpDialog:** Provides instructions for playing the game.

## Documentation

For a detailed explanation of the program structure, game logic, board generation, timer, win/loss conditions, and statistics, see the documentation below.

[**Read the full documentation (PDF)**](./Funktionsweise%20des%20Minesweeper.pdf)

## Project Structure

The project is divided into separate C++ classes and Qt UI files to keep the game logic, interface, and dialogs organized.

## Author

Developed as a C++ and Qt programming project.
