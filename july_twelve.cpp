/*
 * July 12 Daily Challenge
 * 
 * code by: Chris Hamby 
 * 
 * ----------------------------------------------------------------------------------
 * Challenge:
 * Implement a job scheduler which takes in a function f and an integer n, 
 * and calls f after n milliseconds.
 * 
 * ----------------------------------------------------------------------------------
 * Solution Notes   
 * This was a good learning exercise!
 * 
 * Things learned:
 * - calling functions as parameters (using std::function)
 * - creating threaded processes 
 * - using the clock() function 
 * - signals, which weren't used in the final solution
 * 
 * 
*/


#include <iostream>
#include <thread>
#include <functional>
#include <ctime>


using namespace std;

void foo();
void bar();
void pause(int);
void pause_execute(function<void()> , int );
void schedule_task(function<void()> , int );

int run_program = 1;

int main(){
    schedule_task(bar, 0);
    schedule_task(foo, 5000);

    /* this keeps the program alive for the scheduled tasks */
    while( run_program );

    return 0;
}


/* task function that gets scheduled */
void foo(){
    cout << "Thread 2 Function Called" << endl;
}

/* print a message every second, for 7 seconds */
void bar(){
    int t = clock();
    while(t < 6000){
        if( clock() - t > 1000){
            t = clock();
            cout << "A Second Passed" << endl;
        }
    }
    run_program = 0;
}



/* amt is in milliseconds */
void pause(int amt){
    int t = clock();            /* get the current time in ms */
    while(clock() - t < amt);   /* wait for the time to pass  */
}



/* execute a function after a delay */
void pause_execute( function<void()> task, int delay ){
    pause(delay);
    task();
}



/* create a thread for the scheduled task 
   the thread will pause for D milliseconds 
   then execute the function
*/
void schedule_task( function<void()> task, int d ){
    /* create a new thread for the task */
    thread task_thread ( pause_execute, task, d );

    /* the new thread is allowed to run independently from the main thread */
    task_thread.detach();
}




