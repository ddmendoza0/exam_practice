#pragma once

#include "searchable_bag.hpp"

class set
{
    private:
        searchable_bag *bag;

    public:
        set(searchable_bag& b);
        ~set();
        set(const set& other);
        set& operator=(const set& other);

        void insert(int v);
        void insert (int *arr, int n);
        void print() const;
        void clear();

        searchable_bag& get_bag();
        bool has(int v) const;

};