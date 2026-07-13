#include<stdio.h>
#include<string.h>
#include <stdlib.h>
#include <ctype.h>

#include "edit.h"

#define RED     "\033[1;31m"
#define GREEN   "\033[1;32m"
#define YELLOW  "\033[1;33m"
#define BLUE    "\033[1;34m"
#define CYAN    "\033[1;36m"
#define RESET   "\033[0m"

int get_size(unsigned char arr[]);


Status edit_tag(TagInfo *tag)
{
    if(strcmp(tag->modify_option,"-t") == 0)
        return edit_title(tag);

    else if(strcmp(tag->modify_option,"-a") == 0)
        return edit_frame(tag,"TPE1");

    else if(strcmp(tag->modify_option,"-A") == 0)
        return edit_frame(tag,"TALB");

    else if(strcmp(tag->modify_option,"-y") == 0)
        return edit_frame(tag,"TYER");

    else if(strcmp(tag->modify_option,"-c") == 0)
        return edit_frame(tag,"TCON");

    else if(strcmp(tag->modify_option,"-C") == 0)
    return edit_frame(tag,"TCOM");

    else if(strcmp(tag->modify_option,"-m") == 0)
    return edit_frame(tag,"COMM");


    return e_failure;
}

// Editing the Title //

Status edit_title(TagInfo *tag)
{
    char target_frame[5];

    if(strcmp(tag->modify_option,"-t") == 0)
    {
        strcpy(target_frame,"TIT2");
    }
    else if(strcmp(tag->modify_option,"-a") == 0)
    {
        strcpy(target_frame,"TPE1");
    }
    else if(strcmp(tag->modify_option,"-A") == 0)
    {
        strcpy(target_frame,"TALB");
    }
    else if(strcmp(tag->modify_option,"-y") == 0)
    {
        strcpy(target_frame,"TDRC");
    }
    

    printf("Target Frame : %s\n",target_frame);

    FILE *src;
FILE *temp;

src = fopen(tag->filename,"rb");
temp = fopen("temp.mp3","wb");

if(src == NULL || temp == NULL)
{
    printf("File Open Error\n");
    return e_failure;
}

//printf("Files Opened Successfully\n");

char header[10];

fread(header,1,10,src);
fwrite(header,1,10,temp);

//printf("Header Copied Successfully\n");

char frame_id[5];

fread(frame_id,1,4,src);
frame_id[4] = '\0';

printf("Frame ID : %s\n",frame_id);

unsigned char size_arr[4];

fread(size_arr,1,4,src);

int size;

size = (size_arr[0] << 24) |
       (size_arr[1] << 16) |
       (size_arr[2] << 8)  |
       size_arr[3];

printf("Old Size : %d\n",size);

char flags[2];

fread(flags,1,2,src);

printf("Flags Read\n");

int new_size = strlen(tag->modify_value) + 1;

printf("New Size : %d\n",new_size);

fwrite(frame_id,1,4,temp);

char new_size_arr[4];

new_size_arr[0] = (new_size >> 24) & 0xFF;
new_size_arr[1] = (new_size >> 16) & 0xFF;
new_size_arr[2] = (new_size >> 8) & 0xFF;
new_size_arr[3] = new_size & 0xFF;

fwrite(new_size_arr,1,4,temp);

fwrite(flags,1,2,temp);

char encoding;

fread(&encoding,1,1,src);

fwrite(&encoding,1,1,temp);

fwrite(tag->modify_value,
       1,
       strlen(tag->modify_value),
       temp);

// Skip old title //
fseek(src,size-1,SEEK_CUR);

// Copy remaining file //
char buffer[1024];
size_t bytes;

while((bytes = fread(buffer,1,sizeof(buffer),src)) > 0)
{
    fwrite(buffer,1,bytes,temp);
}

fclose(src);
fclose(temp);

remove(tag->filename);

rename("temp.mp3",tag->filename);

printf(CYAN"Title Modified Successfully\n"RESET);

    return e_success;
}

// Editing all the other parameters in one function //

Status edit_frame(TagInfo *tag, char *target_frame)
{

   // printf("GENERIC EDIT FUNCTION CALLED\n");
    FILE *src = fopen(tag->filename,"rb");
    FILE *temp = fopen("temp.mp3","wb");

    if(src == NULL || temp == NULL)
    {
        printf("File Open Error\n");
        return e_failure;
    }

    char header[10];

    fread(header,1,10,src);
    fwrite(header,1,10,temp);

    char frame_id[5];
    unsigned char size_arr[4];
    char flags[2];

    int found = 0;
    while(fread(frame_id,1,4,src) == 4)
    {
        frame_id[4] = '\0';
        if(frame_id[0] < 'A' || frame_id[0] > 'Z')
{
    break;
}

        fread(size_arr,1,4,src);

        int old_size =
        (size_arr[0] << 24) |
        (size_arr[1] << 16) |
        (size_arr[2] << 8)  |
         size_arr[3];

        fread(flags,1,2,src);

        //printf("Frame = %s\n", frame_id);
        if(strcmp(frame_id,target_frame) == 0)
        {
            found = 1;
            
            int new_size = strlen(tag->modify_value) + 1;

            unsigned char new_size_arr[4];

            new_size_arr[0] = (new_size >> 24) & 0xFF;
            new_size_arr[1] = (new_size >> 16) & 0xFF;
            new_size_arr[2] = (new_size >> 8) & 0xFF;
            new_size_arr[3] = new_size & 0xFF;

            fwrite(frame_id,1,4,temp);
            fwrite(new_size_arr,1,4,temp);
            fwrite(flags,1,2,temp);

            char encoding;

            fread(&encoding,1,1,src);
            fwrite(&encoding,1,1,temp);

            fwrite(tag->modify_value,
                   1,
                   strlen(tag->modify_value),
                   temp);

            fseek(src,old_size - 1,SEEK_CUR);

            char buf[1024];
            size_t bytes;

while((bytes = fread(buf,1,sizeof(buf),src)) > 0)
{
    fwrite(buf,1,bytes,temp);
}

if(strcmp(target_frame,"TPE1") == 0)
{
    printf(CYAN"Artist Modified Successfully\n"RESET);
}
else if(strcmp(target_frame,"TALB") == 0)
{
    printf(CYAN"Album Modified Successfully\n"RESET);
}
else if(strcmp(target_frame,"TYER") == 0||
        strcmp(target_frame,"TDRC") == 0)
{
    printf(CYAN"Year Modified Successfully\n"RESET);
}
else if(strcmp(target_frame,"TCON") == 0)
{
    printf(CYAN"Content Type Modified Successfully\n"RESET);
}
else if(strcmp(target_frame,"TCOM") == 0)
{
    printf(CYAN"Composer Modified Successfully\n"RESET);
}
else if(strcmp(target_frame,"COMM") == 0)
{
    printf(CYAN "Comment Modified Successfully\n" RESET);
}

break;

        }

        else
        {
            fwrite(frame_id,1,4,temp);
            fwrite(size_arr,1,4,temp);
            fwrite(flags,1,2,temp);

            char *buffer = malloc(old_size);

            fread(buffer,1,old_size,src);
            fwrite(buffer,1,old_size,temp);

            free(buffer);
        }
        
    }

    if(found == 0)
{
     printf(RED"ERROR : Frame %s not found\n"RESET, target_frame);

     fclose(src);
     fclose(temp);

     remove("temp.mp3");

     return e_failure;
 }

    fclose(src);
    fclose(temp);

    remove(tag->filename);
    rename("temp.mp3",tag->filename);

    return e_success;
}


int get_size(unsigned char arr[])
{
    return (arr[0] << 24) |
           (arr[1] << 16) |
           (arr[2] << 8)  |
            arr[3];
            
}
