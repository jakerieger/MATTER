!include "MUI2.nsh"

Name "MATTER 2022"
OutFile "MATTER2022-setup.exe"
Unicode True

InstallDir "$PROGRAMFILES64\MATTER"

!define MUI_ABORTWARNING
!define MUI_ICON "icon.ico"

!insertmacro MUI_PAGE_WELCOME
!insertmacro MUI_PAGE_LICENSE "../LICENSE"
!insertmacro MUI_PAGE_COMPONENTS
!insertmacro MUI_PAGE_DIRECTORY
!insertmacro MUI_PAGE_INSTFILES
!insertmacro MUI_UNPAGE_CONFIRM
!insertmacro MUI_UNPAGE_INSTFILES

!insertmacro MUI_LANGUAGE "English"

Section

    CreateDirectory "$INSTDIR\2022"
    SetOutPath $INSTDIR
    WriteUninstaller $INSTDIR\Uninstall.exe

SectionEnd

Section "Uninstall"

    RMDir "$INSTDIR\2022"
    Delete $INSTDIR\Uninstall.exe
    RMDir $INSTDIR

SectionEnd