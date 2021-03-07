#pragma once

#include <utility>

namespace avl_tree_map
{
	template <typename K, typename T>
	class avl_tree_node
	{
	public:
		using key_type = K;
		using mapped_type = T;
		using value_type = std::pair<const key_type, mapped_type>;
		using reference = value_type&;
		using pointer = value_type*;
		using size_type = long;

		avl_tree_node() noexcept : key_value_pair_(value_type()), parent_(nullptr), left_(nullptr), right_(nullptr),
		                           height_(0)
		{
		}

		avl_tree_node(const value_type& x) : key_value_pair_(value_type(x)), parent_(nullptr), left_(nullptr),
		                                     right_(nullptr), height_(1)
		{
		}

		reference get_ref()
		{
			return key_value_pair_;
		}

		pointer get_pointer()
		{
			return (&key_value_pair_);
		}

		const key_type& get_key() { return key_value_pair_.first; }

		size_type get_height() const { return height_; }

		size_type get_balance()
		{
			size_type leftHeight = left_ == nullptr ? 0 : left_->get_height();
			size_type rightHeight = right_ == nullptr ? 0 : right_->get_height();
			return leftHeight - rightHeight;
		}

		void set_left(avl_tree_node* node)
		{
			left_ = node;
			if (left_ != nullptr)
			{
				left_->set_parent(this);
			}
			height_update();
		}

		void set_right(avl_tree_node* node)
		{
			right_ = node;
			if (right_ != nullptr)
			{
				right_->set_parent(this);
			}
			height_update();
		}

		void set_parent(avl_tree_node* node)
		{
			parent_ = node;
		}

		avl_tree_node* get_left()
		{
			return left_;
		}

		avl_tree_node* get_right()
		{
			return right_;
		}

		avl_tree_node* get_parent()
		{
			return parent_;
		}

	private:
		value_type key_value_pair_;
		avl_tree_node* parent_;
		avl_tree_node* left_;
		avl_tree_node* right_;
		size_type height_;

		void height_update()
		{
			size_type leftHeight = left_ == nullptr ? 0 : left_->get_height();
			size_type rightHeight = right_ == nullptr ? 0 : right_->get_height();
			height_ = std::max(leftHeight, rightHeight) + 1;
		}
	};
} // namespace avl_tree_map
