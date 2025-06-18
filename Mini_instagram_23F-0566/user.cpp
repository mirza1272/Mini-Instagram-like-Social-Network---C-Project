#include "user.h"
User::User()
{
    username = "";
    email = "";
    password = "";
    first_name = "";
    last_name = "";
    DOB = "";
    gender = '\0';
    security_questions[0] = "What is your pet name?";
    security_questions[1] = "What is your favourite color?";
    security_questions[2] = "What is your favourite food?";
    post_stack = PostStack();
    request_list = RequestList();
    friend_list = FriendList();
    notification_list = NotificationList();
    news_feed = NewsFeed();
    messages = Messages();
}

User::User(string username, string email, string password, string first_name, string last_name, string DOB, char gender)
{
    this->username = username;
    this->email = email;
    this->password = password;
    this->first_name = first_name;
    this->last_name = last_name;
    this->DOB = DOB;
    this->gender = gender;
    security_questions[0] = "What is your pet name?";
    security_questions[1] = "What is your favourite color?";
    security_questions[2] = "What is your favourite food?";
}

////////////// setters ///////////////
void User::setpassword(string password)
{
    this->password = password;
}
void User::setemail(string email)
{
    this->email = email;
}
void User::setfirst_name(string first_name)
{
    this->first_name = first_name;
}
void User::setlast_name(string last_name)
{
    this->last_name = last_name;
}
void User::setlast_sign_in(string last_sign_in)
{
    this->last_sign_in = last_sign_in;
}
void User::setDOB(string DOB)
{
    this->DOB = DOB;
}
void User::setgender(char gender)
{
    this->gender = gender;
}
void User::setusername(string username)
{
    this->username = username;
}

/////////////// Getters ////////////////////
string User::getfirst_name()
{
    return this->first_name;
}
string User::getlast_name()
{
    return this->last_name;
}

string User::getusername()
{
    return this->username;
}
string User::getpassword()
{
    return this->password;
}
string User::getemail()
{
    return email;
}
string User::getDOB()
{
    return DOB;
}
string User::getlast_sign_in()
{
    return last_sign_in;
}
char User::getgender()
{
    return gender;
}

////// verify qs for resetting password //////////////////
bool User::verifySecurityAnswers()
{
    string arr[3];
    for (int i = 0; i < 3; i++)
    {
        cout << "Question " << i + 1 << ":" << security_questions[i] << endl;
        getline(cin, arr[i]);
        while (arr[i] != security_answers[i] || cin.fail() || security_answers[i].empty() || security_answers[i][0] == ' ')
        {
            cout << "Invalid Answer" << endl;
            cout << security_questions[i] << endl;
            getline(cin, arr[i]);
        }
    }
    return true;
}

////////// set security answers at sign up ////////////////////
void User::setSecurityAnswers()
{
    for (int i = 0; i < 3; i++)
    {
        cout << security_questions[i] << endl;
        getline(cin, security_answers[i]);
        while (cin.fail() || security_answers[i].empty() || security_answers[i][0] == ' ')
        {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Invalid input! Please try again: ";
            getline(cin, security_answers[i]);
        }
    }
    cout << "Security Answers Set" << endl;
}

//////// function to add new post ////////////////////////
void User::newPost()
{
    string post;
    cout << "Enter Post: ";
    getline(cin, post);

    // Get current time
    time_t now = time(0);
    tm ltm; // Local time structure

    // Use localtime_s instead of localtime
    localtime_s(&ltm, &now);

    // Format time safely
    char posttime[20]; // Buffer for formatted time
    strftime(posttime, sizeof(posttime), "%Y-%m-%d %H:%M:%S", &ltm); // Format: YYYY-MM-DD HH:MM:SS

    // Use the formatted time
    post_stack.newPost(this->username, post, string(posttime)); // Pass formatted time as string
}

////////// function to get latest post ///////////////////
void User::getLatestPost()
{
    post_stack.peek();
}
string User::getPostText()
{
    return post_stack.getPost();
}
string User::getPostDate()
{
    return post_stack.getDate();
}
string User::getPostUsername()
{
    return username;
}
void User::showMyPosts()
{
    post_stack.showMyPosts();
}

void User::sendRequest(string sender, int senderIndex, int receiverIndex, int** Connection)
{
    request_list.addRequest(sender, senderIndex, receiverIndex, Connection);
}
int* User::showRequests(int** Connection, int& is_accepted)
{
    return request_list.showRequests(Connection, is_accepted);
}

// === Friend Functions === //
void User::addFriend(string f_name)
{
    friend_list.addFriend(f_name);
}
void User::displayAllFriends()
{
    friend_list.displayAllFriends();
}
void User::clearFriendList()
{
    friend_list.clearFriendList();
}

void User::sendNotifications(string type, string username)
{
    notification_list.addNotification(type, username);
}
void User::showNotifications()
{
    notification_list.showNotifications();
}

// == news feed functions == //
void User::showNewsFeed()
{
    news_feed.displayAllPosts();
}
void User::setNewsFeed(string post, string date, string username)
{
    news_feed.addPost(post, date, username);
}

void User::clearNewsFeed()
{
    news_feed.clearNewsFeed();
}
void User::sendMessage(string receiver, string content)
{
    messages.addMessage(username, receiver, content);
}

void User::showMessages()
{
    messages.showInbox(username);
}

void User::showChatWith(string other_username)
{
    messages.showChat(this->username, other_username);
}