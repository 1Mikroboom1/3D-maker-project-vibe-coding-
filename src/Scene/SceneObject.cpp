#include "SceneObject.h"

namespace VisionBIM::Scene
{

int SceneObject::nextId = 1;

SceneObject::SceneObject()
    :
    id(nextId++),
    name("SceneObject"),
    visible(true),
    selected(false),
    enabled(true)
{
}

int SceneObject::GetId() const noexcept
{
    return id;
}

const std::string& SceneObject::GetName() const noexcept
{
    return name;
}

void SceneObject::SetName(const std::string& newName)
{
    name = newName;
}

Geometry::Transform& SceneObject::GetTransform() noexcept
{
    return transform;
}

const Geometry::Transform&
SceneObject::GetTransform() const noexcept
{
    return transform;
}

bool SceneObject::IsVisible() const noexcept
{
    return visible;
}

void SceneObject::SetVisible(bool value)
{
    visible = value;
}

bool SceneObject::IsSelected() const noexcept
{
    return selected;
}

void SceneObject::SetSelected(bool value)
{
    selected = value;
}

bool SceneObject::IsEnabled() const noexcept
{
    return enabled;
}

void SceneObject::SetEnabled(bool value)
{
    enabled = value;
}

}