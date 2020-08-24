#include<iostream>
#include<stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include<cstdlib>
using namespace ::std;
void findWaitingTime(int processes[], int n, int bt[], int wt[])
{
    wt[0] = 0;
    for (int  i = 1; i < n ; i++ )
        wt[i] =  bt[i-1] + wt[i-1] ;
}
void fcfsfindTurnAroundTime( int processes[], int n, int bt[], int wt[], int tat[])
{
    for (int  i = 0; i < n ; i++)
        tat[i] = bt[i] + wt[i];
}
void findavgTime( int processes[], int n, int bt[])
{
    int wt[n], tat[n], total_wt = 0, total_tat = 0;
    findWaitingTime(processes, n, bt, wt);
    fcfsfindTurnAroundTime(processes, n, bt, wt, tat);
    cout << "Processes  "<< " Burst time  " << " Waiting time  " << " Turn around time\n";
    for (int  i=0; i<n; i++)
    {
        total_wt = total_wt + wt[i];
        total_tat = total_tat + tat[i];
        cout << "   " << i+1 << "\t\t" << bt[i] <<"\t   "<< wt[i] <<"\t\t  " << tat[i] <<endl;
    }

    cout << "Average waiting time = " << (float)total_wt / (float)n;
    cout << "\nAverage turn around time = " << (float)total_tat / (float)n;
}
int fcfs_sched()
{
    int processes[] = { 1, 2, 3};
    int n = sizeof processes / sizeof processes[0];
    int  burst_time[] = {10, 5, 8};
    findavgTime(processes, n,  burst_time);
    return 0;
}


struct process
{
      char process_name;
      int arrival_time, burst_time, ct, waiting_time, turnaround_time, priority;
      int status;
}process_queue[10];

int limit;

void Arrival_Time_Sorting()
{
      struct process temp;
      int i, j;
      for(i = 0; i < limit - 1; i++)
      {
            for(j = i + 1; j < limit; j++)
            {
                  if(process_queue[i].arrival_time > process_queue[j].arrival_time)
                  {
                        temp = process_queue[i];
                        process_queue[i] = process_queue[j];
                        process_queue[j] = temp;
                  }
            }
      }
}

int PrioPE()
{
      int i, time = 0, burst_time = 0, largest;
      char c;
      float wait_time = 0, turnaround_time = 0, average_waiting_time, average_turnaround_time;
      printf("\nEnter Total Number of Processes:\t");
      scanf("%d", &limit);
      for(i = 0, c = 'A'; i < limit; i++, c++)
      {
            process_queue[i].process_name = c;
            printf("\nEnter Details For Process[%C]:\n", process_queue[i].process_name);
            printf("Enter Arrival Time:\t");
            scanf("%d", &process_queue[i].arrival_time );
            printf("Enter Burst Time:\t");
            scanf("%d", &process_queue[i].burst_time);
            printf("Enter Priority:\t");
            scanf("%d", &process_queue[i].priority);
            process_queue[i].status = 0;
            burst_time = burst_time + process_queue[i].burst_time;
      }
      Arrival_Time_Sorting();
      process_queue[9].priority = -9999;
      printf("\nProcess Name\tArrival Time\tBurst Time\tPriority\tWaiting Time");
      for(time = process_queue[0].arrival_time; time < burst_time;)
      {
            largest = 9;
            for(i = 0; i < limit; i++)
            {
                  if(process_queue[i].arrival_time <= time && process_queue[i].status != 1 && process_queue[i].priority > process_queue[largest].priority)
                  {
                        largest = i;
                  }
            }
            time = time + process_queue[largest].burst_time;
            process_queue[largest].ct = time;
            process_queue[largest].waiting_time = process_queue[largest].ct - process_queue[largest].arrival_time - process_queue[largest].burst_time;
            process_queue[largest].turnaround_time = process_queue[largest].ct - process_queue[largest].arrival_time;
            process_queue[largest].status = 1;
            wait_time = wait_time + process_queue[largest].waiting_time;
            turnaround_time = turnaround_time + process_queue[largest].turnaround_time;
            printf("\n%c\t\t%d\t\t%d\t\t%d\t\t%d", process_queue[largest].process_name, process_queue[largest].arrival_time, process_queue[largest].burst_time, process_queue[largest].priority, process_queue[largest].waiting_time);
      }
      average_waiting_time = wait_time / limit;
      average_turnaround_time = turnaround_time / limit;
      printf("\n\nAverage waiting time:\t%f\n", average_waiting_time);
      printf("Average Turnaround Time:\t%f\n", average_turnaround_time);
      return 0;
}


int PrioNPE()
{
      int burst_time[20], process[20], waiting_time[20], turnaround_time[20], priority[20];
      int i, j, limit, sum = 0, position, temp;
      float average_wait_time, average_turnaround_time;
      printf("Enter Total Number of Processes:\t");
      scanf("%d", &limit);
      printf("\nEnter Burst Time and Priority For %d Processes\n", limit);
      for(i = 0; i < limit; i++)
      {
            printf("\nProcess[%d]\n", i + 1);
            printf("Process Burst Time:\t");
            scanf("%d", &burst_time[i]);
            printf("Process Priority:\t");
            scanf("%d", &priority[i]);
            process[i] = i + 1;
      }
      for(i = 0; i < limit; i++)
      {
            position = i;
            for(j = i + 1; j < limit; j++)
            {
                  if(priority[j] < priority[position])
                  {
                        position = j;
                  }
            }
            temp = priority[i];
            priority[i] = priority[position];
            priority[position] = temp;
            temp = burst_time[i];
            burst_time[i] = burst_time[position];
            burst_time[position] = temp;
            temp = process[i];
            process[i] = process[position];
            process[position] = temp;
      }
      waiting_time[0] = 0;
      for(i = 1; i < limit; i++)
      {
            waiting_time[i] = 0;
            for(j = 0; j < i; j++)
            {
                  waiting_time[i] = waiting_time[i] + burst_time[j];
            }
            sum = sum + waiting_time[i];
      }
      average_wait_time = sum / limit;
      sum = 0;
      printf("\nProcess ID\t\tBurst Time\t Waiting Time\t Turnaround Time\n");
      for(i = 0; i < limit; i++)
      {
            turnaround_time[i] = burst_time[i] + waiting_time[i];
            sum = sum + turnaround_time[i];
            printf("\nProcess[%d]\t\t%d\t\t %d\t\t %d\n", process[i], burst_time[i], waiting_time[i], turnaround_time[i]);
      }
      average_turnaround_time = sum / limit;
      printf("\nAverage Waiting Time:\t%f", average_wait_time);
      printf("\nAverage Turnaround Time:\t%f\n", average_turnaround_time);
      return 0;
}


void findWaitingTime(int processes[], int n,
             int bt[], int wt[], int quantum)
{
    int rem_bt[n];
    for (int i = 0 ; i < n ; i++)
        rem_bt[i] =  bt[i];
    int t = 0;
    while (1)
    {
        bool done = true;
        for (int i = 0 ; i < n; i++)
        {
            if (rem_bt[i] > 0)
            {
                done = false;
                if (rem_bt[i] > quantum)
                {
                    t += quantum;
                    rem_bt[i] -= quantum;
                }
                else
                {
                    t = t + rem_bt[i];
                    wt[i] = t - bt[i];
                    rem_bt[i] = 0;
                }
            }
        }
        if (done == true)
          break;
    }
}
void findTurnAroundTime(int processes[], int n, int bt[], int wt[], int tat[])
{
    for (int i = 0; i < n ; i++)
        tat[i] = bt[i] + wt[i];
}
void findavgTime(int processes[], int n, int bt[], int quantum)
{
    int wt[n], tat[n], total_wt = 0, total_tat = 0;
    findWaitingTime(processes, n, bt, wt, quantum);
    findTurnAroundTime(processes, n, bt, wt, tat);
    cout << "Processes "<< " Burst time "
         << " Waiting time " << " Turn around time\n";
    for (int i=0; i<n; i++)
    {
        total_wt = total_wt + wt[i];
        total_tat = total_tat + tat[i];
        cout << " " << i+1 << "\t\t" << bt[i] <<"\t "
             << wt[i] <<"\t\t " << tat[i] <<endl;
    }
    cout << "Average waiting time = "
         << (float)total_wt / (float)n;
    cout << "\nAverage turn around time = "
         << (float)total_tat / (float)n;
}
int RR_sched()
{
    int processes[] = { 1, 2, 3};
    int n = sizeof processes / sizeof processes[0];
    int burst_time[] = {10, 5, 8};
    int quantum = 2;
    findavgTime(processes, n, burst_time, quantum);
    return 0;
}

int SJF_PE()
{
      int arrival_time[10], burst_time[10], temp[10];
      int i, smallest, count = 0, time, limit;
      double wait_time = 0, turnaround_time = 0, end;
      float average_waiting_time, average_turnaround_time;
      printf("\nEnter the Total Number of Processes:\t");
      scanf("%d", &limit);
      printf("\nEnter Details of %d Processes\n", limit);
      for(i = 0; i < limit; i++)
      {
            printf("\nEnter Arrival Time:\t");
            scanf("%d", &arrival_time[i]);
            printf("Enter Burst Time:\t");
            scanf("%d", &burst_time[i]);
            temp[i] = burst_time[i];
      }
      burst_time[9] = 9999;
      for(time = 0; count != limit; time++)
      {
            smallest = 9;
            for(i = 0; i < limit; i++)
            {
                  if(arrival_time[i] <= time && burst_time[i] < burst_time[smallest] && burst_time[i] > 0)
                  {
                        smallest = i;
                  }
            }
            burst_time[smallest]--;
            if(burst_time[smallest] == 0)
            {
                  count++;
                  end = time + 1;
                  wait_time = wait_time + end - arrival_time[smallest] - temp[smallest];
                  turnaround_time = turnaround_time + end - arrival_time[smallest];
            }
      }
      average_waiting_time = wait_time / limit;
      average_turnaround_time = turnaround_time / limit;
      printf("\n\nAverage Waiting Time:\t%lf\n", average_waiting_time);
      printf("Average Turnaround Time:\t%lf\n", average_turnaround_time);
      return 0;
}


int SJF_NPE()
{
      int temp, i, j, limit, sum = 0, position;
      float average_wait_time, average_turnaround_time;
      int burst_time[20], process[20], waiting_time[20], turnaround_time[20];
      printf("\nEnter Total Number of Processes:\t");
      scanf("%d", &limit);
      for(i = 0; i < limit; i++)
      {
            printf("Enter Burst Time For Process[%d]:\t", i + 1);
            scanf("%d", &burst_time[i]);
            process[i] = i + 1;
      }
      for(i = 0; i < limit; i++)
      {
            position = i;
            for(j = i + 1; j < limit; j++)
            {
                  if(burst_time[j] < burst_time[position])
                  {
                        position = j;
                  }
            }
            temp = burst_time[i];
            burst_time[i] = burst_time[position];
            burst_time[position] = temp;
            temp = process[i];
            process[i] = process[position];
            process[position] = temp;
      }
      waiting_time[0] = 0;
      for(i = 1; i < limit; i++)
      {
            waiting_time[i] = 0;
            for(j = 0; j < i; j++)
            {
                  waiting_time[i] = waiting_time[i] + burst_time[j];
            }
            sum = sum + waiting_time[i];
      }
      average_wait_time = (float)sum / limit;
      sum = 0;
      printf("\nProcess ID\t\tBurst Time\t Waiting Time\t Turnaround Time\n");
      for(i = 0; i < limit; i++)
      {
            turnaround_time[i] = burst_time[i] + waiting_time[i];
            sum = sum + turnaround_time[i];
            printf("\nProcess[%d]\t\t%d\t\t %d\t\t %d\n", process[i], burst_time[i], waiting_time[i], turnaround_time[i]);
      }
      average_turnaround_time = (float)sum / limit;
      printf("\nAverage Waiting Time:\t%f\n", average_wait_time);
      printf("\nAverage Turnaround Time:\t%f\n", average_turnaround_time);
      return 0;
}



int main()
{
    float result;
    int choice, num;
    printf("Press 1 for fcfs scheduling\n");
    printf("Press 2 for preemptive priority scheduling\n");
    printf("Press 3 for non preemptive priority scheduling\n");
    printf("Press 4 for round robin scheduling\n");
    printf("Press 5 for SJF preemptive scheduling\n");
    printf("Press 6 for SJF non preemptive scheduling\n");
    printf("Enter your choice:\n");
    cin >> choice;
    switch (choice) {
    case 1: {
        fcfs_sched();
        break;
    }
    case 2: {
        PrioPE();
        break;
    }
    case 3: {
        PrioNPE();
        break;
    }
    case 4: {
        RR_sched();
        break;
    }
    case 5: {
        SJF_PE();
        break;
    }
    case 6: {
        SJF_NPE();
        break;
    }
    default:
        printf("wrong Input\n");
    }
    return 0;
}


