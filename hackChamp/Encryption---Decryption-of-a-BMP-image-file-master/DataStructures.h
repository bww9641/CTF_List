#ifndef DATASTRUCTURES_H
#define DATASTRUCTURES_H

typedef struct
{
    // blue, green and red color channels
    unsigned char b, g, r;
} pixel;

typedef struct
{
    unsigned int width, height, image_dimensions, padding;
    unsigned char* header;
    pixel *v;
} liniarized_image;

#endif // DATASTRUCTURES_H
