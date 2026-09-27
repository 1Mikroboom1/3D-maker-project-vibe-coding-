#include "Room.h"

#include <algorithm>

namespace VisionBIM::Scene
{

Room::Room()
    :
    m_height(3.0)
{
    SetName("Room");
}

void Room::AddWall(const std::shared_ptr<Wall>& wall)
{
    m_walls.emplace_back(wall);
}

void Room::RemoveWall(const std::shared_ptr<Wall>& wall)
{
    m_walls.erase(
        std::remove_if(
            m_walls.begin(),
            m_walls.end(),
            [&](const std::weak_ptr<Wall>& weakWall)
            {
                auto locked = weakWall.lock();
                return locked && locked == wall;
            }),
        m_walls.end());
}

void Room::ClearWalls()
{
    m_walls.clear();
}

const std::vector<std::weak_ptr<Wall>>&
Room::GetWalls() const noexcept
{
    return m_walls;
}

double Room::GetHeight() const noexcept
{
    return m_height;
}

void Room::SetHeight(double height)
{
    m_height = height;
}

const Geometry::Polygon&
Room::GetBoundary() const noexcept
{
    return m_boundary;
}

void Room::SetBoundary(const Geometry::Polygon& polygon)
{
    m_boundary = polygon;
}

std::shared_ptr<Material>
Room::GetFloorMaterial() const noexcept
{
    return m_floorMaterial;
}

void Room::SetFloorMaterial(const std::shared_ptr<Material>& material)
{
    m_floorMaterial = material;
}

std::shared_ptr<Material>
Room::GetCeilingMaterial() const noexcept
{
    return m_ceilingMaterial;
}

void Room::SetCeilingMaterial(const std::shared_ptr<Material>& material)
{
    m_ceilingMaterial = material;
}

double Room::GetArea() const
{
    return m_boundary.Area();
}

double Room::GetPerimeter() const
{
    return m_boundary.Perimeter();
}

double Room::GetVolume() const
{
    return GetArea() * m_height;
}

}