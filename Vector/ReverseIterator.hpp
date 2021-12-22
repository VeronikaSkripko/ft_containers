#ifndef FT_CONTAINERS_REVERSEITERATOR_HPP
#define FT_CONTAINERS_REVERSEITERATOR_HPP


namespace ft {
	template<typename Iterator>
	class ReverseIterator
			: public iterator<typename iterator_traits<Iterator>::iterator_category,
					typename iterator_traits<Iterator>::value_type,
					typename iterator_traits<Iterator>::difference_type,
					typename iterator_traits<Iterator>::pointer,
					typename iterator_traits<Iterator>::reference>
	{
	protected:
		Iterator current;
		typedef iterator_traits<Iterator>                traits_type;
	public:
		typedef Iterator                                 iterator_type;
		typedef typename traits_type::difference_type    difference_type;
		typedef typename traits_type::pointer            pointer;
		typedef typename traits_type::reference          reference;

		ReverseIterator() : current() { }
		ReverseIterator(iterator_type x) : current(x) { }
		ReverseIterator(const ReverseIterator& x) : current(x.current) { }

		template<typename _Iter>
		ReverseIterator(const ReverseIterator<_Iter>& x) : current(x.base()) { }

		iterator_type base() const
		{
			return current;
		}

		reference operator*() const
		{
			Iterator tmp = current;
			return *--tmp;
		}

		pointer operator->() const
		{
			return &(operator*());
		}

		ReverseIterator& operator++()
		{
			--current;
			return *this;
		}

		ReverseIterator operator++(int)
		{
			ReverseIterator tmp = *this;
			--current;
			return tmp;
		}

		ReverseIterator& operator--()
		{
			++current;
			return *this;
		}

		ReverseIterator operator--(int)
		{
			ReverseIterator tmp = *this;
			++current;
			return tmp;
		}

		ReverseIterator operator+(difference_type n) const
		{
			return ReverseIterator(current - n);
		}

		ReverseIterator& operator+=(difference_type n)
		{
			current -= n;
			return *this;
		}

		ReverseIterator operator-(difference_type n) const
		{
			return ReverseIterator(current + n);
		}

		ReverseIterator& operator-=(difference_type n)
		{
			current += n;
			return *this;
		}

		reference operator[](difference_type n) const
		{
			return *(*this + n);
		}
	};

	template<typename _Iterator>
	bool operator==(const ReverseIterator<_Iterator>& x, const ReverseIterator<_Iterator>& y)
	{ return x.base() == y.base(); }

	template<typename _Iterator>
	bool operator<(const ReverseIterator<_Iterator>& x, const ReverseIterator<_Iterator>& y)
	{ return y.base() < x.base(); }

	template<typename _Iterator>
	bool operator!=(const ReverseIterator<_Iterator>& x, const ReverseIterator<_Iterator>& y)
	{ return !(x == y); }

	template<typename _Iterator>
	bool operator>(const ReverseIterator<_Iterator>& x, const ReverseIterator<_Iterator>& y)
	{ return y < x; }

	template<typename _Iterator>
	bool operator<=(const ReverseIterator<_Iterator>& x, const ReverseIterator<_Iterator>& y)
	{ return !(y < x); }

	template<typename _Iterator>
	bool operator>=(const ReverseIterator<_Iterator>& x, const ReverseIterator<_Iterator>& y)
	{ return !(x < y); }

// _GLIBCXX_RESOLVE_LIB_DEFECTS
// DR 280. Comparison of ReverseIterator to const ReverseIterator.
	template<typename _IteratorL, typename _IteratorR>
	bool operator==(const ReverseIterator<_IteratorL>& x, const ReverseIterator<_IteratorR>& y)
	{ return x.base() == y.base(); }

	template<typename _IteratorL, typename _IteratorR>
	bool operator<(const ReverseIterator<_IteratorL>& x, const ReverseIterator<_IteratorR>& y)
	{ return y.base() < x.base(); }

	template<typename _IteratorL, typename _IteratorR>
	bool operator!=(const ReverseIterator<_IteratorL>& x, const ReverseIterator<_IteratorR>& y)
	{ return !(x == y); }

	template<typename _IteratorL, typename _IteratorR>
	bool operator>(const ReverseIterator<_IteratorL>& x, const ReverseIterator<_IteratorR>& y)
	{ return y < x; }

	template<typename _IteratorL, typename _IteratorR>
	bool operator<=(const ReverseIterator<_IteratorL>& x, const ReverseIterator<_IteratorR>& y)
	{ return !(y < x); }

	template<typename _IteratorL, typename _IteratorR>
	bool operator>=(const ReverseIterator<_IteratorL>& x, const ReverseIterator<_IteratorR>& y)
	{ return !(x < y); }

	template <class Iter1, class Iter2>
	typename ReverseIterator<Iter1>::difference_type operator-(const ReverseIterator<Iter1>& x, const ReverseIterator<Iter2>& y)
	{ return y.base() - x.base();}

	template <class Iter>
	ReverseIterator<Iter> operator+(typename ReverseIterator<Iter>::difference_type n, const ReverseIterator<Iter>& x)
	{ return ReverseIterator<Iter>(x.base() - n);}

}

#endif
