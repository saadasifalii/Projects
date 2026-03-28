#include <iostream>
#include <string>
using namespace std;

struct Customer
{
    string name;
    string transaction;
};

class CircularQueue
{
private:
    Customer* arr;
    int front;
    int rear;
    int maxSize;
    int currentSize;

public:
    CircularQueue(int size)
    {
        maxSize = size;
        arr = new Customer[maxSize];
        front = 0;
        rear = -1;
        currentSize = 0;
    }

    ~CircularQueue()
    {
        delete[] arr;
    }

    bool isEmpty()
    {
        return currentSize == 0;
    }

    bool isFull()
    {
        return currentSize == maxSize;
    }

    void enqueue(Customer c)
    {
        if (isFull())
        {
            cout << "Queue Overflow! No more customers can be added.\n";
            return;
        }

        rear = (rear + 1) % maxSize;
        arr[rear] = c;
        currentSize++;
        cout << "Customer added successfully.\n";
    }

    Customer dequeue()
    {
        if (isEmpty())
        {
            cout << "Queue Underflow! No customers to serve.\n";
            return {"", ""};
        }

        Customer servedCustomer = arr[front];
        front = (front + 1) % maxSize;
        currentSize--;
        return servedCustomer;
    }

    void display()
    {
        if (isEmpty())
        {
            cout << "No customers are waiting.\n";
            return;
        }

        cout << "\nCustomers waiting in queue:\n";
        int i = front;
        for (int count = 0; count < currentSize; count++)
        {
            cout << "Name: " << arr[i].name << ", Transaction: " << arr[i].transaction << endl;
            i = (i + 1) % maxSize;
        }
    }

    int totalCustomers()
    {
        return currentSize;
    }
};

int main()
{
    int size, choice;
    cout << "Enter queue size: ";
    cin >> size;
    cin.ignore();

    CircularQueue q(size);

    do
    {
        cout << "\n===== BANK QUEUE MENU =====\n";
        cout << "1. Add a customer\n";
        cout << "2. Serve a customer\n";
        cout << "3. Display all waiting customers\n";
        cout << "4. Show total number of customers waiting\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore();

        if (choice == 1)
        {
            Customer c;
            cout << "Enter customer name: ";
            getline(cin, c.name);
            cout << "Enter transaction type: ";
            getline(cin, c.transaction);
            q.enqueue(c);
        }
        else if (choice == 2)
        {
            if (!q.isEmpty())
            {
                Customer served = q.dequeue();
                cout << "Served Customer: " << served.name << ", Transaction: " << served.transaction << endl;
            }
            else
            {
                q.dequeue();
            }
        }
        else if (choice == 3)
        {
            q.display();
        }
        else if (choice == 4)
        {
            cout << "Total customers waiting: " << q.totalCustomers() << endl;
        }
        else if (choice == 5)
        {
            cout << "Exiting program...\n";
        }
        else
        {
            cout << "Invalid choice. Try again.\n";
        }

    } while (choice != 5);

    return 0;
}