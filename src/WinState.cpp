#include "WinState.hpp"

namespace chap
{
    WinState::WinState(rl::Window &p_window, std::stack<std::unique_ptr<State>> &p_states, AssetsManager &p_assetsManager, bool p_soundOn)
        : State { p_window, p_states, p_assetsManager, p_soundOn }
    {
        m_assetsManager.Add<rl::Sound>("win");
    }

    void WinState::Update()
    {
        m_dt = m_window.GetFrameTime();
        m_rotation += s_rotationSpeed * m_dt;

        if (rl::Mouse::IsButtonPressed(MOUSE_BUTTON_LEFT))
        {
            if (m_soundOn && m_assetsManager.GetSound("win").IsPlaying())
            {
                m_assetsManager.GetSound("win").Stop();
            }

            // While you are not back to the first state (which is MenuState)
            while (m_states.size() > 1)
            {
                m_states.pop();
            }
        }

        if (m_soundOn && !m_soundPlayedOnce)
        {
            m_assetsManager.GetSound("win").Play();
            m_soundPlayedOnce = true;
        }
    }

    void WinState::Draw()
    {
        m_window.ClearBackground({ 64, 0, 64 });

        m_assetsManager.GetTexture("spritesheet").Draw(m_assetsManager.GetRect("cave"));

        this->DrawDoubleText("You found the statue!", 50);

        const rl::Vector2 pos{ 
            (m_window.GetWidth() - m_assetsManager.GetRect("statue").width) / 2.f,
            (m_window.GetHeight() - m_assetsManager.GetRect("statue").height) / 2 + 10.f
        };

        m_assetsManager.GetTexture("spritesheet").Draw(
            m_assetsManager.GetRect("star"), 
            rl::Rectangle{ { m_window.GetWidth() / 2.f, m_window.GetHeight() / 2.f + 10.f }, m_assetsManager.GetRect("star").GetSize() },
            rl::Vector2{ m_assetsManager.GetRect("star").width / 2.f, m_assetsManager.GetRect("star").height / 2.f },
            m_rotation
        );

        m_assetsManager.GetTexture("spritesheet").Draw(m_assetsManager.GetRect("statue"), pos);

        rl::Color::Gray().DrawText(
            "Click to go back", (m_window.GetWidth() - rl::MeasureText("Click to go back", 30)) / 2, m_window.GetHeight() * 3 / 4, 30
        );

        State::Draw();
    }
} // namespace chap
