#ifndef DATA_STRUCTURES_H
#define DATA_STRUCTURES_H

typedef struct {
    int op;
    int x;
    int y;
} operation;

extern operation stack[100];
extern operation *sptr;
extern operation *max_sptr;

typedef struct {
    int red;
    int green;
    int blue;
} pixel;

extern pixel orig[128][128];
extern pixel eb[128][128];

extern unsigned char *header;

#endif
