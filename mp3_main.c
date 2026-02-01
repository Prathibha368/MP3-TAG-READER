/*NAME: BOGA PRATHIBHA
DATE: 30/12/25
DESCRIPTION :  An MP3 Tag Reader is a C-based application that reads, parses, and displays data such as title, artist, album, and year from MP3 files using ID3 tag analysis.*/
#include "mp3_header.h"

int main(int argc, char *argv[])
{
    /* structure variable declaration */
    struct MP3 mp3;

    int ret = validate_cla(argc,argv,&mp3);
    if(ret == VIEW)             //if ret is View we are passing address of mp3 for view.
    {
        view(&mp3);
    }
    else if(ret == EDIT)
    {
        edit(argv,&mp3);        //if ret is edit .
    }

    return 0;
}
