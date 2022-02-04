#ifndef SRC_CHAP_MENU_STATE_HPP
#define SRC_CHAP_MENU_STATE_HPP

#include "State.hpp"

namespace chap
{
    class MenuState : public State
    {
    public:
        MenuState(rl::Window &p_window, std::stack<std::unique_ptr<State>> &p_states, AssetsManager &p_assetsManager, bool p_soundOn);

        void LoadTexturesRects();

        void Update() override;
        void Draw() override;
    
    private:
        const rl::Rectangle m_textRect{ 
            (m_window.GetWidth() - rl::MeasureText("Click to start!", 30)) / 2.f, m_window.GetHeight() * 3 / 4.f,
            rl::MeasureText("Click to start!", 30) * 1.f, 30.f
        };
    };
} // namespace chap

#endif // SRC_CHAP_MENU_STATE_HPP
