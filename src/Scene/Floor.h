#pragma once

#include <memory>
#include <string>
#include <vector>

#include "SceneObject.h"
#include "Room.h"

namespace VisionBIM::Scene
{

class Floor : public SceneObject
{
public:

    Floor();

    //========================
    // Level
    //========================

    [[nodiscard]]
    int GetLevel() const noexcept;

    void SetLevel(int level);

    [[nodiscard]]
    double GetElevation() const noexcept;

    void SetElevation(double elevation);

    [[nodiscard]]
    double GetHeight() const noexcept;

    void SetHeight(double height);

    //========================
    // Rooms
    //========================

    void AddRoom(const std::shared_ptr<Room>& room);

    void RemoveRoom(const std::shared_ptr<Room>& room);

    void ClearRooms();

    [[nodiscard]]
    const std::vector<std::weak_ptr<Room>>& GetRooms() const noexcept;

    //========================
    // Calculated values
    //========================

    [[nodiscard]]
    double GetArea() const;

private:

    int m_level;

    double m_elevation;

    double m_height;

    std::vector<std::weak_ptr<Room>> m_rooms;
};

}