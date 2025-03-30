#include <cstdio>

int fib(int n) {
	int* table = new int[n + 3];
	int result = -1;
	
	table[0] = 0;
	table[1] = 1;
	table[2] = 1;
	
	for (int i = 2; i < n + 3; i++) {
		table[i] = table[i - 1] + table[i - 2];	
	}

	result = table[n];

	delete [] table;
	return result;
}

int main() {
    const char* str = R"(
    Fib %d is %d!
  )";

    std::printf(str, 5, fib(10));
}
