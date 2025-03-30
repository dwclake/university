/*
 *  CSCI 115 - 03
 *  Lab 15
 *
 *  Devon Webb
 */

#include "Queue.h"

namespace Queue {
    // Prints list to terminal
    template <>
    void Priority<std::tuple<char, double>>::debug() {
        if ( !this->head ) {
            std::printf("[]\n");
            return;
        }

        std::stringstream ss;

        for ( auto node = this->head; node; node = node->next ) {
            char c;
            double d;
            std::tie(c, d) = node->data;

            ss << "[" << c << ", " << d << "]" << std::endl;
        }

        std::printf("%s\n", ss.str().c_str());
    }
}