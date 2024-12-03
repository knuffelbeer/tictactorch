#include "dataClasses.h"
#include <cassert>

#include <iostream>
#define NUM_EPOCHS 100
#define BATCH_SIZE 1
#define BOARD_SIZE_2D 3
#define BOARD_SIZE_1D 9

Net::Net() {
  fc1 = register_module("fc1", torch::nn::Linear(9, 64));
  fc2 = register_module("fc2", torch::nn::Linear(64, 32));
  fc3 = register_module("fc3", torch::nn::Linear(32, 9));
}

torch::Tensor Net::forward(torch::Tensor x) {
  x = torch::relu(fc1->forward(x));
  x = torch::dropout(x, /*p=*/0.5, /*train=*/is_training());
  x = torch::relu(fc2->forward(x));
  x = torch::log_softmax(fc3->forward(x), /*dim=*/1);
  return x.view({-1, 3, 3});
}
using namespace torch::indexing;

torch::Tensor DataGenerator::generateSample(int batch_num) {
  return game.getBoard();
}

void DataGenerator::reset() { game.reset(); }

torch::Tensor DataGenerator::computeScore(torch::Tensor &dist) {
  torch::Tensor &score = game.computeScore();
  torch::Tensor loss = dist * score;
  return torch::sum(loss);
}

void DataGenerator::move(torch::Tensor &dist) {
  auto sorted = torch::argsort(dist.flatten());
  auto maxValues = sorted.accessor<long, 1>();
  assert(maxValues.size(0) == BOARD_SIZE_1D);
  for (int option = 0; option < BOARD_SIZE_1D; option++) {
    long row = maxValues[option] / BOARD_SIZE_2D; // Calculate the row index
    long col = maxValues[option] % BOARD_SIZE_2D; // Calculate the column index
    if (game.move(col, row))
      return;
  }
  throw;
}

DataGenerator::DataGenerator() {
  options = torch::TensorOptions().dtype(torch::kFloat32).requires_grad(true);
}

DataGenerator::~DataGenerator() {}
