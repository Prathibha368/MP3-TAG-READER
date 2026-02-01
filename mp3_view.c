#include "mp3_header.h"

void view(struct MP3 *mp3)
{
    mp3->org_mp3_fptr=fopen(mp3->mp3_filename,"r");         //by using org pointer we open the file in read mode.
    if((mp3->org_mp3_fptr)==NULL){
        printf("Error");
        return;
    }
    fseek(mp3->org_mp3_fptr,10,SEEK_CUR);           //by using fseek we move the cursor to 10 bytes.
    char TAG[5];
    for(int i=0;i<6;i++){                           //running the loop for 6 times i.e for each tag.
        fread(TAG,4,1,mp3->org_mp3_fptr);
        int frame_size;                             
        fread(&frame_size,sizeof(int),1,mp3->org_mp3_fptr);     //read 4 bytes from the file.
        toggle_endianess(mp3,(char *)&frame_size);              //converts the big endian to little endian to represent in stdio.
        fseek(mp3->org_mp3_fptr,3,SEEK_CUR);                    // moving cursor 3 bytes .
        tag_to_name(TAG);           
        for(int i=0;i<frame_size-1;i++){                        // running loop for size-1 to read each character to print.
            char ch;
            fread(&ch,sizeof(char),1,mp3->org_mp3_fptr);
            printf("%c",ch);
        }
        printf("\n");
    }
    fclose(mp3->org_mp3_fptr);                              // closing of the file.
    printf("------------------------------------------------------\n");

}

