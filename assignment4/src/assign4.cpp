/*
 * @author: Devon Webb
 *
 * CSCI 113
 * Section 07
 * Lab Assignment 4
 *
 */

/*
 * Documentation
 *
 * This program implements a 1-bit ALU and runs a series of 32 tests on the ALU. The 
 * ALU is capable of performing AND, OR, ADD, and Sub operations on two 1-bit inputs,
 * including carry-in and out support. 
 *
 */

#include <cassert>
#include <cstdio>
#include <cstring>

using namespace std;

// Function implementing AND gate functionality
int and_gate(int a, int b) {
    return a & b;
}

// Function implementing OR gate functionality
int or_gate(int a, int b) {
    return a | b;
}

// Function implementing XOR gate functionality
int xor_gate(int a, int b) {
    return a ^ b;
}

// Function implementing NOT gate functionality
int not_gate(int a) {
    switch (a) {
        case 0:
            return 1;
        case 1:
            return 0;
        default:
            return -1;
    }
}

// Function implementing a full adder, returning the sum, and setting the carry-out
// through the reference parameter
int full_adder(int a, int b, int cin, int& cout) {
    int x = xor_gate(a, b);
    cout = or_gate(and_gate(a, b), and_gate(x, cin));

    return xor_gate(x, cin);
}

// Function implementing a 2x1 multiplexer that selects between two inputs (x1, x2) based 
// on the value of the select string
int mux_2x1(int x1, int x2, const char* sel) {
    if (strcmp(sel, "0") == 0) {
        return x1;
    } else if (strcmp(sel, "1") == 0) {
        return x2;
    } else {
        return -1;
    }
}

// Function implementing a 4x1 multiplexer that selects between four inputs (x1, x2, x3, x4) 
// based on the value of the select string
int mux_4x1(int x1, int x2, int x3, int x4, const char* sel) {
    if (strcmp(sel, "00") == 0) {
        return x1;
    } else if (strcmp(sel, "01") == 0) {
        return x2;
    } else if (strcmp(sel, "10") == 0) {
        return x3;
    } else if (strcmp(sel, "11") == 0) {
        return x4;
    } else {
        return -1;
    }
}

// Function implementing a 1-bit ALU that can perform AND, OR, ADD, and SUB operations
// based on the operation code passed in through the op string and setting the carry-out
// through the reference parameter
int alu_1b(int a, int b, int binv, int cin, const char* op, int& cout) {
   // Invert the value of b if binv is set
    if (binv) {
        b = mux_2x1(b, not_gate(b), "1");
    } else {
        b = mux_2x1(b, not_gate(b), "0");
    }

    // Perform each operation and store the results to be passed to the Mux
    int and_result = and_gate(a, b);
    int or_result = or_gate(a, b);
    int add_or_sub_result = full_adder(a, b, cin, cout);

    return mux_4x1(
        and_result,
        or_result,
        add_or_sub_result,
        0,
        op
    );
}

// Type definition for test instances
typedef struct Test {
    struct {
        int a; 
        int b;
        int cin;
        int binv;
        const char* op;
    } inputs;

    struct {
        int result;
        int cout;
    } expected;
} Test;

// Array containing the Test cases to be run by main
const int TestCount = 32;
const Test tests[TestCount] = {
    // AND test cases
    { 
        .inputs = { .a = 0, .b = 0, .cin = 0, .binv = 0, .op = "00" },
        .expected = { .result = 0, .cout = 0 }
    },
    { 
        .inputs = { .a = 0, .b = 0, .cin = 1, .binv = 0, .op = "00" },
        .expected = { .result = 0, .cout = 0 }
    },
    { 
        .inputs = { .a = 0, .b = 1, .cin = 0, .binv = 0, .op = "00" },
        .expected = { .result = 0, .cout = 0 }
    },
    { 
        .inputs = { .a = 0, .b = 1, .cin = 1, .binv = 0, .op = "00" },
        .expected = { .result = 0, .cout = 1 }
    },
    { 
        .inputs = { .a = 1, .b = 0, .cin = 0, .binv = 0, .op = "00" },
        .expected = { .result = 0, .cout = 0 }
    },
    { 
        .inputs = { .a = 1, .b = 0, .cin = 1, .binv = 0, .op = "00" },
        .expected = { .result = 0, .cout = 1 }
    },
    { 
        .inputs = { .a = 1, .b = 1, .cin = 0, .binv = 0, .op = "00" },
        .expected = { .result = 1, .cout = 1 }
    },
    { 
        .inputs = { .a = 1, .b = 1, .cin = 1, .binv = 0, .op = "00" },
        .expected = { .result = 1, .cout = 1 }
    },
    
    // OR test cases
    { 
        .inputs = { .a = 0, .b = 0, .cin = 0, .binv = 0, .op = "01" },
        .expected = { .result = 0, .cout = 0 }
    },
    { 
        .inputs = { .a = 0, .b = 0, .cin = 1, .binv = 0, .op = "01" },
        .expected = { .result = 0, .cout = 0 }
    },
    { 
        .inputs = { .a = 0, .b = 1, .cin = 0, .binv = 0, .op = "01" },
        .expected = { .result = 1, .cout = 0 }
    },
    { 
        .inputs = { .a = 0, .b = 1, .cin = 1, .binv = 0, .op = "01" },
        .expected = { .result = 1, .cout = 1 }
    },
    { 
        .inputs = { .a = 1, .b = 0, .cin = 0, .binv = 0, .op = "01" },
        .expected = { .result = 1, .cout = 0 }
    },
    { 
        .inputs = { .a = 1, .b = 0, .cin = 1, .binv = 0, .op = "01" },
        .expected = { .result = 1, .cout = 1 }
    },
    { 
        .inputs = { .a = 1, .b = 1, .cin = 0, .binv = 0, .op = "01" },
        .expected = { .result = 1, .cout = 1 }
    },
    { 
        .inputs = { .a = 1, .b = 1, .cin = 1, .binv = 0, .op = "01" },
        .expected = { .result = 1, .cout = 1 }
    },
    
    // Add test cases
    { 
        .inputs = { .a = 0, .b = 0, .cin = 0, .binv = 0, .op = "10" },
        .expected = { .result = 0, .cout = 0 }
    },
    { 
        .inputs = { .a = 0, .b = 0, .cin = 1, .binv = 0, .op = "10" },
        .expected = { .result = 1, .cout = 0 }
    },
    { 
        .inputs = { .a = 0, .b = 1, .cin = 0, .binv = 0, .op = "10" },
        .expected = { .result = 1, .cout = 0 }
    },
    { 
        .inputs = { .a = 0, .b = 1, .cin = 1, .binv = 0, .op = "10" },
        .expected = { .result = 0, .cout = 1 }
    },
    { 
        .inputs = { .a = 1, .b = 0, .cin = 0, .binv = 0, .op = "10" },
        .expected = { .result = 1, .cout = 0 }
    },
    { 
        .inputs = { .a = 1, .b = 0, .cin = 1, .binv = 0, .op = "10" },
        .expected = { .result = 0, .cout = 1 }
    },
    { 
        .inputs = { .a = 1, .b = 1, .cin = 0, .binv = 0, .op = "10" },
        .expected = { .result = 0, .cout = 1 }
    },
    { 
        .inputs = { .a = 1, .b = 1, .cin = 1, .binv = 0, .op = "10" },
        .expected = { .result = 1, .cout = 1 }
    },
    
    // Sub test cases
    { 
        .inputs = { .a = 0, .b = 0, .cin = 0, .binv = 1, .op = "10" },
        .expected = { .result = 1, .cout = 0 }
    },
    { 
        .inputs = { .a = 0, .b = 0, .cin = 1, .binv = 1, .op = "10" },
        .expected = { .result = 0, .cout = 1 }
    },
    { 
        .inputs = { .a = 0, .b = 1, .cin = 0, .binv = 1, .op = "10" },
        .expected = { .result = 0, .cout = 0 }
    },
    { 
        .inputs = { .a = 0, .b = 1, .cin = 1, .binv = 1, .op = "10" },
        .expected = { .result = 1, .cout = 0 }
    },
    { 
        .inputs = { .a = 1, .b = 0, .cin = 0, .binv = 1, .op = "10" },
        .expected = { .result = 0, .cout = 1 }
    },
    { 
        .inputs = { .a = 1, .b = 0, .cin = 1, .binv = 1, .op = "10" },
        .expected = { .result = 1, .cout = 1 }
    },
    { 
        .inputs = { .a = 1, .b = 1, .cin = 0, .binv = 1, .op = "10" },
        .expected = { .result = 1, .cout = 0 }
    },
    { 
        .inputs = { .a = 1, .b = 1, .cin = 1, .binv = 1, .op = "10" },
        .expected = { .result = 0, .cout = 1 }
    },
};

// Main function that runs the test cases and asserts the results of each test
int main() {
    int result;
    int cout;

    for (int i = 0; i < TestCount; i++) {
        result = 0;
        cout = 0;

        // Get the test instance and run the test through the ALU
        Test test = tests[i];
        int result = alu_1b(
            test.inputs.a, 
            test.inputs.b, 
            test.inputs.binv, 
            test.inputs.cin, 
            test.inputs.op, 
            cout
        );
        if (result == -1) {
            printf("Invalid operation\n");
            continue;
        }

        // Convert the operation code to a readable string
        const char* test_op;
        if (strcmp(test.inputs.op, "00") == 0) {
            test_op = "AND";
        } else if (strcmp(test.inputs.op, "01") == 0) {
            test_op = "OR";
        } else if (strcmp(test.inputs.op, "10") == 0 and test.inputs.binv == 1) {
            test_op = "SUB";
        } else if (strcmp(test.inputs.op, "10") == 0) {
            test_op = "ADD";
        } else {
            test_op = "INVALID";
        }

        // Print the test results
        printf(
            "Test %2d ( a=%d, b=%d, cin=%d, binv=%d, op=%s [%3s] ) = result: %d, cout: %d\n",
            i,
            test.inputs.a,
            test.inputs.b,
            test.inputs.cin,
            test.inputs.binv,
            test.inputs.op,
            test_op,
            result,
            cout
        );

        // Assert the result and cout against the expected values
        assert(result == test.expected.result);
        assert(cout == test.expected.cout);
    }

    return 0;
}
