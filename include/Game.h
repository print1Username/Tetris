#pragma once

#include "Board.h"

#include <random>

class Game {
public:
	static constexpr int FallIntervalMs = 700;

	Game(Board & board, const Piece & pieces);

	void MoveLeft();
	void MoveRight();
	void MoveDown();
	void Rotate();
	void HardDrop();
	void Update(int elapsedMilliseconds);

	Piece::Type GetCurrentType() const { return currentType_; }
	int GetCurrentRotation() const { return currentRotation_; }
	int GetCurrentX() const { return x_; }
	int GetCurrentY() const { return y_; }
	Piece::Type GetNextType() const { return nextType_; }
	int GetNextRotation() const { return nextRotation_; }
	bool IsGameOver() const { return gameOver_; }

private:
	Board & board_;
	const Piece & pieces_;
	std::mt19937 random_;
	Piece::Type currentType_ = Piece::O;
	int currentRotation_ = 0;
	Piece::Type nextType_ = Piece::O;
	int nextRotation_ = 0;
	int x_ = 0;
	int y_ = 0;
	int fallElapsedMs_ = 0;
	bool gameOver_ = false;

	Piece::Type RandomType();
	int RandomRotation();
	void CreateNewPiece();
	void LockCurrentPiece();
};

