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
#include <map>
//#include "Collatz.h"

// ------------
// collatz_read
// ------------
std::map<unsigned int, unsigned int> collatz_cache;

std::pair<unsigned int, unsigned int> ordered_pair(std::pair<unsigned int, unsigned int> a_pair){
	unsigned int i = a_pair.first;
	unsigned int j = a_pair.second;
	
	unsigned int temp = i;
	if(j < i){
		i = j;
		j = temp;
	}
	return std::make_pair(i,j);	
}

std::pair<unsigned int, unsigned int> collatz_read (std::istream& r) {
    unsigned int i;
    r >> i;
    if (!r)
        return std::make_pair(0U, 0U);
    unsigned int j;
    r >> j;	
    return std::make_pair(i, j);
}


unsigned int get_cycle_length(unsigned int n){
	unsigned int cycle_length = 1U;
	while(n > 1U){
		if(n%2U == 0U){
			n = n / 2U;
		}
		else{
			n = n * 3U + 1U;
		}
		cycle_length++;
	}
	return cycle_length;
}

// ------------
// collatz_eval
// ------------

unsigned int collatz_eval (unsigned int i, unsigned int j) {
	unsigned int count = 1U;
    for(unsigned int k = i; k < j+1U; k++){
    	unsigned int cycle_length = get_cycle_length(k);
		if(cycle_length > count){
			count = cycle_length;
		}
    }
    return count;
}

// -------------
// collatz_prunsigned int
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
		const std::pair<unsigned int, unsigned int> ordered_p = ordered_pair(p);
        const unsigned int v = collatz_eval(ordered_p.first, ordered_p.second);
        collatz_print(w, p.first, p.second, v);
	}
}

int main () {
    using namespace std;
    collatz_solve(cin, cout);
    return 0;
}
