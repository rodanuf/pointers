#pragma once

#include "shared_ptr.hpp"
#include "control_block.hpp"

template <typename T>
class weak_ptr
{
private:
    T& _ptr;
    control_block* cb;
private:
    weak_ptr(const shared_ptr<T>& ptr);
public:
    weak_ptr();
    weak_ptr(const weak_ptr<T>& ptr);
    weak_ptr(weak_ptr<T>&& ptr);

    weak_ptr& operator=(const weak_ptr<T>& ptr);

    bool expired() const;

    long use_count() const;

    shared_ptr<T>& lock() const;

    void swap(weak_ptr<T>& ptr);
};