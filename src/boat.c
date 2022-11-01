#include "./headers/boat.h"

// pthread_create function params
struct pthread_board{
    Boat * boat;
    int is_captain;
    int type;
};

// Board function
// The caller thread asks permition to use boat's resources by signaling the pthread_barrier
// There can never be 1 tester with 3 programmers or 3 programmers with 1 tester
void * board(void *a){
    struct pthread_board * args = (struct pthread_board *)a;
        
    if(args->type == TESTER){
        
        // it's a tester!
        args->boat->n_testers++;
        sem_post(&args->boat->testers_queue);
        // The last thread (passenger) enters here:
        if(args->boat->n_testers == args->boat->cap){
            print_boat_fleet(*args->boat);
            pthread_barrier_wait(&(args->boat->barrier));    // It signals the barrier

            args->is_captain = 1;   // it becomes the captain

            // and rows the boat
            pthread_mutex_lock(&args->boat->mutex);
            row_boat(&args->boat->mutex, &args->is_captain, &args->boat->testers_queue, args->boat->cap);

            // by the and of the travel, the boat is empty
            args->boat->n_testers = 0;
        }else if (args->boat->n_programmers == args->boat->cap/2 && args->boat->n_testers == args->boat->cap/2){
            print_boat_fleet(*args->boat);
            pthread_barrier_wait(&(args->boat->barrier));    // It signals the barrier
            args->is_captain = 1;   // it becomes the captain

            // and rows the boat
            pthread_mutex_lock(&args->boat->mutex);
            row_boat(&args->boat->mutex, &args->is_captain, &args->boat->testers_queue, args->boat->cap);

            // by the and of the travel, the boat is empty
            args->boat->n_programmers = 0;
            args->boat->n_testers = 0;
        }else{
            if(args->boat->n_programmers + args->boat->n_testers >= args->boat->cap){
                // If the boat is still full
                // we have to recalculate how many are at the boat
                args->boat->n_testers--;
            }else{
                // If it's not the last thread, it enters here
                print_boat_fleet(*args->boat);
                pthread_barrier_wait(&(args->boat->barrier));    // It signals the barrier
                pthread_mutex_unlock(&(args->boat->mutex));
            }
        }
        sem_wait(&args->boat->testers_queue);           
    }else{
        // it's a programmer!
        args->boat->n_programmers++;
        sem_post(&args->boat->programmers_queue);
        if(args->boat->n_programmers == args->boat->cap){
            print_boat_fleet(*args->boat);

            pthread_barrier_wait(&(args->boat->barrier));    // It signals the barrier
            args->is_captain = 1;   // it becomes the captain

            // and rows the boat
            pthread_mutex_lock(&args->boat->mutex);
            row_boat(&args->boat->mutex, &args->is_captain, &args->boat->programmers_queue, args->boat->cap);

            // by the and of the travel, the boat is empty
            args->boat->n_programmers = 0;
        }else if (args->boat->n_programmers == args->boat->cap/2 && args->boat->n_testers == args->boat->cap/2){
            print_boat_fleet(*args->boat);

            pthread_barrier_wait(&(args->boat->barrier));    // It signals the barrier
            args->is_captain = 1;   // it becomes the captain

            // and rows the boat
            pthread_mutex_lock(&args->boat->mutex);
            row_boat(&args->boat->mutex, &args->is_captain,&args->boat->programmers_queue, args->boat->cap);

            // by the and of the travel, the boat is empty
            args->boat->n_testers = 0;
            args->boat->n_programmers = 0;
        }else{
            if(args->boat->n_programmers + args->boat->n_testers >= args->boat->cap){
                // If the boat is still full
                // we have to recalculate how many are at the boat
                args->boat->n_programmers--;
            }else{
                // If it's not the last thread, it enters here
                print_boat_fleet(*args->boat);
                pthread_barrier_wait(&(args->boat->barrier));    // It signals the barrier
                pthread_mutex_unlock(&(args->boat->mutex));
            }
        }
        // decrement (lock) the programmers_queue semaphore
        sem_wait(&args->boat->programmers_queue);             
        // }
    }
}; // end board

// Row function
// The last thread that signals the barrier activates boat's mutex
// and the boat sets sail
void row_boat(pthread_mutex_t * mutex, int * is_captain, sem_t * queue, const int cap){
    int i;
    printf("Row!!\n");
    sleep(5);               // resource

    printf("Unload!!\n\n");   // unload console exhibition
    sleep(5);               // resource
    pthread_mutex_unlock(mutex);
    for(i=0;i<cap;i++) sem_post(queue);
                          
    *is_captain = 0;
};// end row

// Print boat function
void print_boat_fleet(const Boat boat){
    printf("Programmer: %d, Tester: %d\n", boat.n_programmers, boat.n_testers);
}//  end print boat