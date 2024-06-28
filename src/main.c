#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <getopt.h>

#include "checksum.h"

#define VERSION "v0.1.0"

const int PrimaryAddresses[2] = { 0x2009, 0x2d68 };
const int SecondaryAddresses[6] = { 0x0c6b, 0x17ec, 0x3d96, 0x3f3f, 0x7e39, 0x7e6c };

void usage(void) {
	fprintf(stderr, "Usage: goldsave [OPTIONS]... [FILE]\n\n");
	fprintf(stderr, "OPTIONS: \n\
	-h,	--help		prints this help and exits\n\
	-v,	--version	prints version of program\n\n");
	exit(EXIT_SUCCESS);
}

void version(void) {
	fprintf(stderr, "goldsave " VERSION "\n");
	exit(EXIT_SUCCESS);
}

int getOptions(int argc, char **argv) {
	opterr = 1;
	struct option longOptions[] = {
		{ "help",    no_argument, 0,    'h' },
        { "version", no_argument, 0,    'v' },
        { NULL,      0,           NULL, 0   }
	};
	int index = 0, option = 0, passed = 0;
	while ((option = getopt_long(argc, argv, "+hv", longOptions, &index)) != -1) {

		switch (option) {

		default:
		case '0':
			break;

		case 'h':
			usage();
			break;

		case 'v':
			version();
			break;

		case '?':
			fprintf(stderr, "Ignoring option '%c'\n", optopt);
			break;
		}

		passed++;
	}
	return passed;
}

int main(int argc, char **argv) {
	if (getOptions(argc, argv) == -1)
		return EXIT_FAILURE;

	char *savefilePath = NULL;
	if (optind < argc)
		savefilePath = argv[optind];

	if (savefilePath == NULL) {
		fprintf(stderr, "Please specify a savefile!\n");
		return EXIT_FAILURE;
	}

	FILE *savefile = fopen(savefilePath, "rb");
	if (savefile == NULL) {
		perror(savefilePath);
		return EXIT_FAILURE;
	}


	int fileChecksum = 0, checksum = 0;

	fseek(savefile, PRIMARY_CHECKSUM_LOCATION, SEEK_SET);
	fread(&fileChecksum, 2, 1, savefile);
	printf("Primary: ");

	// fvalidateChecksum returns -1 if successful
	if ((checksum = fvalidateChecksum(savefile, fileChecksum, 2, PrimaryAddresses)) == -1) {
		printf("VALID\n\tchecksum: 0x%x\n", fileChecksum);
	} else {
		printf("INVALID\n\texpected checksum: 0x%x\n\tchecksum on file: 0x%x\n", checksum, fileChecksum);
	}


	fseek(savefile, SECONDARY_CHECKSUM_LOCATION, SEEK_SET);
	fread(&fileChecksum, 2, 1, savefile);
	printf("Secondary: ");

	if ((checksum = fvalidateChecksum(savefile, fileChecksum, 6, SecondaryAddresses)) == -1) {
		printf("VALID\n\tchecksum: 0x%x\n", fileChecksum);
	} else {
		printf("INVALID\n\texpected checksum: 0x%x\n\tchecksum on file: 0x%x\n", checksum, fileChecksum);
	}

	fclose(savefile);
	return EXIT_SUCCESS;
}