#include "requestList.h"
RequestList::RequestList() : front(nullptr), rear(nullptr) {}

RequestList::~RequestList()
{
    while (front != nullptr)
    {
        RequestNode* temp = front;
        front = front->next;
        delete temp;
    }
    rear = nullptr;
}

void RequestList::addRequest(const string& username, int senderIndex, int receiverIndex, int** Connection)
{
    if (senderIndex < 0 || receiverIndex < 0 || !Connection)
    {
        cout << "Invalid parameters provided.\n";
        return;
    }

    RequestNode* newNode = new RequestNode{
        username,
        senderIndex,
        receiverIndex,
        STATUS_PENDING,
        nullptr };

    if (rear == nullptr)
    {
        front = rear = newNode;
    }
    else
    {
        rear->next = newNode;
        rear = newNode;
    }

    Connection[senderIndex][receiverIndex] = 1;
    cout << "Request added successfully.\n";
}

string getStatusString(int status)
{
    switch (status)
    {
    case STATUS_PENDING:
        return "PENDING";
    case STATUS_ACCEPTED:
        return "ACCEPTED";
    case STATUS_REJECTED:
        return "REJECTED";
    default:
        return "UNKNOWN";
    }
}

void RequestList::displayAllRequests()
{
    if (front == nullptr)
    {
        cout << "No requests.\n";
        return;
    }

    cout << "\nAll Requests:\n";
    RequestNode* current = front;
    int count = 1;

    while (current != nullptr)
    {
        string status;
        if (current->status == STATUS_PENDING)
            status = "PENDING";
        else if (current->status == STATUS_ACCEPTED)
            status = "ACCEPTED";
        else if (current->status == STATUS_REJECTED)
            status = "REJECTED";

        cout << count << ". Request from: " << current->friend_username << " [" << status << "]\n";
        count++;
        current = current->next;
    }
    cout << endl;
}

int* RequestList::showRequests(int** Connection, int& acceptedCount)
{
    if (!Connection || front == nullptr)
    {
        acceptedCount = 0;
        return nullptr;
    }
    displayAllRequests();
    int requestCount = 0;
    RequestNode* temp = front;
    while (temp != nullptr)
    {
        if (temp->status == STATUS_PENDING)
        {
            requestCount++;
        }
        temp = temp->next;
    }

    if (requestCount == 0)
    {
        cout << "No pending requests to process.\n";
        return nullptr;
    }

    AcceptedRequest* acceptedRequests = new AcceptedRequest[requestCount];
    acceptedCount = 0;

    cout << "Choose processing method:\n";
    cout << "1. Process all pending requests\n";
    cout << "2. Process pending by index\n";
    cout << "3. Process pending one by one\n";

    int method;
    cin >> method;
    while (cin.fail() || method < 1 || method > 3)
    {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Invalid input!! Please try again: ";
        cin >> method;
    }
    cin.ignore();

    switch (method)
    {
    case 1:
    {
        cout << "1. Accept all\n2. Reject all\nChoice: ";
        int choice;
        cin >> choice;

        while (cin.fail() || choice < 1 || choice > 2)
        {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Invalid input!! Please try again: ";
            cin >> choice;
        }

        RequestNode* current = front;
        while (current != nullptr)
        {
            if (current->status == STATUS_PENDING)
            {
                if (choice == 1)
                {
                    current->status = STATUS_ACCEPTED;
                    Connection[current->senderIndex][current->receiverIndex] = 1;
                    Connection[current->receiverIndex][current->senderIndex] = 1;
                    acceptedRequests[acceptedCount++].senderIndex = current->senderIndex;
                }
                else
                {
                    current->status = STATUS_REJECTED;
                }
            }
            current = current->next;
        }
        break;
    }

    case 2:
    {
        cout << "Enter request indices to process (0 to finish):\n";
        int* indices = new int[requestCount];
        int idx, indexCount = 0;

        while (true)
        {
            cin >> idx;
            if (idx == 0)
                break;
            if (idx > 0 && idx <= requestCount)
            {
                indices[indexCount++] = idx - 1;
            }
        }

        cout << "1. Accept selected\n2. Reject selected\nChoice: ";
        int choice;
        cin >> choice;
        while (cin.fail() || choice < 1 || choice > 2)
        {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Invalid input!! Please try again: ";
            cin >> choice;
        }
        for (int i = 0; i < indexCount; i++)
        {
            RequestNode* current = front;
            int currentIdx = 0;
            int pendingIdx = -1;

            while (current != nullptr)
            {
                if (current->status == STATUS_PENDING)
                {
                    pendingIdx++;
                    if (pendingIdx == indices[i])
                    {
                        if (choice == 1)
                        {
                            current->status = STATUS_ACCEPTED;
                            Connection[current->senderIndex][current->receiverIndex] = 1;
                            Connection[current->receiverIndex][current->senderIndex] = 1;
                            acceptedRequests[acceptedCount++].senderIndex = current->senderIndex;
                        }
                        else
                        {
                            current->status = STATUS_REJECTED;
                        }
                        break;
                    }
                }
                current = current->next;
            }
        }

        delete[] indices;
        break;
    }

    case 3:
    {
        RequestNode* current = front;
        while (current != nullptr)
        {
            if (current->status == STATUS_PENDING)
            {
                cout << "Processing request from: " << current->friend_username << endl;
                cout << "1. Accept\n2. Reject\nChoice: ";
                int choice;
                cin >> choice;

                while (cin.fail() || choice < 1 || choice > 2)
                {
                    cin.clear();
                    cin.ignore(1000, '\n');
                    cout << "Invalid input!! Please try again: ";
                    cin >> choice;
                }
                if (choice == 1)
                {
                    current->status = STATUS_ACCEPTED;
                    Connection[current->senderIndex][current->receiverIndex] = 1;
                    Connection[current->receiverIndex][current->senderIndex] = 1;
                    acceptedRequests[acceptedCount++].senderIndex = current->senderIndex;
                }
                else
                {
                    current->status = STATUS_REJECTED;
                }

                if (current->next != nullptr)
                {
                    cout << "Process next? (y/n): ";
                    char cont;
                    cin >> cont;
                    if (tolower(cont) != 'y')
                        break;
                }
            }
            current = current->next;
        }
        break;
    }
    }

    int* senderIndices = new int[acceptedCount];
    for (int i = 0; i < acceptedCount; i++)
    {
        senderIndices[i] = acceptedRequests[i].senderIndex;
    }

    delete[] acceptedRequests;
    return senderIndices;
}