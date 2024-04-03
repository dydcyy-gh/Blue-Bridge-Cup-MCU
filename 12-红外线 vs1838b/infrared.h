#include "typedef.h"

#ifndef INFRARED_H
#define INFRARED_H

void InitInfrared();
void IRScan();

extern bit irflag;
extern u8 ircode[4];

#endif