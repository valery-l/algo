#pragma once
#include <functional>
#include <algorithm>

// TODO: need testing

namespace treap
{
	using namespace std;

	struct node
	{
		node(int key, int value)
			: key(key)
			, value(value)
		{
			dummy = rand();
		}

		int key  ;
		int dummy;
		int value;

		node* left  = nullptr;
		node* right = nullptr;
	};

	node* merge(node* a, node* b)
	{
		if (a == nullptr)
			return b;

		if (b == nullptr)
			return a;

		if (a->dummy >= b->dummy)
		{
			a->right = merge(a->right, b);
			return a;
		}
		
		b->left = merge(a, b->left);
		return b;
	}

	pair<node*, node*> split(node* r, int value)
	{
		pair<node*, node*> pr = { nullptr, nullptr };

		if (r == nullptr)
			return pr;

		if (r->value == value)
			return { r->left, r->right };

		if (value < r->value)
		{
			pr = split(r->left, value);
			r->left = pr.second;
			pr.second = r;
		}
		else
		{
			pr = split(r->right, value);
			r->right = pr.first;
			pr.first = r;
		}
		
		return pr;
	}

	node* insert(node* r, int key, int value)
	{
		auto pr = split(r, value);
		return merge(merge(pr.first, new node(key, value)), pr.second);
	}

	node* erase(node* r, int value)
	{
		auto pr = split(r, value);
		return merge(pr.first, pr.second);
	}
}
