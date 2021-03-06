!include "MUI2.nsh"

Name "MATTER 2022"
OutFile "MATTER_2022.6.15a_x64_en-US.exe"
Unicode True

InstallDir "$PROGRAMFILES64\MATTER"

!define MUI_ABORTWARNING
!define MUI_ICON "icon.ico"
!define MUI_HEADERIMAGE
!define MUI_HEADERIMAGE_BITMAP "header.bmp"
!define MUI_WELCOMEFINISHPAGE_BITMAP "side.bmp"

!insertmacro MUI_PAGE_WELCOME
!insertmacro MUI_PAGE_LICENSE "../LICENSE"
!insertmacro MUI_PAGE_DIRECTORY
!insertmacro MUI_PAGE_INSTFILES
!insertmacro MUI_UNPAGE_CONFIRM
!insertmacro MUI_UNPAGE_INSTFILES

!insertmacro MUI_LANGUAGE "English"

Section

    CreateDirectory "$INSTDIR\2022"
    SetOutPath "$INSTDIR\2022"

    File "..\LICENSE"
    File /nonfatal /a /r "..\build\SOLID\Debug\"
    File "..\build\HUB\matter-hub\dist\MatterHub.exe"

    CreateShortCut "$DESKTOP\SOLID.lnk" "$INSTDIR\2022\SOLID.exe"
    CreateShortCut "$DESKTOP\Matter Hub.lnk" "$INSTDIR\2022\MatterHub.exe"

    WriteUninstaller $INSTDIR\Uninstall.exe

SectionEnd

Section "Uninstall"

    Delete "$DESKTOP\SOLID.lnk"
    RMDir /r "$INSTDIR\2022"
    Delete $INSTDIR\Uninstall.exe
    RMDir $INSTDIR

SectionEnd