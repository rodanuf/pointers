#pragma once

#include "shared_ptr.hpp"
#include "control_block.hpp"

template <typename T>
class weak_ptr
{
private:
    T* ptr;
    control_block* cb;
public:
    weak_ptr();
    weak_ptr(const shared_ptr<T>& other);
    weak_ptr(const weak_ptr<T>& other);
    weak_ptr(weak_ptr<T>&& other);
    ~weak_ptr();

    weak_ptr& operator=(const weak_ptr<T>& other);
    weak_ptr& operator=(const shared_ptr<T>& other);

    bool expired() const;

    long use_count() const;

    shared_ptr<T>& lock() const;

    void swap(weak_ptr<T>& ptr);
};

#include "weak_ptr.tpp"