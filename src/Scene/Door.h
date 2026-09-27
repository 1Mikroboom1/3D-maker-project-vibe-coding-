#pragma once

#include <memory>

#include "../Geometry/Vector2.h"

#include "SceneObject.h"

namespace VisionBIM::Scene
{

class Wall;

class Door : public SceneObject
{
public:

    Door();

    //========================
    // Wall
    //========================

    [[nodiscard]]
    std::shared_ptr<Wall> GetWall() const noexcept;

    void SetWall(std::shared_ptr<Wall> wall);

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
    // Opening direction
    //========================

    [[nodiscard]]
    bool OpensInside() const noexcept;

    void SetOpensInside(bool value);

private:

    std::shared_ptr<Wall> m_wall;

    double m_offset;

    double m_width;

    double m_height;

    bool m_opensInside;
};

}