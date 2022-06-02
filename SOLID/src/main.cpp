#include <stdio.h>

#include "SolidEditorConfig.hpp"
#include "SolidEditor.hpp"

int main(int argc, char *argv[]) {
    // Get last opened project

    if (argv[1] != nullptr) {
        // Project path provided, load project
    }

    SolidEditor editor;
    editor.Run();

    return 0;
}