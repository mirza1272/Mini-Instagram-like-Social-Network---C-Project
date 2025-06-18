#include "newsFeed.h"
NewsFeed::NewsFeed() : top(nullptr) {}
void NewsFeed::addPost(string post, string date, string username)
{
    if (post.empty())
    {
        cout << "Error: Post cannot be empty!" << endl;
        return;
    }
    NewsFeedNode* newNode = new NewsFeedNode(post, date, username);
    newNode->next = top;
    top = newNode;
}
void NewsFeed::displayAllPosts()
{
    if (top == nullptr)
    {
        cout << "News feed is empty!" << endl;
        return;
    }
    NewsFeedNode* current = top;
    int count = 1;
    while (current != nullptr)
    {
        if (current->post != "No posts available.")
            cout << current->username << " has posted: " << current->post << " at " << current->date << endl;
        current = current->next;
    }
    cout << endl;
}

void NewsFeed::clearNewsFeed()
{
    NewsFeedNode* current = top;
    NewsFeedNode* temp;
    while (current != nullptr)
    {
        temp = current;
        current = current->next;
        delete temp;
    }
    top = nullptr;
}