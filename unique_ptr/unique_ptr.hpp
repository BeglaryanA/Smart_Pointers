#include "unique_ptr.h"

template <typename T, typename Deleter>
unique_ptr<T, Deleter>::unique_ptr()
: m_ptr{nullptr}
{}

template <typename T, typename Deleter>
unique_ptr<T, Deleter>::unique_ptr(std::nullptr_t rhs) 
: m_ptr{rhs}
{}

template <typename T, typename Deleter>
unique_ptr<T, Deleter>::unique_ptr(unique_ptr&& rhs) {
    this->m_ptr = rhs.m_ptr; 
    rhs.m_ptr = nullptr;
}

template <typename T, typename Deleter>
unique_ptr<T, Deleter>::unique_ptr(T* rhs)
: m_ptr{rhs}
{}

template <typename T, typename Deleter>
unique_ptr<T, Deleter>::~unique_ptr() {
    Deleter(m_ptr);
}

template <typename T, typename Deleter>
unique_ptr<T, Deleter>& unique_ptr<T, Deleter>::operator=(unique_ptr<T, Deleter>&& rhs) {
    this->m_ptr = rhs.m_ptr;
    rhs.m_ptr = nullptr;
} 

template <typename T, typename Deleter>
unique_ptr<T, Deleter>::operator bool() {
    return this->m_ptr != nullptr;
}

template <typename T, typename Deleter>
T& unique_ptr<T, Deleter>::operator*() const {
    return *this->m_ptr;
}

template <typename T, typename Deleter>
T* unique_ptr<T, Deleter>::operator->() {
    return this->m_ptr;
}

template <typename T, typename Deleter>
T* unique_ptr<T, Deleter>::get() const {
    return this->m_ptr;
}

template <typename T, typename Deleter>
Deleter& unique_ptr<T, Deleter>::get_deleter() {
    return Deleter::type;
}

template <typename T, typename Deleter>
const Deleter& unique_ptr<T, Deleter>::get_deleter() const {
    return Deleter::type;
}

template <typename T, typename Deleter>
T* unique_ptr<T, Deleter>::release() {
    return this->m_ptr;
}

template <typename T, typename Deleter>
void unique_ptr<T, Deleter>::swap(unique_ptr<T, Deleter>& rhs) {
    std::swap(this->m_ptr, rhs.m_ptr);
}