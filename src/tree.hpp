#ifndef LIST_H
#define LIST_H

#include <iostream>
#include <queue>

template <typename T>
struct Node
{
    T data;
    Node<T>* left;
    Node<T>* right;

};

template <typename T>
class tree
{
    private:
        Node<T>* root;
        // helper function to find element with data (without recursion)
        bool search_helper(Node<T>* root, T data);  

        // helper function to find element with data (recursion)
        bool find_helper(Node<T>* root, T data);

        // helper function to insert node with given data in the tree
        void insert_helper(Node<T>* root, T data);
        
        // helper function to print tree in-order
        void in_order_helper(Node<T>* root);
        
        // helper function to print tree pre-order
        void pre_order_helper(Node<T>* root);
        
        // helper function to print tree post-order
        void post_order_helper(Node<T>* root);
        
        // helper function to calculate the depth of the tree
        int max_depth_helper(Node<T>* root);
        
        // prints the given level(this function is for level order traverse)
        void print_given_level(Node<T>* root, int level);
        
        // returns the minimum value(this function is used to remove node
        // which has two children)
        T min_value(Node<T>* root);
        
        //helper function to delete the node with given value
        Node<T>* remove_helper(T data, Node<T>* root, Node<T>* parent);
    
    public:
        tree();   
        ~tree();
    
        //this function is used in destructor(for deleting all nodes)
        //recursive function
        void delete_tree(Node<T>* root);

        //this function is for inserting the node with given data
        void insert(T data);     

        //this function is for checking if the node 
        //with given data exists or not
        bool search(T data);

        //this function is for checking if the node 
        //with given data exists or not (recursive)
        bool find(T data);

        //prints tree in in-order
        void in_order();

        //prints tree in pre-order
        void pre_order();

        //prints tree in post-order
        void post_order();

        //calculates the depth of the tree
        int max_depth();

        //prints tree in level-order
        void level_order();

        //prints tree in level-order(function is written with queue)
        void level_order_queue();

        //removes the node with given value
        Node<T>* remove(T data);
};

#endif 

template <typename T>
tree<T>::tree() : root(NULL) {}

template <typename T>
void tree<T>::delete_tree(Node<T>* root)
{
    if (NULL != root)
    {
        delete_tree(root->left);
        delete_tree(root->right);
        delete root;
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


template <typename T>
void tree<T>::level_order_queue()
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


template <typename T>
void tree<T>::level_order()
{
    std::cout << "Level order traversal is : ";
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


template <typename T>
Node<T>* tree<T>::remove(T data) 
{
    if (root == NULL) {
        return root;
    } else {
        if (root->data == data) {
            Node<T>* parent = new Node<T>;
            parent->data = 0;
            parent->left = root;
            parent->right = NULL;
            Node<T>* removedNode = remove_helper(data, root, parent);
            root = parent->left;
            delete removedNode;
        } else {
            Node<T>* removedNode = remove_helper(data, root, NULL);
            delete removedNode;
        }
    }
    return root;
}

template <typename T>
Node<T>* tree<T>::remove_helper(T data, Node<T>* root, Node<T>* parent) {
    if (data < root->data) {
        if (root->left != NULL)
            return remove_helper(data, root->left, root);
        else
            return NULL;
    } else if (data > root->data) {
        if (root->right != NULL)
            return remove_helper(data, root->right, root);
        else
            return NULL;
    } else {
        if (root->left != NULL && root->right != NULL) {
            root->data = min_value(root->right);
            return remove_helper(root->data, root->right, root);
        } else if (parent->left == root) {
            parent->left = (root->left != NULL) ? root->left : root->right;
            return root;
        } else {
            parent->right = (root->left != NULL) ? root->left : root->right;
            return root;
        }
    }
}

template <typename T>
T tree<T>::min_value(Node<T>* root) {
    if (root->left == NULL) {
        return root->data;
    } 
    return min_value(root->left);
}
