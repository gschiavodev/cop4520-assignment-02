
# Programming Assignment 2

In this project we were given two problems to solve, each problem concerned N guests and each represented a thread. To run both problems, the `problem_to_solve` variable in `main.h` must be changed to one of the values in the enum list, such as `Minotaur_Birthday_Party` or `Minotaur_Crystal_Vase`. You can also change the number of guests (or threads) by updating the value of `n_guests` in the same file. Then recompile the program.

### Problem 1: Minotaur’s Birthday Party

Since the guests cannot communicate with each other in this problem, the solution I implemented was to designate one guest (or thread) to count. When guests would enter the labyrinth, if they saw a cupcake on the plate and they had not eaten one already, they would eat it and then leave without requesting another one. If there was no cupcake, they would just leave and not request another one. When the counting guest entered the room, they would also eat a cupcake if they had not already, but then he would request another one and account for another guest in their tally (themselves). If there was no cupcake when the counter entered, they would then know another guest had to have eaten one (they only can each eat one), so they would account for another guest in their tally, then request another cupcake for the next guest to enter and leave.

Once the counter had accounted for N empty plates, they would know that at least every guest entered the labyrinth at least once. They would announce this to the minotaur, and the minotaur would then end the party.

### Problem 2: Minotaur’s Crystal Vase

For this problem, I chose the third strategy to allow the guests to enter a queue when they wanted to see the crystal vase. I used an MCS lock as my implementation of this strategy.

#### Advantages
- FIFO order - minimizes contention, and guests don't have to fight for who goes first.
- Spin on local memory only - minimizes contention, and could help reduce the number of page faults.
- Starvation free - each guest that tried to see the vase, eventually got to see it.

#### Disadvantages
- One guest at a time - if the minotaur decided he was comfortable with multiple guests seeing the vase at a time, it would be complicated to use MCS lock for this (unlocking multiple queue nodes).

## Authors

- [@gschiavodev](https://github.com/gschiavodev)

## Run Locally

To compile and run the program locally, either execute the makefile, open the visual studio project and compile in x64 release mode, or manually compile the current state of the project with the commands below:

```bash
$ mkdir -p int
$ mkdir -p bin
$ g++ -std=c++17 -O3 -I include  -c -o int/MCSLock.o src/MCSLock.cpp
$ g++ -std=c++17 -O3 -I include  -c -o int/MinotaurBirthdayParty.o src/MinotaurBirthdayParty.cpp
$ g++ -std=c++17 -O3 -I include  -c -o int/MinotaurCrystalVase.o src/MinotaurCrystalVase.cpp
$ g++ -std=c++17 -O3 -I include  -c -o int/main.o src/main.cpp
$ g++ -std=c++17 -O3 -I include  -o bin/minotaur int/MCSLock.o int/MinotaurBirthdayParty.o int/MinotaurCrystalVase.o int/main.o
```
