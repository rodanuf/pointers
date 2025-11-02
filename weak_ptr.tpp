#include "weak_ptr.hpp"

template <typename T>
weak_ptr<T>::weak_ptr() : ptr(nullptr), cb(nullptr) {}

template <typename T>
weak_ptr<T>::weak_ptr(const shared_ptr<T>& other) : ptr(other.ptr), cb(other.cb)
{
    cb->weakrf_count++;
}

template <typename T>
weak_ptr<T>::weak_ptr(const weak_ptr<T>& other) : ptr(other.ptr), cb(other.cb)
{
    cb->weakrf_count++;
}

template <typename T>
weak_ptr<T>::weak_ptr(weak_ptr<T>&& other) : ptr(other.ptr), cb(other.cb)
{
    other.ptr = nullptr;
    other.cb = nullptr;
}

template <typename T>
weak_ptr<T>::~weak_ptr()
{
    if (cb != nullptr)
    {
        cb->weakrf_count--;
        if (cb->weakrf_count == 0 && cb->rf_count == 0)
        {
            delete cb;
        }
    }
}

template <typename T>
weak_ptr<T>& weak_ptr<T>::operator=(const weak_ptr<T>& other)
{
    weak_ptr tmp(other);
    this->swap(other);
    return *this;
}

template <typename T>
bool weak_ptr<T>::expired() const
{
    return ptr == nullptr;
}

template <typename T>
long weak_ptr<T>::use_count() const
{
    if (cb != nullptr)
    {
        return cb->weakrf_count;
    }
}

template <typename T>
shared_ptr<T>& weak_ptr<T>::lock() const
{
    cb->strongrf_count++;
    shared_ptr<T> ptr_;
    ptr_.ptr = ptr;
    ptr_.cb = cb;
    cb->strongrf_count++;
    return ptr_;
}

template <typename T>
void weak_ptr<T>::swap(weak_ptr<T>& other)
{
    std::swap(ptr, other.ptr);
    std::swap(cb, other.cb);
}