//
// Created by apple on 05.07.2024.
//

#include "setting.h"


std::mt19937 Setting::rng;
bool Setting::DEBUG;

int64_t Setting::a;
int64_t Setting::b;
int64_t Setting::c;



void Setting::initializeSeed(unsigned int seed) {
    rng.seed(seed);
    a = rng();
    b = rng();
    c = rng();
}

int Setting::PROJECT_RND() {
//    int res = ((a * b + c) >> 32);
//    b = a;
//    a = res;
//    return res;
    return Setting::rng() >> 1;
//    return Setting::rng() % (end - start)
//    std::uniform_int_distribution<int> dist(start, end);
//    return dist(rng);
}

void Setting::shuffle(std::vector<int>::iterator first, std::vector<int>::iterator last) {
    int sz = last - first;
    for (int it = 0; it < last - first; ++it) {
        int step = PROJECT_RND() % sz;
        std::swap(first[it], first[step]);
    }
}

void Setting::shuffle(std::vector<uint32_t>::iterator first, std::vector<uint32_t>::iterator last) {
    int sz = last - first;
    for (int it = 0; it < last - first; ++it) {
        int step = PROJECT_RND() % sz;
        std::swap(first[it], first[step]);
    }
}

void Setting::set_debug(bool debug_flag) {
    Setting::DEBUG = debug_flag;
}


bool Setting::is_debug() {
    return Setting::DEBUG;
}
