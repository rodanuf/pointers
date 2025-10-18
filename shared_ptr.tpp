#include "shared_ptr.hpp"

template <typename T>
shared_ptr<T>::shared_ptr() : ptr(nullptr), ref_count(nullptr) {}

template <typename T> 
shared_ptr<T>::shared_ptr(T* ptr) : ptr(ptr)
{
    if (ptr) {
        count = new int(1);
    } else {
        count = nullptr;
    }
}

template <typename T> 
shared_ptr<T>::shared_ptr(const shared_ptr& other) : ptr(other.ptr), count(other.count)
{
    if (count) {
        ++(*count);
    }
}

template <typename T>
shared_ptr<T>::shared_ptr(shared_ptr&& other) : ptr(other.ptr), count(other.count)
{
    other.ptr = nullptr;
    other.count = nullptr;
}

template <typename T>
shared_ptr<T>::~shared_ptr()
{
    if (count) {
        --(*count);
        if (*count == 0) {
            delete ptr;
            delete count;
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
T* shared_ptr<T>::operator->()
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
    return ptr[index];
}

template <typename T>
T* shared_ptr<T>::release()
{
    //return ptr;
}