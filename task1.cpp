#include <iostream>
using namespace std;

template <class T>
class MyQueue
{
private:
    T* arr;
    int maxSize;
    int currentSize;
    int front;
    int rear;

public:
    MyQueue(int size)
    {
        maxSize = size;
        currentSize = 0;
        arr = new T[maxSize];
        front = 0;
        rear = -1;
    }

    ~MyQueue()
    {
        delete[] arr;
    }

    bool isFull()
    {
        return currentSize == maxSize;
    }

    bool isEmpty()
    {
        return currentSize == 0;
    }

    void enqueue(T data)
    {
        if (isFull())
        {
            cout << "Queue Overflow! Queue is full.\n";
            return;
        }

        rear++;
        arr[rear] = data;
        currentSize++;
        cout << "Element added successfully.\n";
    }

    T dequeue()
    {
        if (isEmpty())
        {
            cout << "Queue Underflow! Queue is empty.\n";
            return T();
        }

        T removed = arr[front];

        for (int i = front; i < rear; i++)
        {
            arr[i] = arr[i + 1];
        }

        rear--;
        currentSize--;

        return removed;
    }

    T peek()
    {
        if (isEmpty())
        {
            cout << "Queue is empty.\n";
            return T();
        }

        return arr[front];
    }

    void display()
    {
        if (isEmpty())
        {
            cout << "Queue is empty.\n";
            return;
        }

        cout << "Queue elements: ";
        for (int i = front; i <= rear; i++)
        {
            cout << arr[i] << " ";
        }
        cout << endl;
    }
};

int main()
{
    int size;
    cout << "Enter queue size: ";
    cin >> size;

    MyQueue<int> q(size);

    int choice, value;

    do
    {
        cout << "\n===== MENU =====\n";
        cout << "1. Enqueue\n";
        cout << "2. Dequeue\n";
        cout << "3. Peek\n";
        cout << "4. isEmpty\n";
        cout << "5. isFull\n";
        cout << "6. Display\n";
        cout << "0. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            cout << "Enter value: ";
            cin >> value;
            q.enqueue(value);
            break;

        case 2:
            if (!q.isEmpty())
                cout << "Removed: " << q.dequeue() << endl;
            else
                q.dequeue();
            break;

        case 3:
            if (!q.isEmpty())
                cout << "Front: " << q.peek() << endl;
            else
                q.peek();
            break;

        case 4:
            cout << (q.isEmpty() ? "Queue is empty\n" : "Queue is not empty\n");
            break;

        case 5:
            cout << (q.isFull() ? "Queue is full\n" : "Queue is not full\n");
            break;

        case 6:
            q.display();
            break;

        case 0:
            cout << "Exiting...\n";
            break;

        default:
            cout << "Invalid choice!\n";
        }

    } while (choice != 0);

    return 0;
}