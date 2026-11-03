#pragma once

#include "Piece.h"

class Board {
public:
	static constexpr int Width = 10;
	static constexpr int Height = 20;

	explicit Board(const Piece & pieces);

	bool IsFreeBlock(int x, int y) const;
	bool IsPossibleMovement(int x, int y, Piece::Type type, int rotation) const;
	void StorePiece(int x, int y, Piece::Type type, int rotation);
	void DeletePossibleLines();
	bool IsGameOver() const;

private:
	bool blocks_[Height][Width]{};
	bool overflow_ = false;
	const Piece & pieces_;

	void DeleteLine(int y);
};
