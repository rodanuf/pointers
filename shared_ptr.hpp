#pragma once

template <typename T>
class shared_ptr
{
private:
    T* ptr;
    int* count;
public:
    shared_ptr();
    shared_ptr(T* ptr);
    shared_ptr(const shared_ptr& other);
    shared_ptr(shared_ptr&& other);
    ~shared_ptr();

    shared_ptr& operator=(const shared_ptr& other);
    shared_ptr& operator=(shared_ptr&& other);

    T* operator->();

    T& operator*();
    T& operator[](size_t index);

    T* release();

    int use_count() const;
    
    bool is_unique() const;

    void reset(T* ptr);
    void swap(shared_ptr &other);


};

template <typename T>
shared_ptr<T> make_shared_from(T& obj);

#include "shared_ptr.tpp"