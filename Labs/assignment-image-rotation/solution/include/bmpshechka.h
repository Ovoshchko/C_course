#include "util_for_structs.h"
#include <stdio.h>

#define DEFAULT_biSize 40
#define DEFAULT_byPlanes 1
#define DEFAULT_PixelCounts 24
#define DEFAULT_Type 0x4D42

enum read_status  {
    READ_OK = 0,
    READ_INVALID_SIGNATURE ,
    READ_INVALID_BITS ,
    READ_INVALID_HEADER,
    READ_INVALID_SIZE,
    DESTROYED_IMAGE
};

enum  write_status  {
    WRITE_OK = 0,
    WRITE_ERROR
};

enum read_status check_header(struct bmp_header const* bmp);

enum read_status print_read(enum read_status st);

enum write_status print_write(enum write_status st);

struct bmp_header create_bmp(struct image const* image);

enum read_status from_bmp( FILE* in, struct image* img );

enum write_status to_bmp( FILE* out, struct image const** img );
