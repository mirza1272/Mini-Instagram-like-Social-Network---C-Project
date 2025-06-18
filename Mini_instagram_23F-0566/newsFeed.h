#include <iostream>
using namespace std;
class NewsFeedNode
{
public:
    string post;
    string date;
    string username;
    NewsFeedNode* next;
    NewsFeedNode(string post, string date, string username) : post(post), date(date), username(username), next(nullptr) {}
};
class NewsFeed
{
private:
    NewsFeedNode* top;

public:
    NewsFeed();
    void addPost(string post, string date, string username);
    void displayAllPosts();
    void clearNewsFeed();
};