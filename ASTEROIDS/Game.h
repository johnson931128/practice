#pragma once
#include <SFML/Graphics.hpp>
#include "Player.h"

class Game {
public:
    Game();
    void run();

private:
    void processEvents();
    void update(sf::Time dt);
    void render();

    sf::RenderWindow _window;
    Player _player;
};
