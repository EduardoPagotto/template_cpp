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

class BufferWrapper {
  public:
    BufferWrapper(size_t max, size_t increment = 256) : max(max), increment(increment), last(0) { buffer = malloc(max); }
    virtual ~BufferWrapper() { free(buffer); }

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

int main(int argn, char** argv) {

    struct Teste3D {
        float x, y, z;
    };

    BufferWrapper b{2, 0};

    int itens[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 0, 11, 12};

    // int itens[] = {999, 998, 0};

    double val1 = 10.0;

    b.add("val1", 12345, UV_UINT);
    b.add("val2", 1230, UV_INT);
    b.add("val3", 30.0f, UV_FLOAT);
    b.add("val4", 20.0, UV_DOUBLE);
    b.addPtr("val5", &val1, UV_DOUBLE);
    // b.add("val6", Teste3D{1.0f, 2.0f, 3.0f}, UV_FLOAT);
    // b.add("val7", 32000, UV_INT);
    b.addPtr("lista1", itens, (UV_INT | UV_ARRAY), std::size(itens));

    // teste
    b.deploy([](const char* name, int proper, void* buffer, size_t size) {
        std::cout << " name: " << std::string(name) << " size: " << size;

        switch (proper) {
            case UV_UINT:
                std::cout << " uint: " << *static_cast<uint*>(buffer) << std::endl;
                break;
            case UV_INT:
                std::cout << " int: " << *static_cast<int*>(buffer) << std::endl;
                break;
            case UV_FLOAT:
                std::cout << " float: " << *static_cast<float*>(buffer) << std::endl;
                break;
            case UV_DOUBLE:
                std::cout << " double: " << *static_cast<double*>(buffer) << std::endl;
                break;
            case (UV_UINT | UV_MAT3):
                break;
            case (UV_INT | UV_MAT3):
                break;
            case (UV_FLOAT | UV_MAT3):
                break;
            case (UV_DOUBLE | UV_MAT3):
                break;
            case (UV_UINT | UV_MAT4):
                break;
            case (UV_INT | UV_MAT4):
                break;
            case (UV_FLOAT | UV_MAT4):
                break;
            case (UV_DOUBLE | UV_MAT4):
                break;

            default:
                std::cout << std::endl;
                break;
        }
    });

    std::cout << "Hello stupid world" << std::endl;

    return 0;
}