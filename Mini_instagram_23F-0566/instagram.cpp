#include "instagram.h"
///======== Constructor ===========///
Instagram::Instagram()
{
    user_count = 0;
    bst = new BST();
    connections = nullptr;
    user = nullptr;
    activeuser = nullptr;
}
//////////////////////////////////////////
/////////////////////////////////////////
///////////////////////////////////////
///======= Update Connections =======///
int** Instagram::updateConnections()
{
    if (user_count <= 0)
        return nullptr;
    int** temp_connections = new int* [user_count];
    for (int i = 0; i < user_count; i++)
    {
        temp_connections[i] = new int[user_count];
        for (int j = 0; j < user_count; j++)
        {
            temp_connections[i][j] = 0;
        }
    }

    if (connections != nullptr)
    {
        int oldSize = user_count - 1;
        for (int i = 0; i < oldSize; i++)
        {
            for (int j = 0; j < oldSize; j++)
            {
                temp_connections[i][j] = connections[i][j];
            }
        }

        for (int i = 0; i < oldSize; i++)
        {
            delete[] connections[i];
        }
        delete[] connections;
    }

    return temp_connections;
}
//////////////////////////////////////////
/////////////////////////////////////////
///////////////////////////////////////
///======= Show Menu ======= ///
void Instagram::showMenu()
{
    int choice;
    cout << "1. Create Account" << endl;
    cout << "2. Log In" << endl;
    cout << "3. Exit" << endl;
    cout << "Enter your choice: ";
    cin >> choice;
    while (cin.fail() || choice < 1 || choice > 3)
    {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Invalid input!! Please try again: ";
        cin >> choice;
    }
    cin.ignore();
    switch (choice)
    {
    case 1:
        createAccount();
        break;
    case 2:
        logIn();
        break;
        // case 3:
        //     showConnections();
        //     showMenu();
        //     break;
    case 3:
        cout << "Goodbye!" << endl;
        break;
    }
}
//////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
///======= Create Account ======= ///
void Instagram::createAccount()
{
    cout << "Enter the following details to Create New Account: " << endl;
    ///////////////////////////// Username //////////////////////////////////
    string username;
    cout << "Enter username: ";
    getline(cin, username);

    while (!validateusername(username) || search(username))
    {
        cout << "Username Is Already Registred!! OR Invalid Username " << endl;
        cout << "Enter username: ";
        getline(cin, username);
    }

    ///////////////////////////// Email //////////////////////////////////
    string email;
    cout << "Enter email: ";
    getline(cin, email);

    while (!validate_email(email))
    {
        cout << "Invalid email. Please enter a valid email: ";
        getline(cin, email);
    }
    ///////////////////////////// Password //////////////////////////////////
    string password;
    cout << "Enter password: ";
    getline(cin, password);
    while (!validate_strong_password(password))
    {
        cout << "Invalid password. Please enter a strong password: ";
        getline(cin, password);
    }
    cout << "============================" << endl;
    cout << "Sign up successfull!!" << endl;
    cout << "Let' Setup Your Profile" << endl;
    cout << "============================" << endl;
    ///================ First Name ==================///
    string first_name;
    cout << "Enter First Name: ";
    getline(cin, first_name);
    while (cin.fail() || first_name.empty() || first_name[0] == ' ')
    {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Invalid input! Please try again: ";
        getline(cin, first_name);
    }
    ///================ Last Name ===============///
    string last_name;
    cout << "Enter Last Name: ";
    getline(cin, last_name);
    while (cin.fail() || last_name.empty() || last_name[0] == ' ')
    {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Invalid input! Please try again: ";
        getline(cin, last_name);
    }
    ///================== DOB =================///
    string DOB;
    cout << "Enter DOB (DD-MM-YYYY): ";
    getline(cin, DOB);
    while (!validate_DOB(DOB))
    {
        cout << "Invalid DOB. Please enter a valid DOB: ";
        getline(cin, DOB);
    }
    ///================= Gender ================///
    int choice;
    cout << "1. Male" << endl;
    cout << "2. Female" << endl;
    cout << "Choose Your Gender :" << endl;
    cin >> choice;
    char gender;
    while (cin.fail() || choice < 1 || choice > 2)
    {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Invalid input!! Please try again: ";
        cin >> choice;
    }
    if (choice == 1)
    {
        gender = 'M';
    }
    else if (choice == 2)
    {
        gender = 'F';
    }
    cin.ignore();
    User* newUser = new User(username, email, password, first_name, last_name, DOB, gender);
    cout << "============================" << endl;
    cout << "Let's Secure Your Account" << endl;
    newUser->setSecurityAnswers();
    bst->insert(newUser);
    user_count++;
    int** new_connections = updateConnections();
    if (new_connections != nullptr)
    {
        connections = new_connections;
    }
    cout << "============================" << endl;
    cout << "Yahoooo You Made it!! " << endl;
    cout << "Welcome To Instagram" << endl;
    cout << "============================" << endl;
    setActiveUser(bst->search(username));
    home(username);
}
//////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
/// ======= Search ======= ///
bool Instagram::search(string username)
{
    BSTNode* userNode = bst->search(username);
    return userNode != nullptr;
}
//////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
///======= Log In ======= ///
void Instagram::logIn()
{
    string username;
    string password;
    cout << "Enter username: ";
    getline(cin, username);
    while (!validateusername(username))
    {
        cout << "Invalid Username " << endl;
        cout << "Enter username: ";
        getline(cin, username);
    }
    cout << "Enter password: ";
    getline(cin, password);
    bool is_valid = false;
    BSTNode* userNode = bst->search(username);

    if (userNode != nullptr && userNode->user->getpassword() == password)
    {
        activeuser = userNode;
        time_t now = time(0);
        tm ltm; // Declare a local `tm` structure

        // Use localtime_s instead of localtime
        localtime_s(&ltm, &now);

        // Format the time using strftime
        char formatted_time[20]; // Buffer for formatted time
        strftime(formatted_time, sizeof(formatted_time), "%Y-%m-%d %H:%M:%S", &ltm); // Format: YYYY-MM-DD HH:MM:SS

        userNode->user->setlast_sign_in(formatted_time); // Pass formatted time as a string
        is_valid = true;
    }


    if (is_valid)
    {
        cout << "Login successfull!!" << endl;
        setActiveUser(bst->search(username));
        home(username);
    }
    else
    {
        cout << "Invalid username or password" << endl;
        showMenu();
    }
}
///////////////////////////////////////////////////////
///////////////////////////////////////////////////////
///////////////////////////////////////////////////////
/////////// Reset Password //////////
void Instagram::resetpassword()
{
    if (activeuser->user->verifySecurityAnswers())
    {
        string password;
        cout << "Enter new password: ";
        getline(cin, password);
        while (!validate_strong_password(password) || password == activeuser->user->getpassword())
        {
            cout << "Please enter a new and strong password: ";
            getline(cin, password);
        }
        activeuser->user->setpassword(password);
        cout << "Password updated successfully." << endl;
        cout << "Press 1 to go back to home" << endl;
        int choice;
        cin >> choice;
        while (cin.fail() || choice < 1 || choice > 1)
        {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Invalid input!! Please try again: ";
            cin >> choice;
        }
        if (choice == 1)
        {
            home(activeuser->user->getusername());
        }
    }
    else
    {
        cout << "Invalid Security Answers" << endl;
    }
}
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///======= search Profile ======= ///
void Instagram::searchProfile()
{
    string username;
    cout << "Enter username: ";
    getline(cin, username);
    int choice;
    // Search for the user in the BST
    BSTNode* userNode = bst->search(username);
    if (userNode != nullptr)
    {
        // User found
        cout << "+----------------------- User Profile--------------------------+" << endl;
        cout << "First Name: " << userNode->user->getfirst_name() << endl;
        cout << "Last Name: " << userNode->user->getlast_name() << endl;
        cout << "Username: " << userNode->user->getusername() << endl;
        cout << "+-------------------------------------------------+" << endl;
        cout << "1. Add Friend" << endl;
        cout << "2. Send Message" << endl;
        cout << "3. Back" << endl;
        cout << "Enter Your Choice: ";
        cin >> choice;
        while (cin.fail() || choice < 1 || choice > 3)
        {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Invalid input!! Please try again: ";
            cin >> choice;
        }
        cin.ignore();

        switch (choice)
        {
        case 1:
            addfriend(userNode->user->getusername());
            break;
        case 2:
        {
            sendMessage(userNode->user->getusername());
            home(activeuser->user->getusername());
            break;
        }
        case 3:
            home(activeuser->user->getusername());
            break;
        default:
            cout << "Invalid choice!" << endl;
            home(activeuser->user->getusername());
            break;
        }
    }
    else
    {
        cout << "User Not Found!!" << endl;
        home(activeuser->user->getusername());
    }
}
/// === Set Active User === ///
void Instagram::setActiveUser(BSTNode* activeuser)
{
    this->activeuser = activeuser;
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///================================ Sign Out=============================== ///
void Instagram::signout()
{
    cout << "You have been signed out" << endl;
    showMenu();
}
// === build news feed === //
void Instagram::buildNewsFeed()
{
    if (activeuser == nullptr)
    {
        cout << "Error: No active user" << endl;
        return;
    }
    activeuser->user->clearNewsFeed();
    int active_user_index = getuserindex(activeuser->user->getusername());
    if (active_user_index == -1)
    {
        cout << "Error: Active user not found in the system" << endl;
        return;
    }

    int* direct_friends = new int[user_count]();
    int direct_friend_count = 0;

    for (int i = 0; i < user_count; i++)
    {
        if (connections[active_user_index][i] == 1)
        {
            direct_friends[direct_friend_count++] = i;
        }
    }

    cout << "News Feed for " << activeuser->user->getusername() << ":" << endl;
    for (int i = 0; i < direct_friend_count; i++)
    {
        BSTNode* friend_node = findUserNodeByIndex(bst->getRoot(), direct_friends[i], i);
        if (friend_node != nullptr && friend_node->user != nullptr)
        {
            activeuser->user->setNewsFeed(friend_node->user->getPostText(), friend_node->user->getPostDate(), friend_node->user->getusername());
        }
    }

    delete[] direct_friends;
}
void Instagram::showNewsFeed()
{
    activeuser->user->showNewsFeed();
}

///================================ Home ================================= ///
void Instagram::home(string username)
{
    int choice;
    string post;
    string date;
    int acceptedCount = 0;
    int* accepted_indices;
    int subchoice;
    string poster_username;
    int poster_index;
    cout << "welcome " << username << endl;
    cout << "1. Show News Feed" << endl;
    cout << "2. Search User" << endl;
    cout << "3. New Post" << endl;
    cout << "4. Show Notifications" << endl;
    cout << "5. Show My Posts" << endl;
    cout << "6. Show Requests" << endl;
    cout << "7. Show Follow List" << endl;
    cout << "8. Show Messages" << endl;
    cout << "9. Sign Out" << endl;
    cout << "10. Reset Password" << endl;
    cout << "Enter Choice:";
    cin >> choice;
    while (cin.fail() || choice < 1 || choice > 10)
    {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Invalid input!! Please try again: ";
        cin >> choice;
    }
    cin.ignore();

    switch (choice)
    {
    case 1:
        buildNewsFeed();
        showNewsFeed();
        cout << "Press 1 to go back to home" << endl;
        cin >> subchoice;
        while (cin.fail() || subchoice < 1 || subchoice > 1)
        {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Invalid input!! Please try again: ";
            cin >> subchoice;
        }
        if (subchoice == 1)
        {
            home(activeuser->user->getusername());
        }
        break;
    case 2:
        searchProfile();
        break;
    case 3:
        poster_username = activeuser->user->getusername();
        activeuser->user->newPost();
        poster_index = getuserindex(poster_username);
        for (int i = 0; i < user_count; i++)
        {
            if (connections[poster_index][i] == 1)
            {
                string friend_username = getUsernameByIndex(i);
                BSTNode* friend_node = bst->search(friend_username);
                if (friend_node != nullptr && friend_node->user != nullptr)
                {
                    friend_node->user->sendNotifications("post", poster_username);
                }
            }
        }

        cout << "Press 1 to go back to home" << endl;
        cin >> subchoice;
        while (cin.fail() || subchoice < 1 || subchoice > 1)
        {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Invalid input!! Please try again: ";
            cin >> subchoice;
        }
        if (subchoice == 1)
        {
            home(activeuser->user->getusername());
        }
        break;
    case 4:
        showNotifiactions();
        cout << "Press 1 to go back to home" << endl;
        cin >> subchoice;
        while (cin.fail() || subchoice < 1 || subchoice > 1)
        {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Invalid input!! Please try again: ";
            cin >> subchoice;
        }
        if (subchoice == 1)
        {
            home(activeuser->user->getusername());
        }
        break;
    case 5:
        activeuser->user->showMyPosts();
        cout << "Press 1 to go back to home" << endl;
        cin >> subchoice;
        while (cin.fail() || subchoice < 1 || subchoice > 1)
        {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Invalid input!! Please try again: ";
            cin >> subchoice;
        }
        if (subchoice == 1)
        {
            home(activeuser->user->getusername());
        }
        break;
    case 6:
        accepted_indices = activeuser->user->showRequests(connections, acceptedCount);
        if (accepted_indices != nullptr)
        {
            for (int i = 0; i < acceptedCount; i++)
            {
                string sender_username = getUsernameByIndex(accepted_indices[i]);
                bst->search(sender_username)->user->sendNotifications("accepted", activeuser->user->getusername());
                activeuser->user->addFriend(sender_username);
            }
            delete[] accepted_indices;
        }

        cout << "Press 1 to go back to home" << endl;
        cin >> subchoice;
        while (cin.fail() || subchoice < 1 || subchoice > 1)
        {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Invalid input!! Please try again: ";
            cin >> subchoice;
        }
        if (subchoice == 1)
        {
            home(activeuser->user->getusername());
        }
        break;
    case 7:
        showFriendList();
        cout << "Press 1 to go back to home" << endl;
        cin >> subchoice;
        while (cin.fail() || subchoice < 1 || subchoice > 1)
        {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Invalid input!! Please try again: ";
            cin >> subchoice;
        }
        if (subchoice == 1)
        {
            home(activeuser->user->getusername());
        }
        break;
        // case 8:
        //     showSuggestion();
        //     cout << "Press 1 to go back to home" << endl;
        //     cin >> subchoice;
        //     while (cin.fail() || subchoice < 1 || subchoice > 1)
        //     {
        //         cin.clear();
        //         cin.ignore(1000, '\n');
        //         cout << "Invalid input!! Please try again: ";
        //         cin >> subchoice;
        //     }
        //     if (subchoice == 1)
        //     {
        //         home(activeuser->user->getusername());
        //     }
        //     break;
    case 8:
        showMessages();
        cout << "Press 1 to go back to home" << endl;
        cin >> subchoice;
        while (cin.fail() || subchoice < 1 || subchoice > 1)
        {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Invalid input!! Please try again: ";
            cin >> subchoice;
        }
        if (subchoice == 1)
        {
            home(activeuser->user->getusername());
        }
        break;
    case 9:
        signout();
        break;
    case 10:
        resetpassword();
        break;
    default:
        cout << "Invalid choice" << endl;
        home(activeuser->user->getusername());
        break;
    }
}

//// ===== get user index ======== //////
int Instagram::getuserindex(string username)
{
    int current_index = 0;
    BSTNode* node = bst->getRoot();
    return findIndexInBST(node, username, current_index);
}

//// ========= add friend ======== ///////////
void Instagram::addfriend(string username)
{
    if (activeuser == nullptr)
    {
        cout << "No active user session!" << endl;
        return;
    }

    BSTNode* userNode = bst->search(username);
    if (userNode == nullptr)
    {
        cout << "User not found" << endl;
        return;
    }

    if (username == activeuser->user->getusername())
    {
        cout << "Cannot send request to yourself!" << endl;
        return;
    }

    if (connections == nullptr)
    {
        cout << "Error: Connection matrix not initialized" << endl;
        return;
    }

    int senderIndex = getuserindex(activeuser->user->getusername());
    int receiverIndex = getuserindex(username);

    if (senderIndex == -1 || receiverIndex == -1)
    {
        cout << "Error: Could not determine user indices" << endl;
        return;
    }

    if (senderIndex >= user_count || receiverIndex >= user_count)
    {
        cout << "Error: Invalid user indices" << endl;
        home(activeuser->user->getusername());
        return;
    }

    if (connections[senderIndex][receiverIndex] == 1 || connections[receiverIndex][senderIndex] == 1)
    {
        cout << "Connection already exists!" << endl;
        home(activeuser->user->getusername());
        return;
    }

    userNode->user->sendRequest(activeuser->user->getusername(),
        senderIndex, receiverIndex, connections);
    userNode->user->sendNotifications("request", activeuser->user->getusername());
    activeuser->user->addFriend(username);

    // cout << "Debug - Initial connection status:" << endl;
    // cout << "connections[" << senderIndex << "][" << receiverIndex << "] = "
    //      << connections[senderIndex][receiverIndex] << endl;

    home(activeuser->user->getusername());
}

void Instagram::showConnections()
{
    if (connections == nullptr)
    {
        cout << "Error: Connection matrix not initialized" << endl;
        return;
    }

    for (int i = 0; i < user_count; i++)
    {
        for (int j = 0; j < user_count; j++)
        {
            cout << connections[i][j] << " ";
        }
        cout << endl;
    }
}

void Instagram::showFriendList()
{
    if (activeuser == nullptr)
    {
        cout << "Error: No active user" << endl;
        return;
    }

    cout << "Friend List for " << activeuser->user->getusername() << ":" << endl;
    activeuser->user->displayAllFriends();
}

string Instagram::getUsernameByIndex(int index)
{
    int current_index = 0;
    BSTNode* node = findUserNodeByIndex(bst->getRoot(), index, current_index);
    if (node != nullptr && node->user != nullptr)
    {
        return node->user->getusername();
    }
    return "";
}

BSTNode* Instagram::findUserNodeByIndex(BSTNode* root, int target_index, int& current_index)
{
    if (root == nullptr)
        return nullptr;

    BSTNode* left_result = findUserNodeByIndex(root->left, target_index, current_index);
    if (left_result != nullptr)
        return left_result;

    if (current_index == target_index)
        return root;
    current_index++;

    return findUserNodeByIndex(root->right, target_index, current_index);
}
void Instagram::showNotifiactions()
{
    activeuser->user->showNotifications();
}
// Update in instagram.cpp
void Instagram::showMessages()
{
    string username;
    if (activeuser == nullptr)
    {
        cout << "No active user session!" << endl;
        return;
    }

    activeuser->user->showMessages();

    cout << "\nOptions:" << endl;
    cout << "1. Open a chat" << endl;
    cout << "2. New message" << endl;
    cout << "3. Back to home" << endl;

    int choice;
    cout << "Enter your choice: ";
    cin >> choice;
    while (cin.fail() || choice < 1 || choice > 3)
    {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Invalid input!! Please try again: ";
        cin >> choice;
        cin.ignore();
    }
    cin.ignore();
    switch (choice)
    {
    case 1:
    {
        cout << "Enter username to view chat: ";
        string username;
        getline(cin, username);

        BSTNode* otherUser = bst->search(username);
        if (otherUser == nullptr)
        {
            cout << "User not found!" << endl;
            return;
        }

        activeuser->user->showChatWith(username);

        cout << "\nWant to send a new message? (y/n): ";
        char response;
        cin >> response;
        cin.ignore();

        if (response == 'y' || response == 'Y')
        {
            sendMessage(username);
        }
        break;
    }
    case 2:
        cout << "Enter username to message: ";
        getline(cin, username);
        sendMessage(username);
        break;
    case 3:
        return;
    default:
        cout << "Invalid choice!" << endl;
    }
}

void Instagram::sendMessage(string recipient)
{
    if (activeuser == nullptr)
    {
        cout << "No active user session!" << endl;
        return;
    }

    BSTNode* recipientNode = bst->search(recipient);
    if (recipientNode == nullptr)
    {
        cout << "User not found!" << endl;
        return;
    }

    cout << "Enter your message: ";
    string message;
    getline(cin, message);

    activeuser->user->sendMessage(recipient, message);
    recipientNode->user->sendMessage(activeuser->user->getusername(), message);
    recipientNode->user->sendNotifications("message", activeuser->user->getusername());
    cout << "Message sent successfully!" << endl;
}
