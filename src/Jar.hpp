#ifndef SRC_JAR_HPP
#define SRC_JAR_HPP

#include "raylib-cpp.hpp"

class Jar
{
public:
    Jar(rl::Texture2D &p_texture, const rl::Rectangle &p_normalJarRect, const rl::Rectangle &p_brokenJarRect, const rl::Vector2 &p_pos);

    rl::Vector2 GetPosition() const noexcept { return m_rect.GetPosition(); }

    bool Clicked() const noexcept
    {
        return m_rect.CheckCollision(rl::Mouse::GetPosition()) && rl::Mouse::IsButtonPressed(MOUSE_BUTTON_LEFT);
    }

    void DrawBroken() noexcept;
    void Draw() noexcept;

private:
    rl::Texture2D &m_texture;
    const rl::Rectangle m_normalJarRect;
    const rl::Rectangle m_brokenJarRect;
    const rl::Rectangle m_rect;
};

#endif // SRC_JAR_HPP
