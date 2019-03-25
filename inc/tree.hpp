#ifndef LIST_H
#define LIST_H

#include <iostream>
#include <queue>

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
    public:
        Node<T>* root;
        bool search_helper(Node<T>* root, T data);  
        bool find_helper(Node<T>* root, T data);
        void insert_helper(Node<T>* root, T data);
        void in_order_helper(Node<T>* root);
        void pre_order_helper(Node<T>* root);
        void post_order_helper(Node<T>* root);
        Node<T>* remove_helper(Node<T>* root, T data);
        Node<T>* find_max_right(Node<T>* root);
        int max_depth_helper(Node<T>* root);
        void print_given_level(Node<T>* root, int level);
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
        Node<T>* remove(T data);
        int max_depth();
        void level_order();
};

#endif 

template <typename T>
tree<T>::tree() : root(NULL) {}

template <typename T>
void tree<T>::delete_tree(Node<T>* node)
{
    if (NULL != node)
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
    if (NULL == root) {
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
    while (NULL != root) 
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
        if (NULL == root->left) {
            Node<T>* temp = new Node<T>;
            temp->data = data;
            temp->right = NULL;
            temp->left = NULL;
            root->left = temp;
        } else {
            insert_helper(root->left, data);
        }
    } else {
        if (NULL == root->right) {
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
    if (NULL != root) {
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
void tree<T>::in_order_helper(Node<T>* root)
{
    if (NULL != root) {
        in_order_helper(root->left);
        std::cout << root->data << "  " ;
        in_order_helper(root->right);
    }
}

template <typename T>
void tree<T>::pre_order_helper(Node<T>* root)
{
    if (NULL != root) {
        std::cout << root->data << "  ";
        pre_order_helper(root->left);
        pre_order_helper(root->right);
    }
}

template <typename T>
void tree<T>::post_order_helper(Node<T>* root)
{
    if (NULL != root) {
        post_order_helper(root->left);
        post_order_helper(root->right);
        std::cout << root->data << "  ";
    }
}

template <typename T>
Node<T>* tree<T>::find_max_right(Node<T>* root)
{
    if (NULL == root) {
        return NULL;
    }
    while(NULL != root->right) {
        root = root->right;
    }
    return root;
}

template <typename T>
Node<T>* tree<T>::remove_helper(Node<T>* root, T data)
{
    if (NULL == root) {
        return root;
    }
    if (data < root->data) {
        root->left = remove_helper(root->left, data);
    } else if (data > root->data)
        root->right = remove_helper(root->right, data);
    else {
        if(root->right == NULL && root->left == NULL) {
            delete root;
            root = NULL;
        } else if(root->right == NULL) {
            Node<T>* temp = root;
            root= root->left;
            delete temp;
        } else if(root->left == NULL) {
            Node<T>* temp = root;
            root= root->right;
            delete temp;
        } else {
            Node<T>* temp = find_max_right(root->left);
            root->data = temp->data;
            root->left = remove_helper(root->left, temp->data);
        }
    }
    return root;
}

template <typename T>
Node<T>* tree<T>::remove(T data)
{
    return remove_helper(root, data);
}

template <typename T>
int tree<T>::max_depth_helper(Node<T>* root)
{
    if (NULL == root) {
        return 0;
    }
    int l_depth = max_depth_helper(root->left);
    int r_depth = max_depth_helper(root->right);
    return (l_depth > r_depth) ? l_depth + 1 : r_depth + 1;
}

template <typename T>
int tree<T>::max_depth()
{
    return max_depth_helper(root);
}
/*
template <typename T>
void tree<T>::level_order()
{
    std::cout << "Level order traversal is: ";
    if (root == NULL) {
        return;
    }
    std::queue<Node<T>*> q;
    Node<T>* curr = root;
    q.push(curr);
    while (0 != q.size()) {
        curr = q.front();
        q.pop();
        if(curr->left)
            q.push(curr->left);
        if(curr->right)
            q.push(curr->right);
        std::cout << curr->data << "  ";
    }
    std::cout << std::endl;
}
*/

template <typename T>
void tree<T>::level_order()
{
    for (int i = 1; i <= max_depth(); ++i) {
        print_given_level(root, i);
    }
    std::cout << std::endl;
}

template <typename T>
void tree<T>::print_given_level(Node<T>* root, int level)
{
    if (NULL == root) {
        return;
    }
    if (1 == level) {
        std::cout << root->data << "  ";
    } else if (level > 1) {
        print_given_level(root->left, level - 1);
        print_given_level(root->right, level - 1);
    }
}
