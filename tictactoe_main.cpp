#include "tictactoe.h"
int main(int argc, char *argv[]) {
  /*int boardData[9]{};*/
  /*int scoreData[9]{};*/
  /*torch::TensorOptions optionsNoGradFloat =*/
  /*    torch::TensorOptions().dtype(torch::kFloat32).requires_grad(false);*/
  /*torch::Tensor board = torch::from_blob(boardData, {3, 3},
   * optionsNoGradFloat);*/
  /*torch::Tensor scoreBoard = torch::from_blob(scoreData, {3, 3},
   * optionsNoGradFloat);*/
  /**/
  TicTacToe spelletj;
  spelletj.reset();
  for (int i = 0; i < 100; i++) {
    std::cout << "player: " << spelletj.player << '\n';
    torch::Tensor score = spelletj.computeScore();
    std::cout << "score: \n" << score << '\n';

    int maxVal = score.argmax().item<int>();
    std::cout << "max val: " << maxVal << '\n';
    int x, y;
    if (maxVal == 9) {
      x = 2;
      y = 2;
    } else {
      y = maxVal % 3;
      x = maxVal / 3;
    }
    std::cout << "max val x/y: " << x << ' ' << y << '\n';
    spelletj.move(x, y);
    std::cout << "board: \n" << spelletj.getBoard() << '\n';
  }
  return 0;
}
