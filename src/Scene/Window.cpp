#include "Window.h"

namespace VisionBIM::Scene
{

Window::Window()
    :
    m_offset(0.0),
    m_width(1.2),
    m_height(1.5),
    m_sillHeight(0.9)
{
    SetName("Window");
}

std::weak_ptr<Wall> Window::GetWall() const noexcept
{
    return m_wall;
}

void Window::SetWall(const std::shared_ptr<Wall>& wall)
{
    m_wall = wall;
}

double Window::GetOffset() const noexcept
{
    return m_offset;
}

void Window::SetOffset(double offset)
{
    m_offset = offset;
}

double Window::GetWidth() const noexcept
{
    return m_width;
}

void Window::SetWidth(double width)
{
    m_width = width;
}

double Window::GetHeight() const noexcept
{
    return m_height;
}

void Window::SetHeight(double height)
{
    m_height = height;
}

double Window::GetSillHeight() const noexcept
{
    return m_sillHeight;
}

void Window::SetSillHeight(double height)
{
    m_sillHeight = height;
}

}