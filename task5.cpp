#include <iostream>
#include <string>
using namespace std;

struct Process
{
    string pid;
    int burstTime;
};

class Queue
{
private:
    Process* arr;
    int front;
    int rear;
    int maxSize;

public:
    Queue(int size = 100)
    {
        maxSize = size;
        arr = new Process[maxSize];
        front = 0;
        rear = -1;
    }

    ~Queue()
    {
        delete[] arr;
    }

    bool isEmpty()
    {
        return front > rear;
    }

    bool isFull()
    {
        return rear == maxSize - 1;
    }

    void enqueue(Process p)
    {
        if (isFull())
        {
            cout << "Queue Overflow!\n";
            return;
        }
        rear++;
        arr[rear] = p;
    }

    Process dequeue()
    {
        if (isEmpty())
        {
            return {"", 0};
        }
        return arr[front++];
    }
};

class RoundRobin
{
private:
    Queue readyQueue;

public:
    RoundRobin(int size) : readyQueue(size) {}

    void addProcess(string pid, int burstTime)
    {
        Process p;
        p.pid = pid;
        p.burstTime = burstTime;
        readyQueue.enqueue(p);
        cout << "Process " << pid << " added with burst time " << burstTime << endl;
    }

    void executeNext(int timeSlice)
    {
        if (readyQueue.isEmpty())
        {
            cout << "No process in ready queue.\n";
            return;
        }

        Process current = readyQueue.dequeue();

        cout << "Executing " << current.pid << " for ";

        if (current.burstTime <= timeSlice)
        {
            cout << current.burstTime << " units. ";
            current.burstTime = 0;
            cout << current.pid << " finished.\n";
        }
        else
        {
            cout << timeSlice << " units. ";
            current.burstTime -= timeSlice;
            cout << "Remaining burst time of " << current.pid << " = " << current.burstTime << endl;
            readyQueue.enqueue(current);
        }
    }

    void runAll(int timeSlice)
    {
        cout << "\nExecution Order:\n";
        while (!readyQueue.isEmpty())
        {
            executeNext(timeSlice);
        }
        cout << "All processes completed.\n";
    }
};

int main()
{
    RoundRobin rr(10);

    rr.addProcess("P1", 10);
    rr.addProcess("P2", 4);
    rr.addProcess("P3", 6);

    int timeSlice = 3;
    cout << "\nTime Slice = " << timeSlice << endl;

    rr.runAll(timeSlice);

    return 0;
}