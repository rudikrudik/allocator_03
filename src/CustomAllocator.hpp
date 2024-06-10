#pragma once

template <class T, signed int S>
struct CustomPoolAllocator {
    typedef T value_type;

    static int pos;
    static constexpr int size = sizeof(T) * S;
    static uint8_t data[size];

    CustomPoolAllocator () = default;
    ~CustomPoolAllocator() = default;

    template <class U, signed int SU>
    explicit CustomPoolAllocator (const CustomPoolAllocator<U, SU>&) noexcept {}

    template <class TU, signed int SU>
    constexpr bool operator==(const CustomPoolAllocator<TU, SU>& a2) noexcept;

    template <class TU, signed int SU>
    constexpr bool operator!=(const CustomPoolAllocator<TU, SU>& a2) noexcept;

    T* allocate (std::size_t n) {
        if (pos + n > size)
            throw std::bad_alloc();

        int cur = pos;
        pos += n;
        return reinterpret_cast<T*>(data) + cur;
    }

    void deallocate (T*, std::size_t) {}

    template<typename U>
    struct rebind {
        using other = CustomPoolAllocator<U, S>;
    };
};


template <typename T, signed int S>
uint8_t CustomPoolAllocator<T, S>::data[size];

template <typename T, signed int S>
int CustomPoolAllocator<T, S>::pos = 0;


template<class T, int S>
template<class TU, int SU>
constexpr bool CustomPoolAllocator<T, S>::operator==(const CustomPoolAllocator<TU, SU> &a2) noexcept {
    return true;
}

template<class T, int S>
template<class TU, int SU>
constexpr bool CustomPoolAllocator<T, S>::operator!=(const CustomPoolAllocator<TU, SU> &a2) noexcept {
    return false;
}