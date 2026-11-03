#include "../include/Board.h"

Board::Board(const Piece & pieces) : _pieces(pieces) {}

bool Board::IsFreeBlock(int x, int y) const {
	return !_blocks[y][x];
}

bool Board::IsPossibleMovement(int x, int y, Piece::Type type, int rotation) const {
	for ( int row = 0; row < Piece::size; ++row ) {
		for ( int col = 0; col < Piece::size; ++col ) {
			if ( _pieces.GetBlockType(type, rotation, row, col) == 0 )
				continue;

			const int boardX = x + col;
			const int boardY = y + row;
			if ( boardX < 0 || boardX >= width || boardY >= height )
				return false;
			if ( boardY >= 0 && !IsFreeBlock(boardX, boardY) )
				return false;
		}
	}
	return true;
}

void Board::StorePiece(int x, int y, Piece::Type type, int rotation) {
	for ( int row = 0; row < Piece::size; ++row ) {
		for ( int col = 0; col < Piece::size; ++col ) {
			if ( _pieces.GetBlockType(type, rotation, row, col) == 0 )
				continue;

			if ( y + row < 0 )
				_overflow = true;
			else
				_blocks[y + row][x + col] = true;
		}
	}
}

void Board::DeleteLine(int y) {
	for ( int row = y; row > 0; --row )
		for ( int x = 0; x < width; ++x )
			_blocks[row][x] = _blocks[row - 1][x];

	for ( int x = 0; x < width; ++x )
		_blocks[0][x] = false;
}

void Board::DeletePossibleLines() {
	for ( int y = 0; y < height; ++y ) {
		bool full = true;
		for ( int x = 0; x < width; ++x )
			full = full && _blocks[y][x];

		if ( full )
			DeleteLine(y);
	}
}

bool Board::IsGameOver() const {
	if ( _overflow )
		return true;

	for ( int x = 0; x < width; ++x )
		if ( _blocks[0][x] )
			return true;
	return false;
}
