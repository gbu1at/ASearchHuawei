//
// Created by apple on 05.07.2024.
//

#ifndef ASEARCH_RANDOM_UNTIL_H
#define ASEARCH_RANDOM_UNTIL_H

#include <random>

class RandomUtil {
public:
    static void initializeSeed(unsigned int seed);
    static int PROJECT_RND(int start = 0, int end = INT32_MAX);

    static void shuffle(std::vector<int>::iterator first, std::vector<int>:: iterator second);
    static void shuffle(std::vector<u_int32_t>::iterator first, std::vector<u_int32_t>:: iterator second);


private:
    static std::mt19937 rng;
};

#endif //ASEARCH_RANDOM_UNTIL_H
