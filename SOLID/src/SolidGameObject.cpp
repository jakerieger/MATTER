#include "SolidGameObject.hpp"

SolidGameObject::SolidGameObject(const char* name, SolidGameObjectType type) {
    mName = std::move(name);
    mType = std::move(type);
    mTransform = SolidTransform();
    Awake();
}

void SolidGameObject::Awake() {
    for (auto& component : mComponents) {
        component->Awake();
    }

    for (auto& child : mChildren) {
        child->Awake();
    }
}

void SolidGameObject::Start() {
    for (auto& component : mComponents) {
        component->Start();
    }

    for (auto& child : mChildren) {
        child->Start();
    }
}

void SolidGameObject::Update() {
    for (auto& component : mComponents) {
        component->Update();
    }

    for (auto& child : mChildren) {
        child->Update();
    }
}

void SolidGameObject::LateUpdate() {
    for (auto& component : mComponents) {
        component->LateUpdate();
    }

    for (auto& child : mChildren) {
        child->LateUpdate();
    }
}

void SolidGameObject::FixedUpdate() {
    for (auto& component : mComponents) {
        component->FixedUpdate();
    }

    for (auto& child : mChildren) {
        child->FixedUpdate();
    }
}

void SolidGameObject::Destroyed() {
    for (auto& component : mComponents) {
        component->Destroyed();
    }

    for (auto& child : mChildren) {
        child->Destroyed();
    }
}
