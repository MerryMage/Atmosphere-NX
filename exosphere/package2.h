#ifndef EXOSPHERE_PACKAGE2_H
#define EXOSPHERE_PACKAGE2_H

/* This is code responsible for validating a package2. Actual file reading is done by bootloader. */

#include <stdint.h>
#include "bootconfig.h"

/* Physaddr 0x40002EF8 */
#define MAILBOX_NX_BOOTLOADER_SETUP_STATE (*((volatile uint32_t *)(0x1F009FEF8ULL)))

#define NX_BOOTLOADER_STATE_INIT 0
#define NX_BOOTLOADER_STATE_MOVED_BOOTCONFIG 1
#define NX_BOOTLOADER_STATE_LOADED_PACKAGE2 2
#define NX_BOOTLOADER_STATE_FINISHED 3 

/* Physaddr 0x40002EFC */
#define MAILBOX_NX_BOOTLOADER_IS_SECMON_AWAKE (*((volatile uint32_t *)(0x1F009FEFCULL)))

#define NX_BOOTLOADER_BOOTCONFIG_POINTER ((void *)(0x4003D000ULL))

#define NX_BOOTLOADER_PACKAGE2_LOAD_ADDRESS ((void *)(0xA9800000ULL))

#define DRAM_BASE_PHYSICAL (0x80000000ULL)

#define MAGIC_PK21 (0x31324B50)
#define PACKAGE2_SIZE_MAX 0x7FC000
#define PACKAGE2_SECTION_MAX 0x3

#define PACKAGE2_MINVER_THEORETICAL 0x0
#define PACKAGE2_MAXVER_100 0x2
#define PACKAGE2_MAXVER_200 0x3
#define PACKAGE2_MAXVER_300 0x4
#define PACKAGE2_MAXVER_302 0x5
#define PACKAGE2_MAXVER_400_CURRENT 0x6

#define PACKAGE2_MINVER_100 0x3
#define PACKAGE2_MINVER_200 0x4
#define PACKAGE2_MINVER_300 0x5
#define PACKAGE2_MINVER_302 0x6
#define PACKAGE2_MINVER_400_CURRENT 0x7


#pragma pack(push, 1)
typedef struct {
    union {
        uint8_t ctr[0x10];
        uint32_t ctr_dwords[0x4];
    };
    uint8_t section_ctrs[4][0x10];
    uint32_t magic;
    uint32_t entrypoint;
    uint32_t _0x58;
    uint8_t version_max; /* Must be > TZ value. */
    uint8_t version_min; /* Must be < TZ value. */
    uint16_t _0x5E;
    uint32_t section_sizes[4];
    uint32_t section_offsets[4];
    uint8_t section_hashes[4][0x20];
} package2_meta_t;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct {
    uint8_t signature[0x100];
    union {
        package2_meta_t metadata;
        uint8_t encrypted_header[0x100];
    };
} package2_header_t;
#pragma pack(pop)

void load_package2(void);

#endif