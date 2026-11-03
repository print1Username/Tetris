#include <SFML/Graphics.hpp>
#include "../include/Renderer.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode({ Renderer::WindowWidth, Renderer::WindowHeight }), "Tetris");
    window.setFramerateLimit(60);

    Piece pieces;
    Board board(pieces);
    Game game(board, pieces);
    Renderer renderer(board, game, pieces);
    sf::Clock clock;
    bool gameOverShown = false;

    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
            {
                window.close();
            }
            else if (const auto* key = event->getIf<sf::Event::KeyPressed>())
            {
                switch (key->code)
                {
                case sf::Keyboard::Key::Escape: window.close(); break;
                case sf::Keyboard::Key::Left: game.MoveLeft(); break;
                case sf::Keyboard::Key::Right: game.MoveRight(); break;
                case sf::Keyboard::Key::Down: game.MoveDown(); break;
                case sf::Keyboard::Key::Z: game.Rotate(); break;
                case sf::Keyboard::Key::X: game.HardDrop(); break;
                default: break;
                }
            }
        }

        if (!window.isOpen())
            break;

        game.Update(clock.restart().asMilliseconds());
        if (game.IsGameOver() && !gameOverShown)
        {
            window.setTitle("Tetris - Game Over");
            gameOverShown = true;
        }

        window.clear();
        renderer.Draw(window);
        window.display();
    }
}
