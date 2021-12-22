#ifndef FT_CONTAINERS_STACK_HPP
#define FT_CONTAINERS_STACK_HPP

#include "../Vector/Vector.hpp"

template <class T, class Container = Vector<T> >
class Stack {

public:
	typedef T			value_type;
	typedef	Container	container_type;
	typedef	size_t		size_type;

protected:
	container_type	c;

public:
	explicit Stack (const container_type& a = container_type()) : c(a) {
	}
	bool empty() const {
		return this->c.empty();
	}
	size_type size() const {
		return this->c.size();
	}
	value_type& top() {
		return this->c.back();
	}
	const value_type& top() const {
		return this->c.back();
	}
	void push (const value_type& val) {
		this->c.push_back(val);
	}
	void pop() {
		this->c.pop_back();
	}

	friend bool	operator==(const Stack<T, Container>& lhs, const Stack<T, Container>& rhs) {
		return (lhs.c == rhs.c);
	}
	friend bool operator!=(const Stack<T, Container>& lhs, const Stack<T, Container>& rhs) {
		return (lhs.c != rhs.c);
	}
	friend bool	operator<(const Stack<T, Container>& lhs, const Stack<T, Container>& rhs) {
		return (lhs.c < rhs.c);
	}
	friend bool operator>(const Stack<T, Container>& lhs, const Stack<T, Container>& rhs) {
		return (lhs.c > rhs.c);
	}
	friend bool	operator<=(const Stack<T, Container>& lhs, const Stack<T, Container>& rhs) {
		return (lhs.c <= rhs.c);
	}
	friend bool operator>=(const Stack<T, Container>& lhs, const Stack<T, Container>& rhs) {
		return (lhs.c >= rhs.c);
	}
};

#endif
