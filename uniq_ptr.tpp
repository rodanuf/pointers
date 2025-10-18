#include "uniq_ptr.hpp"

template <typename T>
struct malloc_deleter
{
    void operator()(T* ptr)
    {
        free(ptr);
    }
};

template <typename T, typename deleter>
uniq_ptr<T, deleter>::uniq_ptr() : pointer(nullptr), deleter__() {} 

template <typename T, typename deleter>
uniq_ptr<T, deleter>::uniq_ptr(T* ptr) : pointer(ptr), deleter__() {}

template <typename T, typename deleter>
uniq_ptr<T, deleter>::uniq_ptr(uniq_ptr &&other) : pointer(other.pointer), deleter__(std::move(other.deleter__))
{
    other.pointer = nullptr;
}

template <typename T, typename deleter>
template <typename U, typename other_deleter>
uniq_ptr<T, deleter>::uniq_ptr(uniq_ptr<U, other_deleter>&& other) : pointer(other.realese()), deleter__(std::move(other.deleter__)) {}

template <typename T, typename deleter>
uniq_ptr<T, deleter>::~uniq_ptr()
{
    if (pointer != nullptr)
    {
        deleter__(pointer);
    }
}

template <typename T, typename deleter>
T& uniq_ptr<T, deleter>::operator*()
{
    return *pointer;
}

template <typename T, typename deleter>
uniq_ptr<T, deleter>::operator bool() const
{
    return pointer != nullptr;
}

template <typename T, typename deleter>
const T* uniq_ptr<T, deleter>::get()
{
    return pointer;
}

template <typename T, typename deleter>
T* uniq_ptr<T, deleter>::release()
{
    T* ptr = pointer;
    pointer = nullptr;
    return ptr;
}

template <typename T, typename deleter>
void uniq_ptr<T, deleter>::reset(T* ptr)
{
    if (pointer != nullptr)
    {
        deleter__(pointer);
    }
    pointer = ptr;
}

template <typename T, typename deleter>
void uniq_ptr<T, deleter>::swap(uniq_ptr& other)
{
    std::swap(pointer, other.pointer);
    std::swap(deleter__, other.deleter__);
}

template <typename T, typename deleter>
void uniq_ptr<T, deleter>::clear()
{
    if (pointer != nullptr)
    {
        deleter__(pointer);
        pointer = nullptr;
    }
}

template <typename T>
uniq_ptr<T, default_deleter<T>> make_uniq_from(T*& ptr)
{
    uniq_ptr<T, default_deleter<T>> uptr__(ptr);
    ptr = nullptr;
    return uptr__;
}

template <typename T>
uniq_ptr<T, malloc_deleter<T>> make_uniq_from(const T& obj)
{
    T* ptr = (T*)malloc(sizeof(T));
    new (ptr) T(std::move(obj)); //placement_new (не выделение памяти, а создание объекта на уже выделенной)
    uniq_ptr<T, malloc_deleter<T>> uptr__(ptr);    
    return uptr__;
}