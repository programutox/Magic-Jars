/*
 * main.cpp
 * Author: Eric-Nicolas
 * Description: Entry point of the program. Contains the game loop.
 */

#include "Game.hpp"

#if defined(PLATFORM_WEB)
    #include <emscripten/emscripten.h>
#endif

void UpdateDrawFrame()
{
    static chap::Game game;
    game.Update();
    game.Draw();
}

int main()
{
    // We must call the function once so that the window is created
    // and you can call WindowShouldClose()
    UpdateDrawFrame();
    
    #if defined(PLATFORM_WEB)
        emscripten_set_main_loop(UpdateDrawFrame, 0, 1);
    #else
        while (!WindowShouldClose())
        {
            UpdateDrawFrame();
        }
    #endif

	return 0;
}