#include <string>
#include <iostream>
#include <ctime>
using namespace std;

struct MessageNode
{
    string sender;
    string content;
    string timestamp;
    MessageNode* next;

    MessageNode(string s, string c, string t) : sender(s), content(c), timestamp(t), next(nullptr) {}
};

struct ChatNode
{
    string username;
    MessageNode* messages;
    ChatNode* next;

    ChatNode(string u) : username(u), messages(nullptr), next(nullptr) {}
};

class Messages
{
private:
    ChatNode* chat_list;
    void deleteMessages(MessageNode* head);
    void deleteChatList();
    MessageNode* getLastMessage(MessageNode* head);
    ChatNode* findChat(string username);

public:
    Messages();
    void addMessage(string sender, string receiver, string content);
    void showChat(string username1, string username2);
    void showInbox(string username);
    bool hasChat(string username1, string username2);
    void loadChat(string username1, string username2);
};
