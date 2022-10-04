#include <iostream>
#include "utils.hpp"
namespace ft 
{



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
    avl(rebind_allocator rebind = rebind_allocator(), _allocator alloc = _allocator(), compare _c = compare()) 
    {
        _NodeAll = rebind;
        _PairAll = alloc;
        _comp = _c;    
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
    
    void height_again(node_type* root)
    {
        if (root != NULL) 
        {

            int val = 1;
            if (root->left != NULL)
                val = root->left->height + 1;
    
            if (root->right != NULL)
                val = max(val, root->right->height + 1);
            root->height = val;
        }
    }
    
    node_type* left_left(node_type* root)
    {

        node_type* tmpnode = root->left;
    
        root->left = tmpnode->right;
    
        if (tmpnode->right != NULL)
            tmpnode->right->par = root;
    

        tmpnode->right = root;
    
        tmpnode->par = root->par;
    
        root->par = tmpnode;
    

        if (tmpnode->par != NULL && _comp(root->pair->first, tmpnode->par->pair->first))
            tmpnode->par->left = tmpnode;
        else {
            if (tmpnode->par != NULL)
                tmpnode->par->right = tmpnode;
        }
    
        root = tmpnode;
    
        height_again(root->left);
        height_again(root->right);
        height_again(root);
        height_again(root->par);
    
        return root;
    }
    
    node_type* right_right (node_type* root)
    {

        node_type* tmpnode = root->right;
    
        root->right = tmpnode->left;
    
        if (tmpnode->left != NULL)
            tmpnode->left->par = root;
    

        tmpnode->left = root;
    

        tmpnode->par = root->par;
    

        root->par = tmpnode;
    

        if (tmpnode->par != NULL && _comp(root->pair->first, tmpnode->par->pair->first)) 
            tmpnode->par->left = tmpnode;
        else {
            if (tmpnode->par != NULL)
                tmpnode->par->right = tmpnode;
        }
    
        root = tmpnode;
    
        height_again(root->left);
        height_again(root->right);
        height_again(root);
        height_again(root->par);
    
        return root;
    }
    
    node_type* left_right(node_type* root)
    {
        root->left = right_right(root->left);
        return left_left(root);
    }
    
    node_type* right_left(node_type* root)
    {
        root->right = left_left(root->right);
        return right_right(root);
    }
    

    node_type* Balance(node_type* root)
    {

        int firstheight = 0;
        int secondheight = 0;
    
        if (root->left != NULL)
            firstheight = root->left->height;
    
        if (root->right != NULL)
            secondheight = root->right->height;
    
        if (abs(firstheight - secondheight) == 2) 
        {
            if (firstheight < secondheight) 
            {
    
                int rightheight1 = 0;
                int rightheight2 = 0;
                if (root->right->right != NULL)
                    rightheight2 = root->right->right->height;
    
                if (root->right->left != NULL)
                    rightheight1 = root->right->left->height;
    
                if (rightheight1 > rightheight2) {
    
                    root = right_left(root);
                }
                else 
                    root = right_right(root);
            }
            else 
            {

                int leftheight1 = 0;
                int leftheight2 = 0;
                if (root->left->right != NULL)
                    leftheight2 = root->left->right->height;
    
                if (root->left->left != NULL)
                    leftheight1 = root->left->left->height;
    
                if (leftheight1 > leftheight2) 
                    root = left_left(root);
                else
                    root = left_right(root);
            }
        }
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
        if (root == NULL) 
        {
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
                return root;
        }
    
        else if (!_comp(root->pair->first, _pair.first)) 
        {
            root->left = Insert(root->left,root, _pair);
            int firstheight = 0;
            int secondheight = 0;
    
            if (root->left != NULL)
                firstheight = root->left->height;
    
            if (root->right != NULL)
                secondheight = root->right->height;
    
            if (abs(firstheight - secondheight) == 2) 
            {
    
                if (root->left != NULL && _comp(_pair.first, root->left->pair->first)) 
                    root = left_left(root);
                else
                    root = left_right(root);
            }
        }
    
        else if (_comp(root->pair->first, _pair.first))
        {
            root->right = Insert(root->right,root, _pair);
            int firstheight = 0;
            int secondheight = 0;
    
            if (root->left != NULL)
                firstheight = root->left->height;
    
            if (root->right != NULL)
                secondheight = root->right->height;

            if (abs(firstheight - secondheight) == 2) 
            {
                if (root->right != NULL && _comp(_pair.first, root->right->pair->first)) 
                    root = right_left(root);
                else
                    root = right_right(root);
            }
        }
        else 
            return root;
    
        height_again(root);

        return root;
    }

    node_type* Delete(node_type* root,pair _pair, int *index)
    {
        if (root != NULL) 
        {
                if (root->pair->first == _pair.first)
                {
                if (root->right == NULL && root->left != NULL)
                {
                    if (root->par != NULL) 
                    {
                        if (_comp(root->par->pair->first , root->pair->first))
                            root->par->right = root->left;
                        else
                            root->par->left = root->left;
                        height_again(root->par);
                    }
    
                    root->left->par = root->par;
    

                    root->left = Balance(root->left);
    
                    return root->left;
                }
    

                else if (root->left == NULL && root->right != NULL) 
                {
                    if (root->par != NULL) 
                    {
                        if (_comp(root->par->pair->first , root->pair->first))
                            root->par->right = root->right;
                        else
                            root->par->left = root->right;
    

                        height_again(root->par);
                    }
    
                    root->right->par = root->par;

                    root->right = Balance(root->right);
                    return root->right;
                }
    
                else if (root->left == NULL && root->right == NULL) 
                {
                    if ( root->par && _comp(root->par->pair->first, root->pair->first)) {
                        root->par->right = NULL;
                    }
                    else if (root->par)
                    {
                        root->par->left = NULL;
                    }
    
                    if (root->par != NULL)
                        height_again(root->par);
    
                    root = NULL;
                    return NULL;
                }

                else 
                {
                    node_type* tmpnode = root;
                    tmpnode = tmpnode->right;
                    while (tmpnode->left != NULL) 
                        tmpnode = tmpnode->left;
    
                    pair *val =  tmpnode->pair;
    
                    root->right = Delete(root->right, *tmpnode->pair,index);
    
                    root->pair = val;

                    root = Balance(root);
                }
            }
    


            else if (_comp(root->pair->first, _pair.first))
             {
                root->right = Delete(root->right, _pair,index);
    
                root = Balance(root);
            }

            else if (!_comp(root->pair->first, _pair.first)) {
                root->left = Delete(root->left, _pair,index);
    
                root = Balance(root);
            }
    
            if (root != NULL) 
                height_again(root);
        }

        else 
            *index = 0;
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