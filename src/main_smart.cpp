#include <functional>
#include <iostream>
#include <memory>
#include <string.h>
#include <vector>

enum class UniformType {
    INVALID = 0,
    INT,
    UINT,
    INTP,
    IVEC2,
    IVEC3,
    IVEC4,
    FLOAT,
    DOUBLE,
    VEC2,
    VEC3,
    VEC4,
    MAT3,
    MAT4,
};

using UniformCallBack = std::function<void(const char*, UniformType, void*, size_t)>;

struct UniformItens {

    UniformItens(const std::string& name, const UniformType& type, void* payload, const size_t& size, const size_t& itens)
        : name(name), type(type), payload(payload), size(size), itens(itens){};

    UniformItens(const UniformItens& o) : name(o.name), type(o.type), payload(o.payload), size(o.size), itens(o.itens) {}

    virtual ~UniformItens() {}

    std::string name;
    UniformType type{UniformType::INVALID};
    void* payload{nullptr};
    size_t size{0};
    size_t itens{0};
};

class UniformBuffer {
  public:
    UniformBuffer(const UniformBuffer& o) : last(o.last), max(o.max), increment(o.increment) {
        // buffer = malloc(o.last);
        // memcpy(buffer, o.buffer, o.last);
        vItens.assign(o.vItens.begin(), o.vItens.end());
        // pipe.assign(o.pipe.begin(), o.pipe.end());
    }

    UniformBuffer(size_t max, size_t increment = 256) : max(max), increment(increment), last(0) { buffer = malloc(max); }
    virtual ~UniformBuffer() {
        vItens.clear();
        free(buffer);
    }

    void clear() {
        vItens.clear();
        last = 0;
    }

    template <typename T>
    void set(const std::string& name, const T& val, const UniformType& type) {
        const size_t size = sizeof(val);
        const size_t nova = last + size;
        if (nova >= max)
            rebuild(nova);

        void* payload = (void*)((char*)buffer + last);

        vItens.push_back(std::shared_ptr<UniformItens>(new UniformItens(name, type, payload, size, 1)));
        memcpy(payload, &val, size);
        last = nova;
    }

    template <typename T>
    void setPtr(const std::string& name, const T* val, const UniformType& type, const size_t& itens = 1) {
        const size_t size = sizeof(*val) * itens;
        const size_t nova = last + size;
        if (nova >= max)
            rebuild(nova);

        void* payload = (void*)((char*)buffer + last);

        vItens.push_back(std::shared_ptr<UniformItens>(new UniformItens(name, type, payload, size, itens)));

        memcpy(payload, val, size);
        last = nova;
    }

    void deploy(UniformCallBack cb) {
        for (const auto& val : vItens) {
            cb(val->name.c_str(), val->type, val->payload, val->size);
        }
    }

  private:
    void rebuild(const size_t& nova) {
        max += ((nova - max) + increment);
        std::cout << "Buffer increment to " << max << std::endl;
        void* bufferNew = malloc(max);

        // realocar valores antigos
        size_t last_old{0};
        for (auto& val : vItens) {
            val->payload = (void*)((char*)bufferNew + last_old);
            last_old += val->size;
        }

        memcpy(bufferNew, buffer, last);

        free(buffer);
        buffer = bufferNew;
    }

    void* buffer{nullptr};
    size_t max{0};
    size_t last{0};
    size_t increment{256};
    std::vector<std::shared_ptr<UniformItens>> vItens;
};

int main(int argn, char** argv) {

    struct Teste3D {
        float x, y, z;
    };

    UniformBuffer b{2, 0};

    uint32_t itens[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 0, 11, 12};

    double val1 = 10.0;

    b.set("val1", -12345, UniformType::INT);
    b.set("val2", 1230, UniformType::UINT);
    b.set("val3", -1, UniformType::INT);
    b.set("val4", 2, UniformType::INT);
    b.set("val5", 30.0f, UniformType::FLOAT);
    b.set("val6", -20.0f, UniformType::FLOAT);
    b.set("val7", -5, UniformType::INT);
    b.set("val8", -200.01f, UniformType::FLOAT);
    //  b.addPtr("val5", &val1, UV_DOUBLE);
    //   b.set("val6", Teste3D{1.0f, 2.0f, 3.0f}, UV_FLOAT);
    //   b.set("val7", 32000, UV_INT);
    b.setPtr("lista1", itens, UniformType::INT, std::size(itens));
    b.set("val9", 3.1415169264, UniformType::DOUBLE);

    // teste
    b.deploy([](const char* name, UniformType type, void* buffer, size_t size) {
        std::cout << " name: " << std::string(name) << " size: " << size;

        switch (type) {
            case UniformType::UINT:
                std::cout << " uint: " << *static_cast<uint*>(buffer) << std::endl;
                break;
            case UniformType::INT:
                std::cout << " int: " << *static_cast<int*>(buffer) << std::endl;
                break;
            case UniformType::FLOAT:
                std::cout << " float: " << *static_cast<float*>(buffer) << std::endl;
                break;
            case UniformType::DOUBLE:
                std::cout << " double: " << *static_cast<double*>(buffer) << std::endl;
                break;
                // case (UV_UINT | UV_MAT3):
                //     break;
                // case (UV_INT | UV_MAT3):
                //     break;
                // case (UV_FLOAT | UV_MAT3):
                //     break;
                // case (UV_DOUBLE | UV_MAT3):
                //     break;
                // case (UV_UINT | UV_MAT4):
                //     break;
                // case (UV_INT | UV_MAT4):
                //     break;
                // case (UV_FLOAT | UV_MAT4):
                //     break;
                // case (UV_DOUBLE | UV_MAT4):
                //     break;

            default:
                std::cout << std::endl;
                break;
        }
    });

    std::cout << "Hello stupid world" << std::endl;

    return 0;
}