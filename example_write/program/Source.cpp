#include <conio.h>
#include <stdlib.h>
#include <stdio.h>
#include "dynamixel_sdk.h" 
#include "easy_dynamixel.h"

// Don't set an angle to motor 3.
int idarr[] = { 1, 2, 4, 5, 6, 7 };
double angles[] = { 180.3, 71, 272.27, 226.33, 189.16, 129.4 };

// 1 enables Torque
int torque[] = { 1, 1, 1, 1, 1, 1 };
char com[5] = "COM3";

int main() {
	Easydxl edxl(com);
	edxl.setTorqueMult(idarr, torque, 6);
	edxl.setAngleMult(idarr, angles, 6);
	edxl.closePort();
	return 0;
}
