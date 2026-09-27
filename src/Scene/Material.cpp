#include "Material.h"

namespace VisionBIM::Scene
{

Material::Material()
    :
    m_name("Default"),
    m_density(0.0)
{
}

Material::Material(const std::string& name)
    :
    m_name(name),
    m_density(0.0)
{
}

const std::string& Material::GetName() const noexcept
{
    return m_name;
}

void Material::SetName(const std::string& name)
{
    m_name = name;
}

double Material::GetDensity() const noexcept
{
    return m_density;
}

void Material::SetDensity(double density)
{
    m_density = density;
}

}