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

#include "Collatz.h"

// ------------
// collatz_read
// ------------

std::pair<int, int> collatz_read (std::istream& r) {
    int i;
    r >> i;
    if (!r)
        return std::make_pair(0, 0);
    int j;
    r >> j;
	int temp = i;
	if(j < i){
		i = j;
		j = temp;
	}
    return std::make_pair(i, j);}

int get_cycle_length(int n){
	int cycle_length = 1;
	while(n > 1){
		if(n%2 == 0){
			n = n / 2;
		}
		else{
			n = n * 3 + 1;
		}
	}
} 

// ------------
// collatz_eval
// ------------

int collatz_eval (int i, int j) {
	int count = 1;
    for(int k = i; k < j+1; k++){
    	int cycle_length = get_cycle_length(k);
		if(cycle_length > count){
			count = cycle_length;
		}
    }
    return count;
}

// -------------
// collatz_print
// -------------

void collatz_print (std::ostream& w, int i, int j, int v) {
    w << i << " " << j << " " << v << std::endl;}

// -------------
// collatz_solve
// -------------

void collatz_solve (std::istream& r, std::ostream& w) {
    while (true) {
        const std::pair<int, int> p = collatz_read(r);
        if (p == std::make_pair(0, 0))
            return;
        const int v = collatz_eval(p.first, p.second);
        collatz_print(w, p.first, p.second, v);}}
