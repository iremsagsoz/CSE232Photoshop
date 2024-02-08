#include "DataStructures.h"
#include "umut.h"
#include <stdlib.h>
#include <stdio.h>

pixel orig[128][128];
pixel eb[128][128];

operation stack[100];

operation *sptr = stack;
operation *max_sptr = stack;

bool filter (int op, int x, int y) {
    // if stack is full
    if (sptr == stack + 100) {
        return false;
    }

    sptr->op = op;
    sptr->x = x;
    sptr->y = y;
    sptr++;
    max_sptr = sptr;

    return true;
}

void blur() {
    pixel (*temp_pic)[128] = malloc(sizeof *temp_pic  * 128);
    if (temp_pic == NULL) {
        printf("Memory allocation failed cannot blue the image!\n");
        return;
    }

    for (int y = 0; y < 128; y++) {
        for (int x = 0; x < 128; x++) {
            temp_pic[x][y] = eb[x][y];
        }
    }

    for (int y = 0; y < 128; y++) {
        for (int x = 0; x < 128; x++) {
           
            if (x==0 && y==0){

                eb[x][y].red = (temp_pic [x+1][y].red + temp_pic [x][y+1].red + temp_pic [x][y].red)/3;
                eb[x][y].green = (temp_pic [x+1][y].green + temp_pic [x][y+1].green + temp_pic [x][y].green)/3;
                eb[x][y].blue = (temp_pic [x+1][y].blue + temp_pic [x][y+1].blue + temp_pic [x][y].blue)/3;

            }

            else if (x==0 && y==127){

                eb[x][y].red = (temp_pic [x+1][y].red + temp_pic [x][y-1].red + temp_pic [x][y].red)/3;
                eb[x][y].green = (temp_pic [x+1][y].green + temp_pic [x][y-1].green + temp_pic [x][y].green)/3;
                eb[x][y].blue = (temp_pic [x+1][y].blue + temp_pic [x][y-1].blue + temp_pic [x][y].blue)/3;

            }
            
            else if (x==127 && y==127){

                eb[x][y].red = (temp_pic [x-1][y].red + temp_pic [x][y-1].red + temp_pic [x][y].red)/3;
                eb[x][y].green = (temp_pic [x-1][y].green + temp_pic [x][y-1].green + temp_pic [x][y].green)/3;
                eb[x][y].blue = (temp_pic [x-1][y].blue + temp_pic [x][y-1].blue + temp_pic [x][y].blue)/3;

            }

            else if (x==127 && y==0){

                eb[x][y].red = (temp_pic [x-1][y].red + temp_pic [x][y+1].red + temp_pic [x][y].red)/3;
                eb[x][y].green = (temp_pic [x-1][y].green + temp_pic [x][y+1].green + temp_pic [x][y].green)/3;
                eb[x][y].blue = (temp_pic [x-1][y].blue + temp_pic [x][y+1].blue + temp_pic [x][y].blue)/3;

            }
            
            else if (x==0) {

                eb[x][y].red = (temp_pic [x+1][y].red + temp_pic [x][y+1].red + temp_pic [x][y-1].red + temp_pic [x][y].red)/4;
                eb[x][y].green = (temp_pic [x+1][y].green + temp_pic [x][y+1].green + temp_pic [x][y-1].green + temp_pic [x][y].green)/4;
                eb[x][y].blue = (temp_pic [x+1][y].blue + temp_pic [x][y+1].blue + temp_pic [x][y-1].blue + temp_pic [x][y].blue)/4;

            }
            
            else if (x==127) {

                eb[x][y].red = (temp_pic [x-1][y].red + temp_pic [x][y+1].red + temp_pic [x][y-1].red + temp_pic [x][y].red)/4;
                eb[x][y].green = (temp_pic [x-1][y].green + temp_pic [x][y+1].green + temp_pic [x][y-1].green + temp_pic [x][y].green)/4;
                eb[x][y].blue = (temp_pic [x-1][y].blue + temp_pic [x][y+1].blue + temp_pic [x][y-1].blue + temp_pic [x][y].blue)/4;

            }

            else if (y==0) {

                eb[x][y].red = (temp_pic [x-1][y].red + temp_pic [x+1][y].red + temp_pic [x][y+1].red + temp_pic [x][y].red)/4;
                eb[x][y].green = (temp_pic [x-1][y].green + temp_pic [x+1][y].green + temp_pic [x][y+1].green + temp_pic [x][y].green)/4;
                eb[x][y].blue = (temp_pic [x-1][y].blue + temp_pic [x+1][y].blue + temp_pic [x][y+1].blue + temp_pic [x][y].blue)/4;

            }

            else if (y==127) {

                eb[x][y].red = (temp_pic [x-1][y].red + temp_pic [x+1][y].red + temp_pic [x][y-1].red + temp_pic [x][y].red)/4;
                eb[x][y].green = (temp_pic [x-1][y].green + temp_pic [x+1][y].green + temp_pic [x][y-1].green + temp_pic [x][y].green)/4;
                eb[x][y].blue = (temp_pic [x-1][y].blue + temp_pic [x+1][y].blue + temp_pic [x][y-1].blue + temp_pic [x][y].blue)/4;

            }

            else {

                eb[x][y].red = (temp_pic [x-1][y].red + temp_pic [x+1][y].red +temp_pic [x][y+1].red +temp_pic [x][y-1].red + temp_pic [x][y].red)/5;
                eb[x][y].green = (temp_pic [x-1][y].green + temp_pic [x+1][y].green +temp_pic [x][y+1].green +temp_pic [x][y-1].green + temp_pic [x][y].green)/5;
                eb[x][y].blue = (temp_pic [x-1][y].blue + temp_pic [x+1][y].blue +temp_pic [x][y+1].blue +temp_pic [x][y-1].blue + temp_pic [x][y].blue)/5;

            }
        }
    }
    free(temp_pic);
}
