#ifndef RANDOMGEN_H
#define RANDOMGEN_H

#include <random>

class RandomGen {
public:
    // Constructor to initialize the random number generator
    RandomGen();

    // Function to generate a random integer within a specific range
    int getRandomInt(int lower_bound, int upper_bound);

    // Function to generate a random float within a specific range
    float getRandomFloat(float lower_bound, float upper_bound);

private:
    std::mt19937 gen; // Mersenne Twister engine
};

#endif // RANDOMGEN_H