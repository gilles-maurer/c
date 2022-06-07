// By Gilles Maurer
// Progamming and Data Structure
// Strtol

#include <errno.h>
#include <limits.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <ctype.h>

typedef enum { BASE10, BASE8, BASE8_EMPTY, BASE16, BASE16_EMPTY } NoBaseCase;

NoBaseCase find_case_when_base_is_null(const char* nPtr, int i);

bool is_char_valid(char c, int base);

bool is_char_alphanumeric(char c);

int specific_sign(const char* nPtr, int* i);

int handle_base_is_null(const char* nPtr, int* i);

long compute_result(const char* nPtr, int lenght, int index_start, int base, int sign);

void change_endPtr(const char* nPtr, char** endPtr, int addition);

long strtol(const char* nPtr, char** endPtr, int base) {

	if ((base < 2 || base > 36) && base != 0) {
		errno = EINVAL;
		change_endPtr(nPtr, endPtr, 0);
		return 0;
	}

	if (nPtr[0] == '\0') {
		change_endPtr(nPtr, endPtr, 0);
		return 0;
	}

	int i = 0;

	while (!is_char_alphanumeric(nPtr[i])) {
		i++;
	}

	int sign = specific_sign(nPtr, &i);

	if (base == 16 && nPtr[i] == '0' && toupper(nPtr[i + 1]) == 'X') {
		if (is_char_valid(nPtr[i + 2], base)) {
			i = i + 2;
		}
	}

	if (base == 0) {
		base = handle_base_is_null(nPtr, &i);
	}

	int index_start = i;

	while (is_char_valid(nPtr[i], base)) {
		i++;
	}

	int index_end = i;

	int lenght = (index_end - index_start);

	if (lenght == 0) {
		change_endPtr(nPtr, endPtr, 0);
		return 0;
	}

	long result = compute_result(nPtr, lenght, index_start, base, sign);

	change_endPtr(nPtr, endPtr, index_end);
	
	return result;
}

bool is_char_valid(char c, int base) {

	if (c < '0' || c > '9') {
		if (c < 'A' || c > 'Z') {
			if (c < 'a' || c > 'z') {
				return false;
			}
		}
	}

	if (base < 10) {
		if (c - '0' >= base) {
			return false;
		}
	} else {
		if (c - 'a' + 10 >= base) {
			return false;
		}
		if ((c - 'A' + 10 >= base) && (c <= 'Z')) {
			return false;
		}
	}

	return true;
}

bool is_char_alphanumeric(char c) {

	if (c > '!' && c < '~') {
		return true;
	}

	return false;
}

NoBaseCase find_case_when_base_is_null(const char* nPtr, int i) {

	if (nPtr[i] == '0') {

		if (nPtr[i + 1] == 'x' || nPtr[i + 1] == 'X') {

			if (is_char_valid(nPtr[i + 2], 16)) {
				return BASE16;
			} else {
				return BASE16_EMPTY;
			}

		} else {
			if (is_char_valid(nPtr[i + 1], 8)) {
				return BASE8;
			} else {
				return BASE8_EMPTY;
			}
		}
	}
	return BASE10;
}

int specific_sign(const char* nPtr, int* i) {

	int sign = 1;

	if (nPtr[*i] == '-') {
		sign = -1;
		*i = *i + 1;
	}

	if (nPtr[*i] == '+') {
		*i = *i + 1;
	}

	return sign;
}

int handle_base_is_null(const char* nPtr, int* i) {

	NoBaseCase event = find_case_when_base_is_null(nPtr, *i);

	int base = 0; 

	if (event == BASE10) {
		base = 10;
	}
	if (event == BASE8) {
		base = 8;
		*i = *i + 1;
	}
	if (event == BASE8_EMPTY) {
		base = 8;
	}
	if (event == BASE16) {
		base = 16;
		*i = *i + 2;
	}
	if (event == BASE16_EMPTY) {
		base = 16;
	}

	return base;
}

long compute_result(const char* nPtr, int lenght, int index_start, int base, int sign) {
	
	long result = 0;
	long temp;
	int power = lenght - 1;

	for (int j = 0; j < lenght; j++) {

		if (nPtr[index_start + j] <= '9') {
			temp = nPtr[index_start + j] - '0';
		} else if (nPtr[index_start + j] <= 'Z') {
			temp = nPtr[index_start + j] - 'A' + 10;
		} else {
			temp = nPtr[index_start + j] - 'a' + 10;
		}

		if ((result + (long)(sign * temp * pow(base, power)) < 0) &&
			(sign == 1)) {
			errno = ERANGE;
			result = LONG_MAX;
			break;
		}
		if ((result + (long)(sign * temp * pow(base, power)) > 0) &&
			(sign == -1)) {
			errno = ERANGE;
			result = LONG_MIN;
			break;
		}

		result = result + (long)(sign * temp * pow(base, power));
		power--;
	}
	return result; 
}

void change_endPtr(const char* nPtr, char** endPtr, int addition){
	
	if (endPtr != NULL) {
		*endPtr = (char*)(nPtr + addition);
	}
	
}


