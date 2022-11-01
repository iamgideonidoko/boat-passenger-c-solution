#pragma once // include this file only once in compilation
#include "main.h"

// Boat definition
typedef struct{
    pthread_mutex_t mutex;      // mutex
    pthread_barrier_t barrier;  // barrier
    int n_programmers;   // number of programmers at the boat
    int n_testers;     // number of testers at the boat
    int cap;         // passenger's cap
    sem_t programmers_queue;    // not used, why?
    sem_t testers_queue;      // not used, why?
} Boat;

// prototypes
void * board(void *a);
void row_boat(pthread_mutex_t * mutex, int * is_captain, sem_t * queue, const int cap);
void print_boat_fleet(const Boat boat);