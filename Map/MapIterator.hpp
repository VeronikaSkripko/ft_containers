#ifndef FT_CONTAINERS_MAPITERATOR_HPP
#define FT_CONTAINERS_MAPITERATOR_HPP

#include "/Users/nika_skripko/Documents/Veronika/school/ft_containers/ft_utils.h"
#include "stl_tree_like.hpp"

template <class ValueType>
class MapIterator : public ft::iterator<ft::bidirectional_iterator_tag, ValueType>
{
public:
	typedef ValueType                                                               value_type;
	typedef ft::bidirectional_iterator_tag                                          iterator_category;
	typedef typename ft::iterator<iterator_category, value_type>::pointer           pointer;
	typedef typename ft::iterator<iterator_category, value_type>::reference         reference;
	typedef typename ft::iterator<iterator_category, value_type>::difference_type   difference_type;

	typedef MapIterator<value_type>                                              	_self;
	typedef typename ft::stl_tree_like<value_type>::_base_ptr                       _base_ptr;
	typedef typename ft::stl_tree_like<value_type>*                                 _link_type;

	_base_ptr                                                                       _node;

	MapIterator() : _node() {}
	MapIterator(const MapIterator& src) : _node(src.base()) { }
	MapIterator(_base_ptr x) : _node(x) { }

	template<typename _Iter>
	MapIterator(const MapIterator<_Iter>& src) : _node(src.base()) {}

	~MapIterator() {};

	const _base_ptr             base() const { return (_node); }
	reference                   operator*() const { return *static_cast<_link_type>(_node)->valptr(); }
	pointer                     operator->() const { return static_cast<_link_type> (_node)->valptr(); }
	bool                        operator==(const _self& x) const { return _node == x._node; }
	bool                        operator!=(const _self& x) const { return _node != x._node; }
	_self&                      operator++() { _node = rb_tree_increment(_node); return *this; }
	_self&                      operator--() { _node = rb_tree_decrement(_node); return *this; }
	_self                       operator++(int)
	{
		_self _tmp = *this;
		_node = rb_tree_increment(_node);
		return _tmp;
	}
	_self           operator--(int)
	{
		_self _tmp = *this;
		_node = rb_tree_decrement(_node);
		return _tmp;
	}
};

template<typename ValueType>
class MapConstIterator : public ft::iterator<ft::bidirectional_iterator_tag, ValueType>
{
public:
	typedef ValueType                                                               value_type;
	typedef MapIterator<ValueType>                                               iterator;
	typedef ft::bidirectional_iterator_tag                                          iterator_category;
	typedef const ValueType&                                                        reference;
	typedef const ValueType*                                                        pointer;
	typedef typename ft::iterator<iterator_category, value_type>::difference_type   difference_type;

	typedef MapConstIterator<ValueType>                                         _self;
	typedef ft::rb_tree_node_base::_const_base_ptr                                 _base_ptr;
	typedef const ft::stl_tree_like<ValueType>*                                     _link_type;

	_base_ptr                                                                       _node;

	MapConstIterator() : _node() { }
	MapConstIterator(_base_ptr x) : _node(x) { }
	MapConstIterator(const iterator& it) : _node(it._node) { }
	bool            operator==(const _self& x) const { return _node == x._node; }
	bool            operator!=(const _self& x) const { return _node != x._node; }
	iterator        _M_const_cast() const { return iterator(const_cast<typename iterator::_base_ptr>(_node)); }
	reference       operator*() const { return *static_cast<_link_type>(_node)->valptr(); }
	pointer         operator->() const { return static_cast<_link_type>(_node)->valptr(); }
	_self&          operator++() { _node = rb_tree_increment(_node); return *this; }
	_self&          operator--() { _node = rb_tree_decrement(_node); return *this; }
	_self           operator++(int)
	{
		_self _tmp = *this;
		_node = rb_tree_increment(_node);
		return _tmp;
	}
	_self           operator--(int)
	{
		_self _tmp = *this;
		_node = rb_tree_decrement(_node);
		return _tmp;
	}
};

template <class ValueType>
MapIterator<ValueType>                       operator+(int a, MapIterator<ValueType> b)
{
	return (b.base() + a);
}

template <class ValueType>
MapConstIterator<ValueType>                  operator+(int a, MapConstIterator<ValueType> b)
{
	return (b.base() + a);
}

template<typename Val>
bool                                            operator==(const MapIterator<Val>& x, const MapConstIterator<Val>& y)
{
	return x._node == y._node;
}

template<typename Val>
bool                                            operator!=(const MapIterator<Val>& x, const MapConstIterator<Val>& y)
{
	return x._node != y._node;
}

#endif