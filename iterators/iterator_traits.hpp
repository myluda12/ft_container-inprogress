#pragma once

#include <iostream>

namespace ft
{
    template <	class Category, class T, class Distance = std::ptrdiff_t, class Pointer = T*, class Reference = T&>
	struct iterator {
		typedef T			value_type;
		typedef Distance	difference_type;
		typedef Pointer		pointer;
		typedef Reference	reference;
		typedef Category	iterator_category;
	};

    // For general iterator
    template <class Iterator>
    class iterator_traits
    {
        public:
            typedef typename Iterator::value_type value_type;
            typedef typename Iterator::difference_type difference_type;
            typedef typename Iterator::pointer pointer;
            typedef typename Iterator::reference reference;
            typedef typename Iterator::iterator_category iterator_category;
    };

    // For native pointer
    template <typename T>
    class iterator_traits<T*>
    {
        public:
            typedef T value_type;
            typedef ptrdiff_t difference_type;
            typedef T* pointer;
            typedef T& reference;
            typedef std::random_access_iterator_tag iterator_category;
    };

    // For const native pointer
    template <typename T>
    class iterator_traits<const T*>
    {
        public:
            typedef T value_type;
            typedef ptrdiff_t difference_type;
            typedef const T* pointer;
            typedef const T& reference;
            typedef std::random_access_iterator_tag iterator_category;
    };
};