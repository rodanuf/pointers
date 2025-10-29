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
uniq_ptr<T, deleter>::uniq_ptr(uniq_ptr &&other) : pointer(other.pointer), deleter__(std::move(other.get_deleter()))
{
    other.pointer = nullptr;
}

template <typename T, typename deleter>
uniq_ptr<T, deleter>::~uniq_ptr()
{
    if (pointer != nullptr)
    {
        deleter__(pointer);
    }
}

template <typename T, typename deleter>
deleter& uniq_ptr<T, deleter>::get_deleter()
{
    return deleter__;
}

template <typename T, typename deleter>
uniq_ptr<T, deleter>& uniq_ptr<T, deleter>::operator=(uniq_ptr&& other)
{
    if (pointer != nullptr)
    {
        deleter__(pointer);
    }
    pointer = other.pointer;
    deleter__ = std::move(other.get_deleter());
    other.pointer = nullptr;
    return *this;
}

template <typename T, typename deleter>
T* uniq_ptr<T, deleter>::operator->() const
{
    return pointer;
}

template <typename T, typename deleter>
T& uniq_ptr<T, deleter>::operator*()
{
    return *pointer;
}

template <typename T, typename deleter>
T& uniq_ptr<T, deleter>::operator[](int index)
{
    if (index < 0 || index >= sizeof(pointer))
    {
        throw std::out_of_range("Index out of range");
    }
    return pointer[index];
}

template <typename T, typename deleter>
uniq_ptr<T, deleter>::operator bool() const
{
    return pointer != nullptr;
}

template <typename T, typename deleter>
T* uniq_ptr<T, deleter>::get() const
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
    uniq_ptr<T, default_deleter<T>> uptr__;
    uptr__.reset(ptr);
    ptr = nullptr;
    return uptr__;
}

template <typename T>
uniq_ptr<T, malloc_deleter<T>> make_uniq_from(const T& obj)
{
    T* ptr = (T*)malloc(sizeof(T));
    new (ptr) T(std::move(obj)); //placement_new (не выделение памяти, а создание объекта на уже выделенной)
    uniq_ptr<T, malloc_deleter<T>> uptr__;
    uptr__.reset(ptr);  
    ptr = nullptr;  
    return uptr__;
}