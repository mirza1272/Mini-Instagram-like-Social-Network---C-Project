#include <iostream>
#include <string>
using namespace std;
class FriendNode
{
public:
    string friend_username;
    FriendNode* next;
    FriendNode(string f_name) : friend_username(f_name), next(nullptr) {}
};
class FriendList
{
private:
    FriendNode* top;

public:
    FriendList();
    FriendNode* getTop() const;
    void addFriend(string f_name);
    void displayAllFriends();
    void clearFriendList();
    ~FriendList();
};
