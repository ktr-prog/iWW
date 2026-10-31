
#include <cstdlib>
#include <new>

extern "C" void Mem_FreeForDelete(void *p);
extern "C" int host_is_game_heap(const void *p);

void *operator new(std::size_t size) {
    void *p = std::malloc(size ? size : 1);
    if (!p) std::abort();
    return p;
}

void *operator new[](std::size_t size) {
    return ::operator new(size);
}

void *operator new(std::size_t size, const std::nothrow_t &) noexcept {
    return std::malloc(size ? size : 1);
}

void *operator new[](std::size_t size, const std::nothrow_t &) noexcept {
    return std::malloc(size ? size : 1);
}

void operator delete(void *p) noexcept {
    if (!p) return;
    if (host_is_game_heap(p)) Mem_FreeForDelete(p);
    else std::free(p);
}

void operator delete[](void *p) noexcept {
    ::operator delete(p);
}

void operator delete(void *p, std::size_t) noexcept {
    ::operator delete(p);
}

void operator delete[](void *p, std::size_t) noexcept {
    ::operator delete(p);
}

void operator delete(void *p, const std::nothrow_t &) noexcept {
    ::operator delete(p);
}

void operator delete[](void *p, const std::nothrow_t &) noexcept {
    ::operator delete(p);
}
