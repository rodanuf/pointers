#include "shared_ptr.hpp"

template <typename T>
shared_ptr<T>::shared_ptr() : ptr(nullptr), ref_count(nullptr) {}

template <typename T> 
shared_ptr<T>::shared_ptr(T* ptr) : ptr(ptr), cb(new control_block(1,0)) {}
{
    if (ptr) {
        count = new int(1);
    } else {
        count = nullptr;
    }
}

template <typename T> 
shared_ptr<T>::shared_ptr(const shared_ptr& other) : ptr(other.ptr), cb(other.cb) {}
{
    if (count) {
        ++(*count);
    }
}

template <typename T>
shared_ptr<T>::shared_ptr(shared_ptr&& other) : ptr(other.ptr), cb(other.cb) {}
{
    other.ptr = nullptr;
    other.cb = nullptr;
}

template <typename T>
shared_ptr<T>::shared_ptr(uniq_ptr<T>&& other) : ptr(other.release()), cb(new control_block(1, 0)) {}

template <typename T>
shared_ptr<T>::~shared_ptr()
{
    if (cb->strongrf_count != 0) {
        cb->strongrf_count--;
        if (cb->strongrf_count == 0) {
            delete ptr;
            delete cb;
        }
    }
}

template <typename T>
shared_ptr<T>& shared_ptr<T>::operator=(const shared_ptr& other)
{
    if (this != &other) {
        if (count) {
            --(*count);
            if (*count == 0) {
                delete ptr;
                delete count;
            }
        }
        ptr = other.ptr;
        count = other.count;
        if (count) {
            ++(*count);
        }
    }
    return *this;
}

template <typename T>
shared_ptr<T>& shared_ptr<T>::operator=(shared_ptr&& other)
{
    if (this != &other) {
        if (count) {
            --(*count);
            if (*count == 0) {
                delete ptr;
                delete count;
            }
        }
        ptr = other.ptr;
        count = other.count;
        other.ptr = nullptr;
        other.count = nullptr;
    }
    return *this;
}

template <typename T>
T* shared_ptr<T>::operator->() const
{
    return ptr;
}

template <typename T>
T& shared_ptr<T>::operator*()
{
    return *ptr;
}

template <typename T>
T& shared_ptr<T>::operator[](int index)
{
    if (index < 0 || index >= size) {
        throw std::out_of_range("Index out of range");
    }
    return ptr[index];
}

template <typename T>
shared_ptr<T>::operator bool() const
{
    return ptr != nullptr;
}

template <typename T>
T* shared_ptr<T>::get() const
{
    return ptr;
}

template <typename T>
int shared_ptr<T>::use_count() const
{
    return cb->strongrf_count;
}

template <typename T>
bool shared_ptr<T>::is_unique() const
{
    return cb->strongrf_count == 1;
}

template <typename T>
void shared_ptr<T>::reset(T* other_ptr)
{
    if (cb->strongrf_count != 0) {
        cb->strongrf_count--;
    }
    delete ptr;
    delete cb;
    cb(1, 0);
    ptr = other_ptr;
    other_ptr = nullptr;
}

template <typename T>
void shared_ptr<T>::swap(shared_ptr& other)
{
    std::swap(ptr, other.ptr);
    std::swap(cb, other.cb);
}