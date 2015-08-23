#include <stdio.h>
#include <stdint.h>
#include "types.h"

/**
 * Basic GPT data structures
 * 
 *     +-------------------------------------+
 *     |      Protective MBR (see mbr.c)     |
 *     +-------------------------------------+
 *     | Primary GUID partition table header |
 *     +-------------------------------------+
 *     |       GUID Partition entry 1        |
 *     +-------------------------------------+
 *     |       GUID Partition entry 2        |
 *     +-------------------------------------+
 *     |       GUID Partition entry 3        |
 *     +-------------------------------------+
 *     |       GUID Partition entry n        |
 *     +-------------------------------------+
 *     |       GUID Partition entry 128      |
 *     +-------------------------------------+
 *     |         Primary Partition 1 (data)  |
 *     +-------------------------------------+
 *     |         Primary Partition 2 (data)  |
 *     +-------------------------------------+
 *     |         Primary Partition n (data)  |
 *     +-------------------------------------+
 *     |       GUID Partition entry 1        | <- backup
 *     +-------------------------------------+
 *     |       GUID Partition entry 2        | <- backup
 *     +-------------------------------------+
 *     |       GUID Partition entry 3        | <- backup
 *     +-------------------------------------+
 *     |       GUID Partition entry n        | <- backup
 *     +-------------------------------------+
 *     |       GUID Partition entry 128      | <- backup
 *     +-------------------------------------+
 *     |  Backup GUID partition table header | <- backup
 *     +-------------------------------------+
 */
int main(int argc, char **argv) {
	return 0;
}