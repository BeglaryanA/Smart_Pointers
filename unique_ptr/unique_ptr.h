#ifndef UNIQUE_PTR_H
#define UNIQUE_PTR_H
#include <memory>

template <typename T, typename Deleter = std::default_delete<T>>
class unique_ptr {
public:
    unique_ptr();
    unique_ptr(unique_ptr&&);
    unique_ptr(std::nullptr_t);
    unique_ptr(T*);
    ~unique_ptr();
public:
    unique_ptr& operator=(unique_ptr&&);
public:
    T& operator*() const;
    T* operator->();
    operator bool();

public:
    T* get() const;
    Deleter& get_deleter();  
    const Deleter& get_deleter() const;  
    T* release();
    void reset();
    void swap(unique_ptr&);
private:
    T* m_ptr;
}; 

#endif // UNIQUE_PTR_H 