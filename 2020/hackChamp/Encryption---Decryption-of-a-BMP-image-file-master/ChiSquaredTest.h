#ifndef CHI_SQUARED_TEST_H
#define CHI_SQUARED_TEST_H

double chiSquaredTest(liniarized_image* image, unsigned char color_channel)
{
    int i, j;
    double chi = 0, frequence_of_value_i, mean_frequence; // astea
    mean_frequence = (image->width * image->height) / 256;

    for (i = 0; i < 256; i++)
    {
        frequence_of_value_i = 0;
        for (j = 0; j < image->width * image->height; j++)
        {
            if (color_channel == 'r')
            {
                if (image->v[j].r == i) frequence_of_value_i = frequence_of_value_i + 1;
            }
            if (color_channel == 'g')
            {
                if (image->v[j].g == i) frequence_of_value_i = frequence_of_value_i + 1;
            }
            if (color_channel == 'b')
            {
                if (image->v[j].b == i) frequence_of_value_i = frequence_of_value_i + 1;
            }
        }
        chi = chi + ((frequence_of_value_i - mean_frequence) * (frequence_of_value_i - mean_frequence)) / mean_frequence;
    }
    return chi;
}

#endif // CHI_SQUARED_TEST_H
