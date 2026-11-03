#pragma once

#include "Board.h"

#include <random>

class Game {
public:
	static constexpr int fallIntervalMs = 700;

	Game(Board & board, const Piece & pieces);

	void MoveLeft();
	void MoveRight();
	void MoveDown();
	void Rotate();
	void HardDrop();
	void Update(int elapsedMilliseconds);

	Piece::Type GetCurrentType() const { return _currentType; }
	int GetCurrentRotation() const { return _currentRotation; }
	int GetCurrentX() const { return _x; }
	int GetCurrentY() const { return _y; }
	Piece::Type GetNextType() const { return _nextType; }
	int GetNextRotation() const { return _nextRotation; }
	bool IsGameOver() const { return _gameOver; }

private:
	Board & _board;
	const Piece & _pieces;
	std::mt19937 _random;
	Piece::Type _currentType = Piece::O;
	int _currentRotation = 0;
	Piece::Type _nextType = Piece::O;
	int _nextRotation = 0;
	int _x = 0;
	int _y = 0;
	int _fallElapsedMs = 0;
	bool _gameOver = false;

	Piece::Type RandomType();
	int RandomRotation();
	void CreateNewPiece();
	void LockCurrentPiece();
};

