/**
 * Name:  Ali Alwaily
 * Date:  19 July 2026
 * About: This program takes two strings and returns an integer based upon the
 *          extent to which they can be matched up. This is a natural way to
 *          describe "closeness" with strings.
 *              See Algorithms pg. 174-7.
 * Example: Consider the strings 'SHORE' and 'CORE'. Here are two possible
 *          alignments:
 *          (1) COST: 2
 *              S H O R E
 *              C - O R E
 *          As explained in Algorithms, "The cost of an alignment is the number
 *          of columns in which the letters differ" (pg. 174).
 *          Here, 'S' is not the same as 'C' and we needed to add a gap inside
 *          'CORE' in order to align the suffix 'ORE' in both words. We only
 *          needed two modifications, so the cost is 2.
 *          Note that any number of gaps may be added to any string, so:
 *          (2) COST: 4
 *              S H O - R E
 *              C - O R - E
 *          Here, we added many more gaps.
 *          Ultimately, "the *edit distance* between two strings is the cost of
 *          their best possible alignment" (ibid). There is not a better alignment for
 *          'SHORE' and 'CORE' than with a cost of 2.
 * In general: There are three types of modifications we can make: Insertions,
 *          Deletions, and Substitutions (more information below).
 *          There are lots of possible alignments we could make to a string, so
 *          if we were to brute force all possible combinations and find the
 *          minimum cost of all of them, it would take too long (there's a
 *          minimum of 3^n different combinations we would need to check!).
 * NOTE: Other languages that are represented in formats such as UTF-8 don't
 *          work very well with this program! The reason is likely due to the
 *          way other characters are represented, where every character is made
 *          up of more than one byte, unlike ASCII characters.
 */

/**
 * Libraries
 */
#include <iostream>     // loads cout, cin
#include <string>       // loads string functions and data type
using namespace std;    // for readability

/**
 * Function Declarations
 */
// Custom Min() Function
int min(int & n1, int & n2, int n3);

// Custom toUpperCase() Function
void toUpperCase(string & str);

// Function Definition. See Implementation Below.
int editDist(string & s1, string & s2);

/**
 * Main Function; entry point into the program
 */
int main() {
    // Variables
    string str1;
    string str2;

    // Prompt User Input
    cout << "Input two strings:" << endl;
    cin >> str1;
    cin >> str2;

    // To allow for 'number' and 'NUMBER' to be treated the same
    toUpperCase(str1);
    toUpperCase(str2);

    int ed = editDist(str1, str2);

    // Calculate and Return Value
    cout << "The Edit Distance is: " << ed << endl;

    return 0;   // EOP
}

/**
 * Function Definitions
 */
/**
 * editDist() - A function that finds the minimum cost to transform string
 *      s1[1,...,n] to s2[1,...,m] (this notation refers to each character of
 *      strings s1 and s2).
 *
 * -=-=-=-=-=-=-=-=-=-=-=-=-  THE  SEVEN  DP  STEPS  -=-=-=-=-=-=-=-=-=-=-=-=-
 * (1) Let E[i,j] be the minimum number of changes necessary to change
 *      s1[1,...,n] to s2[1,...,m].
 * (2) We have two base cases:
 *      (a) E[0,j] = j because when the first word is empty, then the edit
 *          distance is the length of the second word.
 *      (b) E[i,0] = i because when the second word is empty, then the edit
 *          distance is the length of the first word.
 * (3) To find the minimum cost of two words s1[1,...,n] and s2[1,...,m], we
 *      have essentially three cases (for this to work, we are considering
 *      the changes we make to the right-most column, see Algorithms pg. 175
 *      for more details):
 *      (a) Insertion:    E[i,j] = E[i, j-1] + 1. This basically means we
 *          need to insert a gap (that's where the +1 comes from) to align
 *          s1[1,...,i] with s2[1,...,j-1].
 *      (b) Deletion:     E[i,j] = E[i-1, j] + 1. This basically means we
 *          insert a gap to align s1[1,...,i-1] with s2[1,...,j].
 *      (c) Substitution: E[i,j] = {
 *                                  E[i-1, j-1] + 0  if  x_i == y_j
 *                                  E[i-1, j-1] + 1  if  x_i != y_j
 *                                 } (piecewise function)
 *          Essentially, this means if the current character of both strings
 *          are equal, take the value of the previous square diagonally up and
 *          to the left. If they are NOT equal, look at the value of the
 *          square up and to the left, and add 1.
 *      Then, we have to find the minimum of these three cases. Therefore, our
 *      final recurrence relation is:
 *          IF  x_i == y_j, then min(E[i,j-1]+1,  E[i-1,j]+1,  E[i-1,j-1]+0)
 *       OR IF  x_i != y_j, then min(E[i,j-1]+1,  E[i-1,j]+1,  E[i-1,j-1]+1)
 * (4) To calculate E[i,j] we need to know E[i,j-1], E[i,j-1], and E[i-1,j-1],
 *      which are the squares to the left, up, and up-and-to-the-left. One way
 *      of doing this is by filling in the table left to right, top to bottom
 *      (as you would read a book, from left to right!). So, we would have two
 *      for-loops: from i = 1 to n, and from j = 1 to m.
 * (5) Our final form will be E[n,m], which is the bottom right-most value.
 * (6) (See C++ implementation below)
 * (7) (Proof of Correctness not necessary)
 *      Runtime: Let us only take the nested for-loop that takes care of the
 *          recurrence relation into consideration because we are confident
 *          that it dominates the other for-loops as the lengths of str1 and
 *          str2 approach infinity:
 *          Inside, we run substr() twice, which is linear with respect to the
 *          length of the substring, which is 1 in my code below, so this step
 *          should run in constant time. Then, comparing two strings of length
 *          1 should run in constant time. Finally, my min() function also
 *          runs in constant time, so this will be
 *                          O(n^2 * (1+1+2)) = O(4*n^2) = O(n^2)
 *
 * @param s1 the first string, passed by as reference
 * @param s2 the second string, passed by as reference
 * @return integer, the "edit distance" of the two strings
 */
int editDist(string & s1, string & s2){
    //
    int len1 = s1.size(), len2 = s2.size();

    // Define tabulation (aka 2d-vector) and initialize all values to 1
    int E[len1+1][len2+1];
    // initialize array
    for(int i = 0; i <= len1; ++i){
        for(int j = 0; j <= len2; ++j){
            E[i][j] = -1;
        }
    }

    // Base Cases
    for(int i = 0; i <= len1; ++i) { E[i][0] = i; }
    for(int j = 0; j <= len2; ++j) { E[0][j] = j; }

    // Recurrence Relation
    for(int i = 1; i <= len1; ++i){
        for(int j = 1; j <= len2; ++j){
            // Get the appropriate character
            string char1 = s1.substr(i-1,1);
            string char2 = s2.substr(j-1,1);
            // Compute the three different cases
            int case1 = E[i][j-1] + 1;
            int case2 = E[i-1][j] + 1;
            int case3 = E[i-1][j-1];
            // If the two characters are not equal, add one and find the min
            if(char1.compare(char2) == 0)
                E[i][j] = min(case1, case2, case3);
            else
                E[i][j] = min(case1, case2, (case3+1));
        }
    }

    // Final Form
    return E[len1][len2];
}

/**
 * min() - This function takes in three integers and computes the minimum value
 *  between them. First, it looks at the first two parameters. Whichever value
 *  is less is assigned to the temporary variable min. Then, compare n3 with
 *  min. Return the smaller value, or if they are equal, return n3.
 *
 * Proof of Correctness: Let M be the minimum value between n1, n2, and n3.
 * Case 1: If n1 == n2 == n3, then the minimum value returned may be either one
 *  of n1, n2, or n3. In my function below, n3 is returned, so my function works
 *  as expected.
 * Case 2: If n1 is the minimum value, n2 may be equal or less than or greater
 *  than n3. In any case, n1 must be returned. In my function, when n1 is less
 *  than n2, min is assigned n1. Then, when min is less than n3, min is returned
 *  as expected.
 * Case 3: If n2 is the minimum value, n2 must be returned. In my function, when
 *  n2 < n1, min is assigned the value of n2. Then, when min is compared with n3,
 *  min is obviously less than n3, so min is returned as expected.
 * Case 4: If n3 is the minimum value, n1 may be equal or less than or greater
 *  than n2. In any case, min will be assigned to the smaller value between n1
 *  and n2. Then, my function will compare min and n3. Because n3 is less than
 *  min, return n3 as expected. Q.E.D.
 *
 * Runtime: O(1) because all we need to do is comparisons with if-statements.
 *
 * @param n1 the first integer to be compared, passed by as reference
 * @param n2 the second integer to be compared, passed by as reference
 * @param n3 the third integer to be compared. We do not pass this integer by
 *      as reference like we do for n1 and n2 because editDist() may add 1 or
 *      not to it.
 * @return the minimum-valued paramater
 */
int min(int & n1, int & n2, int n3){
    // Initialize an integer called min with the value -1
    int min = -1;
    // If n1 is less than n2, let min be n1. Otherwise, let min be n2
    if(n1 < n2)
        min = n1;
    else
        min = n2;
    /**
     * If min (the minimum value between n1 and n2) be less than n3, then
     *  return min. Otherwise, it must mean that n3 is less than or equal
     *  to min, so return n3
     */
    if(min < n3)
        return min;
    else
        return n3;
}

/**
 * toUpperCase() - transforms all lowercase characters within a string to
 *  uppercase.
 *
 * Runtime: Let N be the length of str. Then, the runtime of this function is
 *  O(N) because the for-loop runs as many times as the length of str is. The
 *  inside of the for-loop runs in constant time.
 *
 * @param str a string passed by as reference
 */
void toUpperCase(string & str){
    // For every lowercase character, turn it into an uppercase (ASCII math)
    for(char & c : str){
        if(c >= 'a' && c <= 'z')
            c -= 32;
    }
}
