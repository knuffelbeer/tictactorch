#pragma once
#include "tictactoe.h"
#include <cassert>
#include <iostream>
#define NUM_EPOCHS 100
#define BATCH_SIZE 1

using namespace torch::indexing;
// Define a new Module.
struct Net : torch::nn::Module {
  Net();
  torch::Tensor forward(torch::Tensor x);
  torch::nn::Linear fc1{nullptr}, fc2{nullptr}, fc3{nullptr};
};

class DataGenerator {
public:
  DataGenerator();
  DataGenerator(DataGenerator &&) = default;
  DataGenerator(const DataGenerator &) = default;
  DataGenerator &operator=(DataGenerator &&) = default;
  DataGenerator &operator=(const DataGenerator &) = default;
  torch::TensorOptions options;
  ~DataGenerator();
  void reset();
  torch::Tensor computeScore(torch::Tensor &dist);
  void printBoard();
  void move(torch::Tensor &dist);
  torch::Tensor generateSample(int batch_num);
  TicTacToe game;
};
