#include "mp3_header.h"

void edit(char *argv[],struct MP3 *mp3)
{
    mp3->org_mp3_fptr=fopen(mp3->mp3_filename,"r");             //opening the sample file in read mode  using the file org_mp3 pointer
    mp3->dup_mp3_fptr=fopen("temp.mp3","w");                    // opening a temporary file in write mode using dup_mp3 pointer.
    if(mp3->org_mp3_fptr == NULL){
        printf("invalid");
        return;
    }

    char head[10];
    fread(head,10,1,mp3->org_mp3_fptr);                         // reading 10 bytes from sample file .
    fwrite(head,10,1,mp3->dup_mp3_fptr);                        // writing 10 bytes to temporary file.
    for(int i=0;i<6;i++){
        char TAG[5];                                            
        fread(TAG,4,1,mp3->org_mp3_fptr);                       // read 4bytes from sample file.
        printf("%s",TAG);
        TAG[4] = '\0';                                           
        fwrite(TAG, 4, 1, mp3->dup_mp3_fptr);                   // writing 4 bytes of tag to temporary file.
        if(!strcmp(TAG,mp3->given_tag)){                        // if the given tag and tag existed matches..
            printf("checking1\n");
            int frame_length;                                      //reading 4 bytes from sample file.
            fread(&frame_length,sizeof(int),1,mp3->org_mp3_fptr);
            toggle_endianess(mp3,(char *)&frame_length);            // conversion of system
        
            int len=strlen(argv[3])+1;                              
            toggle_endianess(mp3,(char *)&len);
            fwrite(&len,4,1,mp3->dup_mp3_fptr);

            char flags[3];                                          // reading 3 bytes form sample and writing 3 bytes.
            fread(flags,3,1,mp3->org_mp3_fptr);
            fwrite(flags,3,1,mp3->dup_mp3_fptr);
            toggle_endianess(mp3,(char *) &len);

            fwrite(argv[3],len-1,1,mp3->dup_mp3_fptr);
            fseek(mp3->org_mp3_fptr,frame_length-1,SEEK_CUR);       //moving cursor to the framelength-1,
            print_edit(argv,mp3);
            break;
        }
        else{
            printf("checking2\n");
            int frame_length;
            fread(&frame_length,4,1,mp3->org_mp3_fptr);         //reading 4 bytes from sample and writing if tag not found.
            
            fwrite(&frame_length,4,1,mp3->dup_mp3_fptr);
            toggle_endianess(mp3,(char*)&frame_length);

            char flag[3];
            fread(flag,3,1,mp3->org_mp3_fptr);              //reading 3 bytes from ,writing 3 bytes to temp;
            fwrite(flag,3,1,mp3->dup_mp3_fptr);
            

           
            for(int i=0;i<frame_length-1;i++){
                char ch;
                fread(&ch,sizeof(char),1,mp3->org_mp3_fptr);            //reading each character and writing them to temp file
                fwrite(&ch,sizeof(char),1,mp3->dup_mp3_fptr);
            }  
        }
    }
    print_tag_data(mp3);                    //printing data of tag 
    fclose(mp3->org_mp3_fptr);              // closing of both files..
    fclose(mp3->dup_mp3_fptr);
    //remove(mp3->mp3_filename);
    //rename("temp.mp3",mp3->mp3_filename);
}
void print_tag_data(struct MP3 *mp3){
    char ch;
    while (fread(&ch, 1, 1, mp3->org_mp3_fptr)>0){       //!feof()can also be used;
        fwrite(&ch, 1, 1, mp3->dup_mp3_fptr);
    }

}
   
    


    

