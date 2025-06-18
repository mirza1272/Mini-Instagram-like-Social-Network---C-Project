#include "notificationList.h"
#include <iostream>
using namespace std;
NotificationList::NotificationList()
{
    this->messages[0] = " Made a New Post !!";
    this->messages[1] = " Sent You Follow Request!!";
    this->messages[2] = " has Accepted Your Follow Request!!";
    this->messages[3] = "Sent You Message";
    top = nullptr;
}
void NotificationList::addNotification(string type, string username)
{
    if (type == "request")
    {
        string message = username + messages[1];
        NotificationNode* newNode = new NotificationNode(type, username, message);
        newNode->next = top;
        top = newNode;
    }
    else if (type == "accepted")
    {
        string message = username + messages[2];
        NotificationNode* newNode = new NotificationNode(type, username, message);
        newNode->next = top;
        top = newNode;
    }
    else if (type == "post")
    {
        string message = username + messages[0];
        NotificationNode* newNode = new NotificationNode(type, username, message);
        newNode->next = top;
        top = newNode;
    }
    else if (type == "message")
    {
        string message = username + messages[3];
        NotificationNode* newNode = new NotificationNode(type, username, message);
        newNode->next = top;
        top = newNode;
    }
    else
    {
        cout << "Exception" << endl;
    }
}
void NotificationList::showNotifications()
{
    if (top == nullptr)
    {
        cout << "No Notification!" << endl;
        return;
    }

    NotificationNode* current = top;
    int count = 1;

    while (current != nullptr)
    {
        cout << count++ << ". " << current->notification << endl;
        current = current->next;
    }
    cout << endl;
}