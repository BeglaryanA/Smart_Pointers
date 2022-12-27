#ifndef SHARED_PTR_H
#define SHARED_PTR_H
#include <memory>
#include <functional>

template <typename T, typename Deleter = std::default_delete<T>>
class shared_ptr {
    struct ControlBlock {
        int RC;
        std::function<void(T*)> deleter;
        ControlBlock();
    };
    using pointer = T*;
    using reference = T&;
public:
    shared_ptr();
    shared_ptr(std::nullptr_t);
    shared_ptr(const shared_ptr&);
    shared_ptr(shared_ptr&&);
    shared_ptr(pointer);
    ~shared_ptr();

public:
    shared_ptr& operator=(const shared_ptr&);
    shared_ptr& operator=(shared_ptr&&);

public:
    pointer get() const;
    int use_count() const;
    bool unique() const;
    void reset();
    void reset(pointer);
    void swap(shared_ptr&);

public:
    reference operator*() const;
    pointer operator->() const;
private:
    T* m_ptr;
    ControlBlock* CB;
};


#endif // SHARED_PTR_H