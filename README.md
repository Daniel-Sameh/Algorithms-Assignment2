# Algorithms Assignment

This repository contains the implementation of various hashing techniques, collision resolution methods, and data structures such as red-black trees and skip lists. Additionally, it includes solutions to problems that utilize these implementations.

## Table of Contents
- [Task 1: Hashing and Collision Resolution Techniques](#task-1-hashing-and-collision-resolution-techniques)
  - [Hashing Techniques](#hashing-techniques)
  - [Collision Resolution Techniques](#collision-resolution-techniques)
- [Task 2: Red-Black Tree](#task-2-red-black-tree)
- [Task 3: Skip List](#task-3-skip-list)
  - [Skip List Implementation](#skip-list-implementation)
  - [Multiplayer Game Problem](#multiplayer-game-problem)

## Task 1: Hashing and Collision Resolution Techniques 

### Hashing Techniques
1. **Division Method** 
2. **Multiplication Method** 
3. **Mid Square Method** 
4. **Folding Method** 

### Collision Resolution Techniques
1. **Chaining Method** 
2. **Open Addressing Method** 
3. **Double Hashing** 

Define a C++ function for each of the hashing and collision resolution techniques mentioned above. Please refer to the lecture 8 slides for further details on these methods.

## Task 2: Red-Black Tree 

Implement the insertion and deletion operations of a red-black tree using C++. Your implementation should maintain the properties of the tree according to red-black tree rules. Your code should include the following functionalities:
1. **Insert nodes while ensuring tree balance and color properties are maintained** 
2. **Delete nodes with appropriate restructuring to uphold red-black properties** 

## Task 3: Skip List

### Skip List Implementation

Implement a Skip List data structure in C++. Your implementation should support the following functionalities:
1. **Insertion of elements into the skip list while maintaining the probabilistic balancing criteria** 
2. **Deletion of elements from the skip list** 
3. **Searching for elements efficiently within the skip list** 

### Multiplayer Game Problem

Utilize your skip list implementation to efficiently manage player scores in a multiplayer game. Implement the following functionalities:
1. **Dynamic Score Updates**: Players can increase or decrease their scores based on their performance. Handle these updates efficiently. 
2. **Leaderboard Retrieval**: Retrieve the top N players quickly when requested. 
3. **Player Management**: Players can join the game anytime and leave as well. They should be able to view their score at any time. 

## Getting Started

### Prerequisites
- C++ compiler (e.g., g++)

### Compilation
To compile the C++ files, use the following command:
```sh
g++ -o main main.cpp
```
