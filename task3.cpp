#include <iostream>
#include <string>
using namespace std;

struct Student
{
    string name;
    int score;
    int timeTaken;
};

class LinearQueue
{
private:
    Student* arr;
    int front;
    int rear;
    int maxSize;

public:
    LinearQueue(int size)
    {
        maxSize = size;
        arr = new Student[maxSize];
        front = 0;
        rear = -1;
    }

    ~LinearQueue()
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

    void enqueue(Student s)
    {
        if (isFull())
        {
            cout << "Queue Overflow! Cannot add more students.\n";
            return;
        }

        rear++;
        arr[rear] = s;
    }

    Student dequeue()
    {
        if (isEmpty())
        {
            cout << "Queue Underflow! Queue is empty.\n";
            return {"", 0, 0};
        }

        return arr[front++];
    }

    void display()
    {
        if (isEmpty())
        {
            cout << "No quiz results available.\n";
            return;
        }

        for (int i = front; i <= rear; i++)
        {
            cout << "Name: " << arr[i].name
                 << ", Score: " << arr[i].score
                 << ", Time Taken: " << arr[i].timeTaken << " seconds" << endl;
        }
    }
};

int generateScore()
{
    static int seed = 37;
    seed = (seed * 17 + 13) % 101;
    return seed;
}

int generateTime()
{
    static int seed = 19;
    seed = (seed * 23 + 7) % 60;
    return seed + 1;
}

int main()
{
    int size;
    cout << "Enter maximum number of students: ";
    cin >> size;
    cin.ignore();

    LinearQueue waitingQueue(size);
    LinearQueue resultQueue(size);

    int choice;

    do
    {
        cout << "\n===== QUIZ COMPETITION MENU =====\n";
        cout << "1. Add a student to the waiting queue\n";
        cout << "2. Start the quiz and generate score for one student\n";
        cout << "3. Display results\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore();

        if (choice == 1)
        {
            Student s;
            cout << "Enter student name: ";
            getline(cin, s.name);
            s.score = 0;
            s.timeTaken = 0;
            waitingQueue.enqueue(s);
        }
        else if (choice == 2)
        {
            if (waitingQueue.isEmpty())
            {
                cout << "Quiz has ended. No students left in waiting queue.\n";
            }
            else
            {
                Student s = waitingQueue.dequeue();
                s.score = generateScore();
                s.timeTaken = generateTime();
                resultQueue.enqueue(s);

                cout << "Student " << s.name << " completed the quiz.\n";
                cout << "Score: " << s.score << ", Time Taken: " << s.timeTaken << " seconds\n";

                if (waitingQueue.isEmpty())
                {
                    cout << "Quiz has ended.\n";
                }
            }
        }
        else if (choice == 3)
        {
            cout << "\n===== QUIZ RESULTS =====\n";
            resultQueue.display();
        }
        else if (choice == 4)
        {
            cout << "Exiting program...\n";
        }
        else
        {
            cout << "Invalid choice. Try again.\n";
        }

    } while (choice != 4);

    return 0;
}