#include "UniformBuffer.hpp"
#include "WrapperBuffer.hpp"
#include <config_params.hpp>
#include <iostream>

// struct Teste3D {
//     float x, y, z;
// };

void testeSmart() {

    UniformBuffer b{2, 0};

    uint32_t itens[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 0, 11, 12};

    // double val1 = 10.0;

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
}

void testeWrapperBuffer() {

    WrapperBuffer b{2, 0};

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
}

int main(int argn, char** argv) {

    std::cout << "Hello stupid world" << std::endl;
    std::cout << project_name << '\n';
    std::cout << project_version << '\n';

    // testeSmart();
    // testeWrapperBuffer();

    return 0;
}