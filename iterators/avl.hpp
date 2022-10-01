#include <iostream>
#include "utils.hpp"
namespace ft {



// AVL tree node
template <class Key, class T>
struct node {
    node* left;
    node* right;
    // int key;
    ft::pair<const Key, T> *pair;
    node* par;
    int height;
};


template<class T> 
const T& max(const T& a, const T& b)
{
    return (a < b) ? b : a;
}

// template <typename A, typename B, typename C = std::less<>>
// bool fun(A a, B b, C cmp = C{})
// {
//     return cmp(a, b);
// }
 

template <class Key, class T , class compare = std::less<Key>, class Alloc = std::allocator<Key> >
class avl {

    typedef node<Key, T> node_type;
    typedef ft::pair<Key, T> pair;
    typedef typename Alloc::template rebind<node_type>::other rebind_allocator;
    typedef typename Alloc::template rebind<pair>::other _allocator;
    rebind_allocator _NodeAll;
    _allocator _PairAll;
    compare _comp;

    public:
    avl() {
        
    }
    ~avl() {
        
    }


    node_type *find(node_type *node, Key key)const
     {
        if (node == nullptr)
            return nullptr;
        if (!_comp(node->pair->first, key) && !_comp(key, node->pair->first))
            return node;
        else if (!_comp(node->pair->first, key))
            return(find(node->left, key));
        else if (_comp(node->pair->first , key))
            return (find(node->right, key));
        return node; 
    }
    void printpreorder(node_type* root)
    {
        // Print the node's value along
        // with its parent value
        std::cout << "Node: " << root->pair->first
            << ", Parent Node: ";
    
        if (root->par != NULL)
            std::cout << root->par->pair->first << std::endl;
        else
            std::cout << "NULL" << std::endl;
    
        // Recur to the left subtree
        if (root->left != NULL) {
            printpreorder(root->left);
        }
    
        // Recur to the right subtree
        if (root->right != NULL) {
            printpreorder(root->right);
        }
    }
    
    // Function to update the height of
    // a node according to its children's
    // node's heights
    void Updateheight(
        node_type* root)
    {
        if (root != NULL) {
    
            // Store the height of the
            // current node
            int val = 1;
    
            // Store the height of the left
            // and right subtree
            if (root->left != NULL)
                val = root->left->height + 1;
    
            if (root->right != NULL)
                val = max(val, root->right->height + 1);
    
            // Update the height of the
            // current node
            root->height = val;
        }
    }
    
    // Function to handle Left Left Case
    node_type* LLR(
        node_type* root)
    {
        // Create a reference to the
        // left child
        node_type* tmpnode = root->left;
    
        // Update the left child of the
        // root to the right child of the
        // current left child of the root
        root->left = tmpnode->right;
    
        // Update parent pointer of left
        // child of the root node
        if (tmpnode->right != NULL)
            tmpnode->right->par = root;
    
        // Update the right child of
        // tmpnode to root
        tmpnode->right = root;
    
        // Update parent pointer of tmpnode
        tmpnode->par = root->par;
    
        // Update the parent pointer of root
        root->par = tmpnode;
    
        // Update tmpnode as the left or
        // the right child of its parent
        // pointer according to its key value
        if (tmpnode->par != NULL
            && _comp(root->pair->first, tmpnode->par->pair->first)) {
            tmpnode->par->left = tmpnode;
        }
        else {
            if (tmpnode->par != NULL)
                tmpnode->par->right = tmpnode;
        }
    
        // Make tmpnode as the new root
        root = tmpnode;
    
        // Update the heights
        Updateheight(root->left);
        Updateheight(root->right);
        Updateheight(root);
        Updateheight(root->par);
    
        // Return the root node
        return root;
    }
    
    // Function to handle Right Right Case
    node_type* RRR(
        node_type* root)
    {
        // Create a reference to the
        // right child
        node_type* tmpnode = root->right;
    
        // Update the right child of the
        // root as the left child of the
        // current right child of the root
        root->right = tmpnode->left;
    
        // Update parent pointer of the
        // right child of the root node
        if (tmpnode->left != NULL)
            tmpnode->left->par = root;
    
        // Update the left child of the
        // tmpnode to root
        tmpnode->left = root;
    
        // Update parent pointer of tmpnode
        tmpnode->par = root->par;
    
        // Update the parent pointer of root
        root->par = tmpnode;
    
        // Update tmpnode as the left or
        // the right child of its parent
        // pointer according to its key value
        if (tmpnode->par != NULL
            && _comp(root->pair->first, tmpnode->par->pair->first)) {
            tmpnode->par->left = tmpnode;
        }
        else {
            if (tmpnode->par != NULL)
                tmpnode->par->right = tmpnode;
        }
    
        // Make tmpnode as the new root
        root = tmpnode;
    
        // Update the heights
        Updateheight(root->left);
        Updateheight(root->right);
        Updateheight(root);
        Updateheight(root->par);
    
        // Return the root node
        return root;
    }
    
    // Function to handle Left Right Case
    node_type* LRR(
        node_type* root)
    {
        root->left = RRR(root->left);
        return LLR(root);
    }
    
    // Function to handle right left case
    node_type* RLR(
        node_type* root)
    {
        root->right = LLR(root->right);
        return RRR(root);
    }
    
    // Function to balance the tree after
    // deletion of a node
    node_type* Balance(
        node_type* root)
    {
        // Store the current height of
        // the left and right subtree
        int firstheight = 0;
        int secondheight = 0;
    
        if (root->left != NULL)
            firstheight = root->left->height;
    
        if (root->right != NULL)
            secondheight = root->right->height;
    
        // If current node is not balanced
        if (abs(firstheight - secondheight) == 2) {
            if (firstheight < secondheight) {
    
                // Store the height of the
                // left and right subtree
                // of the current node's
                // right subtree
                int rightheight1 = 0;
                int rightheight2 = 0;
                if (root->right->right != NULL)
                    rightheight2 = root->right->right->height;
    
                if (root->right->left != NULL)
                    rightheight1 = root->right->left->height;
    
                if (rightheight1 > rightheight2) {
    
                    // Right Left Case
                    root = RLR(root);
                }
                else {
    
                    // Right Right Case
                    root = RRR(root);
                }
            }
            else {
    
                // Store the height of the
                // left and right subtree
                // of the current node's
                // left subtree
                int leftheight1 = 0;
                int leftheight2 = 0;
                if (root->left->right != NULL)
                    leftheight2 = root->left->right->height;
    
                if (root->left->left != NULL)
                    leftheight1 = root->left->left->height;
    
                if (leftheight1 > leftheight2) {
    
                    // Left Left Case
                    root = LLR(root);
                }
                else {
    
                    // Left Right Case
                    root = LRR(root);
                }
            }
        }
    
        // Return the root node
        return root;
    }
    
    node_type *findmin(node_type *root)
    {
        if (root == NULL)
            return NULL;
        if (root->left != NULL)
            root = root->left;
        return root;
    }
    node_type *findmax(node_type *root)
    {
        if (root == NULL)
            return NULL;
        if (root->right != NULL)
            root = root->right;
        return root;
    }
    node_type* Insert(node_type* root, node_type* parent, pair _pair)
    {
       // std::cout << "Pair" << _pair.first << ">" << _pair.second << std::endl;
        if (root == NULL) {
    
            // Create and assign values
            // to a new node
            root = _NodeAll.allocate(1);
            // if (root == NULL)
            //     std::cout << "Error in memory" << std::endl;
            // else {
                //root = _NodeAll.allocate(1);
                root->pair = _PairAll.allocate(1);
                _PairAll.construct(root->pair, _pair);
                root->height = 1;
                root->left = NULL;
                root->right = NULL;
                root->par = parent;
        }
    
        else if (!_comp(root->pair->first, _pair.first)) {
    
            // Recur to the left subtree
            // to insert the node
            root->left = Insert(root->left,
                                root, _pair);
    
            // Store the heights of the
            // left and right subtree
            int firstheight = 0;
            int secondheight = 0;
    
            if (root->left != NULL)
                firstheight = root->left->height;
    
            if (root->right != NULL)
                secondheight = root->right->height;
    
            // Balance the tree if the
            // current node is not balanced
            if (abs(firstheight - secondheight) == 2) 
            {
    
                if (root->left != NULL
                    && _comp(_pair.first, root->left->pair->first)) {
    
                    // Left Left Case
                    root = LLR(root);
                }
                else {
    
                    // Left Right Case
                    root = LRR(root);
                }
            }
        }
    
        else if (_comp(root->pair->first, _pair.first)) {
    
            // Recur to the right subtree
            // to insert the node
            root->right = Insert(root->right,
                                root, _pair);
    
            // Store the heights of the left
            // and right subtree
            int firstheight = 0;
            int secondheight = 0;
    
            if (root->left != NULL)
                firstheight = root->left->height;
    
            if (root->right != NULL)
                secondheight = root->right->height;
    
            // Balance the tree if the
            // current node is not balanced
            if (abs(firstheight - secondheight) == 2) {
                if (root->right != NULL
                    && _comp(_pair.first, root->right->pair->first)) {
    
                    // Right Left Case
                    root = RLR(root);
                }
                else {
    
                    // Right Right Case
                    root = RRR(root);
                }
            }
        }
    
        // Case when given key is
        // already in tree
        else {
            return root;
        }
    
        // Update the height of the
        // root node
        Updateheight(root);
    
        // Return the root node
        return root;
    }
    
    // Function to delete a node from
    // the AVL tree
    node_type* Delete(node_type* root,pair _pair)
    {
        if (root != NULL) {
    
            // If the node is found
                if (root->pair->first == _pair.first) {
    
                // Replace root with its
                // left child
                if (root->right == NULL
                    && root->left != NULL) {
                    if (root->par != NULL) {
                        if (_comp(root->par->pair->first
                            , root->pair->first))
                            root->par->right = root->left;
                        else
                            root->par->left = root->left;
    
                        // Update the height
                        // of root's parent
                        Updateheight(root->par);
                    }
    
                    root->left->par = root->par;
    
                    // Balance the node
                    // after deletion
                    root->left = Balance(
                        root->left);
    
                    return root->left;
                }
    
                // Replace root with its
                // right child
                else if (root->left == NULL
                        && root->right != NULL) {
                    if (root->par != NULL) {
                        if (_comp(root->par->pair->first
                            , root->pair->first))
                            root->par->right = root->right;
                        else
                            root->par->left = root->right;
    
                        // Update the height
                        // of the root's parent
                        Updateheight(root->par);
                    }
    
                    root->right->par = root->par;
    
                    // Balance the node after
                    // deletion
                    root->right = Balance(root->right);
                    return root->right;
                }
    
                // Remove the references of
                // the current node
                else if (root->left == NULL
                        && root->right == NULL) {
                    if (_comp(root->par->pair->first, root->pair->first)) {
                        root->par->right = NULL;
                    }
                    else {
                        root->par->left = NULL;
                    }
    
                    if (root->par != NULL)
                        Updateheight(root->par);
    
                    root = NULL;
                    return NULL;
                }
    
                // Otherwise, replace the
                // current node with its
                // successor and then
                // recursively call Delete()
                else {
                    node_type* tmpnode = root;
                    tmpnode = tmpnode->right;
                    while (tmpnode->left != NULL) {
                        tmpnode = tmpnode->left;
                    }
    
                    pair *val =  tmpnode->pair;
                    // tmpnode->pair;
    
                    root->right = Delete(root->right, *tmpnode->pair);
    
                    root->pair = val;
    
                    // Balance the node
                    // after deletion
                    root = Balance(root);
                }
            }
    
            // Recur to the right subtree to
            // delete the current node
            else if (_comp(root->pair->first, _pair.first)) {
                root->right = Delete(root->right, _pair);
    
                root = Balance(root);
            }
    
            // Recur into the right subtree
            // to delete the current node
            else if (!_comp(root->pair->first, _pair.first)) {
                root->left = Delete(root->left, _pair);
    
                root = Balance(root);
            }
    
            // Update height of the root
            if (root != NULL) {
                Updateheight(root);
            }
        }
    
        // Handle the case when the key to be
        // deleted could not be found
        else {
            std::cout << "Key to be deleted "
                << "could not be found\n";
        }
    
        // Return the root node
        return root;
    }

     node_type *lowerBound(node_type *root, const Key &k) const
            {
                node_type *r = NULL;
                while(root != nullptr)
                {
                    if (!_comp(root->pair->first, k))
                    {
                        r = root;
                        root = root->left;
                    }
                    else
                        root = root->right;
                }
                return r;
            }
    node_type *treeSuccesor(node_type *x)const
        {
            if (x == NULL)
                return x;
            if (x->right != NULL)
                return treemin(x->right);
            node_type *y = x->par;
            while(y!= NULL && (x == y->right ))
            {
                 x = y;
                 y = y->par;
            }
                return y;
        }
            node_type *treepredecessor(node_type *x)const
            {
                if (x == NULL)
                    return x;
                if (x->left != NULL)
                    return findmax(x->left);
                node_type *y = x->par;
                while(y!= NULL && (x == y->left))
                {
                    x =y;
                    y = y->par;
                }
                return y;
            }
            node_type *upperbound(node_type *root, const Key &k)const
            {
                node_type *r = NULL;
                while(root != nullptr)
                {
                    if (_comp(k,root->pair->first))
                    {
                        r = root;
                        root = root->left;                         
                    }
                    else
                        root = root->right;
                }
                return r;
            }
};
 }