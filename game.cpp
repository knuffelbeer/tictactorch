#include <cstddef>
#include <iostream>
#include "tictactoe.h"

template <size_t BOARD_SIZEX, size_t BOARD_SIZEY>
vierOpenRij<BOARD_SIZEX, BOARD_SIZEY>::vierOpenRij() {}

template <size_t BOARD_SIZEX, size_t BOARD_SIZEY>
bool vierOpenRij<BOARD_SIZEX, BOARD_SIZEY>::win() {

  unsigned int playerNum = player + 1;
  bool winning = true;
  unsigned int streak{};
  for (int i = (lastmove[0] - 4 >= 0) ? -4 : -lastmove[0]; i < 4; i++) {
    winning = playerNum == board[lastmove[0]][lastmove[1] + i];
    streak = (winning) ? streak + 1 : 0;
		std::cout << winning << '\n';
		std::cout << lastmove[0] << lastmove[1] << '\n';
		
		
    if (streak >= 4)
      return true;
  }
	return false;
}

template <size_t BOARD_SIZEX, size_t BOARD_SIZEY>
void vierOpenRij<BOARD_SIZEX, BOARD_SIZEY>::move(int column) {
  lastmove[0] = column;

  if (column >= BOARD_SIZEY) {
    std::cout << "invalid move" << '\n';
    return;
  }
  for (int i = BOARD_SIZEY; i > 0; i--) {
    if (!board[i - 1][column]) {
      board[i - 1][column] = player + 1;
      player = !player;
      lastmove[1] = i - 1;
      return;
    }
  }
  std::cout << "invalid move" << '\n';
}

template <size_t BOARD_SIZEX, size_t BOARD_SIZEY>
void vierOpenRij<BOARD_SIZEX, BOARD_SIZEY>::printBoard() {
  for (int i = 0; i < BOARD_SIZEX; i++) {
    for (int j = 0; j < BOARD_SIZEY; j++) {
      std::cout << board[i][j];
    }
    std::cout << '\n';
  }
}

int main(int argc, char *argv[]) {
  vierOpenRij<10, 10> vierOpenRij;
  vierOpenRij.printBoard();
  std::cout << '\n';


  for (int i = 0; i < 4; i++) {
    vierOpenRij.move(i);
		
    vierOpenRij.move(8);
		
  }
	std::cout << vierOpenRij.win() << '\n';
  vierOpenRij.printBoard();
  return 0;
}
