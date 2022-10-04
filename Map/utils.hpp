#pragma once

// #include "../Map/iterator_traits.hpp"
// #include "../Vectorr/vector.hpp"
namespace ft
{

  template<bool, typename T = void>
    struct enable_if{};
    template<typename T>
    struct enable_if<true, T>
    {
        typedef T type;
    };
    template<class T>
    struct is_integral
    {
        static const bool value = false;
    };
    template<> struct is_integral<bool> { static const bool value = true;};
    template<> struct is_integral<char> { static const bool value = true;};
    template<> struct is_integral<signed char> { static const bool value = true;};
    template<> struct is_integral<unsigned char> { static const bool value = true;};
    template<> struct is_integral<int> { static const bool value = true;};
    template<> struct is_integral<unsigned int> { static const bool value = true;};
    template<> struct is_integral<short> { static const bool value = true;};
    template<> struct is_integral<long> { static const bool value = true;};
    template<> struct is_integral<unsigned long> { static const bool value = true;};
    template<> struct is_integral<long long> { static const bool value = true;};
    template<> struct is_integral<unsigned long long> { static const bool value = true;};
    template<> struct is_integral<wchar_t> { static const bool value = true;};
    



    template<class T1, class T2> 
    struct pair
    {
        typedef T1 first_type;
        typedef T2 second_type;
        first_type first;
        second_type second;
        pair() :first(first_type()),second(second_type()){};
        template<class U1, class U2>
        pair(const pair<U1,U2> &pr): first(pr.first), second(pr.second){}
        pair (const T1 &f, const T2 &s): first(f), second(s){}
        pair &operator=(const pair &other)
        {   
            first = other.first;
            second = other.second;
            return *this; 
        }
        
    };
    template<class T1, class T2>
    bool operator==(const pair<T1, T2> &lhs, const pair<T1, T2>& rhs)
    {
       return lhs.first == rhs.first && lhs.second == rhs.second;
    }

    template<class T1, class T2>
    bool operator!=(const pair<T1, T2> &lhs, const pair<T1, T2>& rhs)
    {
        return !(lhs==rhs);
    }

    template<class T1, class T2>
    bool operator<(const pair<T1, T2> &lhs, const pair<T1, T2>& rhs)
    {
        return lhs.first<rhs.first || (!(rhs.first<lhs.first) && lhs.second<rhs.second);
    }

    template<class T1, class T2>
    bool operator<=(const pair<T1, T2> &lhs, const pair<T1, T2>& rhs)
    {
       return !(rhs<lhs);
    }

    template<class T1, class T2>
    bool operator>(const pair<T1, T2> &lhs, const pair<T1, T2>& rhs)
    {
        return rhs < lhs;
    }
    
    template<class T1, class T2>
    bool operator>=(const pair<T1, T2> &lhs, const pair<T1, T2>& rhs)
    {
        return !(lhs<rhs);
    }
    
    template<class T1, class T2>
    pair<T1, T2>make_pair(T1 x, T2 y)
    { 
        return (pair<T1, T2>(x, y));        
    };

     template<class InputIterator1, class InputIterator2>
    bool lexicographical_compare(InputIterator1 first, InputIterator1 last, InputIterator2 first2, InputIterator2 last2)
    {
        for ( ; (first != last) && (first2 != last2); ++first, (void) ++first2)
        {
            if (*first < *first2)
                return true;
            if (*first2 < *first)
                return false;
        }
        return (first == last) && (first2 != last2);
    };

    template<class InputIterator1, class InputIterator2>
    bool equal(InputIterator1 first, InputIterator1 last, InputIterator2 first2)
    {
        for(; first != last; ++first, ++first2)
        {
            if (!(*first == *first2))
                return false;
        }
        return true;
    }

    template<class InputIterator1, class InputIterator2, class Compare>
    bool lexicographical_compare(InputIterator1 first, InputIterator1 last, InputIterator2 first2, InputIterator2 last2, Compare comp)
    {
        for ( ; (first != last) && (first2 != last2); ++first, (void) ++first2)
        {
            if (comp(*first, *first2))
                return true;
            if (comp(*first2, *first))
                return false;
        }
        return (first == last) && (first2 != last2);
    };

    template<typename Iterator>
    ptrdiff_t distance(Iterator first, Iterator last)
    {
        ptrdiff_t distanc = 0;
        while(first!=last)
        {
            ++distanc;
            ++first;
        }
    return distanc;
    }

}