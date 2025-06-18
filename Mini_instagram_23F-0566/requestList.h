#include <iostream>
#include <string>
using namespace std;
const int STATUS_PENDING = 0;
const int STATUS_ACCEPTED = 1;
const int STATUS_REJECTED = 2;
struct RequestNode
{
    string friend_username;
    int senderIndex;
    int receiverIndex;
    int status;
    RequestNode* next;
};
struct AcceptedRequest
{
    int senderIndex;
    bool isAccepted;
};

class RequestList
{
private:
    RequestNode* front;
    RequestNode* rear;
    int* receiverIndices;
    int receiverCount;
    void deleteRequest(RequestNode* prev, RequestNode* current);

public:
    RequestList();
    ~RequestList();
    void displayAllRequests();
    void addRequest(const string& username, int senderIndex, int receiverIndex, int** Connection);
    int* showRequests(int** Connection, int& acceptedCount);
};
