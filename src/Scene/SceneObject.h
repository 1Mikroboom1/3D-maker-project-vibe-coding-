#pragma once

#include <string>

#include "../Geometry/Transform.h"

namespace VisionBIM::Scene
{

class SceneObject
{
public:

    SceneObject();

    virtual ~SceneObject() = default;

    //========================
    // ID
    //========================

    [[nodiscard]]
    int GetId() const noexcept;

    //========================
    // Name
    //========================

    [[nodiscard]]
    const std::string& GetName() const noexcept;

    void SetName(const std::string& name);

    //========================
    // Transform
    //========================

    [[nodiscard]]
    Geometry::Transform& GetTransform() noexcept;

    [[nodiscard]]
    const Geometry::Transform& GetTransform() const noexcept;

    //========================
    // Visibility
    //========================

    [[nodiscard]]
    bool IsVisible() const noexcept;

    void SetVisible(bool visible);

    //========================
    // Selection
    //========================

    [[nodiscard]]
    bool IsSelected() const noexcept;

    void SetSelected(bool selected);

    //========================
    // Enabled
    //========================

    [[nodiscard]]
    bool IsEnabled() const noexcept;

    void SetEnabled(bool enabled);

protected:

    int id;

    std::string name;

    Geometry::Transform transform;

    bool visible;

    bool selected;

    bool enabled;

private:

    static int nextId;
};

}