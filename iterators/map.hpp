#pragma once
#include "avl.hpp"
#include <utility>
#include "reverse_iterator.hpp"
#include "bidirectional_iterator.hpp"
#include "utils.hpp"

namespace ft
{
    template <class Key, class T, class Compare = std::less<Key>, class Allocator = std::allocator<ft::pair<const Key, T> > >
    class Map
    {
    public: // types:                
        typedef Key key_type;
        typedef T mapped_type;
        typedef ft::pair<const Key, T> value_type;
        typedef Compare key_compare;
        typedef Allocator allocator_type;
        typedef typename Allocator::reference reference;
        typedef typename Allocator::const_reference const_reference;
        typedef ptrdiff_t difference_type;
        typedef ft::node<value_type,allocator_type> node_type;
        typedef typename ft::Bidirectional_iterator<value_type, node_type*> iterator;
        typedef typename ft::Bidirectional_iterator<const value_type, node_type*> const_iterator;
        typedef size_t size_type;
        typedef typename Allocator::pointer pointer;
        typedef typename Allocator::const_pointer const_pointer;
        typedef ft::reverse_iterator<iterator> reverse_iterator;
        typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;
        typedef typename ft::avl<value_type, key_compare, allocator_type> tree_type;

        size_type size_;
        node_type *root;


        class value_compare : public std::binary_function<value_type, value_type, bool>
        {
            friend class Map;

        protected:
            Compare comp;
            value_compare(Compare c) : comp(c) {}

        public:
            bool operator()(const value_type &x, const value_type &y) const
            {
                return comp(x.first, y.first);
            }
        };
        // 23.3.1.1 construct/copy/destroy:
        explicit Map(const Compare &comp = Compare(), const Allocator &alloca = Allocator())
        {
            size_ = 0;
            root = NULL;
            compare = comp;
            alloc = alloca;

        }

         template<class InputIterator>
         Map(InputIterator first, InputIterator last, const key_compare &comp = key_compare(),const allocator_type &alloca = allocator_type()
         /*,typename std::enable_if<!std::is_integral<InputIterator>::value, InputIterator>::type* = 0*/
         )
          {
           size_ = 0;
           root = NULL;
           compare = comp;
           alloc = alloca;
           for (InputIterator it = first; it != last; it++)
           {
               root = tree.Insert(root, root->par, *it);
               size_++;
           }
          }


        Map(const Map<Key, T, Compare, Allocator> &x)
        {
            root = NULL;
            size_ = 0;
            *this = x;
        }
        ~Map()
        {
            //root = tree.Deleteall(root);
        }
        Map<Key, T, Compare, Allocator> &operator=(const Map<Key, T, Compare, Allocator> &x)
        {
            if (this == &x)
                return *this;
            tree.Deleteall(root);
            size_ = 0;
            for (const_iterator it = x.begin(); it != x.end(); it++)
            {
                root = tree.insert(root, NULL, *it);
                size_++;
            }
            return *this;
        }

        // iterators;
        iterator begin() 
        {   
            node_type *tmp = tree.findmin(root);
            return iterator(tmp, root);
        }
        const_iterator begin() const
        {
            node_type *tmp = tree.findmin(root);
            return const_iterator(tmp, root);
        }
        iterator end() 
        {
            return iterator(NULL, root);
        }
        const_iterator end() const
        {
            return const_iterator(NULL, root);
        }
        reverse_iterator rbegin() 
        {
            return reverse_iterator(end());
        }
        const_reverse_iterator rbegin() const
        {
            return const_reverse_iterator(end());
        }
        reverse_iterator rend()
        {
            return reverse_iterator(begin());
        }
        const_reverse_iterator rend() const
        {
            return const_reverse_iterator(begin());
        }

        // CAPACITY
        bool empty() const
        {
            return size_ == 0;
        }
        size_type size() const
        {
            return size_;
        }
        size_type max_size() const
        {
            return alloc.max_size();
        }
        //TOOOO REMIIIIIND PLEASE
         ft::pair<const iterator, const iterator>equal_range(const key_type &k) const
         {
            return ft::pair<const iterator, const iterator>(lower_bound(k),upper_bound(k));
         }
         ft::pair< iterator,  iterator>equal_range(const key_type &k) 
         {
           return ft::pair< iterator,  iterator>(lower_bound(k),upper_bound(k));
         }
        // 23.3.1.2 element access:
        T& operator[](const key_type& x)
        {
            iterator it = find(x);
            if (it == end())
            {
                insert(ft::pair<const key_type, T>(x, T()));
                it = find(x);
            }
            return it->second;
        }

        // modifiers:
        ft::pair<iterator, bool> insert(const value_type &k)
        {
            iterator it = find(k.first);
            if(it!= end())
                return ft::pair<iterator,bool>(it, false);
            root = tree.insert(root, NULL, k);
             size_++;
             return ft::pair<iterator,bool>(begin(), true);
        }

        iterator insert(iterator position, const value_type &k)
            {
                iterator it = find(k.first);
                if (it != end())
                    return position;
                root = tree.insert(root, NULL, k);
                size_++;
                return begin();
            }

        template <class InputIterator>
        void insert(InputIterator first, InputIterator last, typename std::enable_if<!std::is_integral<InputIterator>::value, InputIterator>::type = InputIterator())
        {
            for (InputIterator it = first; it != last; it++)
            {
                root = tree.insert(root, NULL, *it);
                size_++;
            }
        }
        void erase(iterator position)
        {
            root = tree.Delete(root, position.node);
            size_--;
        }
        size_t erase(const key_type &k)
        {
            iterator it = find(k);
            if (it == end())
                return 0;
            root = tree.Delete(root, it.node);
            size_--;
            return 1;
        }
        void erase(iterator first, iterator last)
        {
            for (iterator it = first; it != last; it++)
            {
                root = tree.Delete(root, it.node);
                size_--;
            }
        }

        // void erase(iterator position)
        // {
        //     root = tree.Delete(root, position.node);
        //     size--;
        // }
        // size_type erase(const key_type& x)
        // {
        // }
        // void erase(iterator first, iterator last);

        void swap(Map<Key,T,Compare,Allocator>& x)
        {
            std::swap(root, x.root);
            std::swap(size_, x.size_);
            std::swap(alloc, x.alloc);
            std::swap(compare, x.compare);
        }
        void clear()
        {
            size_ = 0;
        }

        // observers:
        key_compare key_comp() const
        {
            return compare;
        }
        value_compare value_comp() const
        {
            return value_compare(compare);
        }

        // 23.3.1.3 map operations:
        iterator find(const key_type &k)
        {
            node_type * found = tree.find(root ,k);
            if (found != NULL)
                return iterator(root, found);
            return end();
        }
        const iterator find(const key_type &k) const
        {
            node_type * found = tree.find(root ,k);
            if (found != NULL)
                return const_iterator(root, found);
            return end();
        }

        size_type count(const key_type& x) const;

        iterator lower_bound(const key_type& x)
        {
            return iterator(root,tree.lowerBound(root,x));
        }
        const_iterator lower_bound(const key_type& x) const
        {
            return const_iterator(root,tree.lowerBound(root,x));
        }
        iterator upper_bound(const key_type& x)
        {
            return iterator(root,tree.upperBound(root,x));
        }
        const_iterator upper_bound(const key_type& x) const
        {
            return const_iterator(root,tree.upperBound(root,x));
        }

        allocator_type get_allocator() const
        {
            return alloc;
        };

        private:
            key_compare		compare;
            allocator_type	alloc;
            tree_type		tree;
        // node_type *findmin(node_type *root)
        //     {
        //         if (root == NULL)
        //             return NULL;
        //         if (root->left != NULL)
        //             root = root->left;
        //         return root;
        //     }
        //     node_type *findmax(node_type *root)
        //     {
        //         if (root == NULL)
        //             return NULL;
        //         if (root->right != NULL)
        //             root = root->right;
        //         return root;
        //     }
    };


    


     template<class Key, class T, class Compare, class Alloc>
    bool operator==(const Map<Key, T, Compare, Alloc>&l, const Map<Key, T, Compare, Alloc> &r)
    {
        return std::equal(l.begin(), l.end(), r.begin());
    }
    template<class Key, class T, class Compare, class Alloc>
    bool operator!=(const Map<Key, T, Compare, Alloc>&l, const Map<Key, T, Compare, Alloc> &r)
    {
        return !(l == r);
    }
    
    template<class Key, class T, class Compare, class Alloc>
    bool operator<( const Map<Key,T,Compare,Alloc>& lhs, const Map<Key,T,Compare,Alloc>& rhs ) 
    {    
        return std::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
    }
    template <class Key, class T, class Compare, class Alloc>
    bool operator<= ( const Map<Key,T,Compare,Alloc>& lhs, const Map<Key,T,Compare,Alloc>& rhs ) {
    
        return !( rhs < lhs );
    }
    template <class Key, class T, class Compare, class Alloc>
    bool operator>  ( const Map<Key,T,Compare,Alloc>& lhs, const Map<Key,T,Compare,Alloc>& rhs ) {
    
        return rhs < lhs;
    }
    template <class Key, class T, class Compare, class Alloc>
    bool operator>= ( const Map<Key,T,Compare,Alloc>& lhs, const Map<Key,T,Compare,Alloc>& rhs ) {
    
        return !(lhs < rhs);
    }
    template <class Key, class T, class Compare, class Alloc>
    void swap (Map<Key,T,Compare,Alloc>& x, Map<Key,T,Compare,Alloc>& y) {
    
        // std::swap(x.root, y.root);
        // std::swap(x._size, y._size);
        // std::swap(x._allocator, y._allocator);
        // std::swap(x._cmp, y._cmp);
        std::swap(x.root, y.root);
        std::swap(x._size, y._size);
        std::swap(x._allocator, y._allocator);
        std::swap(x._cmp, y._cmp);
    }
};
