#include "Encrypt&Decrypt.h"
#include "ChiSquaredTest.h"

int main()
{
    unsigned char *original_image_path = NULL, *encrypted_image_destination_path = NULL,
                  *decrypted_image_destination_path = NULL, *secret_key = NULL;
    float chi_r, chi_g, chi_b;
    liniarized_image original_image, encrypted_image;

    original_image_path = (unsigned char*) malloc(256);
    encrypted_image_destination_path = (unsigned char*) malloc(256);
    decrypted_image_destination_path = (unsigned char*) malloc(256);
    secret_key = (unsigned char*) malloc(256);

    printf("Insert the filename of the image to be encrypted: ");
    scanf("%s", original_image_path);
    printf("Insert the filename of the resulting encrypted image: ");
    scanf("%s", encrypted_image_destination_path);
    printf("Insert the name of the file which contains the secret secret_key: ");
    scanf("%s", secret_key);
    encryptImage(original_image_path, encrypted_image_destination_path, secret_key);

    printf("Insert the filename of the image to be decrypted: ");
    scanf("%s", encrypted_image_destination_path);
    printf("Insert the filename of the resulting decrypted image: ");
    scanf("%s", decrypted_image_destination_path);
    decryptImage(encrypted_image_destination_path, decrypted_image_destination_path, secret_key);

    printf("\n");
    original_image = loadImage(original_image_path);
    chi_r = chiSquaredTest(&original_image, 'r');
    chi_g = chiSquaredTest(&original_image, 'g');
    chi_b = chiSquaredTest(&original_image, 'b');
    printf("The results of the chi test for the original image are:\n%.2lf %.2lf %.2lf\n\n", chi_r, chi_g, chi_b);

    printf("\n");
    encrypted_image = loadImage(encrypted_image_destination_path);
    chi_r = chiSquaredTest(&encrypted_image, 'r');
    chi_g = chiSquaredTest(&encrypted_image, 'g');
    chi_b = chiSquaredTest(&encrypted_image, 'b');
    printf("The results of the chi test for the encrypted image are:\n%.2lf %.2lf %.2lf\n\n", chi_r, chi_g, chi_b);

    free(secret_key);
    free(encrypted_image_destination_path);
    free(decrypted_image_destination_path);
    free(original_image_path);

    return 0;

}
