#pragma once

#include "avl.hpp"
#include <utility>
#include "../Vectorr/reverse_iterator.hpp"
#include "bidirectional_iterator.hpp"
#include "utils.hpp"
#include "../Vectorr/vector.hpp"

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
        typedef ft::node<const Key, T> node_type;
        typedef typename ft::Bidirectional_iterator<const Key, T> iterator;
        typedef typename ft::Bidirectional_iterator<const Key, T> const_iterator;
        typedef size_t size_type;
       
       
        typedef typename Allocator::pointer pointer;
        typedef typename Allocator::const_pointer const_pointer;
      
      
        typedef ft::reverse_iterator<iterator> reverse_iterator;
        typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;
       
       
        typedef typename ft::avl<const Key, T, Compare, Allocator > tree_type;

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
        // 23.3.1.1 construct/copy/destroyƒ:
        explicit Map(const Compare &comp = Compare(), const Allocator &alloca = Allocator())
        {
            size_ = 0;
            root = NULL;
            compare = comp;
            alloc = alloca;

        }
        //range contructor of map
        template <class InputIterator>
        Map(InputIterator first, InputIterator last, const Compare &comp = Compare(), const Allocator &alloca = allocator_type(),  typename ft::enable_if<!std::is_integral<InputIterator>::value, InputIterator>::type = InputIterator())
        {
            size_ = 0;
            root = NULL;
            compare = comp;
            alloc = alloca;
            // for(InputIterator it = first; it != last; it++)
            // {
            //     root = tree.Insert(root,NULL,*it);
            //     size_++;
            // }
            insert(first,last);

        }
        //  template<class InputIterator>
        //  Map(InputIterator first, InputIterator last, const key_compare &comp = key_compare(),const allocator_type &alloca = allocator_type()
        //  ,typename std::enable_if<!std::is_integral<InputIterator>::value, InputIterator>::type* = 0)
        //   {
        //    size_ = 0;
        //    root = NULL;
        //    compare = comp;
        //    alloc = alloca;
        //    for (InputIterator it = first; it != last; it++)
        //    {
        //        root = tree.Insert(root, root->par, *it);
        //        size_++;
        //    }
        //   }


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
            //int i = 1;
            //tree.Deleteall(root); REMINDEEER YOULL BACK AGAIN
            //size_ = 0;
            erase(begin(), end());
            for (const_iterator it = x.begin(); it != x.end(); it++)
                insert(*it);
            //size_++;
            size_ = x.size();
            return *this;
        }

        // iterators;
        iterator begin() 
        {   
            node_type *tmp = findmin(root);
            return iterator(tmp, root);
        }
        const_iterator begin() const
        {
            node_type *tmp = findmin(root);
            return const_iterator(tmp, root);
        }
        iterator end() 
        {
            return iterator(NULL,root, findmax(root));
        }
        const_iterator end() const
        {
            return const_iterator(NULL, root,findmax(root));
        }
        reverse_iterator rbegin() 
        {
            return reverse_iterator(end());
        }
        const_reverse_iterator rbegin() const
        {
            return reverse_iterator(end());
        }
        reverse_iterator rend()
        {
            return reverse_iterator(begin());
        }
        const_reverse_iterator rend() const
        {
            return reverse_iterator(begin());
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
           // printTree(root,NULL,false);
           // x.second = T();
            // iterator it = find(x);
            // if (it == end())
            // {
            //     insert(ft::pair<const key_type, T>(x, T()));
            //     it = find(x);
            // }
            // return it->second;
             //return (*((this->insert(ft::make_pair<const key_type, T>(x, T()))).first)).second;

            iterator it = find(x);
            // if (it != end())
            // {
            //     std::cout  << "\n  pair  ==  "<< it.get_root()->pair->first <<  std::endl;
            //     std::cout << "\n key == " << x << std::endl;
            // }

                if (it == end()) 
                {
                   // std::cout << "pair" << x.first << " " << x.second << std::endl;
                    root  = tree.Insert(root, NULL, ft::make_pair<const key_type, T>(x, T()));
                    size_++;
                   // it = find(x);
                   // std::cout << "m e e e e s s s i ::: "<< it->second << std::endl;
                   return find(x)->second;
                }
                return it->second;
        }

        // modifiers:
        pair<iterator, bool> insert(const value_type &k)
        {
            iterator it = find(k.first);
            if(it!= end())
                return pair<iterator,bool>(it, false);
               root = tree.Insert(root, NULL, k);
            //    std::cout << "inseted" 
               size_++;
               return pair<iterator,bool>(begin(), true);
         }

        iterator insert(iterator position, const value_type &k)
            {
                iterator it = find(k.first);
                if (it != end())
                    return position;
                root = tree.Insert(root, NULL, k);
                size_++;
                return begin();
            }

        template <class InputIterator>
        void insert(InputIterator first, InputIterator last, typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type = InputIterator())
        {
            for (InputIterator it = first; it != last; it++)
                insert(*it);
        }

        void erase(iterator position)
        {
            int index = 1;
            //iterator 
            if (position != end())
            {
                root = tree.Delete(root, *position, &index);
                size_--;
            }

        }
        size_t erase(const key_type &k)
        {
            int index = 1;
            iterator it = find(k);
            if (it == end())
                return 0;
            root = tree.Delete(root, *it,&index);
            size_--;
            return index;
        }
        void erase(iterator first, iterator last)
        {
            ft::vector<Key> tmp;
            for(iterator it = first; it != last; it++)
                tmp.push_back(it->first);

            for (size_t i = 0; i < tmp.size(); i++)
                erase(tmp[i]);
            // int index = 1;
            // for (iterator it = first; it != last; it++)
            // {
            //     root = tree.Delete(root, *it,&index);
            //     size_--;
            // }
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
        void swap(Map &x)
        {
            node_type *tmp = root;
            root = x.root;
            x.root = tmp;
            size_type tmp_size = size_;
            size_ = x.size_;
            x.size_ = tmp_size;
        }
        // void swap(Map<Key,T,Compare,Allocator>& x)
        // {
        //     ft::swap(root, x.root);
        //     ft::swap(size_, x.size_);
        //     ft::swap(alloc, x.alloc);
        //     ft::swap(compare, x.compare);
        // }
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
                return iterator(found, root);
            return end();
        }
        const iterator find(const key_type &k) const
        {
            node_type * found = tree.find(root ,k);
            if (found != NULL)
                return const_iterator(found, root);
            return end();
        }

        size_type count(const key_type& x) const
        {
            if (find(x) != end())
                return 1;
            return 0;
        }

        iterator lower_bound(const key_type& x)
        {
            return iterator(tree.lowerBound(root,x),root);
        }
        const_iterator lower_bound(const key_type& x) const
        {
            return const_iterator(tree.lowerBound(root,x),root);
        }
        iterator upper_bound(const key_type& x)
        {
            return iterator(tree.upperbound(root,x),root);
        }
        const_iterator upper_bound(const key_type& x) const
        {
            return const_iterator(tree.upperbound(root,x),root);
        }

        allocator_type get_allocator() const
        {
            return alloc;
        };




        public:
            key_compare		compare;
            allocator_type	alloc;
            tree_type		tree;
            struct Trunk
		{
			Trunk *prev;
			std::string str;
		
			Trunk(Trunk *prev, std::string str)
			{
				this->prev = prev;
				this->str = str;
			}
		};

		// Helper function to print branches of the binary tree
		void showTrunks(Trunk *p)
		{
			if (p == nullptr) {
				return;
			}
		
			showTrunks(p->prev);
			std::cout << p->str;
		}

		// template<class Key, class T>
		void printTree(node_type* root, Trunk *prev, bool isLeft)
		{
			if (root == nullptr) {
				return;
			}
		
			std::string prev_str = "    ";
			Trunk *trunk = new Trunk(prev, prev_str);
		
			printTree(root->right, trunk, true);
		
			if (!prev) {
				trunk->str = "———";
			}
			else if (isLeft)
			{
				trunk->str = ".———";
				prev_str = "   |";
			}
			else {
				trunk->str = "`———";
				prev->str = prev_str;
			}
		
			showTrunks(trunk);
			std::cout << " " << root->pair->first << std::endl;
		
			if (prev) {
				prev->str = prev_str;
			}
			trunk->str = "   |";
		
			printTree(root->left, trunk, false);
		}
	
		node_type * get_root()
		{
			return(root);
		}

        node_type *findmin(node_type *root)
            {
                if (root == NULL)
                    return NULL;
                while (root && root->left != NULL)
                    root = root->left;
                return root;
            }
            node_type *findmax(node_type *root)
            {
                if (root == NULL)
                    return NULL;
                while (root && root->right != NULL)
                    root = root->right;
                return root;
            }
            node_type *findmin(node_type *root) const
            {
                if (root == NULL)
                    return NULL;
                while (root && root->left != NULL)
                    root = root->left;
                return root;
            }
            node_type *findmax(node_type *root) const
            {
                if (root == NULL)
                    return NULL;
                while (root && root->right != NULL)
                    root = root->right;
                return root;
            }
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
        return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
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
        std::swap(x.size_, y.size_);
        std::swap(x.alloc, y.alloc);
        std::swap(x.compare, y.compare);
    }
};
