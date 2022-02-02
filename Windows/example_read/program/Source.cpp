#include <conio.h>
#include <stdlib.h>
#include <stdio.h>
#include "dynamixel_sdk.h" 
#include "easy_dynamixel.h"

// Don't set an angle to motor 3.
int idarr[] = { 1, 2, 4, 5, 6, 7 };
double angles[] = { 180.3, 71, 272.27, 226.33, 189.16, 129.4 };

// 1 enables Torque
int torque[] = { 0, 0, 0, 0, 0, 0 };
char com[5] = "COM3";

int main() {
	Easydxl edxl(com);
	edxl.setTorqueMult(idarr, torque, 6);
	while (1) {
		double* d;
		d = edxl.getAngleMult(idarr, 6);
		printf("%f, %f, %f, %f, %f, %f \n", d[0], d[1], d[2], d[3], d[4], d[5]);
	}
	return 0;
}
