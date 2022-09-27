
#pragma once
#include <iostream>
#include "map.hpp"
//#include "avl.hpp"

namespace ft
{
    template <typename T, typename node_type>
    class Bidirectional_iterator
    {
    private:
        node_type node;
        node_type node_root;

    public:
        typedef T value_type;
        typedef typename std::iterator<std::bidirectional_iterator_tag, T>::difference_type difference_type;
        typedef T *pointer;
        typedef T &reference;
        typedef typename std::iterator<std::bidirectional_iterator_tag, T>::iterator_category iterator_category;

        // GETTERS
        //  node_type *base() const
        //  {
        //      return node;
        //  };
        //  node_type *get_parent() const
        //  {
        //      return node_root;
        //  };

        // CONSTRCTORS

        node_type get_node() const
        {
            return node;
        };
        node_type get_root() const
        {
            return node_root;
        };

        template <typename U, typename V>
        Bidirectional_iterator(const Bidirectional_iterator<U, V> &other)
        {
            this->_node = other.get_node();
            this->_root = other.get_root();
        };

        Bidirectional_iterator() : node(nullptr), node_root(nullptr){};
        Bidirectional_iterator(node_type _node,node_type _root)
        {
            node = _node;
            node_root = _root;
        };
        Bidirectional_iterator(Bidirectional_iterator const &other)
        {
            node = other.get_node();
            node_root = other.get_root();
        };

        // Bidirectional_iterator(node_type *node_root, node_type *node)
        // {
        //     this->node = node;
        //     this->node_root = node_root;
        // };

   
        ~Bidirectional_iterator(){};
        operator Bidirectional_iterator<const T, node_type>()
        {
            return Bidirectional_iterator<const T, node_type>(node, node_root);
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
                return fase;
            return true;
        };
        // OPERATORS
        Bidirectional_iterator &operator=(Bidirectional_iterator const &other)
        {
            this->node = other.get_node();
            this->node_root = other.get_root();
            return *this;
        };

        // node_type root_tree(node_type root)
        // {
        //     while (root->par != nullptr)
        //         root = root->par;
        //     return root;
        // }

        node_type max_tree(node_type root)
        {
            node_type tmp = root;
            while (tmp != NULL && tmp->right != NULL)
                tmp = tmp->right;
            return tmp;
        }

        node_type min_tree(node_type root)
        {
            node_type tmp = root;
            while (tmp != NULL && tmp->left != NULL)
                tmp = tmp->left;
            return tmp;
        }
        Bidirectional_iterator &operator++()
        {
            if (node == NULL)
            {
                node = node_root;
                while (node != NULL && node->left != NULL)
                    node = node->left;
            }
            if (node->right)
            {
                node = node->right;
                while (node->left != NULL)
                    node = node->left;
            }
            else if (node->parent)
            {
                node_type daddy_chill = node->parent;
                if (daddy_chill == node)
                    node = daddy_chill;
                else if (daddy_chill->right == node)
                {
                    while (daddy_chill && daddy_chill->right == node)
                    {
                        node = daddy_chill;
                        daddy_chill = daddy_chill->parent;
                    }
                    node = daddy_chill;
                }
                else if (node == max_tree(node_root))
                    node = NULL;
                return *this;
            }
            return *this;
        };
        Bidirectional_iterator &operator--()
        {
            if (node == NULL)
            {
                node = node_root;
                while (node != NULL && node->right != NULL)
                    node = node->right;
            }
            if (node->left)
            {
                node = node->left;
                while (node->right != NULL)
                    node = node->right;
            }
            else if (node->parent)
            {
                node_type daddy_chill = node->parent;
                if (daddy_chill->right == node)
                    node = daddy_chill;
                else if (daddy_chill->left == node)
                {
                    while (daddy_chill && daddy_chill->left == node)
                    {
                        node = daddy_chill;
                        daddy_chill = node->parent;
                    }
                    node = daddy_chill;
                }
                else if (node == min_tree(node_root))
                    node = NULL;
            }
            return *this;
        };
        Bidirectional_iterator operator++(int)
        {
            Bidirectional_iterator tmp(*this);
            operator++();
            return tmp;
        };
        Bidirectional_iterator operator--(int)
        {
            Bidirectional_iterator tmp(*this);
            operator--();
            return tmp;
        };
        T &operator*() const
        {
            return node->pair;
        };
        T *operator->() const
        {
            return &(node->pair);
        };
    };
};