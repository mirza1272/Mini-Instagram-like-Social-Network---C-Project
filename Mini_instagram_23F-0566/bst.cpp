#include "bst.h"

BSTNode::BSTNode(User* user)
{
    this->user = user;
    left = right = nullptr;
}

BST::BST()
{
    root = nullptr;
}

void BST::insert(BSTNode*& node, User* user)
{
    if (node == nullptr)
    {
        node = new BSTNode(user);
    }
    else if (user->getusername() < node->user->getusername())
    {
        insert(node->left, user);
    }
    else if (user->getusername() > node->user->getusername())
    {
        insert(node->right, user);
    }
}

BSTNode* BST::search(BSTNode* node, const string& username)
{
    if (node == nullptr)
        return nullptr;
    if (node->user->getusername() == username)
        return node;
    if (username < node->user->getusername())
        return search(node->left, username);
    return search(node->right, username);
}

void BST::insert(User* user)
{
    insert(root, user);
}

BSTNode* BST::search(const string& username)
{
    return search(root, username);
}

BSTNode* BST::getRoot()
{
    return root;
}