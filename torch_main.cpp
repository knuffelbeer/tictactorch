#include "dataClasses.h"

int main(int argc, char *argv[]) {
  // torch::autograd::AnomalyMode::set_enabled(true);
  float tensie[3] = {2, 3, 4};
  torch::Tensor foo = torch::from_blob(tensie, {3, 1});
  auto net = std::make_shared<Net>();
  torch::optim::SGD optimizer(net->parameters(), /*lr=*/0.01);
  DataGenerator game;
  for (int epoch = 0; epoch < NUM_EPOCHS; epoch++) {
    for (int num_batch = 0; num_batch < BATCH_SIZE; num_batch++) {
      optimizer.zero_grad();
      torch::Tensor sample =
          game.generateSample(num_batch).clone().set_requires_grad(true);
      torch::Tensor prediction = net->forward(sample.flatten().unsqueeze(0));

      prediction = prediction.squeeze();
      torch::Tensor loss = -game.computeScore(prediction);
      /*std::cout << "Epoch: " << epoch << " | Batch: " << " | Loss: " << loss*/
      /*          << "tensor" << prediction << "sample" << sample <<
       * std::endl;*/
      loss.backward();
      torch::nn::utils::clip_grad_norm_(net->parameters(), 100);
      game.move(prediction);
      // Update the parameters based on the calculated
      // gradients.result.item<float>()
      optimizer.step();
      if (epoch % 10 == 0) {
        std::cout << game.game.numInvalidMoves;
        std::cout << loss;
        game.game.numInvalidMoves = 0;
				std::cout << "sample: \n" << sample << '\n';
				
				std::cout << "prediction: \n" << prediction << '\n';
				
      }
    }
  }
  return 0;
}
