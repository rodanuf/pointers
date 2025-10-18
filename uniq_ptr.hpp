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
public:
    uniq_ptr();
    explicit uniq_ptr(T* ptr);
    uniq_ptr(uniq_ptr&& other);
    template <typename U, typename other_deleter>
    uniq_ptr(uniq_ptr<U, other_deleter>&& other);
    uniq_ptr(const uniq_ptr&) = delete;
    ~uniq_ptr();
    
    uniq_ptr& operator=(const uniq_ptr&) = delete;

    T& operator*();

    operator bool() const;

    const T* get();
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
