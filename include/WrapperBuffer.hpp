#pragma once
#include <functional>
#include <iostream>
#include <string.h>
#include <unordered_map>

#define UV_UINT 0b000'0000'0000
#define UV_INT 0b000'0000'0001
#define UV_FLOAT 0b000'0000'0010
#define UV_DOUBLE 0b000'0000'0011
#define UV_MAT3 0b000'0001'0000
#define UV_MAT4 0b000'0010'0000
#define UV_TRANSPOSE 0b000'1000'0000
#define UV_ARRAY 0b001'0000'0000

using BufferCallback = std::function<void(const char*, int, void*, size_t)>;

struct BufferItens {
    int propert;
    void* payload;
    size_t size{0};
};

class WrapperBuffer {
  public:
    WrapperBuffer(size_t max, size_t increment = 256) : max(max), last(0), increment(increment) { buffer = malloc(max); }
    virtual ~WrapperBuffer() { free(buffer); }

    void clear() {
        mapItens.clear();
        last = 0;
    }

    template <typename T>
    void addPtr(const std::string& name, const T* val, int proper, const size_t& tot = 1) {
        size_t size = sizeof(*val) * tot;

        if (tot > 1)
            proper |= UV_ARRAY;

        if (!sameKeyVal(name, size, val)) {
            size_t nova = last + size;
            if (nova >= max)
                rebuild(nova);

            void* payload = (void*)((char*)buffer + last);
            mapItens[name] = {proper, payload, size};
            memcpy(payload, val, size);
            last = nova;
        }
    }

    template <typename T>
    void add(const std::string& name, const T& val, int proper) {
        size_t size = sizeof(val);
        if (!sameKeyVal(name, size, &val)) {
            size_t nova = last + size;
            if (nova >= max)
                rebuild(nova);

            void* payload = (void*)((char*)buffer + last);
            mapItens[name] = {proper, payload, size};
            memcpy(payload, &val, size);
            last = nova;
        }
    }

    void deploy(BufferCallback cb) {
        for (const auto& val : mapItens) {
            const auto& item = val.second;
            cb(val.first.c_str(), item.propert, item.payload, item.size);
        }
    }

  private:
    template <typename T>
    bool sameKeyVal(const std::string& name, const size_t& size, T* val) {

        if (mapItens.count(name) == 1) {
            const auto& item = mapItens.at(name);
            if (size == item.size) {
                memcpy(item.payload, val, size);
                return true;
            }
        }

        return false;
    }

    void rebuild(const size_t& nova) {
        max += ((nova - max) + increment);
        std::cout << "Buffer increment to " << max << std::endl;
        void* bufferNew = malloc(max);

        memcpy(bufferNew, buffer, last);

        // realocar valores antigos
        size_t last_old{0};
        for (auto& item : mapItens) {
            auto& val = item.second;
            val.payload = (void*)((char*)bufferNew + last_old);
            last_old = val.size;
        }

        free(buffer);
        buffer = bufferNew;
    }

    void* buffer{nullptr};
    size_t max{0};
    size_t last{0};
    size_t increment{256};
    std::unordered_map<std::string, BufferItens> mapItens;
};