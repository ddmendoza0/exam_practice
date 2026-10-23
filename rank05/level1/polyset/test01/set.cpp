#include "set.hpp"

set::set(searchable_bag& b) : bag(&b) {}

set::~set() {}

set::set(const set& other) : bag(other.bag) {}

set& set::operator=( const set& other )
{
    if (this != &other)
        this->bag = other.bag;
    return (*this);
}

void set::insert(int v)
{
    if (!bag->has(v)) 
        bag->insert(v); 
}

void set::insert (int *arr, int n)
{
    for (int i = 0; i < n; i++)
        insert(arr[i]);
}

void set::print() const
{
    bag->print();
}

void set::clear()
{
    bag->clear();
}

bool set::has(int v) const
{
    return bag->has(v);
}

searchable_bag& set::get_bag()
{
    return *bag;
}