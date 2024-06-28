#include "checksum.h"
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>

int fgenChecksum(FILE *file, unsigned int addrCount, const int *addresses) {
	if (addrCount < 2 || addrCount & 1) {
		fprintf(stderr, "Must have a positive even address count.");
		return -1;
	}
	uint16_t checksum = 0;

	for (; addrCount > 0; addresses += 2, addrCount -= 2) {
		assert(addresses[1] > addresses[0]);
		size_t numOfBytes = addresses[1] - addresses[0] + 1;

		uint8_t *buffer = malloc(numOfBytes);
		if (buffer == NULL) {
			perror("malloc");
			return -1;
		}

		// Read (len) num of bytes
		fseek(file, addresses[0], SEEK_SET);
		if (fread(buffer, 1, numOfBytes, file) < numOfBytes) {
			return -1;
		}

		// numOfBytes-- to solve off by one error
		while (numOfBytes-- != 0) {
			checksum += buffer[numOfBytes];
		}

		free(buffer);
	}

	return checksum;
}

int fvalidateChecksum(FILE *file, int expectedChecksum, unsigned int addrCount, const int *addresses) {
	int checksum = fgenChecksum(file, addrCount, addresses);
	if (checksum == -1) {
		fprintf(stderr, "\terror checking save\n");
		return checksum;
	}

	if (checksum != expectedChecksum) {
		return checksum;
	}

	return (checksum == expectedChecksum ? -1 : checksum);
}
