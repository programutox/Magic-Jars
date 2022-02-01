#ifndef SRC_CHAP_BUTTON_HPP
#define SRC_CHAP_BUTTON_HPP

#include "raylib-cpp.hpp"

namespace chap
{
    class Button
    {
    public:
        Button(rl::Texture2D &p_texture, const rl::Vector2 &p_pos) 
            : m_texture{ p_texture }, m_rect{ p_pos, p_texture.GetSize() }
        {

        }

        Button(rl::Texture2D &p_texture, const rl::Rectangle &p_srcRect, const rl::Vector2 &p_pos) 
            : m_texture{ p_texture }, m_rect{ p_pos, p_srcRect.GetSize() }, m_srcRect{ p_srcRect }
        {

        }

        rl::Vector2 GetPosition() const noexcept { return m_rect.GetPosition(); }
        
        bool IsHovered() const noexcept { return m_rect.CheckCollision(rl::Mouse::GetPosition()); }
        bool IsClicked() const noexcept { return this->IsHovered() && rl::Mouse::IsButtonPressed(MOUSE_LEFT_BUTTON); }

        void SetAlpha(int p_alpha) noexcept
        {
            if (m_color.a != p_alpha)
            {
                m_color.a = p_alpha;
            }
        }

        void UpdateAlpha() noexcept
        {  
            this->SetAlpha(this->IsHovered() ? 255 : 128);
        }

        void DrawLine() noexcept
        {
            rl::Color::Black().DrawLine(
                { m_rect.x + m_rect.width, m_rect.y },
                { m_rect.x, m_rect.y + m_rect.height }, 
                3
            );
        }

        void Draw() noexcept
        {
            if (m_srcRect.width == 0)
            {
                m_texture.Draw(m_rect.GetPosition(), m_color);
            }
            else
            {
                m_texture.Draw(m_srcRect, m_rect.GetPosition(), m_color);
            }
        }

    private:
        rl::Texture2D &m_texture;
        const rl::Rectangle m_rect;
        rl::Rectangle m_srcRect;
        rl::Color m_color{ rl::Color::White() };
    };
} // namespace chap

#endif // SRC_CHAP_BUTTON_HPP
