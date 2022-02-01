#ifndef SRC_CHAP_STATE_HPP
#define SRC_CHAP_STATE_HPP

#include "raylib-cpp.hpp"

#include <stack>

#include "AssetsManager.hpp"

namespace chap
{
    class State
    {
    public:
        State(rl::Window &p_window, std::stack<std::unique_ptr<State>> &p_states, AssetsManager &p_assetsManager, bool p_soundOn);

        // You need to create a virtual destructor otherwise emscripten compiler shows a warning
        virtual ~State() { }
        
        void DrawDoubleText(const std::string &p_str, int p_size);

        virtual void Update() = 0;
        virtual void Draw();

    protected:
        rl::Window &m_window;
        std::stack<std::unique_ptr<State>> &m_states;
        AssetsManager &m_assetsManager;
        bool m_soundOn;
    };
} // namespace chap

#endif // SRC_CHAP_STATE_HPP
