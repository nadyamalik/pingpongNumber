/*
 * pa1.cpp
 *
 *  Created on: Oct 6, 2019
 *      Author: user
 */
//============================================================================
// Name        : pa1_skeleton.cpp
// Author      : liuhao
// Version     : PA1 COMP2011 Fall 2019
// Copyright   : COMP2011 teaching team
// Description : Ping-pong number
//============================================================================

#include <iostream>
using namespace std;

/**
 * Task 1
 * This function returns a boolean value indicating whether the input n is a ping-pong number
 * The input n is a non-negative integer
 * Single digits are ping-pong numbers
 */
int num_digits(int n){
	int count = 1;
	while(n/10 != 0){
		n /= 10;
		++count;
	}
	return count;
}



bool is_pingpong(int n) {
	// TODO: start your coding here

	while(num_digits(n) >= 2){
		if(num_digits(n) == 2){
			if(((n % 10) - (n / 10) != 1) && ((n % 10) - (n / 10) != -1))
				return false;
		}
		else if(num_digits(n) > 2){
			if(((n % 10) - ((n/10)%10) != 1) && ((n % 10) - ((n/10)%10) != -1))
				return false;
		}
		n = n/10;
	}

	return true;
}



/**
 * Task 2
 * This function prints all the ping-pong number in range [m, n] five in a row in ascending order
 * Inputs m and n are non-negative integers, and m < n
 * m and n are included in the range
 * Use cout for print
 * The numbers printed within a row is separated by a space (" ")
 * Additional spaces are allowed at the beginning or end of each row, but not allowed between numbers printed
 * Additional newlines are allowed at the beginning or end of all the output, but not allowed in the middle
 * Make sure nothing else is printed out
 */
void print_pingpong(int m, int n) {
	// TODO: start your coding here
	bool isPingPong;
	int count = 0;
	while(m != n){
		isPingPong = is_pingpong(m);
		if(isPingPong){
			cout << m;
			++count;
			if(count != 5)
				cout << " ";
			else{
				cout << endl;
				count = 0;
			}
		}
		++m;
	}
}

/**
 * Task 3
 * This function prints the ping-pong number counting histogram in range [m, n]
 * Inputs m and n are non-negative integers, num_bins is a positive integer, m < n
 * First split the range [m, n] into (num_bins) bins
 * E.g. [0, 10002] into 5 bins: [0, 1999], [2000, 3999], [4000, 5999], [6000, 7999], [8000, 10002]
 * Except for the last bin, each bin contains floor((n - m + 1)/num_bins) numbers
 * Last bin must end at n, and it might have more elements
 * For each bin range, first count the number of ping-pong numbers, denoted by count
 * if count == 0, bin is empty, print a blank row
 * else print a row of ceiling(count / 10) bar_chars (e.g. '*')
 * After each print of a bin, a newline should be inserted
 * Additional newlines are allowed after the last bin
 */
void print_pingpong_histogram(int m, int n, int num_bins, char bar_char) {
	// TODO: start your coding here
	int rangeBin = (n - m + 1) / num_bins;
	int count = 0;
	int num_pingpong = 0;
	int final_num = n;
	n = m + rangeBin - 1;

	while(n != final_num){
		if (num_bins == 1){
			n = final_num;
		}

		for(int j = m; j <= n; ++j){
			if(is_pingpong(j)){
				num_pingpong++;
			}
		}
		num_bins--;

		//count
		if(num_digits(num_pingpong) == 1 && num_pingpong != 0){
			count = 1;
		}
		else{
			if(num_pingpong % 10 >= 5)
				count = num_pingpong / 10 + 1;
			else
				count = num_pingpong / 10;
		}

		//print
		for(int i = 0; i < count; ++i){
				cout << bar_char;
		}

		m = n + 1;
    if(num_bins != 0){
		  n = m + rangeBin - 1;
		  cout << endl;
    }
    num_pingpong = 0;
	}
}

/**
 * Task 4
 * This function returns k-th digit of a non-negative integer n from right
 * The rightmost digit has index 1
 * k can be any integer
 * Returns -1 if given index k is out of bound (i.e. k <= 0 or k is larger than the total number of digits of n)
 */
int kth_digit_from_right(int n, int k) {
	// TODO: start your coding here
	int digits = num_digits(n);
	int number;

	if(k < 1 || k > digits)
		return -1;

	for(int i = k; i > 1; --i){
		n /= 10;
	}
	number = n % 10;

	return number;
}

/**
 * Task 5
 * Check whether n is a generalized ping-pong number with given step and digit-diff
 * n >= 0, diff >= 0, and step > 0
 */
bool is_generalized_pingpong(int n, int step, int diff) {
	// TODO: start your coding here
	if(num_digits(n) == 1 || step >= num_digits(n))
		return true;

	for(int k = 1; k <= (num_digits(n) - step); ++k){
		int sampel1 = kth_digit_from_right(n,k);
		int sampel2 = kth_digit_from_right(n,k+step);
		if((sampel1 - sampel2) != diff && (sampel2 - sampel1) != diff)
			return false;
	}

	return true;
}

int main() {
	cout << "----------------------------------------------------------------------" << endl;
	cout << "Welcome to the Main program of Assignment 1" << endl;
	cout << "You can check whether your code works properly with our below examples" << endl;
	cout << "----------------------------------------------------------------------" << endl;

	cout << boolalpha;
	cout << endl;
	cout << "1. Check whether a given number is a ping-pong number" << endl;
	cout << "Is 3 a ping-pong number: " << is_pingpong(3) << endl;
	cout << "Is 10 a ping-pong number: " << is_pingpong(10) << endl;
	cout << "Is 14 a ping-pong number: " << is_pingpong(14) << endl;
	cout << "Is 100 a ping-pong number: " << is_pingpong(100) << endl;
	cout << "Is 101 a ping-pong number: " << is_pingpong(101) << endl;
	cout << "Is 656787 a ping-pong number: " << is_pingpong(656787) << endl;
	cout << "----------------------------------------------------------------------" << endl;

	cout << endl;
	cout << "2. Print all the ping-pong numbers from 0 to 100" << endl;
	print_pingpong(0, 100);
	cout << endl;
	cout << "----------------------------------------------------------------------" << endl;

	cout << endl;
	cout << "3.1 Print the ping-pong histogram from 0 to 10000 with 5 bins" << endl;
	print_pingpong_histogram(0, 10000, 5, '*');
	cout << endl;

	cout << "3.2 Print the ping-pong histogram from 20 to 52 with 6 bins" << endl;
	print_pingpong_histogram(20, 52, 6, '#');
	cout << endl;
	cout << "----------------------------------------------------------------------" << endl;

	cout << endl;
	cout << "4. Find the k-th digit" << endl;
	cout << "The first digit of 76: " << kth_digit_from_right(76, 1) << endl;
	cout << "The 4-th digit of 654321: " << kth_digit_from_right(654321, 4) << endl;
	cout << "The 8-th digit of 30283: " << kth_digit_from_right(30283, 8) << endl;
	cout << "The (-2)-th digit of 30283: " << kth_digit_from_right(30283, -2) << endl;
	cout << "----------------------------------------------------------------------" << endl;

	cout << endl;
	cout << "5. Check whether a given number is a (step, diff)-ping-pong number" << endl;
	cout << boolalpha;
	cout << "Is 3 a (2, 2)-ping-pong number: " << is_generalized_pingpong(3, 2, 2) << endl;
	cout << "Is 4455463 a (2, 1)-ping-pong number: " << is_generalized_pingpong(4455463, 2, 1) << endl;
	cout << "Is 4061806 a (2, 2)-ping-pong number: " << is_generalized_pingpong(4061806, 2, 2) << endl;
	cout << "Is 12345 a (4, 4)-ping-pong number: " << is_generalized_pingpong(12345, 4, 4) << endl;
	cout << "----------------------------------------------------------------------" << endl;
}



