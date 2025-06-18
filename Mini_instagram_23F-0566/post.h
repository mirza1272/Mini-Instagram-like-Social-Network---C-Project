#include <string>
using namespace std;

class PostNode
{
private:
    string username;
    string post;
    string date;
    PostNode* next;

public:
    ////// Constructor /////////
    PostNode(string username, string post, string date);

    /////////// Getters/////////////
    string getUsername() const;
    string getPost() const;
    string getDate() const;
    PostNode* getNext() const;

    ////////////// Setters/////////////////
    void setNext(PostNode* next);
};

class PostStack
{
private:
    PostNode* top;

public:
    /////////////// Constructor //////////////
    PostStack();

    void newPost(string, string, string);
    void peek() const;
    string getPost() const;
    string getDate() const;
    string getUsername() const;
    void showMyPosts() const;
    /////////////// Destructor //////////////////
    ~PostStack();
};
