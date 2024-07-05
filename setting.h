//
// Created by apple on 05.07.2024.
//

#ifndef ASEARCH_SETTING_H
#define ASEARCH_SETTING_H

#include <random>

class Setting {
public:
    static void initializeSeed(unsigned int seed);
    static int PROJECT_RND();
    static int64_t a, b, c;

    static void shuffle(std::vector<int>::iterator first, std::vector<int>:: iterator second);
    static void shuffle(std::vector<u_int32_t>::iterator first, std::vector<u_int32_t>:: iterator second);

    static void set_debug(bool debug_flag = false);

    static bool is_debug();

private:
    static std::mt19937 rng;
    static bool DEBUG;
};

#endif //ASEARCH_SETTING_H
