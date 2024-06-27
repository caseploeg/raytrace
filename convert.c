#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"
#include <stdio.h>
#include <stdlib.h>

int read_ppm(const char *filename, int *width, int *height, unsigned char **data) {
    FILE *file = fopen(filename, "rb");
    if (!file) {
        fprintf(stderr, "Failed to open file: %s\n", filename);
        return 0;
    }

    char header[3];
    if (fscanf(file, "%2s\n", header) != 1 || header[0] != 'P' || header[1] != '3') {
        fprintf(stderr, "Invalid PPM format (must be P3)\n");
        fclose(file);
        return 0;
    }

    if (fscanf(file, "%d %d\n", width, height) != 2) {
        fprintf(stderr, "Failed to read width and height\n");
        fclose(file);
        return 0;
    }

    int max_val;
    if (fscanf(file, "%d\n", &max_val) != 1 || max_val != 255) {
        fprintf(stderr, "Invalid max value (must be 255)\n");
        fclose(file);
        return 0;
    }

    *data = (unsigned char *)malloc((*width) * (*height) * 3);
    if (!*data) {
        fprintf(stderr, "Failed to allocate memory\n");
        fclose(file);
        return 0;
    }

    for (int i = 0; i < (*width) * (*height) * 3; ++i) {
        int val;
        if (fscanf(file, "%d", &val) != 1) {
            fprintf(stderr, "Failed to read pixel data\n");
            free(*data);
            fclose(file);
            return 0;
        }
        (*data)[i] = (unsigned char)val;
    }

    fclose(file);
    return 1;
}

int main() {
    const char *input_filename = "image.ppm";
    const char *output_filename = "image.png";

    int width, height;
    unsigned char *data;

    if (!read_ppm(input_filename, &width, &height, &data)) {
        return 1;
    }

    if (!stbi_write_png(output_filename, width, height, 3, data, width * 3)) {
        fprintf(stderr, "Failed to write PNG file: %s\n", output_filename);
        free(data);
        return 1;
    }

    printf("Converted %s to %s\n", input_filename, output_filename);
    free(data);
    return 0;
}
