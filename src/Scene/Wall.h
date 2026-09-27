#pragma once

#include <memory>
#include <vector>

#include "../Geometry/Vector2.h"

#include "SceneObject.h"
#include "Material.h"

namespace VisionBIM::Scene
{

class Door;
class Window;

class Wall : public SceneObject
{
public:

    Wall();

    Wall(
        const Geometry::Vector2& start,
        const Geometry::Vector2& end);

    //========================
    // Geometry
    //========================

    [[nodiscard]]
    const Geometry::Vector2& GetStart() const noexcept;

    [[nodiscard]]
    const Geometry::Vector2& GetEnd() const noexcept;

    void SetStart(const Geometry::Vector2& start);

    void SetEnd(const Geometry::Vector2& end);

    //========================
    // Dimensions
    //========================

    [[nodiscard]]
    double GetThickness() const noexcept;

    void SetThickness(double thickness);

    [[nodiscard]]
    double GetHeight() const noexcept;

    void SetHeight(double height);

    [[nodiscard]]
    double GetLength() const noexcept;

    //========================
    // Material
    //========================

    [[nodiscard]]
    std::shared_ptr<Material> GetMaterial() const noexcept;

    void SetMaterial(std::shared_ptr<Material> material);

    //========================
    // Type
    //========================

    [[nodiscard]]
    bool IsLoadBearing() const noexcept;

    void SetLoadBearing(bool value);

    [[nodiscard]]
    bool IsExternal() const noexcept;

    void SetExternal(bool value);

    //========================
    // Openings
    //========================

    void AddDoor(std::shared_ptr<Door> door);

    void AddWindow(std::shared_ptr<Window> window);

    [[nodiscard]]
    const std::vector<std::shared_ptr<Door>>& GetDoors() const noexcept;

    [[nodiscard]]
    const std::vector<std::shared_ptr<Window>>& GetWindows() const noexcept;

private:

    Geometry::Vector2 m_start;
    Geometry::Vector2 m_end;

    double m_thickness;
    double m_height;

    bool m_loadBearing;
    bool m_external;

    std::shared_ptr<Material> m_material;

    std::vector<std::shared_ptr<Door>> m_doors;
    std::vector<std::shared_ptr<Window>> m_windows;
};

}