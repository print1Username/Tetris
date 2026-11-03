#include "../include/Renderer.h"

namespace
{
constexpr int BoardLeft = (Renderer::WindowWidth - Board::Width * Renderer::BlockSize) / 2;
constexpr int BoardTop = Renderer::WindowHeight - Board::Height * Renderer::BlockSize;
constexpr int BorderWidth = 6;
}

Renderer::Renderer(const Board& board, const Game& game, const Piece& pieces)
    : board_(board), game_(game), pieces_(pieces) {}

void Renderer::DrawBlock(sf::RenderTarget& target, int x, int y, sf::Color color) const
{
    sf::RectangleShape block({static_cast<float>(BlockSize - 1), static_cast<float>(BlockSize - 1)});
    block.setPosition({static_cast<float>(x), static_cast<float>(y)});
    block.setFillColor(color);
    target.draw(block);
}

void Renderer::DrawPiece(sf::RenderTarget& target, int x, int y, Piece::Type type, int rotation) const
{
    for (int row = 0; row < Piece::Size; ++row)
    {
        for (int col = 0; col < Piece::Size; ++col)
        {
            const int blockType = pieces_.GetBlockType(type, rotation, row, col);
            if (blockType == 0)
                continue;

            const int pixelY = y + row * BlockSize;
            if (pixelY < 0 || pixelY >= static_cast<int>(WindowHeight))
                continue;

            DrawBlock(target, x + col * BlockSize, pixelY,
                      blockType == 2 ? sf::Color::Blue : sf::Color::Green);
        }
    }
}

void Renderer::Draw(sf::RenderTarget& target) const
{
    sf::RectangleShape border({static_cast<float>(BorderWidth),
                               static_cast<float>(Board::Height * BlockSize)});
    border.setFillColor(sf::Color::Blue);
    border.setPosition({static_cast<float>(BoardLeft - BorderWidth), static_cast<float>(BoardTop)});
    target.draw(border);
    border.setPosition({static_cast<float>(BoardLeft + Board::Width * BlockSize),
                        static_cast<float>(BoardTop)});
    target.draw(border);

    for (int y = 0; y < Board::Height; ++y)
        for (int x = 0; x < Board::Width; ++x)
            if (!board_.IsFreeBlock(x, y))
                DrawBlock(target, BoardLeft + x * BlockSize, BoardTop + y * BlockSize, sf::Color::Red);

    if (!game_.IsGameOver())
        DrawPiece(target, BoardLeft + game_.GetCurrentX() * BlockSize,
                  BoardTop + game_.GetCurrentY() * BlockSize,
                  game_.GetCurrentType(), game_.GetCurrentRotation());

    DrawPiece(target, BoardLeft + (Board::Width + 5) * BlockSize,
              BoardTop + 5 * BlockSize, game_.GetNextType(), game_.GetNextRotation());
}
