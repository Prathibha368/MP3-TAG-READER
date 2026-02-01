#include "mp3_header.h"

int validate_cla(int argc, char *argv[], struct MP3 *mp3)
{
    if( argc == 1 )										// validation for command line arguments
    {
	printf("------------------------------------------------------------------------------\n");
	printf("ERROR: ./a.out : INVALID ARGUMENTS\n");
	printf("USAGE : To view please pass like: ./a.out -v mp3filename\n");
	printf("To edit please pass like: ./a.out -e -t/-a/-A/-m/-y/-c changing_text mp3filename\n");
	printf("To get help pass like : ./a.out --help\n");
	printf("------------------------------------------------------------------------------\n");
	return 0;
    }

    if( (strcmp(argv[1], "--help") == 0) )					// if user gives the argument as help we will diaplay the below message.
    {
	printf("------------------------------->HELP<-----------------------------------------\n");
	printf("1. -v -> to view mp3 file contents\n");
	printf("2. -e -> to edit mp3 file contents\n");
	printf("\t\t2.1. -t -> to edit song title\n");
	printf("\t\t2.2. -a -> to edit artist name\n");
	printf("\t\t2.3. -A -> to edit album name\n");
	printf("\t\t2.4. -y -> to edit year\n");
	printf("\t\t2.5. -m -> to edit content\n");
	printf("\t\t2.6. -c -> to edit comment\n");
	printf("------------------------------------------------------------------------------\n");
	return 0; 
    }

    if(!strcmp(argv[1], "-v"))				// if the argument index is 1 having -v  comparing for the view
    {
		int flag=0;
		if (argc==3){						// if therre are 3 aarguments passing from user then checking if mp3 is existing in that
			char *ptr=strstr(argv[2],".mp3");
           	if(ptr){
				if(strcmp(ptr, ".mp3")==0){		//if existed,then the argument must end with mp3.
					flag=1;
					mp3->mp3_filename=argv[2];	
            		return VIEW;				// all conditions are true it return to view .
           	}
        }
	}
	L1:
		printf("------------------------------------------------------------------------------\n");
		printf("ERROR: ./a.out : INVALID ARGUMENTS\n");
		printf("USAGE : To view please pass like: ./a.out -v mp3filename\n");
		printf("To edit please pass like: ./a.out -e -t/-a/-A/-m/-y/-c changing_text mp3filename\n");
		printf("To get help pass like : ./a.out --help\n");
		printf("------------------------------------------------------------------------------\n");
		return 0;
	}
	if(!strcmp(argv[1],"-e"))			//comparing of argument is -e or not.
		{
			int flag=0;
        	if(argc!=5){				//if there are arguments less than 5 return 0;
            	return 0;
        	}
        	else{
        		if(argc==5){			//if there are 5 arguments then,
					if((strcmp(argv[2],"-t"))==0){			//comparing the 3rd argument with the tags and copying there tag name to given tag.
						strcpy(mp3->given_tag,"TIT2");
					}
					else if((strcmp(argv[2],"-a"))==0){
						strcpy(mp3->given_tag,"TPE1");
					}
					else if((strcmp(argv[2],"-A"))==0){
						strcpy(mp3->given_tag,"TALB");
					}
					else if((strcmp(argv[2],"-y"))==0){
						strcpy(mp3->given_tag,"TYER");
					}
					else if((strcmp(argv[2],"-c"))==0){
						strcpy(mp3->given_tag,"COMM");
					}
					else if((strcmp(argv[2],"-m"))==0){
						strcpy(mp3->given_tag,"TCON");
					}
					else{
						goto L2;
					}
					mp3->given_tag[4] = '\0';
            		char *ptr=strstr(argv[4],".mp3");		//checking that argument 5 is having mp3 or not
           			if(ptr){
						if(strcmp(ptr, ".mp3")==0){			
							mp3->mp3_filename=argv[4];	
            				return EDIT;				//returning the edit if it satifies all the condtions
           				}
           			}
        		}
				
			
			L2:									//if conditions are not satisfied then print error message.
				printf("------------------------------------------------------------------------------\n");
				printf("ERROR: ./a.out : INVALID ARGUMENTS\n");
				printf("USAGE : To view please pass like: ./a.out -v mp3filename\n");
				printf("To edit please pass like: ./a.out -e -t/-a/-A/-m/-y/-c changing_text mp3filename\n");
				printf("To get help pass like : ./a.out --help\n");
				printf("------------------------------------------------------------------------------\n");
				return 0;
			}
			else{
				goto L2;
			}
		}
	}



void toggle_endianess(struct MP3 *mp3, char *size)		// this function converts big endian to little endian and viceversa .
{
	char *ptr;
	ptr=(char *)size;
	for(int i=0;i<2;i++){
		char temp=ptr[i];
		ptr[i]=ptr[4-i-1];
		ptr[4-i-1]=temp;
	}
}
void tag_to_name(char *TAG)			//comparing the tag.
{
	if(!strcmp(TAG,"TIT2")){		// if the tag is tit2 then it is title,so as follows
		printf("\n Title:");
	}
	else if(!strcmp(TAG,"TPE1")){
		printf("\n Artist:");
	}
	else if(!strcmp(TAG,"TALB")){
		printf("\n Album:");
	}
	else if(!strcmp(TAG,"TYER")){
		printf("\n YEAR:");
	}
	else if(!strcmp(TAG,"COMM")){
		printf("\n Comment:");
	}
	else if(!strcmp(TAG,"TCON")){
		printf("\n Composer/music:");
	}

}

void print_edit(char *argv[],struct MP3 *mp3)			// to print the output by selected tag
{
	printf("---------------------------------------Select edit option -------------------------------------\n");
	if(!strcmp(mp3->given_tag,"TIT2"))
	{
		printf("--------------------------------Select Title Change Option---------------------------------\n");
	}
	else if(!strcmp(mp3->given_tag,"TPE1"))
	{
		printf("--------------------------------Select Artist Change Option--------------------------------\n");
	}
	else if(!strcmp(mp3->given_tag,"TALB"))
	{
		printf("--------------------------------Select Album Change Option---------------------------------\n");
	}
	else if(!strcmp(mp3->given_tag,"TYER"))
	{
		printf("--------------------------------Select Year Change Option----------------------------------\n");
	}
	else if(!strcmp(mp3->given_tag,"TCON"))
	{
		printf("--------------------------------Select Music Change Option------------------------------\n");
	}
	else if(!strcmp(mp3->given_tag,"COMM"))
	{
		printf("--------------------------------Select Comment Change Option------------------------------\n");
	}
	tag_to_name(mp3->given_tag);		
	printf("%s \n",argv[3]);


	if(!strcmp(mp3->given_tag,"TIT2"))
	{
		printf("-------------------------------- Title Changed Successfully---------------------------------\n");
	}
	else if(!strcmp(mp3->given_tag,"TPE1"))
	{
		printf("--------------------------------Artist Changed Successfully---------------------------------\n");
	}
	else if(!strcmp(mp3->given_tag,"TALB"))
	{
		printf("--------------------------------Alubm Changed Successfully----------------------------------\n");
	}
	else if(!strcmp(mp3->given_tag,"TYER"))
	{
		printf("--------------------------------Year Changed Successfully-----------------------------------\n");
	}
	else if(!strcmp(mp3->given_tag,"TCON"))
	{
		printf("--------------------------------Music Changed Successfully---------------------------------\n");
	}
	else if(!strcmp(mp3->given_tag,"COMM"))
	{
		printf("--------------------------------Comment Changed Successfully-------------------------------\n");
	}
	return;
}

