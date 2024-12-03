#include "tictactoe.h"
#include <cmath>
#include <cstring>

#define BOARD_SIZE 3

using namespace std;

using namespace torch::indexing;

torch::TensorOptions TicTacToe::optionsNoGradFloat =
    torch::TensorOptions().dtype(torch::kFloat32).requires_grad(false);
torch::TensorOptions TicTacToe::optionsNoGrad =
    torch::TensorOptions().dtype(torch::kInt32).requires_grad(false);
int TicTacToe::diagData[3] = {0, 1, 2};
int TicTacToe::diagReversedData[3] = {2, 1, 0};
torch::Tensor TicTacToe::diag = torch::from_blob(diagData, {3}, optionsNoGrad);
torch::Tensor TicTacToe::diagReversed =
    torch::from_blob(diagReversedData, {3}, optionsNoGrad);

namespace helperFunctions {
bool checkLocation(torch::Tensor &board, int x, int y, int player) {
  // Check rows
  for (int row = 0; row < 3; row++) {
    if ((board.index({row, Slice(None)}) == player).all().item<bool>())
      return true;
  }
  // Check columns
  for (int column = 0; column < 3; column++) {
    if ((board.index({Slice(None), column}) == player).all().item<bool>())
      return true;
  }
  // Check diagonals
  if ((board.index({TicTacToe::diag, TicTacToe::diag}) == player)
          .all()
          .item<bool>())
    return true;
  if ((board.index({TicTacToe::diag, TicTacToe::diagReversed}) == player)
          .all()
          .item<bool>())
    return true;

  return false;
}

torch::Tensor &score(torch::Tensor &scoreBoard, torch::Tensor &board,
                     int player) {
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {

      if (board.index({i, j}).item<int>()) {
        scoreBoard.index_put_({i, j}, -100);

      } else {
        board.index_put_({i, j}, player);
        scoreBoard.index_put_({i, j}, checkLocation(board, i, j, player));
        board.index_put_({i, j}, 0);
      }
    }
  }
  return scoreBoard;
}
} // namespace helperFunctions

bool TicTacToe::checkLocation(int x, int y) {
  return helperFunctions::checkLocation(board, x, y, player);
}

torch::Tensor &TicTacToe::computeScore() {
  return helperFunctions::score(score, board, player);
}

bool TicTacToe::getPlayer() { return player; }

torch::Tensor TicTacToe::getBoard() { return board; }

ostream &operator<<(ostream &os, const TicTacToe &dt) {
  std::cout << dt.board << '\n';
  return os;
}

void TicTacToe::reset() { std::memset(boardData, 0, 9); }

bool TicTacToe::move(int x, int y) {
  if (x < 3 && x >= 0 && y < 3 && y >= 0) {
    /*std::cout << board.index({location}) << " :item";*/
    if (board.index({x, y}).item<float>() != 0) {
      // std::cout << "invalid Location" << x << ' ' << y << '\n';
      numInvalidMoves += 1;
      return false;
    }
    board.index_put_({x, y}, player);
    if ((board != 0).all().item<bool>()) {
      reset();
    } else {
      // std::cout << "switching player from " << player << "to ";
      player = !(player - 1) + 1;
      // std::cout << player << '\n';
    }
    return true;
  }
  std::cout << "location " << x << ' ' << y << "is out of bounds" << '\n';
  throw;
  return false;
}

TicTacToe::TicTacToe() {}
TicTacToe::~TicTacToe() {}
