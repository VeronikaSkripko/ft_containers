#ifndef FT_CONTAINERS_VECTOR_HPP
#define FT_CONTAINERS_VECTOR_HPP

#include <iostream>
#include "../ft_utils.h"
#include "VectorIterator.hpp"
#include "ReverseIterator.hpp"


template <class T, class Allocator = std::allocator<T> >
class Vector {
public:
	typedef T											value_type;
	typedef Allocator									allocator_type;
	typedef std::size_t									size_type;
	typedef std::ptrdiff_t                              difference_type;
	typedef typename allocator_type::reference          reference;
	typedef typename allocator_type::const_reference    const_reference;
	typedef typename allocator_type::pointer            pointer;
	typedef typename allocator_type::const_pointer      const_pointer;
	typedef VectorIterator<pointer>                  	iterator;
	typedef VectorIterator<const_pointer>            	const_iterator;
	typedef ft::ReverseIterator<iterator>               reverse_iterator;
	typedef ft::ReverseIterator<const_iterator>         const_reverse_iterator;

private:
	T*				v_data;		// Pointer on an array of Iterator values
	size_t			_size;		//Number of Iterator values inside the vector
	size_t			_capacity;	// Capacity allocated (can be greater than _size)
	allocator_type	_alloc;		// Copy of allocator_type object

	void			reallocate(size_t newCapacity)
	{
		T* newBlock = _alloc.allocate(newCapacity);

		if(newCapacity < _size)
			_size = newCapacity;
		for (size_t i = 0; i < _size; ++i) {
			newBlock[i] =  v_data[i];
		}

		_alloc.deallocate(v_data, _capacity);
		v_data = newBlock;
		_capacity = newCapacity;
	}
	class			OutOfBoundsException : public std::exception
	{
		virtual const char* what() const throw() { return ("Out of bounds"); }
	};
	class			MaxSizeException : public std::exception
	{
		virtual const char* what() const throw() { return ("Maximum size exceeded"); }
	};

public:
/* Construct/Copy/Destroy */
	explicit Vector(const allocator_type& alloc = allocator_type()) : _size(0), _capacity(0), _alloc(alloc)
	{
		v_data = _alloc.allocate(_capacity);
	}

	explicit Vector(size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type())
	: _size(n), _capacity(n), _alloc(alloc)
	{
		v_data = _alloc.allocate(_capacity);
		for (size_type i = 0; i < _size; ++i)
			_alloc.construct(&v_data[i], val);
	}

	template <class InputIterator>
	Vector (InputIterator first, typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type last, const allocator_type& alloc = allocator_type())
	: _alloc(alloc)
	{
		difference_type len = ft::distance(first, last);
		v_data = _alloc.allocate(len);
		_size = len;
		_capacity = len;
		for (size_type i = 0; i < _size; i++)
		{
			_alloc.construct(v_data + i, *(first + i));
		}
	}

	Vector(const Vector &a){
		*this = a;
	}

	~Vector(){
		for (size_t i = 0; i < _size; i++)
			_alloc.destroy(v_data + i);
		_alloc.deallocate(v_data, _capacity);
	}

	Vector& operator=(const Vector&a)
	{
		if(this != &a)
		{
			this->_alloc = a._alloc;
			this->_size = a._size;
			this->_capacity = a._capacity;
			this->v_data = this->_alloc.allocate(_capacity);
			for (size_t i = 0; i < a._size; i++){
				_alloc.construct(&v_data[i], *(a.v_data + i));
			}
		}
		return *this;
	}
/* Iterators */
	iterator begin(void){
		return (iterator(v_data));
	};

	const_iterator begin() const{
		return (const_iterator(v_data));
	}

	iterator end(void){
		return (iterator(v_data + _size));
	};

	const_iterator end() const{
		return (const_iterator(v_data + _size));
	}

	reverse_iterator rbegin() {
		return (reverse_iterator(this->end()));
	}

	const_reverse_iterator rbegin() const {
		return (const_reverse_iterator(end()));
	}

	reverse_iterator rend() {
		return (reverse_iterator(this->begin()));
	}

	const_reverse_iterator rend() const {
		return (const_reverse_iterator(begin()));
	}
/* Capacity */
	size_t size() const
	{
		return (this->_size);
	}

	size_type max_size()
	{
		std::less<size_t> comp;
		if (comp(_alloc.max_size(), std::numeric_limits<difference_type>::max())) {
			return _alloc.max_size();
		} else {
			return std::numeric_limits<std::allocator<char>::difference_type>::max();
		}
	}

	void resize (size_type n, value_type val = value_type())
	{
		if(n == this->size())
			return;
		if(n > _capacity)
			reallocate(n);
		while(n > _size)
			push_back(val);
		while(n < _size)
			pop_back();
	}

	size_t capacity()
	{
		return (this->_capacity);
	}

	bool empty() const
	{
		return (!_size);
	}

	void reserve(size_type n)
	{
		if (n > max_size())
			throw MaxSizeException();
		else if (n <= _capacity)
			return ;
		else
			reallocate(n);
	}
/* Element Access */
	reference operator[] (size_type n)
	{
		return (v_data[n]);
	}

	const_reference	operator[] (size_type n) const
	{
		return (v_data[n]);
	}

	reference at(size_t index)
	{
		if (index >= _size)
			throw OutOfBoundsException();
		return (v_data[index]);
	}

	const_reference at(size_t index) const
	{
		if (index >= _size)
			throw OutOfBoundsException();
		return (v_data[index]);
	}

	reference back()
	{
		return v_data[_size - 1];
	}

	const_reference back() const
	{
		return v_data[_size - 1];
	}

	reference front()
	{
		return v_data[0];
	}

	const_reference front() const
	{
		return v_data[0];
	}
/* Modifiers */

	template< class InputIt >
	void assign(InputIt first, typename ft::enable_if<!ft::is_integral<InputIt>::value, InputIt>::type last)
	{
		clear();
		insert(begin(), first, last);
	}

	void assign(size_type count, const T& value)
	{
		clear();
		insert(begin(), count, value);
	}

	iterator insert (iterator position, const value_type& val)
	{
		size_type dist;

		dist = ft::distance(this->begin(), position);
		if (_size + 1 > _capacity)
		{
			T*			newBlock;
			size_type	i;
			newBlock = _alloc.allocate(_capacity ? _capacity * 2 : 2);
			for (i = 0; i < dist; i++)
				_alloc.construct(newBlock + i, *(v_data + i));
			_alloc.construct(newBlock + i++, val);
			_size++;
			for ( ; i < _size; i++){
				_alloc.construct(newBlock + i, *(v_data + i - 1));
				_alloc.destroy(v_data + i);
			}
			_alloc.deallocate(v_data, _capacity);
			this->v_data = newBlock;
			_capacity *= 2;
		}
		else
		{
			size_type i;
			for (i = _size; i > dist; i--)
				v_data[i] = v_data[i - 1];
			_size++;
			_alloc.construct(v_data + i, val);
		}
		return (iterator(v_data + dist));
	}

	void insert (iterator position, size_type n, const value_type& val)
	{
		size_type dist = ft::distance(this->begin(), position);
		if (_size + n > _capacity)
		{
			T* newBlock;
			size_type newCapacity = _capacity ? _capacity* 2 : 2;
			while (_size + n > newCapacity)
				newCapacity *= 2;
			newBlock = _alloc.allocate(newCapacity);
			size_type i;
			for (i = 0; i < dist; i++)
				_alloc.construct(newBlock + i, *(v_data + i));
			for (int tmp = n ; tmp > 0; tmp--, _size++, i++)
				_alloc.construct(newBlock + i, val);
			for ( ; i < _size; i++){
				_alloc.construct(newBlock + i, *(v_data + i - n));
				_alloc.destroy(v_data + i);
			}
			_alloc.deallocate(v_data, _capacity);
			this->v_data = newBlock;
			_capacity = newCapacity;

		}
		else
		{
			size_type i;
			size_type stop = n > dist ? n : dist;
			for (i = _size + n; i > stop; i--)
				v_data[i] = v_data[i - n];
			_size += n;
			for ( ; n > 0; n--, i++)
				_alloc.construct(v_data + i, val);
		}
	}

	template< class InputIt >
	void insert(iterator pos, InputIt first, typename ft::enable_if<!ft::is_integral<InputIt>::value, InputIt>::type last)
	{
		size_type dist = ft::distance(this->begin(), pos);
		size_type count = ft::distance(first, last);

		if (_size + count > _capacity)
		{
			T* newBlock;
			size_type newCapacity = _capacity ? _capacity* 2 : 2;

			while (_size + count > newCapacity)
				newCapacity *= 2;
			newBlock = _alloc.allocate(newCapacity);
			size_type i;
			for (i = 0; i < dist; i++)
				_alloc.construct(newBlock + i, *(v_data + i));
			for (int tmp = count ; tmp > 0; tmp--, _size++, i++, first++)
				_alloc.construct(newBlock + i, *first);
			for ( ; i < _size; i++){
				_alloc.construct(newBlock + i, *(v_data + i - count));
				_alloc.destroy(v_data + i);
			}
			_alloc.deallocate(v_data, _capacity);
			this->v_data = newBlock;
			_capacity = newCapacity;
		}
		else
		{
			size_type i;
			size_type stop = count > dist ? count : dist;
			for (i = _size + count; i > stop; i--)
				v_data[i] = v_data[i - count];
			_size += count;

			for ( ; count > 0; count--, i++, first++)
				_alloc.construct(v_data + i, *first);
		}
	}

	iterator erase(iterator position)
	{
		size_type i = ft::distance(begin(), position);
		_alloc.destroy(&(*position));
		for (; i < _size - 1; i++)
			v_data[i] = v_data[i + 1];
		_size--;
		return (position);
	}

	iterator erase(iterator first, iterator last)
	{
		size_type start = ft::distance(begin(), first);
		size_type count = ft::distance(first, last);
		for ( ; first != last ; first++)
			_alloc.destroy(&(*first));
		for ( ; start < _size - count; start++)
			v_data[start] = v_data[start + count];
		_size -= count;
		return (first);
	}

	void push_back (const T& val)
	{
		if((_size + 1) > _capacity)
			reallocate(_capacity ? _capacity * 2 : 1);
		_alloc.construct(&v_data[_size++], val);
	}

	void pop_back()
	{
		if (_size)
			_alloc.destroy(&v_data[_size-- - 1]);
	}

	void swap (Vector& x) {
		ft::swap(v_data, x.v_data);
		ft::swap(_size, x._size);
		ft::swap(_capacity, x._capacity);
	}

	void clear()
	{
		while (_size)
			pop_back();
	}

	size_t getLength()
	{
		return _size;
	}

	void print()
	{
		for (int i = 0; i < _size; ++i) {
			std::cout << v_data[i];
		}
		std::cout<< std::endl;
	}

	allocator_type get_allocator()
	{
		return (Allocator());
	}
};

/* Relational operators */
template<class T, class Alloc>
bool operator==(const Vector<T, Alloc> &a, const Vector<T, Alloc> &b)
{
	if (a.size() != b.size())
		return (false);
	unsigned long i = -1;
	while (++i < a.size())
	{
		if (a[i] != b[i])
			return (false);
	}
	return (true);
};

template<class T, class Alloc>
bool operator!=(const Vector<T, Alloc> &a, const Vector<T, Alloc> &b)
{
	return (!(a == b));
};

template <class T, class Alloc>
bool operator<(const Vector<T,Alloc> &a, const Vector<T,Alloc> &b)
{
	return (ft::lexicographical_compare(a.begin(), a.end(), b.begin(), b.end()));
}

template <class T, class Alloc>
bool operator<=(const Vector<T,Alloc> &a, const Vector<T,Alloc> &b)
{
	return !(b < a);
}

template <class T, class Alloc>
bool operator>(const Vector<T,Alloc> &a, const Vector<T,Alloc> &b)
{
	return (b < a);
}

template <class T, class Alloc>
bool operator>=(const Vector<T,Alloc> &a, const Vector<T,Alloc> &b)
{
	return (!(a < b));
}

template <class T, class Alloc>
void swap (Vector<T,Alloc>& x, Vector<T,Alloc>& y) {
	Vector<T,Alloc>	tmp(x);
	x = y;
	y = tmp;
}

#endif
