#include <iostream>
#include <string>
using namespace std;

class Queue
{
private:
    string* arr;
    int front;
    int rear;
    int maxSize;

public:
    Queue(int size = 10)
    {
        maxSize = size;
        arr = new string[maxSize];
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

    void enqueue(string flightID)
    {
        if (isFull())
        {
            cout << "Queue Overflow! Cannot add more flights.\n";
            return;
        }
        rear++;
        arr[rear] = flightID;
    }

    string dequeue()
    {
        if (isEmpty())
        {
            return "";
        }
        return arr[front++];
    }

    void display()
    {
        if (isEmpty())
        {
            cout << "Empty";
            return;
        }

        for (int i = front; i <= rear; i++)
        {
            cout << arr[i] << " ";
        }
    }
};

class AirportSystem
{
private:
    Queue emergencyQueue;
    Queue passengerQueue;
    Queue cargoQueue;

public:
    AirportSystem(int size) : emergencyQueue(size), passengerQueue(size), cargoQueue(size) {}

    void enqueue(string flightType, string flightID)
    {
        if (flightType == "Emergency")
        {
            emergencyQueue.enqueue(flightID);
        }
        else if (flightType == "Passenger")
        {
            passengerQueue.enqueue(flightID);
        }
        else if (flightType == "Cargo")
        {
            cargoQueue.enqueue(flightID);
        }
        else
        {
            cout << "Invalid flight type.\n";
            return;
        }

        cout << flightType << " flight " << flightID << " added successfully.\n";
    }

    void dequeue()
    {
        string landedFlight = "";

        if (!emergencyQueue.isEmpty())
        {
            landedFlight = emergencyQueue.dequeue();
            cout << "Emergency flight " << landedFlight << " has landed.\n";
        }
        else if (!passengerQueue.isEmpty())
        {
            landedFlight = passengerQueue.dequeue();
            cout << "Passenger flight " << landedFlight << " has landed.\n";
        }
        else if (!cargoQueue.isEmpty())
        {
            landedFlight = cargoQueue.dequeue();
            cout << "Cargo flight " << landedFlight << " has landed.\n";
        }
        else
        {
            cout << "No flights waiting to land.\n";
        }
    }

    void display()
    {
        cout << "\nEmergency Queue: ";
        emergencyQueue.display();

        cout << "\nPassenger Queue: ";
        passengerQueue.display();

        cout << "\nCargo Queue: ";
        cargoQueue.display();
        cout << endl;
    }

    void demonstrateSequence()
    {
        enqueue("Passenger", "P1");
        enqueue("Cargo", "C1");
        enqueue("Emergency", "E1");
        enqueue("Passenger", "P2");
        enqueue("Cargo", "C2");
        enqueue("Emergency", "E2");

        cout << "\nFlights waiting before landing:\n";
        display();

        cout << "\nLanding order:\n";
        dequeue();
        dequeue();
        dequeue();
        dequeue();
        dequeue();
        dequeue();
    }
};

int main()
{
    int size, choice;
    string type, id;

    cout << "Enter maximum size for each queue: ";
    cin >> size;

    AirportSystem system(size);

    do
    {
        cout << "\n===== AIRPORT RUNWAY MENU =====\n";
        cout << "1. Add flight\n";
        cout << "2. Allow one flight to land\n";
        cout << "3. Display all waiting flights\n";
        cout << "4. Demonstrate given sequence\n";
        cout << "5. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        if (choice == 1)
        {
            cout << "Enter flight type (Emergency/Passenger/Cargo): ";
            cin >> type;
            cout << "Enter flight ID: ";
            cin >> id;
            system.enqueue(type, id);
        }
        else if (choice == 2)
        {
            system.dequeue();
        }
        else if (choice == 3)
        {
            system.display();
        }
        else if (choice == 4)
        {
            system.demonstrateSequence();
        }
        else if (choice == 5)
        {
            cout << "Exiting program...\n";
        }
        else
        {
            cout << "Invalid choice.\n";
        }

    } while (choice != 5);

    return 0;
}