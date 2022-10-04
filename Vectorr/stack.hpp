#pragma once

#include "../Map/iterator_traits.hpp"
#include "../Vectorr/vector.hpp"


 namespace ft
 {

	template <class T, class Container = ft::vector<T> > 
	class Stack
	{
		public:
			typedef T 			value_type;
			typedef Container 	container_type;
			typedef size_t		size_type;

			explicit Stack (const container_type& _cont = container_type()) : cont(_cont){};
			bool empty() const
			{ 
				return cont.empty();
			};
			value_type& top()
			{
				return cont.back();
			};
			size_type size() const
			{
				return cont.size();
			};
			const value_type& top() const 
			{
				return cont.back();
			};
			void push (const value_type& val)
			{
				cont.push_back(val);
			};
			void pop()
			{
				cont.pop_back();
			};
			
			template <class type, class cont>
  			friend bool operator== (const Stack<type,cont>& lhs, const Stack<type,cont>& rhs)
			{
				return (lhs.cont == rhs.cont);
			};
			template <class type, class cont>
  			friend bool operator!= (const Stack<type,cont>& lhs, const Stack<type,cont>& rhs)
			{
				return (lhs.cont != rhs.cont);
			};
			template <class type, class cont>
  			friend bool operator>= (const Stack<type,cont>& lhs, const Stack<type,cont>& rhs)
			{
				return (lhs.cont >= rhs.cont);
			};
			template <class type, class cont>
  			friend bool operator<= (const Stack<type,cont>& lhs, const Stack<type,cont>& rhs)
			{
				return (lhs.cont <= rhs.cont);
			};
			template <class type, class cont>
  			friend bool operator> (const Stack<type,cont>& lhs, const Stack<type,cont>& rhs)
			{
				return (lhs.cont > rhs.cont);
			};
			template <class type, class cont>
  			friend bool operator< (const Stack<type,cont>& lhs, const Stack<type,cont>& rhs)
			{
				return (lhs.cont < rhs.cont);
			};

		protected:
			container_type cont;
	};

}