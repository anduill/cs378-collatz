// ----------------------------
// projects/collatz/Collatz.c++
// Copyright (C) 2014
// Glenn P. Downing
// ----------------------------

// --------
// includes
// --------

#include <cassert>  // assert
#include <iostream> // endl, istream, ostream
#include <utility>  // make_pair, pair
//#include "Collatz.h"

// ------------
// collatz_read
// ------------

unsigned int array_cache[4000000] = {0U};


/**
 * read two ints
 * @param a  std::pair<unsigned int, unsigned int> that may, or may not, be ordered.
 * @return a pair of the two ints that are ordered with least-int as first.
 */
std::pair<unsigned int, unsigned int> ordered_pair(std::pair<unsigned int, unsigned int> a_pair){
	unsigned int i = a_pair.first;
	unsigned int j = a_pair.second;
	assert(i >= 1);
	assert(j >= 1);
	unsigned int temp = i;
	if(j < i){
		i = j;
		j = temp;
	}
	assert(i <= j);
	return std::make_pair(i,j);	
}

std::pair<unsigned int, unsigned int> collatz_read (std::istream& r) {
    unsigned int i;
    r >> i;
    if (!r)
        return std::make_pair(0U, 0U);
    unsigned int j;
    r >> j;
	assert(i >= 1);
	assert(j >= 1);	
    return std::make_pair(i, j);
}

/**This implementation uses a very simple c-array for the cache
implementation.  A simple check is utilized to ensure that we
don't inadvertently index outside of the array's bounds.**/
unsigned int get_cycle_length(unsigned int n){
	assert(n >= 1);
	unsigned int cycle_length = 1U;
	/**Obviously, if n==1, then the while loop doesn't run at all.**/
	unsigned int number_of_iterations = 0U;
	unsigned int original_number = n;
	while(n > 1U){
		/**The cache is only utilized if the index is valid**/
		if(n < 4000000){
			unsigned int cached_val = array_cache[n];
			/**All elements of the cache are first initialized to 0...so
			a non-zero entry indicates a valid entry.**/
			if(cached_val != 0U){
				/**the answer must take into account the number of iterations it
				took to get to the present point.**/
				unsigned int answer =  array_cache[n] + number_of_iterations;
				/**This conditional prevents needless updates to the cache in this implementation**/
				if(original_number != n){
					array_cache[original_number] = answer;
				}			
				return answer;
			}
		}		
		if(n%2U == 0U){
			n = n >> 1;			
		}	
		else{
			n = 3*n + 1;
		}
		/**Number of iterations will be offset by 1**/
		number_of_iterations++;
		cycle_length++;		
	}
	array_cache[original_number] = cycle_length;
	assert(cycle_length >= 1);
	return cycle_length;
}

// ------------
// collatz_eval
// ------------

unsigned int collatz_eval (unsigned int i, unsigned int j) {
	assert(i <= j);
	unsigned int count = 1U;
    for(unsigned int k = i; k < j+1U; k++){
    	unsigned int cycle_length = get_cycle_length(k);
		assert(cycle_length >= 1);
		if(cycle_length > count){
			count = cycle_length;
		}
    }
	if(j > 1){
		assert(count > 1);
	}
	assert(count >= 1);
    return count;
}

// -------------
// collatz_print unsigned int
// -------------

void collatz_print (std::ostream& w, unsigned int i, unsigned int j, unsigned int v) {
    w << i << " " << j << " " << v << std::endl;}

// -------------
// collatz_solve
// -------------

void collatz_solve (std::istream& r, std::ostream& w) {
    while (true) {
        const std::pair<unsigned int, unsigned int> p = collatz_read(r);
        if (p == std::make_pair(0U, 0U)){
        	return;
        }
		/**ordered_p is a copy of the original pair but reorders the pair so that
		the smallest integer is in the "first" position and the largest integer
		is in the "second" position.**/
		const std::pair<unsigned int, unsigned int> ordered_p = ordered_pair(p);
		if(p.second < p.first){
			assert(ordered_p.first < ordered_p.second);
		}
        const unsigned int v = collatz_eval(ordered_p.first, ordered_p.second);
        collatz_print(w, p.first, p.second, v);
	}
}

int main () {
    using namespace std;
    collatz_solve(cin, cout);
    return 0;
}
