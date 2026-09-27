#include "Door.h"

namespace VisionBIM::Scene
{

Door::Door()
    :
    m_offset(0.0),
    m_width(0.9),
    m_height(2.1),
    m_opensInside(true)
{
    SetName("Door");
}

std::shared_ptr<Wall> Door::GetWall() const noexcept
{
    return m_wall;
}

void Door::SetWall(std::shared_ptr<Wall> wall)
{
    m_wall = std::move(wall);
}

double Door::GetOffset() const noexcept
{
    return m_offset;
}

void Door::SetOffset(double offset)
{
    m_offset = offset;
}

double Door::GetWidth() const noexcept
{
    return m_width;
}

void Door::SetWidth(double width)
{
    m_width = width;
}

double Door::GetHeight() const noexcept
{
    return m_height;
}

void Door::SetHeight(double height)
{
    m_height = height;
}

bool Door::OpensInside() const noexcept
{
    return m_opensInside;
}

void Door::SetOpensInside(bool value)
{
    m_opensInside = value;
}

}