#ifndef CHECKSUM_H
#define CHECKSUM_H

#include <stdio.h>

#define PRIMARY_CHECKSUM_LOCATION   0x2d69
#define SECONDARY_CHECKSUM_LOCATION 0x7e6d

int fgenChecksum(FILE *file, unsigned int addrCount, const int *addresses);
int fvalidateChecksum(FILE *file, int expectedChecksum, unsigned int addrCount, const int *addresses);

#endif