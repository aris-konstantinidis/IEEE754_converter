#include <stdio.h>
#include <stdlib.h>
#include <string.h>

long unsigned bin_to_int(char bin[], int size) {
	long unsigned dec = 0;
	for (int i = 0; i < size; i++) {
		if (bin[size-i-1] == '1') {
			dec += 1 << i;
		}
	}
	return dec;	
}

double long bin_to_point(char bin[], int size) {
	double long point = 0;
	int i;
	for (i = 0; i < size; i++) {
		if (bin[i] == '1') {
			point += (double long) 1 / (double) ((int) (1 << i+1));
		}
	}
	return point;
}

double long ieee754_to_double(char bin[], int size) {
	int bias = 127;
	int sign = (int)bin[0] - 48; // converts char to int via ascii code 
	char exp_raw[8];
	char mantissa_raw[23];
	for (int i = 0; i < size - 1; i++) {
		 if (i < 8) {
			 exp_raw[i] = bin[i + 1];
		 } else {
			 mantissa_raw[i - 8] = bin[i + 1];
		 }
	}
	return ((double long)1 + bin_to_point(mantissa_raw, 23)) * (1 << (bin_to_int(exp_raw, 8) - bias));

}

int main() {
	ieee754_to_double("01000000011010100011110101110001", 32);
	return 1;
}
