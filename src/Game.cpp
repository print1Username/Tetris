#include "../include/Game.h"

Game::Game(Board & board, const Piece & pieces)
	: _board(board), _pieces(pieces), _random(std::random_device{}()) {
	_currentType = RandomType();
	_currentRotation = RandomRotation();
	_nextType = RandomType();
	_nextRotation = RandomRotation();
	_x = Board::width / 2 + _pieces.GetXInitialPosition(_currentType, _currentRotation);
	_y = _pieces.GetYInitialPosition(_currentType, _currentRotation);
	_gameOver = !_board.IsPossibleMovement(_x, _y, _currentType, _currentRotation);
}

Piece::Type Game::RandomType() {
	std::uniform_int_distribution<int> distribution(Piece::O, Piece::T);
	return static_cast<Piece::Type>(distribution(_random));
}

int Game::RandomRotation() {
	std::uniform_int_distribution<int> distribution(0, 3);
	return distribution(_random);
}

void Game::CreateNewPiece() {
	_currentType = _nextType;
	_currentRotation = _nextRotation;
	_x = Board::width / 2 + _pieces.GetXInitialPosition(_currentType, _currentRotation);
	_y = _pieces.GetYInitialPosition(_currentType, _currentRotation);
	_nextType = RandomType();
	_nextRotation = RandomRotation();
	_gameOver = !_board.IsPossibleMovement(_x, _y, _currentType, _currentRotation);
}

void Game::MoveLeft() {
	if ( !_gameOver && _board.IsPossibleMovement(_x - 1, _y, _currentType, _currentRotation) )
		--_x;
}

void Game::MoveRight() {
	if ( !_gameOver && _board.IsPossibleMovement(_x + 1, _y, _currentType, _currentRotation) )
		++_x;
}

void Game::MoveDown() {
	if ( !_gameOver && _board.IsPossibleMovement(_x, _y + 1, _currentType, _currentRotation) )
		++_y;
}

void Game::Rotate() {
	const int nextRotation = (_currentRotation + 1) % 4;
	if ( !_gameOver && _board.IsPossibleMovement(_x, _y, _currentType, nextRotation) )
		_currentRotation = nextRotation;
}

void Game::LockCurrentPiece() {
	_board.StorePiece(_x, _y, _currentType, _currentRotation);
	_board.DeletePossibleLines();
	_gameOver = _board.IsGameOver();
	if ( !_gameOver )
		CreateNewPiece();
}

void Game::HardDrop() {
	if ( _gameOver )
		return;

	while ( _board.IsPossibleMovement(_x, _y + 1, _currentType, _currentRotation) )
		++_y;
	LockCurrentPiece();
	_fallElapsedMs = 0;
}

void Game::Update(int elapsedMilliseconds) {
	if ( _gameOver || elapsedMilliseconds <= 0 )
		return;

	_fallElapsedMs += elapsedMilliseconds;
	while ( _fallElapsedMs >= fallIntervalMs && !_gameOver ) {
		_fallElapsedMs -= fallIntervalMs;
		if ( _board.IsPossibleMovement(_x, _y + 1, _currentType, _currentRotation) )
			++_y;
		else
			LockCurrentPiece();
	}
}
