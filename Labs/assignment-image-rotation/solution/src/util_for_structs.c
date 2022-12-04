#include "../include/util_for_structs.h"
#include "stdlib.h"

//counts padding of written bmp_file
uint8_t get_padding(struct image const* image){
    return (image->width) % 4 ;
}

//counts size if image
uint32_t count_size(uint32_t height, uint32_t width){
    return height* width * sizeof(struct pixel);
}

//creates new image
struct image create_image(uint32_t height, uint32_t width){
    struct image image_new = {.height = height, .width = width};
    image_new.data = malloc(count_size(height,width));
    return image_new;
}
