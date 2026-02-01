#ifndef MP3_HEADER_H
#define MP3_HEADER_H

#include <stdio.h>
#include <string.h>

#define VIEW 	1
#define EDIT 	2


struct MP3
{                                   //creating of structure with members of pointers and structure array.
    char *mp3_filename;
    FILE *org_mp3_fptr;
    FILE *dup_mp3_fptr;
    char given_tag[5];
};
//all function prototypes of functions used.

int validate_cla(int argc, char *argv[], struct MP3 *mp3);
void view(struct MP3 *mp3);
void edit(char *argv[],struct MP3 *mp3);
void toggle_endianess(struct MP3 *mp3, char * frame_length);
void print_edit(char *argv[],struct MP3 *mp3);
void print_tag_data(struct MP3 *mp3);
void tag_to_name(char * mp3);

#endif
