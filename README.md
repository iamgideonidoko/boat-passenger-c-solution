# C Solution to Boat Passenger Problem

## Problem
The Boat Passenger problem is one of the less classical problems of Process Synchronization. It is similar to the River Crossing problem in the sense that it is a peculiar sort of barrier that only allows threads to pass in certain combinations.

Assuming there is a rowboat that is used by both Programmers and Testers (serfs) to cross a river. The boat can hold exactly four passengers; it won’t leave the shore with more or fewer. To guarantee the safety of the passengers, it is not permissible to put one Programmer in the boat with three Testers or to put one Tester with three Programmers. Any other combination is safe (Programmers and Testers can be likened to threads in an OS).

As each thread boards the boat it should invoke a function called board. You must guarantee that all four threads from each boatload invoke board before any of the threads from the next boatload do. After all four threads have invoked board, exactly one of them should call a function named rowBoat, indicating that that thread will take the oars and steer the boat. It doesn’t matter which thread calls the function, as long as one does.

Don’t worry about the direction of travel. Assume we are only interested in traffic going in one of the directions.


[Ref: Little Book of Semaphores by Allen B. Downey, pag 148] (http://greenteapress.com/semaphores/LittleBookOfSemaphores.pdf)

## Components

### 2 Semaphores
* Programmer's queue; (headers/boat.h)
* Tester's queue; (headers/boat.h)

### 1 Mutex
* Mutex; (headers/boat.h)

### 1 Barrier
* Barrier; (headers/boat.h)

### Threads
* Threads created indefinitely; (src/main.c)
  * Each thread calls the function `board`.

## Run the code:
```
$ make
```
**NB**: Ensure you have [GCC compiler](https://www.guru99.com/c-gcc-install.html) and [Make](https://www.gnu.org/software/make/) installed.

