#pragma once

typedef int64_t int64;
typedef int16_t int16;
typedef int8_t int8;

typedef uint64_t uint64;
typedef uint32_t uint;
typedef uint16_t uint16;
typedef uint8_t uint8;
//typedef char byte;
typedef unsigned char ubyte;

template<typename T>
using Ref = std::shared_ptr<T>;

template<typename T, typename... Args>
std::shared_ptr<T> CreateRef(Args&&... args) {
    return std::make_shared<T>(std::forward<Args>(args)...);
}

template<typename T>
using Owned = std::unique_ptr<T>;

template<typename T, typename... Args>
std::unique_ptr<T> CreateOwned(Args&&... args) {
    return std::make_unique<T>(std::forward<Args>(args)...);
}

template<typename T>
using Weak = std::weak_ptr<T>;