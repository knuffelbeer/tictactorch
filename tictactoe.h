#pragma once
#include <cstddef>
#include <iostream>
#include <torch/torch.h>

using namespace std;
class TicTacToe {
public:
  static int diagData[3];
  static int diagReversedData[3];
  TicTacToe();
  TicTacToe(TicTacToe &&) = default;
  TicTacToe(const TicTacToe &) = default;
  TicTacToe &operator=(TicTacToe &&) = default;
  TicTacToe &operator=(const TicTacToe &) = default;

  static torch::TensorOptions optionsNoGrad;
  static torch::TensorOptions optionsNoGradFloat;
  ~TicTacToe();
  bool move(int x, int y);
  bool getPlayer();
  float boardData[3][3]{};
  float scoreData[3][3]{};
  static torch::Tensor diag;
  static torch::Tensor diagReversed;
  torch::Tensor &computeScore();
  torch::Tensor getBoard();
  friend ostream &operator<<(ostream &os, const TicTacToe &dt);
  void reset();
  int player{1};
	int numInvalidMoves{};

private:
  unsigned int numMoves{};
  bool checkLocation(int x, int y);
  torch::Tensor board = torch::from_blob(boardData, {3, 3}, optionsNoGradFloat);
  torch::Tensor score = torch::from_blob(scoreData, {3, 3}, optionsNoGradFloat);
};
