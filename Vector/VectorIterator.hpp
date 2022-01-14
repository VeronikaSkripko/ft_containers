#ifndef FT_CONTAINERS_VECTORITERATOR_HPP
#define FT_CONTAINERS_VECTORITERATOR_HPP

#include <iostream>
#include "../ft_utils.h"

template<typename Iterator>
class VectorIterator
{
protected:
	Iterator                                           current; //the underlying iterator from which base() copies the name is for exposition only
	typedef typename ft::iterator_traits<Iterator>     traits_type;
public:
	typedef Iterator                                   	iterator_type;
	typedef typename traits_type::iterator_category     iterator_category;
	typedef typename traits_type::value_type            value_type;
	typedef typename traits_type::difference_type       difference_type;
	typedef typename traits_type::reference             reference;
	typedef typename traits_type::pointer               pointer;

	VectorIterator() : current(Iterator()){}
	VectorIterator(const Iterator& i) : current(i){}
	// Allow iterator to const_iterator conversion
	template<typename _Iter>
	VectorIterator(const VectorIterator<_Iter>& src) : current(src.base()) {}

	reference operator*() const
	{
		return *current;
	}

	pointer operator->() const
	{
		return current;
	}

	VectorIterator& operator+=(difference_type n)
	{
		current += n;
		return *this;
	}

	VectorIterator operator+(difference_type n) const
	{
		return VectorIterator(current + n);
	}

	VectorIterator& operator++()
	{
		++current;
		return *this;
	}

	VectorIterator operator++(int)
	{
		return VectorIterator(current++);
	}

	VectorIterator& operator-=(difference_type n)
	{
		current -= n;
		return *this;
	}

	VectorIterator operator-(difference_type n) const
	{
		return VectorIterator(current - n);
	}

	VectorIterator& operator--()
	{
		--current;
		return *this;
	}

	VectorIterator operator--(int)
	{
		return VectorIterator(current--);
	}

	reference operator[](difference_type n) const
	{
		return current[n];
	}

	const Iterator& base() const
	{
		return current;
	}
};


template<typename Iterator>
bool  operator==(const VectorIterator<Iterator>& lhs, const VectorIterator<Iterator>& rhs)
{ return lhs.base() == rhs.base(); }

template<typename IteratorL, typename IteratorR>
bool  operator!=(const VectorIterator<IteratorL>& lhs, const VectorIterator<IteratorR>& rhs)
{ return lhs.base() != rhs.base(); }

template<typename Iterator>
bool  operator!=(const VectorIterator<Iterator>& lhs, const VectorIterator<Iterator>& rhs)
{ return lhs.base() != rhs.base(); }

template<typename IteratorL, typename IteratorR>
bool  operator<(const VectorIterator<IteratorL>& lhs, const VectorIterator<IteratorR>& rhs)
{ return lhs.base() < rhs.base(); }

template<typename Iterator>
bool  operator<(const VectorIterator<Iterator>& lhs, const VectorIterator<Iterator>& rhs)
{ return lhs.base() < rhs.base(); }

template<typename IteratorL, typename IteratorR>
bool  operator>(const VectorIterator<IteratorL>& lhs, const VectorIterator<IteratorR>& rhs)
{ return lhs.base() > rhs.base(); }

template<typename Iterator>
bool  operator>(const VectorIterator<Iterator>& lhs, const VectorIterator<Iterator>& rhs)
{ return lhs.base() > rhs.base(); }

template<typename IteratorL, typename IteratorR>
bool operator<=(const VectorIterator<IteratorL>& lhs, const VectorIterator<IteratorR>& rhs)
{ return lhs.base() <= rhs.base(); }

template<typename Iterator>
bool operator<=(const VectorIterator<Iterator>& lhs, const VectorIterator<Iterator>& rhs)
{ return lhs.base() <= rhs.base(); }

template<typename IteratorL, typename IteratorR>
bool operator>=(const VectorIterator<IteratorL>& lhs, const VectorIterator<IteratorR>& rhs)
{ return lhs.base() >= rhs.base(); }

template<typename Iterator>
bool operator>=(const VectorIterator<Iterator>& lhs, const VectorIterator<Iterator>& rhs)
{ return lhs.base() >= rhs.base(); }

// _GLIBCXX_RESOLVE_LIB_DEFECTS
// According to the resolution of DR179 not only the various comparison
// operators but also operator- must accept mixed iterator/const_iterator
// parameters.
template<typename IteratorL, typename IteratorR>
typename VectorIterator<IteratorL>::difference_type
operator-(const VectorIterator<IteratorL>& lhs, const VectorIterator<IteratorR>& rhs)
{ return lhs.base() - rhs.base(); }

template<typename Iterator>
typename VectorIterator<Iterator>::difference_type
operator-(const VectorIterator<Iterator>& lhs,  const VectorIterator<Iterator>& rhs)
{ return lhs.base() - rhs.base(); }

template<typename Iterator>
VectorIterator<Iterator> operator+(typename VectorIterator<Iterator>::difference_type n, const VectorIterator<Iterator>& i)
{ return VectorIterator<Iterator>(i.base() + n); }

template <class T>
VectorIterator<T> operator+(typename VectorIterator<T>::difference_type i, VectorIterator<T> &tmp)
{
	return tmp.base() + i;
}

template <class T>
VectorIterator<T> operator+(VectorIterator<T> &tmp, typename VectorIterator<T>::difference_type i)
{
	return tmp.base() + i;
}

#endif
