/**
 * Name:  Ali Alwaily
 * Date:  5 July 2026
 * About: This program computes the total number of different ways to make value
 *          D given n different coin denominations with values in cents: c1, c2,
 *          ..., cn.
 * Example: If you had the coins: penny (1), nickel (5), and dime (10), there are
 *          NINE different ways to make change for 20 cents:
 *           (i)    20 pennies;
 *           (ii)   15 pennies and 1 nickel;
 *           (iii)  10 pennies and 2 nickels;
 *           (iv)    5 pennies and 3 nickles;
 *           (v)    10 pennies and 1 dime;
 *           (vi)    5 pennies, 1 nickel, and 1 dime;
 *           (vii)   2 nickels and 1 dime;
 *           (viii)  4 nickels; and
 *           (ix)    2 dimes.
 */

#include <iostream>     // loads cout, cin
#include <vector>       // loads cpp dynamic array
using namespace std;    // for easier readability

/**
 * I added a limit because the number would get too big and overflow occurs. A
 *  fix can simply be to change variable types from ``int" to ``double."
 */
#define LIMIT 4200      // Constant

// Function Definition. See Implementation Below.
int Coins(int & D, vector<int> & denoms);

// Main Function; entry point into the program
int main() {
    // Variables
    int D = -1;
    vector<int> denoms = {1, 5, 10, 25, 50, 100};

    // Prompt User Input
    cout << "Type a positive whole number (soft limit: 4,200)" << endl <<
            "(Press CTRL+C to exit program): " << endl;

    // While still recieving user input:
    while(cin >> D){
        // Calculate and Return Value
        if(D >= 0 && D <= LIMIT)
            cout << "There are " << Coins(D,denoms) << " different ways to make "
                     << D << " cents using typical U.S. coin denominations" << endl;
    }
    return 0;   // EOP
}

/**
 * This function computes the total number of different ways to make value D
 *  (PARAM1) given n different coin denominations (PARAM2).
 *  Using the 7-step procedure outlined in README.md:
 *      1. Let V[k,D] be the total number of ways to make D cents using the coins
 *          c_1, ..., c_k.
 *      2. We have two base cases:
 *         (a) V[k,0] = 1 because there is always 1 way to make 0 cents.
 *         (b) V[0,d] = 0 for d > 0 because there is no way to make any positive
 *          amount of cents without any coins.
 *      3. Recurrence: We need to compute the IN and OUT cases. Essentially, we
 *          need to determine whether it is better to include a coin k or not,
 *          and, based off that, we will add up all combinations with coin k
 *          included and coin k excluded.
 *         (a) OUT CASE: There are V[k - 1, D]  ways in excluding coin k.
 *         (b) IN CASE:  There are V[k,D - x_k] ways when including coin k.
 *          FINAL RECURRENCE:   V[k,D] = V[k - 1,D] + V[k,D - x_k]
 *      4. Order: In the inner-loop, go from k = 1 to n, and in the outer-loop,
 *          from D = 1 to n.
 *      5. Final Form: V[n][D] (see return statement)
 *      6. (See the C++ implementation below)
 *      7. (Proof of Correctness not necessary)
 *         Runtime: There are two nested for loops doing a total of n*D
 *          iterations.
 *         The body of the for-loop is constant-time.
 *         So, the total runtime of the function is O(nD).
 * @param D a user-defined integer
 * @param denoms a vector of integers
 * @return integer value of the last square of the tabulation
 */
int Coins(int & D, vector<int> & denoms){
    // Assign the size of denoms[] vector to the variable n
    int n = denoms.size();

    // Define tabulation (aka 2d-vector)
    vector<vector<int>> V(n+1, vector<int>(D+1,0));

    // First Base Case: 1 way to make 0 cents (use no coins)
    for(int i = 0; i <= n; ++i) { V[i][0] = 1; }

    // Second Base Case: there are 0 ways to make 0 cents with 0 coins.
    // (Already handled with vector initialized to 0)

    // Recurrence Relation
    //  Used i, j for simplicity in filling up the table.
    for(int i = 1; i <= n; ++i){
        for(int j = 1; j <= D; ++j){
            // Case 1: Exclude the current coin
            V[i][j] = V[i-1][j];

            // Case 2: Include the current coin (if it fits)
            //  denoms[i-1] is the value of the i-th coin.
            int ithCoin = denoms[i-1];

            // First, make sure the coin isn't too big. Then, add IN case to the
            //  OUT case previously calculated.
            if(j >= ithCoin) { V[i][j] += V[i][j-ithCoin]; }
        }
    }
    return V[n][D]; // Final Form
}
