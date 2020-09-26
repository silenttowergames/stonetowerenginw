#pragma once

#include <FNA3D.h>
#include "color.h"

unsigned int colorU(unsigned char r, unsigned char g, unsigned char b, unsigned char a);
unsigned int colorToU(color c);
FNA3D_Vec4 colorUToFNA(unsigned int);
FNA3D_Vec4 colorToFNA(color c);
