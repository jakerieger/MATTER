/** Copyright 2022 Jake Rieger
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

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