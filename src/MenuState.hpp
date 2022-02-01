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
    };
} // namespace chap

#endif // SRC_CHAP_MENU_STATE_HPP
