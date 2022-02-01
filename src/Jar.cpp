#include "Jar.hpp"

Jar::Jar(rl::Texture2D &p_texture, const rl::Rectangle &p_normalJarRect, const rl::Rectangle &p_brokenJarRect, const rl::Vector2 &p_pos)
    : m_texture{ p_texture }, m_normalJarRect{ p_normalJarRect }, m_brokenJarRect{ p_brokenJarRect }, m_rect{ p_pos, p_normalJarRect.GetSize() }
{

}

void Jar::DrawBroken() noexcept
{
    m_texture.Draw(m_brokenJarRect, m_rect.GetPosition());
}

void Jar::Draw() noexcept
{
    m_texture.Draw(m_normalJarRect, m_rect.GetPosition());
}
