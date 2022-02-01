#include "State.hpp"

namespace chap
{
    State::State(rl::Window &p_window, std::stack<std::unique_ptr<State>> &p_states, AssetsManager &p_assetsManager, bool p_soundOn)
        : m_window{ p_window }, m_states{ p_states }, m_assetsManager{ p_assetsManager }, m_soundOn{ p_soundOn }
    {
        
    }

    void State::DrawDoubleText(const std::string &p_str, int p_size)
    {
        rl::Color::White().DrawText(
            p_str, (m_window.GetWidth() - rl::MeasureText(p_str, p_size)) / 2, (m_window.GetHeight() - p_size) / 4, p_size
        );
    }

    void State::Draw()
    {
#if !defined(PLATFORM_WEB)
        m_assetsManager.GetTexture("spritesheet").Draw(
            m_assetsManager.GetRect("finger"),
            rl::Vector2{
                rl::Mouse::GetX() - m_assetsManager.GetRect("finger").width / 2.f,
                rl::Mouse::GetY() - m_assetsManager.GetRect("finger").height / 2.f
            }
        );
#endif
    }
} // namespace chap
