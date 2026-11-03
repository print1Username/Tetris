#pragma once

// Shape data follows the tutorial's 5x5 cells and four rotation states.
class Piece {
public:
	enum Type { O, I, L, J, S, Z, T };
	static constexpr int size = 5;

	// 0: empty, 1: block, 2: rotation pivot.
	int GetBlockType(Type type, int rotation, int x, int y) const;
	int GetXInitialPosition(Type type, int rotation) const;
	int GetYInitialPosition(Type type, int rotation) const;
};
