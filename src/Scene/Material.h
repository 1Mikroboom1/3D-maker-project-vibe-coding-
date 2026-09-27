#pragma once

#include <string>

namespace VisionBIM::Scene
{

class Material
{
public:

    Material();
    Material(const std::string& name);

    [[nodiscard]]
    const std::string& GetName() const noexcept;

    void SetName(const std::string& name);

    [[nodiscard]]
    double GetDensity() const noexcept;

    void SetDensity(double density);

private:

    std::string m_name;

    double m_density;
};

}