#include <WIN32/Dialogs.hpp>

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