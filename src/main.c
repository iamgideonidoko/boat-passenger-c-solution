/*
    Boat Passenger Problem
*/
#include "./headers/main.h"
#include "./headers/boat.h"

// pthread_create function params
struct pthread_board{
    Boat * boat;
    int is_captain;
    int type;
};

void display_intro(){
    printf("Solution to Boat Passenger Problem\n");
    printf("TIP: Terminate the program execution by pressing Ctrl+C\n\n");
    printf("After the program start, only combinations that makes a full complement either by either by being the fourth of its kind or by completing a mixed pair of pairs will be presented.!\n");
    sleep(15);
    system("clear");
}
void display_boat_1(){
    printf(" About to start                                                              \n");
    printf(" _ _ _                                                                       \n");
    printf(" _|||||                                                                      \n");
    printf(" _|||||                                                                      \n");
    printf("      |                                                                      \n");
    printf("   _ _|_ _ _ _ _ _ __                                                        \n");
    printf("  |_             _ __|                                                       \n");
    printf("    |_ _ _ _ _ _|/                                                           \n");
}

void display_boat_2(){
    printf(" About to start.                                                             \n");
    printf("               _ _ _                                                         \n");
    printf("               _|||||                                                        \n");
    printf("               _|||||                                                        \n");
    printf("                |                                                            \n");
    printf("             _ _|_ _ _ _ _ _ __                                              \n");
    printf("            |_             _ __|                                             \n");
    printf("              |_ _ _ _ _ _|/                                                 \n");
}  

void display_boat_3(){
    printf(" About to start..                                                           \n");
    printf("                                  _ _ _                                     \n");
    printf("                                  _|||||                                    \n");
    printf("                                  _|||||                                    \n");
    printf("                                   |                                        \n");
    printf("                                _ _|_ _ _ _ _ _ __                          \n");
    printf("                               |_             _ __|                         \n");
    printf("                                |_ _ _ _ _ _|/                              \n");
}

void display_boat_4(){
    printf(" About to start...                                                           \n");
    printf("                                                     _ _ _                   \n");
    printf("                                                     _|||||                  \n");
    printf("                                                     _|||||                  \n");
    printf("                                                      |                      \n");
    printf("                                                   _ _|_ _ _ _ _ _ __        \n");
    printf("                                                  |_             _ __|       \n");
    printf("                                                    |_ _ _ _ _ _|/           \n");
}


void display_begin(){
    printf("START: \n\n");
}

// main
int main(){
    system("clear");
    display_intro();
    for (int p = 0; p < 2; p++)
    {
        display_boat_1();
        sleep(1);
        system("clear");
        display_boat_2();
        sleep(1);
        system("clear");
        display_boat_3();
        sleep(1);
        system("clear");
        display_boat_4();
        sleep(1);
        system("clear");
    }
    display_begin();
    sleep(5);



    srand(time(NULL)); // random seed

    int is_captain;
    Boat boat;
    pthread_t passenger;
    is_captain = 0;

    // initialize boat with standard configuration
    boat.cap = 4;
    boat.n_programmers = 0;
    boat.n_testers = 0;
    /**
     * A barrier for a group of threads or processes in the source code means any thread/process must stop at this point and cannot proceed until all other threads/processes reach this barrier.
    */
    // initialize a barrier reference with attribute NULL and count 4 (4 threads must call pthread_barrier_wait() before any of them will successfully return from the call)
    pthread_barrier_init(&(boat.barrier), NULL, 4);
    // initialize a mutex reference with attribute NULL
    pthread_mutex_init(&(boat.mutex), NULL);
    // release the mutex reference
    pthread_mutex_lock(&(boat.mutex));

    // initialize a new semaphore for programmers queue
    sem_init(&boat.programmers_queue, 0, 0);       
    // initialize a new semaphore for testers queue
    sem_init(&boat.testers_queue, 0, 0);      

    struct pthread_board args; // new board
    args.boat = &boat;
    args.is_captain = is_captain;

    // Creating threads
    while(1){
        sleep(1);
        // select a random thread (passenger)
        int passenger_type = rand() % 2; // with random type (PROGRAMMER or TESTER) (0 or 1)
        args.type = passenger_type;
        // start a new thread for passenger with attribute NULL, function board and function arguments args, 
        pthread_create(&passenger,NULL, board,(void *)&args);

    }
    // wait for the passenger thread to terminate
    pthread_join(passenger, NULL);

    return 0;
} // endmain
