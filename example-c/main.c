#include <stdint.h>
#include <stdio.h>
#include "example-ffi.h" // Include the header for the extern function

int main() {
    uint64_t result = add(10, 20); // Call the extern function
    printf("Result: %llu\n", (unsigned long long)result); // Print the result
    return 0;
}