#include "searchable_tree_bag.hpp"

searchable_tree_bag::searchable_tree_bag() : tree_bag() {}

searchable_tree_bag::~searchable_tree_bag() {}

searchable_tree_bag::searchable_tree_bag(const searchable_tree_bag& other) : tree_bag(other) {}

searchable_tree_bag& searchable_tree_bag::operator=(const searchable_tree_bag& other) 
{
    if (this != &other)
        tree_bag::operator=(other);
    return *this;
}

bool searchable_tree_bag::has( int val ) const
{
    node *cur = tree;
    while (cur != NULL)
    {
        if ( val < cur->value )
            cur = cur->l;
        else if ( val > cur->value )
            cur = cur->r;
        else
            return true;
    }
    return false;
}
