/*
/////////////////////////
// Ferris Whitney 2022 //
/////////////////////////
// easy_dynamixel.cpp /////
///////////////////////////////////////////////////
// Parity cpp file for use with easy_dynamixel.h //
///////////////////////////////////////////////////
*/

// Version Switcher from SDK Example:
#if defined(__linux__) || defined(__APPLE__)
#include <fcntl.h>
#include <termios.h>
#define STDIN_FILENO 0
#elif defined(_WIN32) || defined(_WIN64)
#include <conio.h>
#endif

#include <stdlib.h>
#include <stdio.h>
#include "dynamixel_sdk.h"
#include "easy_dynamixel.h" 

Easydxl::Easydxl(char *com) {
	portHandler = dynamixel::PortHandler::getPortHandler(com);
	packetHandler = dynamixel::PacketHandler::getPacketHandler(2);
	portHandler->openPort();
	portHandler->setBaudRate(1000000);
}

void Easydxl::setLed(int id, int value) {
	packetHandler->write1ByteTxRx(portHandler, id, 65, value, &dxl_error);
}

void Easydxl::setTorque(int id, int value) {
	uint8_t id1 = id;
	uint8_t data = value;
	packetHandler->write1ByteTxRx(portHandler, id, 64, value, &dxl_error);
}
void Easydxl::setTorqueMult(int* id, int* value, int arrlen) {
	dynamixel::GroupSyncWrite groupSyncWrite(portHandler, packetHandler, 64, 1);
	for (int i = 0; i < arrlen; i++) {
		uint8_t torque[1];
		torque[0] = value[i];
		groupSyncWrite.addParam(id[i], torque);
	}
	groupSyncWrite.txPacket();
	groupSyncWrite.clearParam();
}

void Easydxl::setAngle(int id, double angle) {
	uint32_t position = (angle / 0.088);
	packetHandler->write4ByteTxRx(portHandler, id, 116, position, &dxl_error);
}

void Easydxl::setAngleMult(int* id, double* angle, int arrlen) {
	dynamixel::GroupSyncWrite groupSyncWrite(portHandler, packetHandler, 116, 4);
	for (int i = 0; i < arrlen; i++) {
		int32_t dxl_goal_position = (angle[i] / 0.088);
		uint8_t param_goal_position[4];
		param_goal_position[0] = DXL_LOBYTE(DXL_LOWORD(dxl_goal_position));
		param_goal_position[1] = DXL_HIBYTE(DXL_LOWORD(dxl_goal_position));
		param_goal_position[2] = DXL_LOBYTE(DXL_HIWORD(dxl_goal_position));
		param_goal_position[3] = DXL_HIBYTE(DXL_HIWORD(dxl_goal_position));
		groupSyncWrite.addParam(id[i], param_goal_position);
	}
	groupSyncWrite.txPacket();
	groupSyncWrite.clearParam();
}


double Easydxl::getAngle(int id) {
	int32_t a;
	packetHandler->read4ByteTxRx(portHandler, id, 132, (uint32_t*)&a, &dxl_error);
	double angle = (a * 0.088);
	return angle;
}

double *Easydxl::getAngleMult(int *id, int arrlen) {
	dynamixel::GroupSyncRead groupSyncRead(portHandler, packetHandler, 132, 4);
	for (int i = 0; i < arrlen; i++) {
		groupSyncRead.addParam(id[i]);
	}
	groupSyncRead.txRxPacket();
	for (int i = 0; i < arrlen; i++) {
		int32_t a;
		a = groupSyncRead.getData(id[i], 132, 4);
		double angle = (a * 0.088);
		returnDoubleArray[i] = angle;
	}
	return returnDoubleArray;
}

void Easydxl::closePort() {
	portHandler->closePort();
}

int Easydxl::getPosition(int id) {
	int32_t a;
	packetHandler->read4ByteTxRx(portHandler, id, 132, (uint32_t*)&a, &dxl_error);
	int32_t position = (a);
	return position;
}

int *Easydxl::getPositionMult(int *id, int arrlen) {
	for (int i = 0; i < arrlen; i++) {
		int32_t a;
		packetHandler->read4ByteTxRx(portHandler, id[i], 132, (uint32_t*)&a, &dxl_error);
		int32_t position = a;
		returnIntArray[i] = position;
	}
	return returnIntArray;
}

void Easydxl::setPosition(int id, uint32_t value) {
	uint32_t position = value;
	packetHandler->write4ByteTxRx(portHandler, id, 116, position, &dxl_error);
}

void Easydxl::setPositionMult(int* id, uint32_t* value, int arrlen) {
	dynamixel::GroupSyncWrite groupSyncWrite(portHandler, packetHandler, 116, 4);
	for (int i = 0; i < arrlen; i++) {
		uint32_t dxl_goal_position = value[i];
		uint8_t param_goal_position[4];
		param_goal_position[0] = DXL_LOBYTE(DXL_LOWORD(dxl_goal_position));
		param_goal_position[1] = DXL_HIBYTE(DXL_LOWORD(dxl_goal_position));
		param_goal_position[2] = DXL_LOBYTE(DXL_HIWORD(dxl_goal_position));
		param_goal_position[3] = DXL_HIBYTE(DXL_HIWORD(dxl_goal_position));
		groupSyncWrite.addParam(id[i], param_goal_position);
	}
	groupSyncWrite.txPacket();
	groupSyncWrite.clearParam();
}

/*
void Easydxl::setPositionMult(int *id, uint32_t *value, int arrlen) {
	for (int i = 0; i < arrlen; i++) {
		uint32_t position = value[i];
		packetHandler->write4ByteTxRx(portHandler, id[i], 116, position, &dxl_error);
	}
}
*/

void Easydxl::setMode(int id, int mode) {
	packetHandler->write1ByteTxRx(portHandler, id, 11, mode, &dxl_error);
}

void Easydxl::setAcceleration(int id, int value) {
	packetHandler->write4ByteTxRx(portHandler, id, 108, value, &dxl_error);
}

void Easydxl::setMaxVelocity(int id, int value) {
	packetHandler->write4ByteTxRx(portHandler, id, 112, value, &dxl_error);
}

void Easydxl::setVelocityTarget(int id, int value) {
	packetHandler->write4ByteTxRx(portHandler, id, 104, value, &dxl_error);
}

int Easydxl::getVelocity(int id) {
	int32_t a;
	packetHandler->read4ByteTxRx(portHandler, id, 132, (uint32_t*)&a, &dxl_error);
	int32_t velocity = (a);
	return velocity;
}




