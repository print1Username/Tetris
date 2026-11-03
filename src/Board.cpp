#include "../include/Board.h"

Board::Board(const Piece & pieces) : pieces_(pieces) {}

bool Board::IsFreeBlock(int x, int y) const {
	return !blocks_[y][x];
}

bool Board::IsPossibleMovement(int x, int y, Piece::Type type, int rotation) const {
	for ( int row = 0; row < Piece::Size; ++row ) {
		for ( int col = 0; col < Piece::Size; ++col ) {
			if ( pieces_.GetBlockType(type, rotation, row, col) == 0 )
				continue;

			const int boardX = x + col;
			const int boardY = y + row;
			if ( boardX < 0 || boardX >= Width || boardY >= Height )
				return false;
			if ( boardY >= 0 && !IsFreeBlock(boardX, boardY) )
				return false;
		}
	}
	return true;
}

void Board::StorePiece(int x, int y, Piece::Type type, int rotation) {
	for ( int row = 0; row < Piece::Size; ++row ) {
		for ( int col = 0; col < Piece::Size; ++col ) {
			if ( pieces_.GetBlockType(type, rotation, row, col) == 0 )
				continue;

			if ( y + row < 0 )
				overflow_ = true;
			else
				blocks_[y + row][x + col] = true;
		}
	}
}

void Board::DeleteLine(int y) {
	for ( int row = y; row > 0; --row )
		for ( int x = 0; x < Width; ++x )
			blocks_[row][x] = blocks_[row - 1][x];

	for ( int x = 0; x < Width; ++x )
		blocks_[0][x] = false;
}

void Board::DeletePossibleLines() {
	for ( int y = 0; y < Height; ++y ) {
		bool full = true;
		for ( int x = 0; x < Width; ++x )
			full = full && blocks_[y][x];

		if ( full )
			DeleteLine(y);
	}
}

bool Board::IsGameOver() const {
	if ( overflow_ )
		return true;

	for ( int x = 0; x < Width; ++x )
		if ( blocks_[0][x] )
			return true;
	return false;
}
