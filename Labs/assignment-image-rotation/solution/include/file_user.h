#include <stdio.h>

enum open_status{
    OPEN_FAILED,
    OPEN_SUCCESS
};

enum close_status{
    CLOSE_FAILED,
    CLOSE_SUCCESS
};

enum open_status print_open(FILE* file);

enum close_status print_close(int status);

enum open_status open_file(FILE** file, const char* path, const char* mode);

enum close_status close_file(FILE** file);
