
#pragma once
#include <iostream>
#include "map.hpp"
#include "reverse_iterator.hpp"
#include "utils.hpp"
//#include "avl.hpp"
//#include "avl.hpp"

namespace ft
{
    template <class Key, class T, class Compare = std::less<Key>, class Allocator = std::allocator<ft::pair<const Key, T> > >
    class Bidirectional_iterator
    {
    public:
        
        // typedef T value_type;
        // typedef typename std::iterator<std::bidirectional_iterator_tag, T>::difference_type difference_type;
        // typedef T *pointer;
        // typedef T &reference;
        // typedef typename std::iterator<std::bidirectional_iterator_tag, T>::iterator_category iterator_category;
        typedef typename iterator<std::random_access_iterator_tag, pair<const Key, T> >::difference_type difference_type;
        typedef typename iterator<std::random_access_iterator_tag, pair<const Key, T> >::value_type value_type;
        typedef typename iterator<std::random_access_iterator_tag, pair<const Key, T> >::pointer pointer;  
        typedef typename iterator<std::random_access_iterator_tag, pair<const Key, T> >::reference reference;
        typedef typename iterator<std::random_access_iterator_tag, pair<const Key, T> >::iterator_category iterator_category;
        typedef node<const Key, T> node_type;
        typedef pair< Key, T> pair;
        pair *stock;
        
    
    private:
        node_type *node;
        node_type *node_root;
        node_type *end;
           node_type* minValueNode(node_type* node)
                {
                    node_type* current = node;
                
                    /* loop down to find the rightmost leaf */
                    while (current && current->left != NULL)
                        current = current->left;
                
                    return current;
                }
				
                node_type* maxValueNode(node_type* node)
                {
                    node_type* current = node;
                
                    /* loop down to find the leftmost leaf */
                    while (current && current->right != NULL)
                        current = current->right;
                
                    return current;
                }
				
                node_type* minValueNode(node_type* node) const
                {
                    node_type* current = node;
                
                    /* loop down to find the rightmost leaf */
                    while (current && current->left != NULL)
                        current = current->left;
                
                    return current;
                }
				
                node_type* maxValueNode(node_type* node) const
                {
                    node_type* current = node;
                
                    /* loop down to find the leftmost leaf */
                    while (current && current->right != NULL)
                        current = current->right;
                
                    return current;
                }   
    public:

        node_type* get_node() const
        {
            return node;
        };
        node_type* get_root() const
        {
            return node_root;
        };
        node_type* get_end() const
        {
            return end;
        };

        template <typename U, typename V>
        Bidirectional_iterator(const Bidirectional_iterator<U, V> &other)
        {
            this->_node = other.get_node();
            this->_root = other.get_root();
            this->_end = other.get_end();
        };

        Bidirectional_iterator() : node(NULL), node_root(NULL),end(NULL){};
        
        Bidirectional_iterator(node_type *_node,node_type *_root)
        {
            node = _node;
            node_root = _root;
            end = NULL;
            // if(node_root)
            //     std::cout << "\n 2 Parameters :::: Node root:: " << node_root->pair->first <<  std::endl;
        };
        Bidirectional_iterator(node_type *_node,node_type *_root,node_type* end)
        {
           // stock = a
            node = _node;
            node_root = _root;
            this->end = end;
            // if (node_root)
            //     std::cout << "\nParametrize Constructor with 3 Elements :: root :: " << node_root->pair->first << std::endl;
        }
        
        Bidirectional_iterator(Bidirectional_iterator const &other)
        {
            node = other.get_node();

            node_root = other.get_root();
            end = other.get_end();
            // if (node_root)
            //     std::cout << "\nCopy Constructor :: root :: " << node_root->pair->first << std::endl;
        };

        // Bidirectional_iterator(node_type *node_root, node_type *node)
        // {
        //     this->node = node;
        //     this->node_root = node_root;
        // };

   
        ~Bidirectional_iterator(){};
        operator Bidirectional_iterator<const Key, T>()
        {
            return Bidirectional_iterator<const Key, T>(node, node_root,end);
        };
        // Comparisons

        bool operator==(Bidirectional_iterator const &other) const
        {
            if (node == other.get_node())
                return true;
            return false;
        };

        bool operator!=(Bidirectional_iterator const &other) const
        {
            if (node == other.get_node())
                return false;
            return true;
        };
        // OPERATORS
        Bidirectional_iterator &operator=(Bidirectional_iterator const &other)
        {
            this->node = other.get_node();
            this->node_root = other.get_root();
            this->end = other.get_end();
            return *this;
        };


        // node_type root_tree(node_type root)
        // {
        //     while (root->par != nullptr)
        //         root = root->par;
        //     return root;
        // }

        node_type* max_tree(node_type* root)
        {
            node_type *tmp = root;
            while (tmp != NULL && tmp->right != NULL)
                tmp = tmp->right;
            return tmp;
        }

        node_type* min_tree(node_type* root)
        {
            node_type *tmp = root;
            while (tmp != NULL && tmp->left != NULL)
                tmp = tmp->left;
            return tmp;
        }
        Bidirectional_iterator &operator++()
        {
            // if (node == NULL)
            // {
            //     node = node_root;
            //     while (node != NULL && node->left != NULL)
            //         node = node->left;
            // }
            // if (node->right)
            // {
            //     node = node->right;
            //     while (node->left != NULL)
            //         node = node->left;
            // }
            // else if (node->par)
            // {
            //     node_type *daddy_chill = node->par;
            //     if (daddy_chill == node)
            //         node = daddy_chill;
            //     else if (daddy_chill->right == node)
            //     {
            //         while (daddy_chill && daddy_chill->right == node)
            //         {
            //             node = daddy_chill;
            //             daddy_chill = daddy_chill->par;
            //         }
            //         node = daddy_chill;
            //     }
            //     else if (node == max_tree(node_root))
            //         node = NULL;
            // }
            // return *this;
                node_type* n = node;
                node_type* max = maxValueNode(node_root);
	
                if (node == max)
                {    
                    node = NULL;
                    end = node;
                    return *this;
                }
                if (n && n->right != NULL)
                    node = minValueNode(n->right);
                else if (n && n->right == NULL)
                {   
                    node_type* p = n->par;
                    while (p != NULL && n == p->right)
                    {
                        n = p;
                        p = p->par;
                        
                    }
                    node = p;
                }

                return (*this);
        };

        Bidirectional_iterator &operator--()
        {
            // if (node == NULL)
            // {
            //     node = node_root;
            //     while (node != NULL && node->right != NULL)
            //         node = node->right;
            // }
            // if (node->left)
            // {
            //     node = node->left;
            //     while (node->right != NULL)
            //         node = node->right;
            // }
            // else if (node->par)
            // {
            //     node_type *daddy_chill = node->par;
            //     if (daddy_chill->right == node)
            //         node = daddy_chill;
            //     else if (daddy_chill->left == node)
            //     {
            //         while (daddy_chill && daddy_chill->left == node)
            //         {
            //             node = daddy_chill;
            //             daddy_chill = node->par;
            //         }
            //         node = daddy_chill;
            //     }
            //     else if (node == min_tree(node_root))
            //         node = NULL;
            // }
            // return *this;
            node_type *n = node;
          if (node == NULL && end)
          {
             node = end;
              end = NULL;
              return (*this);
          }               
        if (n && n->left != NULL)
        {
            node = maxValueNode(n->left);
        }
        else if (n && n->left == NULL)
        {
            node_type* p = n->par;
            while (p != NULL && n == p->left)
            {
                n = p;
                p = p->par;
            }
            node = p;
        }
        return (*this);
        };

        Bidirectional_iterator operator++(int)
        {
            Bidirectional_iterator tmp(*this);
            operator++();
            return tmp;
        };
            Bidirectional_iterator &operator +=(difference_type rhs)
            {
                for(difference_type it = rhs; it >= 1; it--)
                {
                    (*this)++;
                }
                return *this;
            };
              Bidirectional_iterator &operator -=(difference_type rhs)
            {
                for(difference_type it = rhs; it >= 1; it--)
                {
                    (*this)--;
                }
                return *this;
            };
        Bidirectional_iterator operator--(int)
        {
            Bidirectional_iterator tmp(*this);
            operator--();
            return tmp;
        };
        pair &operator*() const
        {
            return *node->pair;
            //return *node->pair;
        };
        pair *operator->() const
        {
            return (node->pair);
        };
        


    };
};
