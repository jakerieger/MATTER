#include <filesystem>
#include "Hub.hpp"

int main(void) {
    Hub::GetInstance()->Run();
    return 0;
}