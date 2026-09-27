#include "Wall.h"

namespace VisionBIM::Scene
{

Wall::Wall()
    :
    m_thickness(0.2),
    m_height(3.0),
    m_loadBearing(false),
    m_external(false)
{
    SetName("Wall");
}

Wall::Wall(
    const Geometry::Vector2& start,
    const Geometry::Vector2& end)
    :
    m_start(start),
    m_end(end),
    m_thickness(0.2),
    m_height(3.0),
    m_loadBearing(false),
    m_external(false)
{
    SetName("Wall");
}

const Geometry::Vector2& Wall::GetStart() const noexcept
{
    return m_start;
}

const Geometry::Vector2& Wall::GetEnd() const noexcept
{
    return m_end;
}

void Wall::SetStart(const Geometry::Vector2& start)
{
    m_start = start;
}

void Wall::SetEnd(const Geometry::Vector2& end)
{
    m_end = end;
}

double Wall::GetThickness() const noexcept
{
    return m_thickness;
}

void Wall::SetThickness(double thickness)
{
    m_thickness = thickness;
}

double Wall::GetHeight() const noexcept
{
    return m_height;
}

void Wall::SetHeight(double height)
{
    m_height = height;
}

double Wall::GetLength() const noexcept
{
    return (m_end - m_start).Length();
}

std::shared_ptr<Material> Wall::GetMaterial() const noexcept
{
    return m_material;
}

void Wall::SetMaterial(std::shared_ptr<Material> material)
{
    m_material = std::move(material);
}

bool Wall::IsLoadBearing() const noexcept
{
    return m_loadBearing;
}

void Wall::SetLoadBearing(bool value)
{
    m_loadBearing = value;
}

bool Wall::IsExternal() const noexcept
{
    return m_external;
}

void Wall::SetExternal(bool value)
{
    m_external = value;
}

void Wall::AddDoor(std::shared_ptr<Door> door)
{
    m_doors.push_back(std::move(door));
}

void Wall::AddWindow(std::shared_ptr<Window> window)
{
    m_windows.push_back(std::move(window));
}

const std::vector<std::shared_ptr<Door>>& Wall::GetDoors() const noexcept
{
    return m_doors;
}

const std::vector<std::shared_ptr<Window>>& Wall::GetWindows() const noexcept
{
    return m_windows;
}

}