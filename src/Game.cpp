#include "../include/Game.h"

Game::Game(Board & board, const Piece & pieces)
	: board_(board), pieces_(pieces), random_(std::random_device{}()) {
	currentType_ = RandomType();
	currentRotation_ = RandomRotation();
	nextType_ = RandomType();
	nextRotation_ = RandomRotation();
	x_ = Board::Width / 2 + pieces_.GetXInitialPosition(currentType_, currentRotation_);
	y_ = pieces_.GetYInitialPosition(currentType_, currentRotation_);
	gameOver_ = !board_.IsPossibleMovement(x_, y_, currentType_, currentRotation_);
}

Piece::Type Game::RandomType() {
	std::uniform_int_distribution<int> distribution(Piece::O, Piece::T);
	return static_cast<Piece::Type>(distribution(random_));
}

int Game::RandomRotation() {
	std::uniform_int_distribution<int> distribution(0, 3);
	return distribution(random_);
}

void Game::CreateNewPiece() {
	currentType_ = nextType_;
	currentRotation_ = nextRotation_;
	x_ = Board::Width / 2 + pieces_.GetXInitialPosition(currentType_, currentRotation_);
	y_ = pieces_.GetYInitialPosition(currentType_, currentRotation_);
	nextType_ = RandomType();
	nextRotation_ = RandomRotation();
	gameOver_ = !board_.IsPossibleMovement(x_, y_, currentType_, currentRotation_);
}

void Game::MoveLeft() {
	if ( !gameOver_ && board_.IsPossibleMovement(x_ - 1, y_, currentType_, currentRotation_) )
		--x_;
}

void Game::MoveRight() {
	if ( !gameOver_ && board_.IsPossibleMovement(x_ + 1, y_, currentType_, currentRotation_) )
		++x_;
}

void Game::MoveDown() {
	if ( !gameOver_ && board_.IsPossibleMovement(x_, y_ + 1, currentType_, currentRotation_) )
		++y_;
}

void Game::Rotate() {
	const int nextRotation = (currentRotation_ + 1) % 4;
	if ( !gameOver_ && board_.IsPossibleMovement(x_, y_, currentType_, nextRotation) )
		currentRotation_ = nextRotation;
}

void Game::LockCurrentPiece() {
	board_.StorePiece(x_, y_, currentType_, currentRotation_);
	board_.DeletePossibleLines();
	gameOver_ = board_.IsGameOver();
	if ( !gameOver_ )
		CreateNewPiece();
}

void Game::HardDrop() {
	if ( gameOver_ )
		return;

	while ( board_.IsPossibleMovement(x_, y_ + 1, currentType_, currentRotation_) )
		++y_;
	LockCurrentPiece();
	fallElapsedMs_ = 0;
}

void Game::Update(int elapsedMilliseconds) {
	if ( gameOver_ || elapsedMilliseconds <= 0 )
		return;

	fallElapsedMs_ += elapsedMilliseconds;
	while ( fallElapsedMs_ >= FallIntervalMs && !gameOver_ ) {
		fallElapsedMs_ -= FallIntervalMs;
		if ( board_.IsPossibleMovement(x_, y_ + 1, currentType_, currentRotation_) )
			++y_;
		else
			LockCurrentPiece();
	}
}
