#include "../include/Renderer.h"
#include "../include/Window.h"

int main() {
	Piece pieces;
	Board board(pieces);
	Game game(board, pieces);
	Renderer renderer(board, game, pieces);
	Window window(game, renderer);
	window.Run();
}
