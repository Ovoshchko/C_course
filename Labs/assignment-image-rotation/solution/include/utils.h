#include "file_user.h"
#include "rotate.h"
#include "stdio.h"

enum resulted{
    OK,
    FAILED
};

enum resulted read_and_save(FILE** file, const char* path, struct image* img);

enum resulted write_and_save(FILE** file, const char* path, struct  image const* img);

void free_images(struct image* im_old, struct image* im_new);
