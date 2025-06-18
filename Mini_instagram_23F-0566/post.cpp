#include "post.h"
#include <iostream>
using namespace std;

PostNode::PostNode(string username, string post, string date)
    : username(username), post(post), date(date), next(nullptr) {}

string PostNode::getUsername() const
{
    return username;
}

string PostNode::getPost() const
{
    return post;
}

string PostNode::getDate() const
{
    return date;
}

PostNode* PostNode::getNext() const
{
    return next;
}

void PostNode::setNext(PostNode* next)
{
    this->next = next;
}
/////// Constuctor Implemenattaion /////////////////////////
PostStack::PostStack()
{
    top = nullptr;
}
///////// Add New post  /////////////////////
void PostStack::newPost(string name, string post, string date)
{
    PostNode* newPost = new PostNode(name, post, date);

    if (top == nullptr)
    {
        top = newPost;
    }
    else
    {
        newPost->setNext(top);
        top = newPost;
    }

    cout << "Post added successfully!" << endl;
}
//////// Show lastest Post /////////////////
void PostStack::peek() const
{
    if (top == nullptr)
    {
        cout << "No posts available." << endl;
        return;
    }

    cout << "Top Post: " << endl;
    cout << "Username: " << top->getUsername() << endl;
    cout << "Post: " << top->getPost() << endl;
    cout << "Date: " << top->getDate() << endl;
}

string PostStack::getPost() const
{
    if (top == nullptr)
    {
        return "No posts available.";
    }

    return top->getPost();
}
string PostStack::getDate() const
{
    if (top == nullptr)
    {
        return "No posts available.";
    }

    return top->getDate();
}
string PostStack::getUsername() const
{
    if (top == nullptr)
    {
        return "No posts available.";
    }

    return top->getUsername();
}

/////////////// Destructor implementation ////////////////////////
PostStack::~PostStack()
{
    while (top != nullptr)
    {
        PostNode* temp = top;
        top = top->getNext();
        delete temp;
    }
}

void PostStack::showMyPosts() const
{
    PostNode* current = top;
    if (current == nullptr)
    {
        cout << "No posts available." << endl;
        return;
    }

    cout << "My Posts: " << endl;
    while (current != nullptr)
    {
        cout << "Username: " << current->getUsername() << endl;
        cout << "Post: " << current->getPost() << endl;
        cout << "Date: " << current->getDate() << endl;
        cout << "----------------------" << endl;
        current = current->getNext();
    }
}