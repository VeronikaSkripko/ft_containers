#ifndef FT_CONTAINERS_FT_UTILS_H
#define FT_CONTAINERS_FT_UTILS_H

#include <sstream>
#include <string>


namespace ft {

	template<class T>
	void swap(T &a, T &b) {
		T c(a);
		a = b;
		b = c;
	}

	struct input_iterator_tag {};
	struct output_iterator_tag {};
	struct forward_iterator_tag : public input_iterator_tag {};
	struct bidirectional_iterator_tag : public forward_iterator_tag {};
	struct random_access_iterator_tag : public bidirectional_iterator_tag {};

	template<class Iterator>
	struct iterator_traits {
		typedef typename Iterator::iterator_category iterator_category;
		typedef typename Iterator::value_type value_type;
		typedef typename Iterator::difference_type difference_type;
		typedef typename Iterator::pointer pointer;
		typedef typename Iterator::reference reference;
	};

	template<typename Tp>
	struct iterator_traits<Tp *> {
		typedef ft::random_access_iterator_tag iterator_category;
		typedef Tp value_type;
		typedef std::ptrdiff_t difference_type;
		typedef Tp *pointer;
		typedef Tp &reference;
	};

	template<typename Tp>
	struct iterator_traits<const Tp *> {
		typedef ft::random_access_iterator_tag iterator_category;
		typedef Tp value_type;
		typedef std::ptrdiff_t difference_type;
		typedef const Tp *pointer;
		typedef const Tp &reference;
	};

	template<class Category, class T, class Distance = std::ptrdiff_t,
			class Pointer = T *, class Reference = T &>
	struct iterator {
		typedef T value_type;
		typedef Distance difference_type;
		typedef Pointer pointer;
		typedef Reference reference;
		typedef Category iterator_category;
	};

	template<class It>
	typename ft::iterator_traits<It>::difference_type
	do_distance(It first, It last, ft::input_iterator_tag) {
		typename ft::iterator_traits<It>::difference_type result = 0;
		while (first != last) {
			++first;
			++result;
		}
		return result;
	}

	template<class It>
	typename ft::iterator_traits<It>::difference_type
	do_distance(It first, It last, ft::random_access_iterator_tag) {
		return (last - first);
	}

	template<class It>
	typename ft::iterator_traits<It>::difference_type
	distance(It first, It last) {
		return (ft::do_distance(first, last, typename ft::iterator_traits<It>::iterator_category()));
	}

	template <bool B,  typename T = void>
	struct enable_if {};

	template <typename T>
	struct enable_if <true, T> {
		typedef T type;
	};

	template<typename Tp, Tp v>
	struct integral_constant {
		static const Tp value = v;
		typedef Tp value_type;
		typedef integral_constant<Tp, v> type;
		operator value_type() { return value; }
	};

	typedef ft::integral_constant<bool, true> true_type;
	typedef ft::integral_constant<bool, false> false_type;

	template<typename, typename>
	struct are_same {
		enum {
			value = 0
		};
		typedef false_type type;
	};

	template<bool>
	struct truth_type {
		typedef false_type type;
	};

	template<>
	struct truth_type<true> {
		typedef true_type type;
	};

	template<typename>
	struct is_integral_helper : public false_type {};

	template<typename Tp>
	struct is_integer {
		enum {
			value = 0
		};
		typedef false_type type;
	};

	// Thirteen specializations (yes there are eleven standard integer
	// types; <em>long long</em> and <em>unsigned long long</em> are
	// supported as extensions).  Up to four target-specific int<N>
	// types are supported as well.
	template<>
	struct is_integer<bool> {
		enum {
			value = 1
		};
		typedef true_type type;
	};
	template<>
	struct is_integer<char> {
		enum {
			value = 1
		};
		typedef true_type type;
	};
	template<>
	struct is_integral_helper<wchar_t> {
		const static bool value = true;
	};
	template<>
	struct is_integer<signed char> {
		enum {
			value = 1
		};
		typedef true_type type;
	};
	template<>
	struct is_integer<unsigned char> {
		enum {
			value = 1
		};
		typedef true_type type;
	};
	template<>
	struct is_integer<short> {
		enum {
			value = 1
		};
		typedef true_type type;
	};
	template<>
	struct is_integer<unsigned short> {
		enum {
			value = 1
		};
		typedef true_type type;
	};
	template<>
	struct is_integer<int> {
		enum {
			value = 1
		};
		typedef true_type type;
	};
	template<>
	struct is_integer<unsigned int> {
		enum {
			value = 1
		};
		typedef true_type type;
	};
	template<>
	struct is_integer<long> {
		enum {
			value = 1
		};
		typedef true_type type;
	};
	template<>
	struct is_integer<unsigned long> {
		enum {
			value = 1
		};
		typedef true_type type;
	};
	template<>
	struct is_integer<long long> {
		enum {
			value = 1
		};
		typedef true_type type;
	};
	template<>
	struct is_integer<unsigned long long> {
		enum {
			value = 1
		};
		typedef true_type type;
	};
	template<typename Tp>
	struct remove_const {
		typedef Tp type;
	};

	template<typename Tp>
	struct remove_const<Tp const> {
		typedef Tp type;
	};

	/// remove_volatile
	template<typename Tp>
	struct remove_volatile {
		typedef Tp type;
	};

	template<typename Tp>
	struct remove_volatile<Tp volatile> {
		typedef Tp type;
	};

	template<typename Tp>
	struct remove_cv {
		typedef typename remove_const<typename remove_volatile<Tp>::type>::type type;
	};

	template<typename>
	struct is_pointer_helper
			: public false_type {
	};

	template<typename Tp>
	struct is_pointer_helper<Tp *>
			: public true_type {
	};
	/// is_pointer

	template<typename Tp>
	struct is_pointer
			: public is_pointer_helper<typename remove_cv<Tp>::type>::type {
	};

	// is_integral
	template<typename Tp>
	struct is_integral : public integral_constant<bool, (is_integral_helper<typename remove_cv<Tp>::type>::value)> {
	};
	template<>
	struct is_integral<int> : ft::true_type {
	};

	template<class InputIterator1, class InputIterator2>
	bool
	lexicographical_compare(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, InputIterator2 last2) {
		while (first1 != last1) {
			if (first2 == last2 || *first2 < *first1)
				return false;
			else if (*first1 < *first2)
				return true;
			++first1;
			++first2;
		}
		return (first2 != last2);
	}

	template<bool _BoolType>
	struct _equal {
		template<typename _II1, typename _II2>
		static bool equal(_II1 first1, _II1 last1, _II2 first2) {
			for (; first1 != last1; ++first1, ++first2)
				if (!(*first1 == *first2))
					return false;
			return true;
		}
	};

	template<typename _II1, typename _II2>
	bool equal_aux(_II1 first1, _II1 last1, _II2 first2) {
		typedef typename ft::iterator_traits<_II1>::value_type _ValueType1;
		typedef typename ft::iterator_traits<_II2>::value_type _ValueType2;
		const bool simple = ((ft::is_integer<_ValueType1>::value
							  || ft::is_pointer<_ValueType1>::value)
							 && ft::is_pointer<_II1>::value
							 && ft::is_pointer<_II2>::value
							 && ft::are_same<_ValueType1, _ValueType2>::value);
		return ft::_equal<simple>::equal(first1, last1, first2);
	}

	template<typename _II1, typename _II2>
	bool
	equal(_II1 first1, _II1 last1, _II2 first2) {
		return ft::equal_aux(first1, last1, first2);
	}

	template <class arg, class result>
	struct unary_function
	{
		typedef arg argument_type;   ///< @c argument_type is the type of the
		typedef result result_type;  ///< @c result_type is the return type
	};

	template<typename Arg1, typename Arg2, typename Result>
	struct binary_function
	{
		typedef Arg1            first_argument_type;
		typedef Arg2            second_argument_type;
		typedef Result          result_type;
	};

	template <class Pair>
	struct Select1st : public unary_function<Pair,
			typename Pair::first_type>
	{
		typename Pair::first_type&       operator()(Pair& x) const { return x.first; }
		const typename Pair::first_type& operator()(const Pair& x) const  { return x.first; }
	};

	template <class Pair>
	struct Select2nd : public unary_function<Pair,
			typename Pair::second_type>
	{
		typename Pair::second_type&        operator()(Pair& x) const { return x.second; }
		const typename Pair::second_type&  operator()(const Pair& x) const { return x.second; }
	};
}

#endif
