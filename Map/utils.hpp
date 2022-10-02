#pragma once

namespace ft
{
    template<class T1, class T2> 
    struct pair
    {
        typedef T1 first_type;
        typedef T2 second_type;
        first_type first;
        second_type second;
        pair() :first(first_type()),second(second_type())
        {

        }
        template<class U1, class U2>
        pair(const pair<U1,U2> &pr): first(pr.first), second(pr.second)
        {

        }
        pair (const T1 &f, const T2 &s): first(f), second(s)
        {
            
        }
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
}
template <class InputIterator1, class InputIterator2>
    bool lexicographical_compare (InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, InputIterator2 last2)
    {
      size_t len1 = std::distance(first1,last1);
      size_t len2 = std::distance(first2,last2);
      if (len1 < len2)
        return true;
      else if (len1 > len2)
        return false;
      else
      {
        for (size_t i = 0 ; i < len1 ; i++)
        {
          if (first1[i] < first2[i])
            return true;
          else if (first1[i] > first2[i])
            return false;
        }
        return false;
      }
    };

    template <class InputIterator1, class InputIterator2, class Compare>
    bool lexicographical_compare (InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, InputIterator2 last2, Compare comp)
    {
      size_t len1 = std::distance(first1,last1);
      size_t len2 = std::distance(first2,last2);
      if (len1 < len2)
        return true;
      else if (len1 > len2)
        return false;
      else
      {
        for (size_t i = 0 ; i < len1 ; i++)
        {
          if (comp(first1[i],first2[i]))
            return true;
          else if (comp(first2[i],first1[i]))
            return false;
        }
        return false;
      }
    };