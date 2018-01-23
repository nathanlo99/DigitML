
PRIMARY GOALS:
- Make a function which, given the correct label, returns the "perfect" vector.
  - 5 -> [0, 0, 0, 0, 0, 1, 0, 0, 0, 0]
- Implement a cost function, which takes the sum of squares of the differences between the
  "perfect" vector and the computed last layer
- Do some crazy calculus to derive the back-propagation formulas and train our data with gradient
  descent
- MILESTONE 1.0:
  - Have a working three-layer neural network which trains itself

- Output data about accuracy per epoch and tweak constants to get the best results
- ???
- Profit

SECONDARY GOALS:
- Optimize the matrix library and NN class to use valarrays for parallelism
- Memory optimizations, avoid initializing matrices when not necessary
