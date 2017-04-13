#include "common.h"
void int_to_bytes(int n, unsigned char buf[], int start)
{
	buf[start] = n >> 24;
	buf[start + 1] = n >> 16;
	buf[start + 2] = n >> 8;
	buf[start + 3] = n;
}
