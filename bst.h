//
// Created by Diego Pacheco Ferrel on 26/05/23.
//

#ifndef BLOCKCHAIN_BST_H
#define BLOCKCHAIN_BST_H

#include <iostream>
#include <cmath>
#include "node.h"

using namespace std;

template <typename T>
class BSTree
{
private:
    NodeBT<T> *root;

public:
    BSTree() : root(nullptr) {}
    void insert(T value)
    {
        insert(this->root, value);
    }
    bool find(T value)
    {
        return find(this->root, value);
    }
    void displayInOrder()
    {
        displayInOrder(this->root);
    }
    void displayPreOrder()
    {
        displayPreOrder(this->root);
    }
    void displayPostOrder()
    {
        displayPostOrder(this->root);
    }
    int height()
    {
        return height(this->root);
    }
    T minValue()
    {
        return minValue(this->root);
    }
    T maxValue()
    {
        return maxValue(this->root);
    }
    bool isBalanced()//O(n^2)
    {
        return isBalanced(this->root);
    }
    bool isBalancedOptimo()//O(n)
    {
        if (this->root == nullptr) return true;
        return isBalancedOptimo(this->root) != -2;//-2 indica que no esta balanceado
    }
    int size()
    {
        return size(this->root);
    }
    void remove(T value)
    {
        remove(this->root, value);
    }

    ~BSTree(){
        if(this->root != nullptr){
            this->root->killSelf();
        }
    }

private:
    void displayInOrder(NodeBT<T> *node);
    void displayPreOrder(NodeBT<T> *node);
    void displayPostOrder(NodeBT<T> *node);
    void insert(NodeBT<T> *&node, T value);
    bool find(NodeBT<T> *node, T value);
    int height(NodeBT<T> *node);
    bool isBalanced(NodeBT<T> *node);
    T minValue(NodeBT<T> *node);
    T maxValue(NodeBT<T> *node);
    int size(NodeBT<T> *node);
    void remove(NodeBT<T> *&node, T value);
    int isBalancedOptimo(NodeBT<T> *node);

};

template <typename T>
void BSTree<T>::insert(NodeBT<T> *&node, T value)
{
    if (node == nullptr)
        node = new NodeBT<T>(value);
    else if (value < node->data)
        insert(node->left, value);
    else
        insert(node->right, value);
}

template <typename T>
bool BSTree<T>::find(NodeBT<T> *node, T value)
{
    if (node == nullptr)
        return false;
    else if (value < node->data)
        return find(node->left, value);
    else if (value > node->data)
        return find(node->right, value);
    else
        return true;
}

template <typename T>
int BSTree<T>::height(NodeBT<T> *node)
{
    if (node == nullptr)
        return -1;
    else
        return max(height(node->left), height(node->right)) + 1;
}

template <typename T>
bool BSTree<T>::isBalanced(NodeBT<T> *node) //O(n^2)
{
    if (node == nullptr)
        return true;
    else
        return abs(height(node->left) - height(node->right)) <= 1 && isBalanced(node->left) && isBalanced(node->right);
}

template <typename T>
int BSTree<T>::isBalancedOptimo(NodeBT<T> *node)//O(n)
{
    if (node == nullptr)
        return -1;
    else{
        int hleft = isBalancedOptimo(node->left);
        int hright = isBalancedOptimo(node->right);
        if(hleft == -2 || hright== -2 || abs(hleft - hright) > 1)
            return -2;//indicador de no-balanceado
        else
            return max(hleft,hright) + 1;
    }
}

template <typename T>
void BSTree<T>::displayPreOrder(NodeBT<T> *node)
{
    if (node == nullptr)
        return;
    cout << node->data << endl;
    displayPreOrder(node->left);
    displayPreOrder(node->right);
}

template <typename T>
void BSTree<T>::displayInOrder(NodeBT<T> *node)
{
    if (node == nullptr)
        return;
    displayInOrder(node->left);
    cout << node->data<< endl;
    displayInOrder(node->right);
}

template <typename T>
void BSTree<T>::displayPostOrder(NodeBT<T> *node)
{
    if (node == nullptr)
        return;
    displayPostOrder(node->left);
    displayPostOrder(node->right);
    cout << node->data<< endl;
}

template <typename T>
T BSTree<T>::minValue(NodeBT<T> *node)
{
    if (node == nullptr)
        throw("The tree is empty");
    else if (node->left == nullptr)
        return node->data;
    else
        return minValue(node->left);
}

template <typename T>
T BSTree<T>::maxValue(NodeBT<T> *node)
{
    if (node == nullptr)
        throw("The tree is empty");
    else if (node->right == nullptr)
        return node->data;
    else
        return maxValue(node->right);
}

template <typename T>
int BSTree<T>::size(NodeBT<T> *node)
{
    if (node == nullptr)
        return 0;
    else
        return 1 + size(node->left) + size(node->right);
}

template <typename T>
void BSTree<T>::remove(NodeBT<T> *&node, T value)
{
    if (node == nullptr)
        return;
    else if (value < node->data)
        remove(node->left, value);
    else if (value > node->data)
        remove(node->right, value);
    else
    {
        if (node->left == nullptr && node->right == nullptr)
        {
            delete node; //free
            node = nullptr;
        }
        else if (node->left == nullptr)
        {
            NodeBT<T> *temp = node;
            node = node->right;
            delete temp;
        }
        else if (node->right == nullptr)
        {
            NodeBT<T> *temp = node;
            node = node->left;
            delete temp;
        }
        else
        {
            T temp = maxValue(node->left);
            node->data = temp;
            remove(node->left, temp);
        }
    }
}


#endif //BLOCKCHAIN_BST_H
