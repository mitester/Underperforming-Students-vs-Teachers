# Underperforming Students vs Teachers
## Table of Contents
- [Underperforming Students vs Teachers](#underperforming-students-vs-teachers)
  - [Table of Contents](#table-of-contents)
  - [Authors</br>](#authorsbr)
  - [Code Conventions](#code-conventions)
  - [Workflow](#workflow)
  - [Class Structue](#class-structue)

## Authors</br>
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

## Workflow
1. All tasks are listed in `issue` section.
2. Take tasks in `issue` by yourself.
3. Feel free to add issues to `issue`.
4. Create your own `branch` to commit your work. Name your branch as `[your github username]-patch`.
5. After everything is finished, we merge branches together.

## Class Structue
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
|           +-- Redbull
|           +-- Assignment
|           +-- VendingMachine
```
