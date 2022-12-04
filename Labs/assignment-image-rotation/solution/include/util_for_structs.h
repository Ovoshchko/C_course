#include "structures.h"

uint8_t get_padding(struct image const* image);

uint32_t count_size(uint32_t height, uint32_t width);

struct image create_image(uint32_t height, uint32_t width);
