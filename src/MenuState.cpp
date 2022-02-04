#include "MenuState.hpp"

#include <fstream>

#include "GameState.hpp"

namespace chap
{
    MenuState::MenuState(rl::Window &p_window, std::stack<std::unique_ptr<State>> &p_states, AssetsManager &p_assetsManager, bool p_soundOn) 
        : State{ p_window, p_states, p_assetsManager, p_soundOn }
    {
        this->LoadTexturesRects();

        m_assetsManager.Add<rl::Texture2D>("spritesheet");

        m_assetsManager.Add<rl::Sound>("start");
        m_assetsManager.GetSound("start").SetVolume(0.5f);

        m_assetsManager.AddButton(
            "sound_button", "spritesheet", m_assetsManager.GetRect("sound"), { 
                m_window.GetWidth() - m_assetsManager.GetRect("sound").width - 10.f,
                m_window.GetHeight() - m_assetsManager.GetRect("sound").height - 10.f
            }
        );
    }

    void MenuState::LoadTexturesRects()
    {
        std::ifstream ifs{ "../assets/data/textures_rects.txt" };
        std::string id;
        rl::Rectangle rect;
        while (ifs >> id >> rect.x >> rect.y >> rect.width >> rect.height)
        {
            m_assetsManager.Add(id, rect);
        }
    }

    void MenuState::Update()
    {
        m_assetsManager.GetButton("sound_button").UpdateAlpha();

        if (!rl::Mouse::IsButtonPressed(MOUSE_BUTTON_LEFT))
        {
            return;
        }
        
        if (m_assetsManager.GetButton("sound_button").IsHovered())
        {
            m_soundOn = !m_soundOn;
            return;
        }
        
        if (m_soundOn)
        {
            m_assetsManager.GetSound("start").Play();
        }

        m_states.emplace(std::make_unique<GameState>(m_window, m_states, m_assetsManager, m_soundOn));
    }

    void MenuState::Draw()
    {
        m_window.ClearBackground({ 128, 64, 64 });

        m_assetsManager.GetTexture("spritesheet").Draw(m_assetsManager.GetRect("cave"));

        this->DrawDoubleText("Magic Jars", 50);

        rl::Color::Gray().DrawText("Click to start!", m_textRect.x, m_textRect.y, 30);

        m_assetsManager.GetButton("sound_button").Draw();

        if (!m_soundOn)
        {
            m_assetsManager.GetButton("sound_button").DrawLine();
        }
        
        State::Draw();
    }
} // namespace chap
