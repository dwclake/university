/*
 *  CSCI 115 - 03
 *  Lab N
 *
 *  Devon Webb
 */

#include <cstdio>

int main() {
  const char* str = R"(
    Hello, %s!
  )";

  std::printf(str, "world");
}
