#pragma once

#include "Board.h"
#include "Game.h"

#include <SFML/Graphics.hpp>

class Renderer {
public:
	static constexpr unsigned WindowWidth = 800;
	static constexpr unsigned WindowHeight = 600;
	static constexpr int BlockSize = 16;

	Renderer(const Board & board, const Game & game, const Piece & pieces);
	void Draw(sf::RenderTarget & target) const;

private:
	const Board & board_;
	const Game & game_;
	const Piece & pieces_;

	void DrawBlock(sf::RenderTarget & target, int x, int y, sf::Color color) const;
	void DrawPiece(sf::RenderTarget & target, int x, int y, Piece::Type type, int rotation) const;
};

