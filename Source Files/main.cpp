//
// Created by Cassidy Heulings on 1/29/26.
//
#include <SFMl/Graphics.hpp>
#include "../Header Files/Player.hpp"
using namespace sf;

int main() {
    // initializing screen/world vars
    // TODO decide game states
    enum class State { PAUSED, CRAFTING, NEW_GAME, PLAYING, JOURNAL };
    State state = State::NEW_GAME; // start game in game over state

    // create SFML window with screen resolution
    Vector2f resolution;
    resolution.x = VideoMode::getDesktopMode().width;
    resolution.y = VideoMode::getDesktopMode().height;
    RenderWindow window(VideoMode(resolution.x, resolution.y),
        "Maskable", Style::Fullscreen);
    // view following character in world
    View mainView(FloatRect(0,0,resolution.x,resolution.y));

    // Initialize game-wide variables
    Clock clock; // used to time everything
    Vector2f mouseWorldPos; // mouse in relation to world coords
    Vector2i mouseScreenPos; // mouse in relation to screen coords
    Player player; // create instance of player class
    IntRect world; // boundaries of world

    // game loop
    while (window.isOpen()) {
    }

    return 0;
}