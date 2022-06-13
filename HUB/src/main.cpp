#include <filesystem>
#include "Hub.hpp"

int main(void) {
    auto appdata = std::filesystem::temp_directory_path().parent_path().parent_path() / "MatterHub";
    if (!std::filesystem::exists(appdata)) {
        std::filesystem::create_directory(appdata);
    }

    Hub::GetInstance()->Run();
    return 0;
}