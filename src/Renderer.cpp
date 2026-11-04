#include "../include/Renderer.h"
#include "../include/Window.h"

namespace {
	constexpr int BoardLeft = (Window::windowWidth - Board::width * Renderer::blockSize) / 2;
	constexpr int BoardTop = Window::windowHeight - Board::height * Renderer::blockSize;
	constexpr int BorderWidth = 6;
}

Renderer::Renderer(const Board & board, const Game & game, const Piece & pieces)
	: _board(board), _game(game), _pieces(pieces) {}

void Renderer::DrawBlock(sf::RenderTarget & target, int x, int y, sf::Color color) const {
	sf::RectangleShape block({ static_cast<float>(blockSize - 1), static_cast<float>(blockSize - 1) });
	block.setPosition({ static_cast<float>(x), static_cast<float>(y) });
	block.setFillColor(color);
	target.draw(block);
}

void Renderer::DrawPiece(sf::RenderTarget & target, int x, int y, Piece::Type type, int rotation) const {
	for ( int row = 0; row < Piece::size; ++row ) {
		for ( int col = 0; col < Piece::size; ++col ) {
			const int blockType = _pieces.GetBlockType(type, rotation, row, col);
			if ( blockType == 0 )
				continue;

			const int pixelY = y + row * blockSize;
			if ( pixelY < 0 || pixelY >= static_cast<int>(Window::windowHeight) )
				continue;

			DrawBlock(target, x + col * blockSize, pixelY,
					  blockType == 2 ? sf::Color::Blue : sf::Color::Green);
		}
	}
}

void Renderer::Draw(sf::RenderTarget & target) const {
	sf::RectangleShape border({ static_cast<float>(BorderWidth),
							   static_cast<float>(Board::height * blockSize) });
	border.setFillColor(sf::Color::Blue);
	border.setPosition({ static_cast<float>(BoardLeft - BorderWidth), static_cast<float>(BoardTop) });
	target.draw(border);
	border.setPosition({ static_cast<float>(BoardLeft + Board::width * blockSize),
						static_cast<float>(BoardTop) });
	target.draw(border);

	for ( int y = 0; y < Board::height; ++y )
		for ( int x = 0; x < Board::width; ++x )
			if ( !_board.IsFreeBlock(x, y) )
				DrawBlock(target, BoardLeft + x * blockSize, BoardTop + y * blockSize, sf::Color::Red);

	if ( !_game.IsGameOver() )
		DrawPiece(target, BoardLeft + _game.GetCurrentX() * blockSize,
				  BoardTop + _game.GetCurrentY() * blockSize,
				  _game.GetCurrentType(), _game.GetCurrentRotation());

	DrawPiece(target, BoardLeft + (Board::width + 5) * blockSize,
			  BoardTop + 5 * blockSize, _game.GetNextType(), _game.GetNextRotation());
}
