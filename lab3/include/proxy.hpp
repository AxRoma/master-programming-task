/* Proxy object.
 * @file
 * @date 2018-08-07
 * @author Anonymous
 */

#ifndef __PROXY_HPP__
#define __PROXY_HPP__

#include <mutex>

template<class T, class MutexInjection = std::mutex>
class ptr_holder
{
public:
    explicit ptr_holder(T* ptr) : ptr_(ptr) {}

    //{ describe proxy object
    class proxy : private std::lock_guard<MutexInjection>
    {
        using guard_t = std::lock_guard<MutexInjection>;

    public:
        // Захватываем мьютекс в конструкторе (RAII) и запоминаем указатель.
        proxy(T* p, MutexInjection& m) : guard_t(m), ptr_(p) {}

        // Доступ к "сырому" указателю (неконстантный и константный варианты).
        T* operator->() { return ptr_; }
        const T* operator->() const { return ptr_; }

    private:
        T* ptr_;
    };

    // Возвращаем временный proxy-объект.
    proxy operator->() const
    {
        return proxy(ptr_, mutex_);
    }
    //}

private:
    T* ptr_;
    mutable MutexInjection mutex_;
};

#endif // __PROXY_HPP__
