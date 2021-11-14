# Underperforming Students vs Teachers
## Table of Contents
- [Underperforming Students vs Teachers](#underperforming-students-vs-teachers)
  - [Table of Contents](#table-of-contents)
  - [Authors</br>](#authorsbr)
  - [Code Conventions](#code-conventions)
  - [Workflow](#workflow)
  - [Class Structue](#class-structue)

## Authors
- Tim, TSE Wai Chung
- Thomas, LI Ka Chun
- Blaise, LIU Tianmiao

## Code Conventions
- **DO NOT** write function definitions in header files, since the complier will not check mistakes.
- Use ***Camel Case*** to name functions and variables.
- All decimal variables should be stored in `double` type.
- Please use `/* I am some detailed description */` to describe the class at the top of the header files
- Please write comment `//i am a very readable comment` (such that other people can understand your code).
- Use **MIL (Member Initialization List)** in class constructors.
- When creating new class in Qt, please: (Especially when the class makes use of signal and slot)
  - Make sure the class inherits from `QObject`
  - Check the option `Add Q_Object`

## Workflow
1. All tasks are listed in `issue` section.
2. Take tasks in `issue` by yourself.
3. Feel free to add issues to `issue`.
4. Create your own `branch` to commit your work. Name your branch as `[your github username]-patch`.
5. Please send a **pull request from your branch into main** as long as you think your code you're working on should be well-known by everyone
   - This pull request should be approved by all participants.
6. Please fetch **updates from main** every time using **GitHub Desktop** before you start working locally.

## Class Structure
```
+-- TimeVariant
|   +-- Human
|       +-- Student
|           +-- AttackStudent
|               +-- SleepDeprivedStudent
|               +-- DeadlineFighter
|               +-- CgaGod
|           +-- SupportStudent
|               +-- ShamelessStudent
|               +-- TeachersPet
|               +-- GbusStudent
|       +-- Teacher
|           +-- OverworkedTA
|           +-- Kelvin
|           +-- Pang
|           +-- Desmond
|   +-- Item
|       +-- Redbull
|       +-- Assignment
|       +-- VendingMachine
+-- Game
+-- Row
```
