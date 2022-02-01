#include "Game.hpp"

namespace chap
{
    Game::Game()
    {
        m_window.SetIcon(rl::Image{ "../assets/img/raylib_icon.png" });
        SetExitKey(0);
        HideCursor();
        m_states.emplace(std::make_unique<MenuState>(m_window, m_states, m_assetsManager, true));
    }

    void Game::Update()
    {
        m_states.top()->Update();
    }

    void Game::Draw()
    {
        m_window.BeginDrawing();

            m_states.top()->Draw();

        m_window.EndDrawing();
    }
}
