#include "../include/rotate.h"
#include "stdio.h"

//rotates image
struct image rotate(struct image const* image){
    struct image rotated = create_image(image->width, image->height);
    for(size_t i = 0; i < image->width; i++){
        for(size_t j = 0; j < image->height; j++) {
            rotated.data[image->height*i+(image->height-j-1)] = image->data[i+j*image->width];
        }
    }
    return rotated;
}
