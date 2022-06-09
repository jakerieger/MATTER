#pragma once

#include "SolidGameObject.hpp"
#include "SolidColor.hpp"

class SolidLight : public SolidGameObject {
public:
    SolidLight(const char* name) : SolidGameObject(name, GO_Light) {
        SetColor(SolidColor(1.0f));
        SetCastShadows(true);
        SetIntensity(1.0f);
    }

    void SetColor(const SolidColor& color) { mColor = std::move(color); }
    SolidColor GetColor() const { return mColor; }

    void SetIntensity(float intensity) { mIntensity = std::move(intensity); }
    float GetIntensity() const { return mIntensity; }

    void SetCastShadows(bool castShadows) { mCastShadows = std::move(castShadows); }
    bool GetCastShadows() const { return mCastShadows; }

private:
    SolidColor mColor;
    float mIntensity;
    bool mCastShadows;
};

class SolidDirectionalLight : public SolidLight {
public:
    SolidDirectionalLight(const char* name) : SolidLight(name) {}
};

class SolidPointLight : public SolidLight {

};

class SolidSpotLight : public SolidLight {
public:
    SolidSpotLight(const char* name) : SolidLight(name) {
        SetRange(10);
        SetAngle(30.f);
    }

    void SetRange(int range) { mRange = std::move(range); }
    int GetRange() const { return mRange; }

    void SetAngle(float angle) { mAngle = std::move(angle); }
    float GetAngle() const { return mAngle; }

private:
    int mRange;
    float mAngle;
};

class SolidAreaLight : public SolidLight {

};