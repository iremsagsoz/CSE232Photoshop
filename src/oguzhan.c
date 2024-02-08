#include "DataStructures.h"
#include "oguzhan.h"
#include "yahya.h"
#include "umut.h"
#include "irem.h"
#include "gfx.h"
#include <stdlib.h>
#include <stdio.h>

static int pixel_start = 0;

unsigned char *header = NULL;

/*  Function returns its run status:
    true: edit was succesfull
    false: error*/

bool edit (char* filename) {
    FILE* imageOnDisk;

    imageOnDisk = fopen(filename, "rb");
    if (imageOnDisk == NULL) { // NULL is a gcc macro for ((void *)0)
        printf("Error! file does not exist!\n");
        return false;
    }

    unsigned char *file_on_memory = malloc(49152 * sizeof(unsigned char));
    if (file_on_memory == NULL) {
        printf("Memory allocation failed! Program cannot continue!\n");
        return false;
    }

    unsigned char pre_header[14];

    fread(pre_header, sizeof(unsigned char), 14, imageOnDisk);
    pixel_start = ((int) pre_header[10]) + ((int) pre_header[11] * 16) + ((int) pre_header[12] * 256) + ((int) pre_header[13] * 4096);

    unsigned char *without_pre_header;
    
    without_pre_header = malloc(sizeof(unsigned char) * (pixel_start - 14));
    if (without_pre_header == NULL) {
        printf("Memory allocation failed! Program cannot continue!\n");
        return false;
    }

    fread(without_pre_header, sizeof(unsigned char), pixel_start - 14, imageOnDisk);
    fread(file_on_memory, sizeof(unsigned char), 49152, imageOnDisk);
    fclose(imageOnDisk);

    header = malloc(sizeof(unsigned char) * pixel_start);
    if (header == NULL) {
        printf("Memory allocation failed! Program cannot continue!\n");
        return false;
    }

    for (int i = 0; i < 14; i++) {
        header[i] = pre_header[i];
    }

    for (int i = 14; i < pixel_start; i++) {
        header[i] = without_pre_header[i - 14];
    }

    // wihtout_pre_header no longer needed because we combined them in header array with pre_header
    free(without_pre_header);

    // bmp files are reversed they start from the bottom left pixel and go to right then to upper lines thats why I
    // start from the last line
    int current_x_index = 0;
    int current_y_index = 127;
    
    // current byte is manually incremented inside the for loop
    for (int current_byte = 0; current_byte < 49152;) {
        orig[current_x_index][current_y_index].blue = file_on_memory[current_byte];
        eb[current_x_index][current_y_index].blue = file_on_memory[current_byte];
        current_byte++;

        orig[current_x_index][current_y_index].green = file_on_memory[current_byte];
        eb[current_x_index][current_y_index].green = file_on_memory[current_byte];
        current_byte++;

        orig[current_x_index][current_y_index].red = file_on_memory[current_byte];
        eb[current_x_index][current_y_index].red = file_on_memory[current_byte];
        current_byte++;

        current_x_index++;
        if (current_x_index == 128) {
            current_x_index = 0;
            current_y_index--;
        }
    }

    // image is stored in the pixel array thus binary information is longer required
    free(file_on_memory);

    gfx_open(400, 400, "Image Display");

    view();
    view();

    return true;
}

void save (char* filename) {
    operation *current_op = stack;
    while (current_op != sptr) {
        switch (current_op->op) {
            case 1:
                copy_paste(current_op->x, current_op->y);
                break;
            case 2:
                blur();
                break;
            case 3:
                grayscale();
                break;
            case 4:
                brighten();
                break;
        }
        current_op++;
    }

    FILE* imageOnDisk;

    imageOnDisk = fopen(filename, "wb");
    if (imageOnDisk == NULL) {
        printf("Saving failed due to I/O error!\n");
        return;
    }

    fwrite(header, sizeof(unsigned char), pixel_start, imageOnDisk);

    for (int y = 127; y > -1 ; y--) {
        for (int x = 0; x < 128; x++) {
            orig[x][y] = eb[x][y];

            fwrite(&orig[x][y].blue, sizeof(unsigned char), 1, imageOnDisk);
            fwrite(&orig[x][y].green, sizeof(unsigned char), 1, imageOnDisk);
            fwrite(&orig[x][y].red, sizeof(unsigned char), 1, imageOnDisk);
        }
    }

    fclose(imageOnDisk);

    // flush stack
    sptr = stack;
    max_sptr = stack;
}


void view () {
    operation *current_op = stack;
    while (current_op != sptr) {
        switch (current_op->op) {
            case 1:
                copy_paste(current_op->x, current_op->y);
                break;
            case 2:
                blur();
                break;
            case 3:
                grayscale();
                break;
            case 4:
                brighten();
                break;
        }
        current_op++;
    }

    int gfx_x = 0;
    int gfx_y = 0;
    int empty_space = 8;

    for (int y = 0; y < 128; y++) {
        for (int x = 0; x < 128; x++) {
            gfx_color(eb[x][y].red, eb[x][y].green, eb[x][y].blue);
            
            gfx_point(gfx_x + empty_space, gfx_y + empty_space);
            gfx_point(gfx_x + empty_space + 1, gfx_y + empty_space);
            gfx_point(gfx_x + empty_space + 2, gfx_y + empty_space);

            gfx_point(gfx_x + empty_space, gfx_y + empty_space + 1);
            gfx_point(gfx_x + empty_space + 1 , gfx_y + empty_space + 1);
            gfx_point(gfx_x + empty_space + 2, gfx_y + empty_space + 1);

            gfx_point(gfx_x + empty_space, gfx_y + empty_space + 2);
            gfx_point(gfx_x + empty_space + 1, gfx_y + empty_space + 2);
            gfx_point(gfx_x + empty_space + 2, gfx_y + empty_space + 2);
            gfx_x += 3;
        }
        gfx_x = 0;
        gfx_y += 3;
    }

    for (int y = 0; y < 128; y++) {
        for (int x = 0; x < 128; x++) {
            eb[x][y] = orig[x][y];
        }
    }
}
