#include <iostream>
#include <unistd.h>
using namespace std;
//structure for every process
struct Processes
{
    int process_id; // Process ID
    int burstTime; // Burst Time
    int arrivalTime; // Arrival Time
} process[100];


void TurnAroundTime (Processes process[], int number, int waiting_Time[], int turn_around_time[]) 
{
    for (int time = 0; time < number; time++)
    turn_around_time[time] = process[time].burstTime + waiting_Time[time];
}


//This function will find waiting time of all process


void FindWaitingTime (Processes process [], int number, int waiting_Time []) 
{
    int remainingTime[number];
    for (int Time = 0; Time < number; Time++)
     remainingTime[Time] = process[Time].burstTime;
    int complete = 0, t = 0, minm = 999999999; // we are assigning huge value to minm so we could find the smallest number easily.
    int small = 0, finishTime;
    bool checker = false;
    while (complete != number)
    {
        for (int time = 0; time < number; time++)
        {
            if ((process[time].arrivalTime <= t) && (remainingTime[time] < minm) && remainingTime[time] > 0)
            {
                minm = remainingTime[time];
                small = time;
                checker = true;
            }
        }
        if (checker == false)
        {
            t++;
            continue;
        }   
        // decrementing the remaining time
        remainingTime[small]--;
        minm = remainingTime[small];
        if (minm == 0)
        minm = 99999999; // we are assigning huge value to minm so we could find the smallest number easily.
        if (remainingTime[small] == 0)
        {
            complete++;
            checker = false;
            finishTime = t + 1;
            // Calculating waiting time
            waiting_Time[small] = finishTime - process[small].burstTime - process[small].arrivalTime;
            if (waiting_Time[small] < 0)
                waiting_Time[small] = 0;
        }
        t++;
    }
}


// calculate average time and print the data
void findavgTime (Processes process [], int number) 
{
    int waiting_time[number], turn_Around_time[number], total_waiting_time = 0, total_turn_Around_time = 0;


    // calling FindWaitingTime function 


    FindWaitingTime (process, number, waiting_time);


    // calling TurnAroundTime function to find turnaround time for all processes
    TurnAroundTime (process, number, waiting_time, turn_Around_time);


    // It will print all the details.
    cout << "Processes " << " Burst time " << " Waiting time " << " Turn around time" << " Arriving Time \n" ;
    for (int i = 0; i < number; i++)
    {
        total_waiting_time += waiting_time[i];
        total_turn_Around_time += turn_Around_time[i];
        cout << " " << process[i].process_id << "\t\t" << process[i].burstTime << "\t\t " << waiting_time[i] << "\t\t " << turn_Around_time[i]  << "\t\t " << process[i].arrivalTime << endl;
    }
    cout << "\nAverage waiting time = " << (float)total_waiting_time / (float)number; 
    cout << "\nAverage turn around time = " << (float)total_turn_Around_time / (float)number;
}


int main ()
{
    int Process_number;
    cout << "Enter number of processes:- ";
    cin >> Process_number ; // It will be used to create process structures.
    for (int i = 0; i < Process_number; i++)
    {
        process[i].process_id = i+1 ;
        cout << "Enter Arrival Time for process " << process[i].process_id << " :- " ;
        cin >> process[i].arrivalTime;
        cout << "Enter Burst Time for process " << process[i].process_id<< " :- " ;
        cin >> process[i].burstTime ;
    }
    findavgTime(process, Process_number);
    return 0;
}
