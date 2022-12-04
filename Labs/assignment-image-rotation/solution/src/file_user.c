#include "../include/file_user.h"

static const char* open_result[]={
        [OPEN_FAILED] = "Was not able to open file\n",
        [OPEN_SUCCESS] = "Open success\n",
};

static const char* close_result[]={
        [CLOSE_FAILED] = "Was not able to close file\n",
        [CLOSE_SUCCESS] = "Close success\n",
};

//print close_file result
enum open_status print_open(FILE* file){
    enum open_status opened = (!file) ? OPEN_FAILED : OPEN_SUCCESS;
    fprintf(stderr, "%s", open_result[opened]);
    return opened;
}

//print close_file result
enum close_status print_close(int status){
    enum close_status closed = (status!=0) ? CLOSE_FAILED : CLOSE_SUCCESS;
    fprintf(stderr, "%s", close_result[closed]);
    return closed;
}

//opens file with given path
enum open_status open_file(FILE** file, const char* path, const char* mode){
    *file = fopen(path, mode);
    return print_open(*file);
}

//closes file with given path
enum close_status close_file(FILE** file){
    return print_close(fclose(*file));
}

