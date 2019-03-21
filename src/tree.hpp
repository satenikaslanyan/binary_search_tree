#ifndef LIST_H
#define LIST_H

#include <iostream>

template <typename T>
struct Node
{
    T data;
    Node *left;
    Node *right;
};

template <typename T>
class tree
{
    private:
        Node<T>* root;
        bool search_helper(Node<T>* root, T data);  
        bool find_helper(Node<T>* root, T data);
        void insert_helper(Node<T>* tree_node, T data);
        void in_order_helper(Node<T>* tree_node);
        void pre_order_helper(Node<T>* tree_node);
        void post_order_helper(Node<T>* tree_node);
    public:
        tree();   
        ~tree();
        void delete_tree(Node<T>* node);
        void insert(T data);     
        bool search(T data);
        bool find(T data);
        void in_order();
        void pre_order();
        void post_order();
};

#endif 

template <typename T>
tree<T>::tree() : root(NULL) {}

template <typename T>
void tree<T>::delete_tree(Node<T>* node)
{
    if (node)
    {
        delete_tree(node->left);
        delete_tree(node->right);
        delete node;
    }
}

template <typename T>
tree<T>::~tree()
{
    delete_tree(root);
}

template <typename T>
bool tree<T>::find_helper(Node<T>* root, T data)
{
    if (root == NULL) {
       return false;
    }
    if (root->data == data) { 
        return true;
    }
    if (root->data < data) {
        return find_helper(root->right, data);
    }
    return find_helper(root->left, data);
}

template <typename T>
bool tree<T>::find(T data)
{
    return find_helper(root, data);
}

template <typename T>
bool tree<T>::search_helper(Node<T>* root, T data) 
{ 
    while (root != NULL) 
    { 
        if (data > root->data) {
            root = root->right;
        } else if (data < root->data) {
            root = root->left; 
        } else {
            return true;
        }
    } 
    return false; 
} 

template <typename T>
bool tree<T>::search(T data)
{
    return search_helper(root, data);
}

template <typename T>
void tree<T>::insert_helper(Node<T>* root, T data) 
{
    if (root->data > data) {
        if (!root->left) {
            Node<T>* temp = new Node<T>;
            temp->data = data;
            temp->right = NULL;
            temp->left = NULL;
            root->left = temp;
        } else {
            insert_helper(root->left, data);
        }
    } else {
        if (!root->right) {
            Node<T>* temp = new Node<T>;
            temp->data = data;
            temp->right = NULL;
            temp->left = NULL;
            root->right = temp;
        } else {
            insert_helper(root->right, data);
        }
    }
}

template <typename T>
void tree<T>::insert(T data) 
{
    if (root) {
        insert_helper(root, data);
    } else {
        Node<T>* temp = new Node<T>;
        temp->data = data;
        temp->left = NULL;
        temp->right = NULL;
        root = temp;
    }
}

template <typename T>
void tree<T>::in_order() 
{
    in_order_helper(root);
}

template <typename T>
void tree<T>::pre_order() 
{
    pre_order_helper(root);
}

template <typename T>
void tree<T>::post_order() 
{
    post_order_helper(root);
}

template <typename T>
void tree<T>::in_order_helper(Node<T>* tree_node)
{
        if (tree_node) {
            in_order_helper(tree_node->left);
            std::cout << tree_node->data << "  " ;
            in_order_helper(tree_node->right);
        }
}

template <typename T>
void tree<T>::pre_order_helper(Node<T>* tree_node)
{
        if (tree_node) {
            std::cout << tree_node->data << "  ";
            pre_order_helper(tree_node->left);
            pre_order_helper(tree_node->right);
        }
}

template <typename T>
void tree<T>::post_order_helper(Node<T>* tree_node)
{
        if (tree_node) {
            post_order_helper(tree_node->left);
            post_order_helper(tree_node->right);
            std::cout << tree_node->data << "  ";
        }
}
