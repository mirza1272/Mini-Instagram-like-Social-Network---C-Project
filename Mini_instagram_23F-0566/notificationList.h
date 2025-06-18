#include <iostream>
using namespace std;
struct NotificationNode
{
    string type_of_noti;
    string username;
    NotificationNode* next;
    string notification;
    NotificationNode(string type_of_noti, string username, string notification)
    {
        this->type_of_noti = type_of_noti;
        this->username = username;
        this->notification = notification;
    };
};

class NotificationList
{
private:
    string messages[4];
    NotificationNode* top;

public:
    NotificationList();
    void addNotification(string type, string username);
    void showNotifications();
};