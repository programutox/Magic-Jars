#ifndef SRC_CHAP_GAME_HPP
#define SRC_CHAP_GAME_HPP

#include "AssetsManager.hpp"
#include "MenuState.hpp"

namespace chap
{
    class Game
    {
    public:
        Game();

        void Update();
        void Draw();

    private:
        rl::Window m_window{ 800, 600, "Magic Jars" };
        rl::AudioDevice m_audioDevice;

        std::stack<std::unique_ptr<State>> m_states;
        AssetsManager m_assetsManager{ "../assets/img/", "../assets/sfx/", "../assets/mus/" };
    };
} // namespace chap

#endif // SRC_CHAP_GAME_HPP
