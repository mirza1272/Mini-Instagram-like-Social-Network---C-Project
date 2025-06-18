#pragma once
#include <iostream>
#include <string>
#include <ctime>
#include "post.h"
#include "requestList.h"
#include "notificationList.h"
#include "friendList.h"
#include "newsFeed.h"
#include "messages.h"
using namespace std;

class User
{
private:
    string username;
    string password;
    string email;
    string first_name;
    string last_name;
    char gender;
    string last_sign_in;
    string DOB;
    PostStack post_stack;
    RequestList request_list;
    FriendList friend_list;
    NotificationList notification_list;
    NewsFeed news_feed;
    Messages messages;
    string security_answers[3];
    string security_questions[3];

public:
    User();
    User(string username, string email, string password, string first_name, string last_name, string DOB, char gender);

    /////////// Setters /////////////
    void setusername(string);
    void setpassword(string);
    void setemail(string);
    void setfirst_name(string);
    void setlast_name(string);
    void setlast_sign_in(string);
    void setgender(char);
    void setDOB(string);

    ////// Getters ///////
    string getfirst_name();
    string getlast_name();
    string getlast_sign_in();
    string getusername();
    string getpassword();
    string getemail();
    char getgender();
    string getDOB();

    /////////// Functions /////////////////
    bool verifySecurityAnswers();
    void setSecurityAnswers();

    // ====== Post Functions ====== //
    void newPost();
    void getLatestPost();
    void showMyPosts();
    string getPostText();
    string getPostDate();
    string getPostUsername();

    // === Request Functions === //
    void sendRequest(string sender, int senderIndex, int receiverIndex, int** Connection);
    int* showRequests(int** Connection, int& is_accepted);

    // ====== Friend Functions ====== //
    void addFriend(string f_name);
    void displayAllFriends();
    void clearFriendList();

    // === Notifications === //
    void sendNotifications(string, string);
    void showNotifications();

    // === News Feed === //
    void showNewsFeed();
    void setNewsFeed(string post, string date, string username);
    void clearNewsFeed();

    //== Messages ==//
    void sendMessage(string receiver, string content);
    void showMessages();
    void showChatWith(string username);
};
