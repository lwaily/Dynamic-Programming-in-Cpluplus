/**
 * Name:  Ali Alwaily
 * Date:  25 June 2026
 * About: This program takes an integer as input from the user and computes its
 *          Fibonacci number using Dynamic Programming, since the common recursive
 *          function is extremely time-consuming (it runs in exponential time).
 */

#include <iostream>
#include <vector>
using namespace std;

// Function Declarations
unsigned int fib_DP(unsigned int n);

// Main function
int main(){
    unsigned int input;
    cout << "Insert a positive integer: ";
    cin >> input;
    cout << "The " << input << "-Fibonacci number is: "
            << fib_DP(input) << endl;
    return 0;
}

/**
 * This function calculates the n-Fibonacci number using Dynamic Programming for
 *	asymptotic-efficiency
 * Runtime: Linear Time, with the assumption that the addition inside of the
 *  for-loop runs in constant time. Then, the for-loop runs n times.
 *  If the addition took linear time instead, which would be necessary for
 *  extremely precise calculation, then the Runtime would be O(n^2).
 */
unsigned int fib_DP(unsigned int n){
    vector<unsigned int> fib_array;
    // Base Cases
    fib_array.push_back(1); // F(0) = 1
    fib_array.push_back(1); // F(1) = 1
    // Recurrence
    for(unsigned int i = 2; i <= n; ++i){
        fib_array.push_back(fib_array[i-1] + fib_array[i-2]);
    }
    return fib_array[n];
}
