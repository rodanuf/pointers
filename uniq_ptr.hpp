#pragma once
#include <memory>

template <typename T>
struct default_deleter
{
    void operator()(T *ptr)
    {
        delete ptr;
    }
};

template <typename T>
struct default_deleter<T[]>
{
    void operator()(T *ptr)
    {
        delete[] ptr;
    }
};

template <typename T, typename deleter = default_deleter<T>>
class uniq_ptr
{
private:
    T* pointer;
    deleter deleter__;
private:
    uniq_ptr(T* ptr);

public:
    uniq_ptr();
    uniq_ptr(uniq_ptr&& other);
    uniq_ptr(const uniq_ptr&) = delete;
    ~uniq_ptr();

    deleter& get_deleter();

    uniq_ptr& operator=(const uniq_ptr&) = delete;
    uniq_ptr& operator=(uniq_ptr&& other);

    T* operator->() const;
    T& operator*();
    T& operator[](int index);

    operator bool() const;

    T* get() const;
    T* release();

    void reset(T* ptr);
    void swap(uniq_ptr& other);
    void clear();
};

template <typename T, typename deleter>
uniq_ptr<T, deleter> make_uniq_ptr(T*& ptr);

template <typename T, typename deleter>
uniq_ptr<T, deleter> make_uniq_ptr(T& obj);


#include "uniq_ptr.tpp"
