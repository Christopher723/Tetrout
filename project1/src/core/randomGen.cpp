#include "randomGen.h"

// Constructor to initialize the random number generator
RandomGen::RandomGen() {
    std::random_device rd;
    gen = std::mt19937(rd());
}

// Function to generate a random integer within a specific range
int RandomGen::getRandomInt(int lower_bound, int upper_bound) {
    std::uniform_int_distribution<> distr(lower_bound, upper_bound);
    return distr(gen);
}

// Function to generate a random float within a specific range
float RandomGen::getRandomFloat(float lower_bound, float upper_bound) {
    std::uniform_real_distribution<> distr(lower_bound, upper_bound);
    return distr(gen);
}