#include "DataStructures.h"
#include "yahya.h"
#include <stdlib.h>
#include <stdio.h>

void copy_paste(int x, int y)
{
    pixel (*tempArray)[20] = malloc(sizeof(*tempArray) * 20);
    if (tempArray == NULL)
    {
        printf("Memory allocation failed cannot copy paste!\n");
        return;
    }

    for (int a = 0; a < 20; a++) // line
    {
        for (int b = 0; b < 20; b++) // column
        {
            tempArray[b][a] = eb[b][a];
        }
    }

    int counterx=0;
    for (int a = 0; a < 20; a++) // line
    {
        for (int b = 0; b < 20; b++) // column
        {
            eb[x][y] = tempArray[b][a];
            x++;
            counterx++;
            if(x >= 128)
            {
                break;
            }
        }
        x = x - counterx;
        y++;
        if(y >= 128)
        {
            break;
        }
        counterx=0;
    }

    free(tempArray);
}

void grayscale () {
    for (int y = 0; y < 128; y++) {
        for (int x = 0; x < 128; x++) {
            int grayscale_value = (eb[x][y].red + eb[x][y].green + eb[x][y].blue)/3;
            eb[x][y].red = grayscale_value;
            eb[x][y].green = grayscale_value;
            eb[x][y].blue = grayscale_value;
        }
    }
}

bool undo () {
    // if sptr is at the start
    if (sptr == stack) {
        return false;
    }

    sptr--;
    return true;
}

bool redo () {
    // if sptr and max_sptr are in the same position >= for failsafe
    if (sptr >= max_sptr) {
        return false;
    }

    sptr++;
    return true;
}
