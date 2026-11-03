#pragma once

#include "Board.h"
#include "Game.h"

#include <SFML/Graphics.hpp>

class Renderer {
public:
	static constexpr unsigned windowWidth = 800;
	static constexpr unsigned windowHeight = 600;
	static constexpr int blockSize = 16;

	Renderer(const Board & board, const Game & game, const Piece & pieces);
	void Draw(sf::RenderTarget & target) const;

private:
	const Board & _board;
	const Game & _game;
	const Piece & _pieces;

	void DrawBlock(sf::RenderTarget & target, int x, int y, sf::Color color) const;
	void DrawPiece(sf::RenderTarget & target, int x, int y, Piece::Type type, int rotation) const;
};

