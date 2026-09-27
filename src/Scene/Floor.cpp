#include "Floor.h"

#include <algorithm>

namespace VisionBIM::Scene
{

Floor::Floor()
    :
    m_level(0),
    m_elevation(0.0),
    m_height(3.0)
{
    SetName("Floor");
}

int Floor::GetLevel() const noexcept
{
    return m_level;
}

void Floor::SetLevel(int level)
{
    m_level = level;
}

double Floor::GetElevation() const noexcept
{
    return m_elevation;
}

void Floor::SetElevation(double elevation)
{
    m_elevation = elevation;
}

double Floor::GetHeight() const noexcept
{
    return m_height;
}

void Floor::SetHeight(double height)
{
    m_height = height;
}

void Floor::AddRoom(const std::shared_ptr<Room>& room)
{
    m_rooms.emplace_back(room);
}

void Floor::RemoveRoom(const std::shared_ptr<Room>& room)
{
    m_rooms.erase(
        std::remove_if(
            m_rooms.begin(),
            m_rooms.end(),
            [&](const std::weak_ptr<Room>& weakRoom)
            {
                auto locked = weakRoom.lock();
                return locked && locked == room;
            }),
        m_rooms.end());
}

void Floor::ClearRooms()
{
    m_rooms.clear();
}

const std::vector<std::weak_ptr<Room>>&
Floor::GetRooms() const noexcept
{
    return m_rooms;
}

double Floor::GetArea() const
{
    double area = 0.0;

    for (const auto& weakRoom : m_rooms)
    {
        if (auto room = weakRoom.lock())
        {
            area += room->GetArea();
        }
    }

    return area;
}

}