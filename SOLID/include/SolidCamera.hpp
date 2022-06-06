#pragma once

#include <imgui/imgui.h>

#include "SolidComponent.hpp"

enum ProjectionType {
    Perspective,
    Orthographic
};

class SolidCamera : public SolidComponent {
public:
    ImVec4 mClearColor;
    ProjectionType mProjectionType;
    float mFieldOfView;
    float mNearClip;
    float mFarClip;
    float mOrthographicSize;

private:

};