#pragma once

#include "Piece.h"

class Board {
public:
	static constexpr int width = 10;
	static constexpr int height = 20;

	explicit Board(const Piece & pieces);

	bool IsFreeBlock(int x, int y) const;
	bool IsPossibleMovement(int x, int y, Piece::Type type, int rotation) const;
	void StorePiece(int x, int y, Piece::Type type, int rotation);
	void DeletePossibleLines();
	bool IsGameOver() const;

private:
	bool _blocks[height][width]{};
	bool _overflow = false;
	const Piece & _pieces;

	void DeleteLine(int y);
};
