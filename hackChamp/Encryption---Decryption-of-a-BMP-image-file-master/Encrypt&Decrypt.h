#ifndef ENCRYPT_DECRYPT_IMAGE_H
#define ENCRYPT_DECRYPT_IMAGE_H
#include <stdio.h>
#include "DataStructures.h"
#include "Save&Load.h"
#include "Algorithms.h"

void encryptImage(unsigned char* image_path, unsigned char* image_destination_path, unsigned char* secret_key)
{
    liniarized_image original_image, encrypted_image;
    original_image = loadImage(image_path);
    unsigned long int i, *xorshift32_array, *permutation_array, starting_value, *memory_test;
    unsigned char *memory_test1 = NULL;
    pixel *aux, *memory_test2 = NULL;

    memory_test1 = (unsigned char*) malloc(54 * 1);
    if (memory_test1 != NULL) {
        encrypted_image.header = memory_test1;
        memory_test1 = NULL;
    }
    else {
        printf("The memory did not allocate correctly!");
        exit(0);
    }

    memory_test2 = (pixel*) malloc(((original_image.image_dimensions - 54) * 1));
    if (memory_test2 != NULL) {
        encrypted_image.v = memory_test2;
        memory_test2 = NULL;
    }
    else {
        printf("The memory did not allocate correctly!");
        exit(0); // astea
    }

    FILE *fout = fopen ((const char*) image_destination_path, "wb+");
    if (fout == NULL) {
        printf("\nFile %s did not load correctly!\n", image_destination_path);
        exit(0);
    }

    FILE *f_secret_key = fopen ((const char*) secret_key, "r");
    if (f_secret_key == NULL)
    {
        printf("\nFile %s did not load correctly!\n", secret_key);
        exit(0);
    }

    memory_test = (unsigned long int*) malloc(original_image.width * original_image.height * 2 * sizeof(unsigned long int) + 1);
    if (memory_test != NULL) {
        xorshift32_array = memory_test;
        memory_test = NULL;
    }
    else {
        printf("The memory did not allocate correctly!");
        exit(0);
    }

    fscanf(f_secret_key, "%lu", &xorshift32_array[0]);
    fscanf(f_secret_key, "%lu", &starting_value);

    xorshift32(xorshift32_array[0], 2 * original_image.width * original_image.height, xorshift32_array);

    memory_test = (unsigned long int*) malloc(original_image.width * original_image.height * sizeof(unsigned long int));
    if (memory_test != NULL) {
        permutation_array = memory_test;
        memory_test = NULL;
    }
    else {
        printf("The memory did not allocate correctly!");
        exit(0);
    }

    permutation(xorshift32_array, original_image.width * original_image.height, permutation_array);

    memory_test2 = (pixel*) malloc(original_image.width * original_image.height * sizeof(pixel));
    if (memory_test2 != NULL)
    {
        aux = memory_test2;
        memory_test2 = NULL;
    }

    for (i = 0; i < original_image.width * original_image.height; i++)
        aux[permutation_array[i]] = original_image.v[i];

    for (i = 0; i < original_image.width * original_image.height; i++)
        original_image.v[i] = aux[i];

    encrypted_image.header = original_image.header;
    encrypted_image.image_dimensions = original_image.image_dimensions;
    encrypted_image.width = original_image.width;
    encrypted_image.height = original_image.height;
    encrypted_image.padding = original_image.padding;

    //The Durstenfeld shuffle
    for (i = 0; i < original_image.width * original_image.height; i++)
    {
        if (checkEndianness() == 1)
        {
            if (i == 0)
            {
                encrypted_image.v[i].b = ((original_image.v[i].b) ^ (starting_value) )
                                        ^ (xorshift32_array[original_image.width * original_image.height] );
                encrypted_image.v[i].g = ((original_image.v[i].g) ^ (starting_value >> 8) )
                                        ^ ((xorshift32_array[original_image.width * original_image.height] >> 8) );
                encrypted_image.v[i].r = ((original_image.v[i].r) ^ (starting_value >> 16) )
                                        ^ ((xorshift32_array[original_image.width * original_image.height] >> 16) );
            }
            else
            {
                encrypted_image.v[i].b = ((original_image.v[i].b) ^ (encrypted_image.v[i-1].b))
                                        ^ ((xorshift32_array[original_image.width * original_image.height + i]) );
                encrypted_image.v[i].g = ((original_image.v[i].g) ^ (encrypted_image.v[i-1].g))
                                        ^ (((xorshift32_array[original_image.width * original_image.height + i]) >> 8) );
                encrypted_image.v[i].r = ((original_image.v[i].r) ^ (encrypted_image.v[i-1].r))
                                        ^ (((xorshift32_array[original_image.width * original_image.height + i]) >> 16) );
            }
        }
        else
        {
            if (i == 0)
            {
                encrypted_image.v[i].b = ((original_image.v[i].b) ^ (starting_value >> 8) )
                                        ^ ((xorshift32_array[original_image.width * original_image.height] >> 8) );
                encrypted_image.v[i].g = ((original_image.v[i].g) ^ (starting_value >> 16) )
                                        ^ ((xorshift32_array[original_image.width * original_image.height] >> 16) );
                encrypted_image.v[i].r = ((original_image.v[i].r) ^ (starting_value >> 24) )
                                        ^ ((xorshift32_array[original_image.width * original_image.height] >> 24) );
            }
            else
            {
                encrypted_image.v[i].b = ((original_image.v[i].b) ^ (encrypted_image.v[i-1].b))
                                        ^ (((xorshift32_array[original_image.width * original_image.height + i] >> 8) ));
                encrypted_image.v[i].g = ((original_image.v[i].g) ^ (encrypted_image.v[i-1].g))
                                        ^ (((xorshift32_array[original_image.width * original_image.height + i]) >> 16) );
                encrypted_image.v[i].r = ((original_image.v[i].r) ^ (encrypted_image.v[i-1].r))
                                        ^ (((xorshift32_array[original_image.width * original_image.height + i]) >> 24) );
            }
        }
    }
    saveImage(image_destination_path, &encrypted_image);
    free(permutation_array);
    free(xorshift32_array);
    free(aux);
    free(encrypted_image.v);
    free(encrypted_image.header);
    free(original_image.v);
    free(original_image.header);
    fclose(fout);
    fclose(f_secret_key);
}

void decryptImage(unsigned char *image_path, unsigned char *image_destination_path, unsigned char *secret_key)
{
    liniarized_image decrypted_image, encrypted_image;
    encrypted_image = loadImage(image_path);
    unsigned long int *memory_test, *xorshift32_array, *permutation_array, *inverse_permutation_array, starting_value;
    int i;
    unsigned char *memory_test1 = NULL;
    pixel *aux, *memory_test2 = NULL;

    memory_test1 = (unsigned char*) malloc(54 * 1);

    if (memory_test1 != NULL)
    {
        decrypted_image.header = memory_test1;
        memory_test1 = NULL;
    }
    else
    {
        printf("The memory did not allocate correctly!");
        exit(0);
    }

    memory_test2 = (pixel*) malloc(((encrypted_image.image_dimensions - 54) * 1));

    if (memory_test2 != NULL)
    {
        decrypted_image.v = memory_test2;
        memory_test2 = NULL;
    }
    else
    {
        printf("The memory did not allocate correctly!");
        exit(0);
    }

    FILE *fin = fopen ((const char*) image_path, "rb");
    if (fin == NULL)
    {
        printf("\nFile %s did not load correctly!\n", image_path);
        exit(0);
    }

    FILE *fout = fopen ((const char*) image_destination_path, "wb+");
    if (fout == NULL)
    {
        printf("\nFile %s did not load correctly!\n", image_destination_path);
        exit(0);
    }

    FILE *f_secret_key = fopen ((const char*) secret_key, "r");
    if (f_secret_key == NULL)
    {
        printf("\nFile %s did not load correctly!\n", secret_key);
        exit(0);
    }

    memory_test = (unsigned long int*) malloc(encrypted_image.width * encrypted_image.height * 2 * sizeof(unsigned long int));

    if (memory_test != NULL)
    {
        xorshift32_array = memory_test;
        memory_test = NULL;
    }
    else
    {
        printf("The memory did not allocate correctly!");
        exit(0);
    }

    fscanf(f_secret_key, "%lu", &xorshift32_array[0]);
    fscanf(f_secret_key, "%lu", &starting_value);

    xorshift32(xorshift32_array[0], 2 * encrypted_image.width * encrypted_image.height, xorshift32_array);

    memory_test = (unsigned long int*) malloc(encrypted_image.width * encrypted_image.height * sizeof(unsigned long int));

    if (memory_test != NULL)
    {
        permutation_array = memory_test;
        memory_test = NULL;
    }
    else
    {
        printf("The memory did not allocate correctly!");
        exit(0);
    }

    permutation(xorshift32_array, encrypted_image.width * encrypted_image.height, permutation_array);

    for (i = encrypted_image.width * encrypted_image.height - 1 ; i >= 0; i--)
    {
        if (checkEndianness() == 1)
        {
            if (i == 0)
            {
                decrypted_image.v[i].b = ((encrypted_image.v[i].b) ^ (starting_value) )
                                        ^ (xorshift32_array[encrypted_image.width * encrypted_image.height] ); // astea
                decrypted_image.v[i].g = ((encrypted_image.v[i].g) ^ (starting_value >> 8) )
                                        ^ (xorshift32_array[encrypted_image.width * encrypted_image.height] >> 8);
                decrypted_image.v[i].r = ((encrypted_image.v[i].r) ^ (starting_value >> 16) )
                                        ^ (xorshift32_array[encrypted_image.width * encrypted_image.height] >> 16);
            }
            else
            {
                decrypted_image.v[i].b = ((encrypted_image.v[i].b) ^ (encrypted_image.v[i - 1].b))
                                        ^ (xorshift32_array[encrypted_image.width * encrypted_image.height + i]);
                decrypted_image.v[i].g = ((encrypted_image.v[i].g) ^ (encrypted_image.v[i - 1].g))
                                        ^ (xorshift32_array[encrypted_image.width * encrypted_image.height + i] >> 8);
                decrypted_image.v[i].r = ((encrypted_image.v[i].r) ^ (encrypted_image.v[i - 1].r))
                                        ^ (xorshift32_array[encrypted_image.width * encrypted_image.height + i] >> 16);
            }
        }
        else
        {
            if (i == 0)
            {
                decrypted_image.v[i].b = ((encrypted_image.v[i].b) ^ (starting_value >> 8))
                                        ^ (xorshift32_array[encrypted_image.width * encrypted_image.height] >> 8);
                decrypted_image.v[i].g = ((encrypted_image.v[i].g) ^ (starting_value >> 16))
                                        ^ (xorshift32_array[encrypted_image.width * encrypted_image.height] >> 16);
                decrypted_image.v[i].r = ((encrypted_image.v[i].r) ^ (starting_value >> 24))
                                        ^ (xorshift32_array[encrypted_image.width * encrypted_image.height] >> 24);
            }
            else
            {
                decrypted_image.v[i].b = ((encrypted_image.v[i].b) ^ (encrypted_image.v[i - 1].b))
                                        ^ ((xorshift32_array[encrypted_image.width * encrypted_image.height + i] >> 8));
                decrypted_image.v[i].g = ((encrypted_image.v[i].g) ^ (encrypted_image.v[i - 1].g))
                                        ^ ((xorshift32_array[encrypted_image.width * encrypted_image.height + i]) >> 16);
                decrypted_image.v[i].r = ((encrypted_image.v[i].r) ^ (encrypted_image.v[i - 1].r))
                                        ^ ((xorshift32_array[encrypted_image.width * encrypted_image.height + i]) >> 24);
            }
        }
    }

    memory_test = (unsigned long int*) malloc(encrypted_image.width * encrypted_image.height * sizeof(unsigned long int));

    if (memory_test != NULL)
    {
        inverse_permutation_array = memory_test;
        memory_test = NULL;
    }
    else
    {
        printf("The memory did not allocate correctly!");
        exit(0);
    }

    for (i = 0; i < encrypted_image.width * encrypted_image.height; i++)
    {
        inverse_permutation_array[permutation_array[i]] = i;
    }

    decrypted_image.header = encrypted_image.header;
    decrypted_image.image_dimensions = encrypted_image.image_dimensions;
    decrypted_image.width = encrypted_image.width;
    decrypted_image.height = encrypted_image.height;
    decrypted_image.padding = encrypted_image.padding;
    memory_test2 = (pixel*) malloc(decrypted_image.width * decrypted_image.height * sizeof(pixel));

    if (memory_test2 != NULL)
    {
        aux = memory_test2;
        memory_test2 = NULL;
    }
    else
    {
        printf("The memory did not allocate correctly!");
        exit(0);
    }

    for (i = 0; i < decrypted_image.width * decrypted_image.height; i++)
    {
        aux[inverse_permutation_array[i]] = decrypted_image.v[i];
    }

    for (i = 0; i < decrypted_image.width * decrypted_image.height; i++)
    {
        decrypted_image.v[i] = aux[i];
    }

    saveImage(image_destination_path, &decrypted_image);

    free(permutation_array);
    free(xorshift32_array);
    free(aux);
    free(inverse_permutation_array);
    free(encrypted_image.v);
    free(encrypted_image.header);
    free(decrypted_image.v);
    free(decrypted_image.header);
    fclose(fin);
    fclose(fout);
    fclose(f_secret_key);
}

#endif // ENCRYPT_DECRYPT_IMAGE_H
