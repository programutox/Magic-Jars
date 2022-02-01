#ifndef SRC_CHAP_WIN_STATE_HPP
#define SRC_CHAP_WIN_STATE_HPP

#include "State.hpp"

namespace chap
{
    class WinState : public State
    {
    public:
        WinState(rl::Window &p_window, std::stack<std::unique_ptr<State>> &p_states, AssetsManager &p_assetsManager, bool p_soundOn);

        void Update() override;
        void Draw() override;

    private:
        static constexpr float s_rotationSpeed{ 200.f };
        bool m_soundPlayedOnce{ false };
        float m_dt{ };
        float m_rotation{ };
    };
}

#endif // SRC_CHAP_WIN_STATE_HPP
