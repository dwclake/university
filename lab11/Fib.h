#include <chrono>
#include <tuple>
#include <vector>

using namespace std;
using namespace std::chrono;

// Fibonacci implemented recursively
int fib(int n) {
    if (n <= 1) {
        return n;
    }

    return fib(n - 1) + fib(n - 2);
}

// Fibonacci implemented dynamically
int fib_dyn(int n) {
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

typedef tuple<double, int, double, int> timing;

// Returns the times and values of the two fibonacci functions
timing time_fibonacci(int n) {
    // Time recursive fibonacci
    auto start = high_resolution_clock::now();

    int rec_val = fib(n);

    auto end = high_resolution_clock::now();
    double rec_time = duration_cast<nanoseconds>(end - start).count() / 1000.0;
    
    // Time dynamic fibonacci
    start = high_resolution_clock::now();

    int dyn_val = fib_dyn(n);

    end = high_resolution_clock::now();
    double dyn_time = duration_cast<nanoseconds>(end - start).count() / 1000.0;

    return {rec_time, rec_val, dyn_time, dyn_val};
}

// Runs tests of the fibonacci functions and displays the results
void test_fibonacci() {
    vector<vector<timing>> results(5);

    // Get timings for fibonacci numbers in the sequence [5, 10, 15, 20, 25]
    // running 3 runs for each fibonacci number
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 3; j++) {
            results[i].push_back(
                time_fibonacci((i + 1) * 5)
            );
        }
    }
    
    // Formatting string for displaying results
    const char* outter = R"(
    Fib Number: %d)";

    const char* inner = R"(
        Rec Time: %07.3f microseconds, Result: %d
        Dyn Time: %07.3f microseconds, Result: %d
    )";

    // Display results
    for (int i = 0; i < 5; i++) {
        printf(outter, (i + 1) * 5);
        for (auto time : results[i]) {
            printf(inner, 
                get<0>(time), 
                get<1>(time), 
                get<2>(time),
                get<3>(time)
            );
        }
    }
}

