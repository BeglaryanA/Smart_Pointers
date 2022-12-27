#include "shared_ptr.h"

template <typename T, typename Deleter>
shared_ptr<T, Deleter>::ControlBlock::ControlBlock()
:RC{0}
, deleter{Deleter()}
{}

template <typename T, typename Deleter>
shared_ptr<T, Deleter>::shared_ptr() 
: m_ptr{nullptr}
, CB{new ControlBlock()}
{}

template <typename T, typename Deleter>
shared_ptr<T, Deleter>::shared_ptr(const shared_ptr<T, Deleter>& rhs) {
    this->CB = rhs.CB;
    if (rhs.m_ptr == nullptr) {
        this->m_ptr = nullptr;
    } else {
        this->m_ptr = rhs.m_ptr;
        ++this->CB->RC;
    }
}

template <typename T, typename Deleter>
shared_ptr<T, Deleter>::shared_ptr(shared_ptr<T, Deleter>&& rhs) {
    this->CB = rhs.CB;
    if (rhs.m_ptr == nullptr) {
        this->m_ptr = nullptr;
    } else {
        this->m_ptr = rhs.m_ptr;
        ++this->CB->RC;
        rhs.m_ptr = nullptr;
    }
}

template <typename T, typename Deleter>
shared_ptr<T, Deleter>::shared_ptr(pointer rs) 
: m_ptr{rs}
, CB{new ControlBlock()}
{
    ++CB->RC;
}

template <typename T, typename Deleter>
shared_ptr<T, Deleter>::shared_ptr(std::nullptr_t rhs) 
: m_ptr{rhs}
, CB{new ControlBlock()}
{}

template <typename T, typename Deleter>
shared_ptr<T, Deleter>::~shared_ptr() {
    --this->CB->RC;
    if (this->CB->RC == 0) {
        CB->deleter(this->m_ptr);
        delete this->CB;
        this->CB = nullptr;
    }
    this->m_ptr = nullptr;
}

template <typename T, typename Deleter>
shared_ptr<T, Deleter>& shared_ptr<T, Deleter>::operator=(const shared_ptr<T, Deleter>& rhs) {
    this->CB->deleter(this->m_ptr);
    this->CB = rhs.CB;
    if (rhs.m_ptr == nullptr) {
        this->m_ptr = nullptr;
    } else {
        this->m_ptr = rhs.m_ptr;
        ++this->CB->RC;
    }
    return *this;
}

template <typename T, typename Deleter>
shared_ptr<T, Deleter>& shared_ptr<T, Deleter>::operator=(shared_ptr<T, Deleter>&& rhs) {
    this->CB->deleter(this->m_ptr);
    this->CB = rhs.CB;
    if (rhs.m_ptr == nullptr) {
        this->m_ptr = rhs.m_ptr;
    } else {
        this->m_ptr = rhs.m_ptr;
        rhs.m_ptr = nullptr;
    }
    return *this;
}

template <typename T, typename Deleter>
int shared_ptr<T, Deleter>::use_count() const {
    return (this->m_ptr == nullptr) ? 0 : this->CB->RC;
}

template <typename T, typename Deleter>
T* shared_ptr<T, Deleter>::get() const {
    return this->m_ptr;
}

template <typename T, typename Deleter>
bool shared_ptr<T, Deleter>::unique() const {
    return this->use_count() == 1;
}

template <typename T, typename Deleter>
void shared_ptr<T, Deleter>::swap(shared_ptr<T, Deleter>& rhs) {
    std::swap(this->m_ptr, rhs.m_ptr);
    std::swap(this->CB, rhs.CB);
}

template <typename T, typename Deleter>
void shared_ptr<T, Deleter>::reset() {
    this->CB->deleter(this->m_ptr);
    this->m_ptr = nullptr;
    this->CB->RC = 0;
}

template <typename T, typename Deleter>
void shared_ptr<T, Deleter>::reset(pointer rs) {
    this->CB->deleter(this->m_ptr);
    this->m_ptr = rs;
    this->CB->RC = 1;
}


template <typename T, typename Deleter>
T&  shared_ptr<T, Deleter>::operator*() const {
    return *this->m_ptr;
}

template <typename T, typename Deleter>
T*  shared_ptr<T, Deleter>::operator->() const {
    return this->m_ptr;
}