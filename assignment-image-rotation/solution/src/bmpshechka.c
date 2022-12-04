#include "../include/bmpshechka.h"
#include "stdint.h"
#include "stdlib.h"

static const char* read_result[] = {
        [READ_OK] = "Read success\n",
        [READ_INVALID_SIGNATURE] = "Invalid signature\n", //not type
        [READ_INVALID_BITS] = "Invalid bits\n",  //size of pixels
        [READ_INVALID_HEADER] = "Invalid header\n",
        [READ_INVALID_SIZE] = "Invalid size\n",
        [DESTROYED_IMAGE] = "READ_ERROR\n"//size of file
};

static const char* write_result[]={
        [WRITE_OK] = "Write success\n",
        [WRITE_ERROR] = "Writing error\n"
};

//check if bmp_header is valid
enum read_status check_header(struct bmp_header const* bmp){
    if(bmp->bfileSize!=bmp->bOffBits+bmp->biSizeImage){
        return READ_INVALID_SIZE;
    }
    if(bmp->bfType!=0x4D42){
        return READ_INVALID_SIGNATURE;
    }
    if(bmp->biBitCount!=24){
        return READ_INVALID_BITS;
    }
    if(bmp->biSize!=40){
        return READ_INVALID_HEADER;
    }
    return READ_OK;
}

//print errors and statuses
enum read_status print_read(enum read_status st){
    fprintf(stderr, "%s", read_result[st]);
    return st;
}

enum write_status print_write(enum write_status st){
    fprintf(stderr, "%s", write_result[st]);
    return st;
}

//creates bmp_header
struct bmp_header create_bmp(struct image const* image){
    struct bmp_header new = (struct bmp_header) {0};
    new.bfType = DEFAULT_Type;
    new.biSize = DEFAULT_biSize;
    new.biBitCount = DEFAULT_PixelCounts;
    new.biHeight = image->height;
    new.biWidth = image->width;
    new.biSizeImage = (new.biWidth*sizeof(struct pixel)+(get_padding(image)))*new.biHeight;
    new.biPlanes = DEFAULT_byPlanes;
    new.bOffBits = sizeof(struct bmp_header);
    new.bfileSize = new.bOffBits + new.biSizeImage;
    return new;
}

//read bmp image from given file
enum read_status from_bmp(FILE* in, struct image* img){
    struct bmp_header* bmp = malloc(sizeof(struct bmp_header));
    fread(bmp, sizeof(struct bmp_header), 1, in);
    enum read_status read_resulted = check_header(bmp);
    if (read_resulted == READ_OK) {
        *img = create_image(bmp->biHeight, bmp->biWidth);
        free(bmp);

        if(!img->data) return DESTROYED_IMAGE;

        uint8_t padding = get_padding(img);
        for (size_t i = 0; i < img->height; i++) {
            size_t res = fread(&(img->data[i * (img->width)]), sizeof(struct pixel), img->width, in);
            if (res == 0) return print_read(DESTROYED_IMAGE);
            fseek(in, padding, SEEK_CUR);
        }
        return print_read(READ_OK);
    } else {
        free(bmp);
        return print_read(read_resulted);
    }
}

//write bmp image to given file
enum write_status to_bmp( FILE* out, struct image const** img ){
    struct bmp_header prepared = create_bmp(*img);
    size_t res = fwrite(&prepared, sizeof(struct bmp_header),1,out);
    if(res==0) {
        return print_write(WRITE_ERROR);
    }

    uint8_t padding = get_padding(*img);
    uint8_t trash[3] = {0,0,0};

    for(size_t i = 0; i < (*img)->height; i++){
        size_t result = fwrite(&((*img)->data[i*(*img)->width]), sizeof(struct pixel), (*img)->width, out );
        if (result!=(*img)->width){
            return print_write(WRITE_ERROR);
        }
        fwrite(&trash, sizeof(uint8_t), padding, out);
    }
    return print_write(WRITE_OK);
}
