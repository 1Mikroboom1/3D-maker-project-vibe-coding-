#pragma once

#include <memory>

#include "SceneObject.h"

namespace VisionBIM::Scene
{

class Wall;

class Window : public SceneObject
{
public:

    Window();

    //========================
    // Wall
    //========================

    [[nodiscard]]
    std::weak_ptr<Wall> GetWall() const noexcept;

    void SetWall(const std::shared_ptr<Wall>& wall);

    //========================
    // Position
    //========================

    [[nodiscard]]
    double GetOffset() const noexcept;

    void SetOffset(double offset);

    //========================
    // Dimensions
    //========================

    [[nodiscard]]
    double GetWidth() const noexcept;

    void SetWidth(double width);

    [[nodiscard]]
    double GetHeight() const noexcept;

    void SetHeight(double height);

    //========================
    // Sill
    //========================

    [[nodiscard]]
    double GetSillHeight() const noexcept;

    void SetSillHeight(double height);

private:

    std::weak_ptr<Wall> m_wall;

    double m_offset;

    double m_width;

    double m_height;

    double m_sillHeight;
};

}