#include "friendList.h"
FriendList::FriendList() : top(nullptr) {}

FriendNode* FriendList::getTop() const
{
    return top;
}

void FriendList::addFriend(string f_name)
{
    if (f_name.empty())
    {
        cout << "Error: Friend username cannot be empty!" << endl;
        return;
    }

    FriendNode* newNode = new FriendNode(f_name);
    newNode->next = top;
    top = newNode;

    cout << "Friend '" << f_name << "' added successfully!" << endl;
}

/// @brief Display all friends in the list
void FriendList::displayAllFriends()
{
    if (top == nullptr)
    {
        cout << "Friend list is empty!" << endl;
        return;
    }

    FriendNode* current = top;
    int count = 1;

    while (current != nullptr)
    {
        cout << count++ << ". " << current->friend_username << endl;
        current = current->next;
    }
    cout << endl;
}

void FriendList::clearFriendList()
{
    FriendNode* current = top;
    FriendNode* temp;

    while (current != nullptr)
    {
        temp = current;
        current = current->next;
        delete temp;
    }
    top = nullptr;
}

FriendList::~FriendList()
{
    clearFriendList();
}
