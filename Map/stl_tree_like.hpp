#ifndef FT_CONTAINERS_STL_TREE_LIKE_HPP
#define FT_CONTAINERS_STL_TREE_LIKE_HPP

#define RED   false
#define BLACK true
//stl_tree.h

namespace ft {
	struct rb_tree_node_base {
		typedef rb_tree_node_base			*_base_ptr;
		typedef const rb_tree_node_base		*_const_base_ptr;
		bool								color;
		_base_ptr							parent;
		_base_ptr							left;
		_base_ptr							right;

		static _base_ptr _S_minimum(_base_ptr x) {
			while (x->left != 0) x = x->left;
			return x;
		}

		static _const_base_ptr _S_minimum(_const_base_ptr x) {
			while (x->left != 0) x = x->left;
			return x;
		}

		static _base_ptr _S_maximum(_base_ptr x) {
			while (x->right != 0) x = x->right;
			return x;
		}

		static _const_base_ptr _S_maximum(_const_base_ptr x) {
			while (x->right != 0) x = x->right;
			return x;
		}
	};

	static rb_tree_node_base *local_Rb_tree_decrement(rb_tree_node_base *x) throw() {
		if (x->color == RED && x->parent->parent == x)
			x = x->right;
		else if (x->left != 0) {
			rb_tree_node_base *y = x->left;
			while (y->right != 0)
				y = y->right;
			x = y;
		} else {
			rb_tree_node_base *y = x->parent;
			while (x == y->left) {
				x = y;
				y = y->parent;
			}
			x = y;
		}
		return x;
	}

	rb_tree_node_base *rb_tree_decrement(rb_tree_node_base *x) throw() {
		return local_Rb_tree_decrement(x);
	}

	const rb_tree_node_base *rb_tree_decrement(const rb_tree_node_base *x) throw() {
		return local_Rb_tree_decrement(const_cast<rb_tree_node_base *>(x));
	}

	static rb_tree_node_base *local_Rb_tree_increment(rb_tree_node_base *x) throw() {
		if (x->right != 0) {
			x = x->right;
			while (x->left != 0)
				x = x->left;
		} else {
			rb_tree_node_base *y = x->parent;
			while (x == y->right) {
				x = y;
				y = y->parent;
			}
			if (x->right != y)
				x = y;
		}
		return x;
	}

	rb_tree_node_base *rb_tree_increment(rb_tree_node_base *x) throw() {
		return local_Rb_tree_increment(x);
	}

	const rb_tree_node_base *rb_tree_increment(const rb_tree_node_base *x) throw() {
		return local_Rb_tree_increment(const_cast<rb_tree_node_base *>(x));
	}

	template<typename Val>
	struct stl_tree_like : public rb_tree_node_base {
		typedef stl_tree_like<Val>*	_link_type;
		Val							value_field;

		stl_tree_like(const Val &v) : rb_tree_node_base(), value_field(v) {}

		Val *valptr() { return &value_field; }

		const Val *valptr() const { return &value_field; }
	};
}

#endif
