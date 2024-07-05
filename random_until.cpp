//
// Created by apple on 05.07.2024.
//

#include "random_until.h"


std::mt19937 RandomUtil::rng;

void RandomUtil::initializeSeed(unsigned int seed) {
    rng.seed(seed);
}

int RandomUtil::PROJECT_RND(int start, int end) {
    std::uniform_int_distribution<int> dist(start, end);
    return dist(rng);
}

void RandomUtil::shuffle(std::vector<int>::iterator first, std::vector<int>::iterator last) {
    int sz = last - first;
    for (int it = 0; it < last - first; ++it) {
        int step = PROJECT_RND() % sz;
        std::swap(first[it], first[step]);
    }
}

void RandomUtil::shuffle(std::vector<uint32_t>::iterator first, std::vector<uint32_t>::iterator last) {
    int sz = last - first;
    for (int it = 0; it < last - first; ++it) {
        int step = PROJECT_RND() % sz;
        std::swap(first[it], first[step]);
    }
}
