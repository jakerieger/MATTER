#include <Windows/Dialogs.hpp>

char* WindowsDialogs::ShowOpenDialog(LPCWSTR title) {
    IFileOpenDialog* pFileOpen;

    COMDLG_FILTERSPEC rgSpec[] = {
        { L"SOLID Project", L"*.solid" },
        { L"Images", L"*.png;*.jpg;*.jpeg;*.bmp;*.tga" },
        { L"Models", L"*.fbx;*.obj;*.dae" },
        { L"All Files", L"*.*" }
    };

    HRESULT hr = CoCreateInstance(
        CLSID_FileOpenDialog,
        NULL,
        CLSCTX_ALL,
        IID_IFileOpenDialog,
        reinterpret_cast<void**>(&pFileOpen)
    );

    if (SUCCEEDED(hr)) {
        hr = pFileOpen->SetFileTypes(ARRAYSIZE(rgSpec), rgSpec);
        hr = pFileOpen->SetTitle(title);
        hr = pFileOpen->Show(NULL);

        if (SUCCEEDED(hr)) {
            IShellItem* pItem;
            hr = pFileOpen->GetResult(&pItem);

            if (SUCCEEDED(hr)) {
                PWSTR pszFilePath;
                hr = pItem->GetDisplayName(SIGDN_FILESYSPATH, &pszFilePath);

                if (SUCCEEDED(hr)) {
                    wchar_t* wszFilePath = pszFilePath;
                    char* szFilePath = new char[wcslen(wszFilePath) + 1];
                    wcstombs(szFilePath, wszFilePath, wcslen(wszFilePath) +1);
                    return szFilePath;
                }
            }
        }
    }

    return nullptr;
}

char* WindowsDialogs::ShowSaveDialog(LPCWSTR title, LPCWSTR defaultExtension, FileType fileType) {
    IFileSaveDialog* pFileSave;

    HRESULT hr = CoCreateInstance(
        CLSID_FileSaveDialog,
        NULL,
        CLSCTX_ALL,
        IID_IFileSaveDialog,
        reinterpret_cast<void**>(&pFileSave)
    );

    unsigned int filterId = 0;

    switch (fileType) {
        case FileType_Project:
            filterId = 0;
            break;
        case FileType_Scene:
            filterId = 1;
            break;
        case FileType_Any:
            filterId = 4;
            break;
        default:
            break;
    }

    COMDLG_FILTERSPEC rgSpec[] = {
        { L"SOLID Project", L"*.solid" },
        { L"Scene", L"*.scene" },
        { L"Images", L"*.png;*.jpg;*.jpeg;*.bmp;*.tga" },
        { L"Models", L"*.fbx;*.obj;*.dae" },
        { L"All Files", L"*.*" }
    };

    if (SUCCEEDED(hr)) {
        hr = pFileSave->SetTitle(title);
        hr = pFileSave->SetDefaultExtension(defaultExtension);
        hr = pFileSave->SetFileTypes(1, &rgSpec[filterId]);
        // hr = pFileSave->SetDefaultSaveFolder(initialDirectory);
        hr = pFileSave->Show(NULL);

        if (SUCCEEDED(hr)) {
            IShellItem* pItem;
            hr = pFileSave->GetResult(&pItem);

            if (SUCCEEDED(hr)) {
                PWSTR pszFilePath;
                hr = pItem->GetDisplayName(SIGDN_FILESYSPATH, &pszFilePath);

                if (SUCCEEDED(hr)) {
                    wchar_t* wszFilePath = pszFilePath;
                    char* szFilePath = new char[wcslen(wszFilePath) + 1];
                    wcstombs(szFilePath, wszFilePath, wcslen(wszFilePath) +1);
                    return szFilePath;
                }
            }
        }
    }

    return nullptr;
}