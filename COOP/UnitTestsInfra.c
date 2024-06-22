#include "UnitTestsInfra.h"

#include <stdio.h>
#include <stdarg.h>

const char* out_file_path = "results.json";
int __NUM_TESTED_CLASSES__ = 0;
double __ACCAMULATED_SUITES_GRADE__ = 0;

void double_print(const char* const format, ...) {
	FILE* results_file = fopen(out_file_path, "a");
	
	va_list args;

	// Start variadic arguments processing for printf
	va_start(args, format);
	vprintf(format, args);
	va_end(args);
	if (results_file) {
		// Start variadic arguments processing for fprintf
		va_start(args, format);
		vfprintf(results_file, format, args);
		va_end(args);
	}

	if (results_file)
		fclose(results_file);
}


double my_ceil(double num) {
	int int_part = (int)num;
	if (num > 0 && num != int_part) {
		return int_part + 1;
	}
	else {
		return int_part;
	}
}

