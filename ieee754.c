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
    int exponent = bin_to_int(exp_raw, 8) - bias;
    double long mantissa = bin_to_point(mantissa_raw, 23) + 1;
    double long base;
    if (exponent < 0) {
        base = (double long) mantissa * (1 / (1 << exponent));
    }
    printf("%Lf\n", base);
	double long result = ((double long)1 + bin_to_point(mantissa_raw, 23)) * (1 << (bin_to_int(exp_raw, 8) - bias));
    // printf("%Lf\n", result);
    return result;

}

int main() {
	ieee754_to_double("00111111100110011001100110011010", 32);
	return 1;
}
