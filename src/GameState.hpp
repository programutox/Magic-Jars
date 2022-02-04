#ifndef SRC_CHAP_GAME_STATE_HPP
#define SRC_CHAP_GAME_STATE_HPP

#include "State.hpp"

#include <array>

#include "Clock.hpp"
#include "Jar.hpp"

namespace chap
{
    class GameState : public State
    {
    public:
        GameState(rl::Window &p_window, std::stack<std::unique_ptr<State>> &p_states, AssetsManager &p_assetsManager, bool p_soundOn);

        // Mixes jars' content randomly according to the number of parts player is at
        void MixJars();

        void GoToNextRound();
        void HandleKeysForDebug();

        void Update() override;
        void Draw() override;

    private:
        static constexpr int s_partMax{ 4 };
        static constexpr int s_roundMax{ 3 };
        static constexpr int s_livesMax{ 3 };

        int m_part{ 1 };
        int m_round{ 1 };
        int m_lives{ 3 };

        std::array<rl::Color, s_partMax+1> m_partColors{{
            { 128, 64, 64 },
            { 128, 0, 0 },
            { 64, 0, 0 },
            { 64, 0, 64 },
            rl::Color::Black()
        }};

        std::array<std::unique_ptr<Jar>, 5> m_jars{ };
        std::array<std::string, 5> m_texturesName{ };

        Clock m_clock;
        int m_jarContentIndex{ -1 };
    };
} // namespace chap

#endif // SRC_CHAP_GAME_STATE_HPP
