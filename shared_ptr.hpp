#pragma once

#include "uniq_ptr.hpp"
#include "control_block.hpp"

template <typename T>
class shared_ptr
{
private:
    T* ptr;
    control_block* cb;

public:
    shared_ptr();
    shared_ptr(T* ptr);
    shared_ptr(const shared_ptr& other);
    shared_ptr(shared_ptr&& other);
    shared_ptr(uniq_ptr<T>&& other);
    ~shared_ptr();

    shared_ptr& operator=(const shared_ptr& other);
    shared_ptr& operator=(shared_ptr&& other);

    T* operator->() const;

    T& operator*();
    T& operator[](int index);

    operator bool() const;

    T* get() const;

    int use_count() const;
    
    bool is_unique() const;

    void reset(T* other_ptr);
    void swap(shared_ptr &other);

};

#include "shared_ptr.tpp"