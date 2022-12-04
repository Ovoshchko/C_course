#include "../include/utils.h"

// try to open and read bmp. created function just for comfort so you should not write this pattern every time you read bmp
enum resulted read_and_save(FILE** file, const char* path, struct image* img){
    if(open_file(file, path, "rb")!=OPEN_SUCCESS) return FAILED;

    if(from_bmp(*file, img)!=READ_OK){
        close_file(file);
        return FAILED;
    }

    if(close_file(file)!=CLOSE_SUCCESS) return FAILED;

    return OK;
}

//open and write file
enum resulted write_and_save(FILE** file, const char* path, struct  image const* img){
    if (open_file(file, path, "wb")!=OPEN_SUCCESS) return FAILED;

    if(to_bmp(*file, &img)!=WRITE_OK) {
        close_file(file);
        return FAILED;
    }

    if(close_file(file)!=CLOSE_SUCCESS) return FAILED;

    return OK;
}

void free_images(struct image* im_old, struct image* im_new){
    free(im_old->data);
    free(im_new->data);
}
