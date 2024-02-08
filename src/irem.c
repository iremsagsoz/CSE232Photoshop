#include "DataStructures.h"
#include "irem.h"
#include "yahya.h"
#include "oguzhan.h"
#include "umut.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void brighten () {
    for (int y = 0; y < 128; y++) {
        for (int x = 0; x < 128; x++) {
            
            eb[x][y].red += 10;
            if(eb[x][y].red >= 255)
                eb[x][y].red = 255;
            else if( eb[x][y].red <= 0)
                eb[x][y].red = 0;

            eb[x][y].blue += 10;
            if(eb[x][y].blue >= 255)
                eb[x][y].blue = 255;
            else if( eb[x][y].blue <= 0)
                eb[x][y].blue = 0;
            
            eb[x][y].green += 10;
            if(eb[x][y].green >= 255)
                eb[x][y].green = 255;
            else if( eb[x][y].green <= 0)
                eb[x][y].green = 0;
        }
    }
}

int main (int argc, char *argv[]) {
    char *filename;
    if (argc != 2) {
        printf(
        "Invalid usage! Please use like the following:\n"
        "./Iedit imagename.bmp\n"
        "imagename should be an absolute path or if the current execution directory can be only imagename\n");
        return EXIT_FAILURE;
    }
    else {
        filename = argv[1];
    }

    if (!edit(filename)) {
        return EXIT_FAILURE;
    }

    char input = 0;
    char discard = 0;
    int x;
    int y;
    int filter_selection = 0;
    char op_code[3];
    char number_buffer[4];
    do{
        printf(
            "\nSelect an operation:\n"
            "F to apply a filter\n"
            "U to undo last filter\n"
            "R to redo the last undo\n"
            "V to view the current changes\n"
            "S to save the image\n"
            "X to exit the program\n");

        input = getchar();
        if (input != '\n') { // discard extra entered chars from the stdin
            while ((discard = getchar()) && (discard != '\n') && (discard != EOF));
        }
        
        switch (input)
        {
            case 'f':
            case 'F':
                printf(
                    "\nSelect a filter:\n"
                    "cp to copy top left 20x20 pixels to specified position\n"
                    "bl to blur the image\n"
                    "gr to grayscale the image\n"
                    "br to brighten the image\n");

                fgets(op_code, sizeof(op_code), stdin);
                if (!strchr(op_code, '\n')) { // checks if the buffer contains the new line char if not then this loop discards all extra entries in the stdin buffer
                        while ((discard = getchar()) && (discard != '\n') && (discard != EOF));
                }

                filter_selection = 0;
                x = 0;
                y = 0;
                if (!strcmp(op_code, "cp")) {
                    filter_selection = 1;
                    printf("Enter x: ");
                    fgets(number_buffer, sizeof(number_buffer), stdin);
                    if (!strchr(number_buffer, '\n')) { // discard stdin same as above
                        while ((discard = getchar()) && (discard != '\n') && (discard != EOF));
                    }

                    int sscanf_result = sscanf(number_buffer, "%d", &x);
                    if (sscanf_result == 0 || sscanf_result == 2) { // sanity checks for x value, if user entered a non numeric value do not apply any filter
                        printf("Warning! You have entered an invalid numeric value for x. Filter will not be applied!\n");
                        break;
                    }
                    else if (x < 0 || x > 128) { // if given position is out of bounds of the image
                        printf("Warning! You have entered a value for x that is out of bounds for the current picture. Filter will not be applied!\n");
                        break;
                    }
                    
                    printf("\nEnter y: ");
                    fgets(number_buffer, sizeof(number_buffer), stdin);
                    if (!strchr(number_buffer, '\n')) {
                        while ((discard = getchar()) && (discard != '\n') && (discard != EOF));
                    }

                    sscanf_result = sscanf(number_buffer, "%d", &y);
                    if (sscanf_result == 0 || sscanf_result == 2) { // same sanity checks for y value
                        printf("Warning! You have entered an invalid numeric value for y. Filter will not be applied!\n");
                        break;
                    }
                    else if (y < 0 || y > 128) {
                        printf("Warning! You have entered a value for y that is out of bounds for the current picture. Filter will not be applied!\n");
                        break;
                    }
                }
                else if (!strcmp(op_code, "bl")) {
                    filter_selection = 2;
                }
                else if (!strcmp(op_code, "gr")) {
                    filter_selection = 3;
                }
                else if (!strcmp(op_code, "br")) {
                    filter_selection = 4;
                }
                else {
                    printf("Invalid filter!\n");
                    break;
                }

                if (!filter(filter_selection, x, y)) {
                    printf("Stack is full cannot perform operation! Save or undo some filters before applying new ones!\n");
                }
                break;
            case 'u':
            case 'U':
                if (!undo()) {
                    printf("No operation on the stack to undo\n");
                }
                else {
                    printf("Undo succesfull\n");
                }
                break;
            case 'r':
            case 'R':
                if (!redo()) {
                    printf("No operation to redo\n");
                }
                else {
                    printf("Redo succesfull\n");
                }
                break;
            case 'v':
            case 'V':
                printf("Updating view!\n");
                view();
                view();
                break;
            case 's':
            case 'S':
                printf("Saving image!\n");
                save(filename);
                break;
            case 'x':
            case 'X':
                printf("Exiting program...\n");
                break;
            default:
                printf("Invalid operation! Please select a valid operation!\n\n");
                break;
        }
    }while(input != 'x' && input != 'X');
    
    free(header);

    return EXIT_SUCCESS;
}
