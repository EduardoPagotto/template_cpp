#include <config_params.hpp>
#include <iostream>

int main(int argn, char** argv) {

    std::cout << "Hello stupid world" << std::endl;

    // Create in dynamic build
    std::cout << project_name << '\n';
    std::cout << project_version << '\n';

    return 0;
}