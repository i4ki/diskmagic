#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include "types.h"

#define MBRSZ 512
#define BOOTLOADER_END 0x01b8
#define P1OFFSET 0x01BE

typedef struct __attribute__ ((packed)) {
	_u8 active;
	_u8 shead;
	_u16 sSectCyl;
	_u8 sysid;
	_u8 ehead;
	_u16 eSectCyl;
	_u32 relsect;
	_u32 totalsect;
} partition_t;

typedef  struct __attribute__ ((packed)) {
	_u8 bootloader[BOOTLOADER_END];
	_u32 diskid;
	_u16 reserved;
	partition_t p[4];
	_u8 magic[2];
} mbr_t;

/* mbr content */
_u8 mbrbytes[MBRSZ];

_u8 readFile(_u8 *);
void printMBR(mbr_t*);

int main(int argc, char **argv) {
	_u8 error = 0;
	mbr_t *mbr;
	
	printf("MBR info v0.1\n");
	printf("Author: Tiago Natel aka i4k\n");
	
	if (argc < 2) {
		fprintf(stderr, "Invalid number of arguments...\n");
		fprintf(stderr, "Usage: %s <mbr-file or disk device>\n", *argv);
		return 1;
	}
	
	printf("Size of mbr struct: %d\n", sizeof(mbr_t));
	
	error = readFile(argv[1]);
	
	if (!error) {
		fprintf(stderr, "Failed to read file\n");
		return 1;
	}
	
	mbr = (mbr_t *) mbrbytes;
	
	printMBR(mbr);
	
	return 0;
}

void printMBR(mbr_t *mbr) {
	_u8 i = 0;
	printf("----- MBR -----\n");
	
	printf("bootloader code: %02x%02x%02x%02x...\n", 
			mbr->bootloader[0], 
			mbr->bootloader[1],
			mbr->bootloader[2],
			mbr->bootloader[3]);
	
	printf("DiskID: %x\n", mbr->diskid);
	
	printf(" ----- Partitions: ------\n");
	
	for(i = 0; i < 4; i++) {
		printf("active=%s, start head=%d, start sector=%d, start cylinder=%d\n",
				mbr->p[i].active == 0x80 ? "yes" : "no",
				mbr->p[i].shead,
				mbr->p[i].sSectCyl & 0x3F,
				mbr->p[i].sSectCyl & 0x3FF);
	}
	
	printf("Magic: %02x%02x\n", mbr->magic[0], mbr->magic[1]);
	
	printf("----- MBR -----\n");
}

_u8 readFile(_u8 *filename) {
	int 	fd, 
		rbytes = 0,
		n = 0;
	
	fd = open(filename, O_RDONLY);
	
	if (-1 == fd) {
		fprintf(stderr, "Failed to open file '%s'\n", filename);
		return 0;
	}
	
	while (rbytes < MBRSZ) {
		n = read(fd, mbrbytes+rbytes, MBRSZ - rbytes);
		printf("read %d\n", n);
		rbytes += n;
	}
	
	printf("file end: %02x%02x\n", mbrbytes[510], mbrbytes[511]);
	
	return 1;
}