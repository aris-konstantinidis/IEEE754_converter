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
			point += 1 / (double) ((int) (1 << i+1));
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
	printf("Exponent: %d\n", exponent);
    double mantissa = bin_to_point(mantissa_raw, 23) + 1;
	printf("Mantissa: %f\n", mantissa);
	double result;
    if (exponent < 0) { // handle negative exponent
        result = mantissa * ((double)1 / (double) (1 << abs(exponent)));
    } else {
		result = mantissa * (1 << exponent);
	}
	printf("Decimal: %f", result);
	return sign == 0 ? result : -result;

}

int main() {
	ieee754_to_double("01111110111111010110011011111101", 32);
	ieee754_to_double("01101010111111101010001011111110", 32);
	ieee754_to_double("10101011111111101111101111111110", 32);
	ieee754_to_double("00000101111111110101100111111111", 32);
	// unsigned char buffer[32];
	// FILE * fp = fopen("amp-A-000.dat", "r");
	// if (fp == NULL) {
	// 	printf("File not found.");
	// 	return 0;
	// }
	// fread(buffer, sizeof(buffer), 1, fp);
	// for (int i = 0; i < 32; i++) {
	// 	printf("%X", buffer[i]);
	// }
	// return 1;
}
