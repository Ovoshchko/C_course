#include "utils.h"
#include <stdio.h>

int main( int argc, char** argv ) {
    if(argc!=3){
        return 2;
    }

    const char* path_input = argv[1];
    const char* path_output = argv[2];

    struct image old_image = {0};

    FILE* file_input = NULL;
    FILE* file_output = NULL;

    //read bmp_file
    enum resulted readed = read_and_save(&file_input, path_input, &old_image);
    if(readed!=OK) {
        return 3;
    }

    struct image new_image = rotate(&old_image);

    //write rotated bmp_image
    enum resulted written = write_and_save(&file_output, path_output,(struct image const*) &new_image);
    if(written!=OK) return 4;

    free_images(&old_image, &new_image);

    return 0;
}
