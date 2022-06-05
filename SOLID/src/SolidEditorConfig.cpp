#include "SolidEditorConfig.hpp"

void SolidEditorConfig::Load(JSON config) {
    mEditorPreferences.generalPreferences.loadPreviousProjectOnStartup = config["generalPreferences"]["loadPreviousProjectOnStartup"];
    mEditorPreferences.generalPreferences.showWelcomeScreenOnStartup = config["generalPreferences"]["showWelcomeScreenOnStartup"];

    mEditorPreferences.externalTools.externalScriptEditor = config["externalTools"]["externalScriptEditor"].get<std::string>().c_str();
    mEditorPreferences.externalTools.externalScriptEditorArgs = config["externalTools"]["externalScriptEditorArgs"].get<std::string>().c_str();
    mEditorPreferences.externalTools.imageEditor = config["externalTools"]["imageEditor"].get<std::string>().c_str();
    mEditorPreferences.externalTools.imageEditorArgs = config["externalTools"]["imageEditorArgs"].get<std::string>().c_str();
}

void SolidEditorConfig::Save() {
    JSON config;

    config["generalPreferences"]["loadPreviousProjectOnStartup"] = mEditorPreferences.generalPreferences.loadPreviousProjectOnStartup;
    config["generalPreferences"]["showWelcomeScreenOnStartup"] = mEditorPreferences.generalPreferences.showWelcomeScreenOnStartup;

    config["externalTools"]["externalScriptEditor"] = mEditorPreferences.externalTools.externalScriptEditor;
    config["externalTools"]["externalScriptEditorArgs"] = mEditorPreferences.externalTools.externalScriptEditorArgs;
    config["externalTools"]["imageEditor"] = mEditorPreferences.externalTools.imageEditor;
    config["externalTools"]["imageEditorArgs"] = mEditorPreferences.externalTools.imageEditorArgs;

    std::ofstream configFile(SolidUtils::GetEditorConfigPath());
    configFile << config;
    configFile.close();
}

void SolidEditorConfig::InitConfig() {
    JSON config;

    config["generalPreferences"]["loadPreviousProjectOnStartup"] = true;
    config["generalPreferences"]["showWelcomeScreenOnStartup"] = true;

    config["externalTools"]["externalScriptEditor"] = "";
    config["externalTools"]["externalScriptEditorArgs"] = "";
    config["externalTools"]["imageEditor"] = "";
    config["externalTools"]["imageEditorArgs"] = "";

    std::ofstream configFile(SolidUtils::GetEditorConfigPath());
    configFile << config.dump(4);
    configFile.close();

    Load(config);
}