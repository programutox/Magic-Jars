#include "GameState.hpp"

#include <effolkronium/random.hpp>

#include "WinState.hpp"

namespace chap
{
    using Random = effolkronium::random_static;

    GameState::GameState(rl::Window &p_window, std::stack<std::unique_ptr<State>> &p_states, AssetsManager &p_assetsManager, bool p_soundOn)
        : State{ p_window, p_states, p_assetsManager, p_soundOn }
    {
        m_assetsManager.Add<rl::Sound>("key");
        m_assetsManager.Add<rl::Sound>("snake");
        m_assetsManager.GetSound("snake").SetVolume(0.5f);
        m_assetsManager.Add<rl::Sound>("lose");

        m_assetsManager.AddButton(
            "back_button", "spritesheet", m_assetsManager.GetRect("back"), 
            { m_window.GetWidth() - m_assetsManager.GetRect("back").GetWidth() - 10.f, 10.f }
        );
        
        for (int i{ 0 }; auto &jar : m_jars)
        {
            jar = std::make_unique<Jar>(
                m_assetsManager.GetTexture("spritesheet"), m_assetsManager.GetRect("jar"), m_assetsManager.GetRect("jar_broken"),
                rl::Vector2{ 
                    (m_window.GetWidth() - m_assetsManager.GetRect("jar").width) / 40.f + m_assetsManager.GetRect("jar").width * 1.25f * i,
                    m_window.GetHeight() / 3.f + m_assetsManager.GetRect("jar").height * 2.f
                }
            );
            ++i;
        }

        this->MixJars();
    }

    void GameState::MixJars()
    {
        for (int i{ 0 }; auto &name : m_texturesName)
        {
            name = i < m_part ? "snake" : "key";
            ++i;
        }

        Random::shuffle(m_texturesName);
    }

    void GameState::GoToNextRound()
    {
        if (m_round + 1 <= s_roundMax)
        {
            ++m_round;
            Random::shuffle(m_texturesName);
        }
        else
        {
            m_round = 1;
            if (m_part + 1 <= s_partMax)
            {
                ++m_part;
                this->MixJars();
            }
            else
            {
                m_states.emplace(std::make_unique<WinState>(m_window, m_states, m_assetsManager, m_soundOn));
            }
        }
    }

    void GameState::Update()
    {
#if 0 // This part is used to debug the game
        if (IsKeyPressed(KEY_LEFT))
        {
            if (IsKeyDown(KEY_LEFT_SHIFT))
            {
                if (m_round - 1 >= 1)
                {
                    --m_round;
                }
            }
            else if (m_part - 1 >= 1)
            {
                --m_part;
            }
        }
        else if (IsKeyPressed(KEY_RIGHT))
        {
            if (IsKeyDown(KEY_LEFT_SHIFT))
            {
                if (m_round + 1 <= s_roundMax)
                {
                    ++m_round;
                }
            }
            else if (m_part + 1 <= s_partMax)
            {
                ++m_part;
            }
        }
#endif
        
        if (m_jarContentIndex == -1)
        {
            m_assetsManager.GetButton("back_button").UpdateAlpha();
            if (m_assetsManager.GetButton("back_button").IsClicked())
            {
                m_states.pop();
                return;
            }
        }

        if (int i{ -1 }; m_jarContentIndex == -1 && 
            std::find_if(m_jars.begin(), m_jars.end(), [&i](const auto &jar) { ++i; return jar->Clicked(); }) != m_jars.end())
        {
            m_jarContentIndex = i;
            if (m_soundOn)
            {
                m_assetsManager.GetSound(m_texturesName[i]).Play();
            }
            m_clock.Restart();
        }
        else if (m_jarContentIndex != -1 && m_clock.GetElapsedTime() > 1.0)
        {
            bool snake{ m_texturesName[m_jarContentIndex] == "snake" };
            m_jarContentIndex = -1;

            if (snake)
            {
                --m_lives;
                if (m_lives == 0)
                {
                    if (m_soundOn)
                    {
                        m_assetsManager.GetSound("lose").Play();
                    }
                    m_states.pop();
                }
            }
            else
            {
                this->GoToNextRound();
            }
        }
    }

    void GameState::Draw()
    {
        m_window.ClearBackground(m_partColors[m_part-1]);

        m_assetsManager.GetTexture("spritesheet").Draw(m_assetsManager.GetRect("cave"));

        rl::Color::White().DrawText("Part: " + std::to_string(m_part), 10, 10, 30);
        rl::Color::White().DrawText("Round: " + std::to_string(m_round), 10, 10 * 2 + 30, 30);

        for (int i{ 0 }; i < s_livesMax; ++i)
        {
            m_assetsManager.GetTexture("spritesheet").Draw(
                m_assetsManager.GetRect(i < m_lives ? "heart" : "empty_heart"), rl::Vector2{ 10.f + i * 50.f, 10 * 3.f + 30 * 2.f }
            );
        }

        if (m_jarContentIndex == -1)
        {
            this->DrawDoubleText("Choose a jar", 50);

            for (const auto &jar : m_jars)
            {
                jar->Draw();
            }

            m_assetsManager.GetButton("back_button").Draw();

            State::Draw();
        }
        else
        {
            if (m_texturesName[m_jarContentIndex] == "key")
            {
                this->DrawDoubleText("Cool, a key!", 50);
            }
            else if (m_lives > 1)
            {
                this->DrawDoubleText("A snake! Choose another jar!", 30);
            }
            else
            {
                this->DrawDoubleText("A snake! You lost!", 50);
            }

            for (int i{ 0 }; const auto &jar : m_jars)
            {
                m_assetsManager.GetTexture("spritesheet").Draw(
                    m_assetsManager.GetRect(m_texturesName[i]), { 
                        m_jars[i]->GetPosition().x + m_assetsManager.GetRect(m_texturesName[i]).width / 2.f,
                        m_jars[i]->GetPosition().y + m_assetsManager.GetRect(m_texturesName[i]).height / 2.f 
                    }, rl::Color::White().Alpha(i != m_jarContentIndex ? 0.25f : 1.f)
                );

                if (i != m_jarContentIndex)
                {
                    jar->DrawBroken();
                }
                ++i;
            }
        }
    }
} // namespace chap
