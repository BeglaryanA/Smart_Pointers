#ifndef UNIQUE_PTR_H
#define UNIQUE_PTR_H
#include <memory>
#include <functional>

template <typename T, typename Deleter = std::default_delete<T>>
class unique_ptr {
public:
    unique_ptr();
    unique_ptr(unique_ptr&&);
    unique_ptr(const unique_ptr&) = delete;
    unique_ptr(std::nullptr_t);
    unique_ptr(T*);
    ~unique_ptr();
public:
    unique_ptr& operator=(unique_ptr&&);
    unique_ptr& operator=(const unique_ptr&) = delete;

public:
    T& operator*() const;
    T* operator->();
    operator bool();

public:
    T* get() const; 
    T* release();
    void reset();
    void swap(unique_ptr&);
private:
    T* m_ptr;
}; 

#endif // UNIQUE_PTR_H 