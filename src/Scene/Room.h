#pragma once

#include <memory>
#include <string>
#include <vector>

#include "../Geometry/Polygon.h"

#include "Material.h"
#include "SceneObject.h"
#include "Wall.h"

namespace VisionBIM::Scene
{

class Room : public SceneObject
{
public:

    Room();

    //========================
    // Walls
    //========================

    void AddWall(const std::shared_ptr<Wall>& wall);

    void RemoveWall(const std::shared_ptr<Wall>& wall);

    void ClearWalls();

    [[nodiscard]]
    const std::vector<std::weak_ptr<Wall>>& GetWalls() const noexcept;

    //========================
    // Geometry
    //========================

    [[nodiscard]]
    double GetHeight() const noexcept;

    void SetHeight(double height);

    [[nodiscard]]
    const Geometry::Polygon& GetBoundary() const noexcept;

    void SetBoundary(const Geometry::Polygon& polygon);

    //========================
    // Material
    //========================

    [[nodiscard]]
    std::shared_ptr<Material> GetFloorMaterial() const noexcept;

    void SetFloorMaterial(const std::shared_ptr<Material>& material);

    [[nodiscard]]
    std::shared_ptr<Material> GetCeilingMaterial() const noexcept;

    void SetCeilingMaterial(const std::shared_ptr<Material>& material);

    //========================
    // Calculated values
    //========================

    [[nodiscard]]
    double GetArea() const;

    [[nodiscard]]
    double GetPerimeter() const;

    [[nodiscard]]
    double GetVolume() const;

private:

    std::vector<std::weak_ptr<Wall>> m_walls;

    Geometry::Polygon m_boundary;

    double m_height;

    std::shared_ptr<Material> m_floorMaterial;

    std::shared_ptr<Material> m_ceilingMaterial;
};

}