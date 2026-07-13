#include <stdio.h>
#include <string.h>

#include "view.h"

#define RESET   "\033[0m"
#define RED     "\033[1;31m"
#define GREEN   "\033[1;32m"
#define YELLOW  "\033[1;33m"
#define BLUE    "\033[1;34m"
#define MAGENTA "\033[1;35m"
#define CYAN    "\033[1;36m"

void read_title(FILE *fptr);
void read_artist(FILE *fptr);
void read_album(FILE *fptr);
void read_year(FILE *fptr);
void read_content(FILE *fptr);
void read_composer(FILE *fptr);
void read_comment(FILE *fptr);


Status view_tag(TagInfo *tag)
{
    tag->fptr = fopen(tag->filename,"rb");

    if(tag->fptr == NULL)
    {
        printf(RED"ERROR : Unable to open file\n"RESET);
        return e_failure;
    }

    char id[4];

    fread(id,1,3,tag->fptr);
    id[3] = '\0';

    if(strcmp(id,"ID3") != 0)
    {
        printf(RED"ID3 Tag Not Found\n"RESET);
        return e_failure;
    }

    printf(CYAN "--------------------------------------------------\n");
    printf("              MP3 TAG READER AND EDITOR\n");
    printf("--------------------------------------------------\n"RESET);

// Checking the version//
    char version[2];

    fread(version,1,2,tag->fptr);
    //printf("Raw Version Byte = %d\n", version[0]);

    char frame[5];
unsigned char size_arr[4];
int i;

fseek(tag->fptr,10,SEEK_SET);

for(i = 0; i < 4; i++)
{
    fread(frame,1,4,tag->fptr);
    frame[4] = '\0';

   // printf("Frame %d : %s\n",i+1,frame);

    fread(size_arr,1,4,tag->fptr);

    int size = (size_arr[0] << 24) |
               (size_arr[1] << 16) |
               (size_arr[2] << 8)  |
                size_arr[3];

    fseek(tag->fptr,size + 2,SEEK_CUR);
}

    printf("Version : 2.%d\n\n",version[0]);

    read_title(tag->fptr);
    read_artist(tag->fptr);
    read_album(tag->fptr);
    read_year(tag->fptr);
    read_content(tag->fptr);
    read_composer(tag->fptr);
    read_comment(tag->fptr);

    fclose(tag->fptr);

    return e_success;
}

// printing the title of song //
void read_title(FILE *fptr)
{
    rewind(fptr);
    fseek(fptr,10,SEEK_SET);

    char frame[5];
    unsigned char size_arr[4];
    int size;

    while(1)
    {
        fread(frame,1,4,fptr);
        frame[4]='\0';

        fread(size_arr,1,4,fptr);

        size=(size_arr[0]<<24)|(size_arr[1]<<16)|(size_arr[2  ]<<8)|
              size_arr[3];

        if(strcmp(frame,"TIT2")==0)
        {
            break;
        }

        fseek(fptr,size+2,SEEK_CUR);
    }

    fseek(fptr,3,SEEK_CUR);

    char title[100];

    fread(title,1,size-1,fptr);
    title[size-1]='\0';

   printf(MAGENTA "Title      " RESET ": " YELLOW "%s\n" RESET, title);
}

// printing artist name //
void read_artist(FILE *fptr)
{
    rewind(fptr);
    fseek(fptr,10,SEEK_SET);

    char frame[5];
    unsigned char size_arr[4];
    int size;

    while(1)
    {
        fread(frame,1,4,fptr);
        frame[4]='\0';

        fread(size_arr,1,4,fptr);

        size=(size_arr[0]<<24)|
             (size_arr[1]<<16)|
             (size_arr[2]<<8)|
              size_arr[3];

        if(strcmp(frame,"TPE1")==0)
        {
            break;
        }

        fseek(fptr,size+2,SEEK_CUR);
    }

    fseek(fptr,3,SEEK_CUR);

    char artist[100];

    fread(artist,1,size-1,fptr);
    artist[size-1]='\0';

    printf(MAGENTA "Artist     " RESET ": " YELLOW "%s\n" RESET, artist);

}

// printing album name //

void read_album(FILE *fptr)
{
    rewind(fptr);
    fseek(fptr,10,SEEK_SET);

    char frame[5];
    unsigned char size_arr[4];
    int size;

    while(1)
    {
        fread(frame,1,4,fptr);
        frame[4]='\0';

        fread(size_arr,1,4,fptr);

        size=(size_arr[0]<<24)|
             (size_arr[1]<<16)|
             (size_arr[2]<<8)|
              size_arr[3];

        if(strcmp(frame,"TALB")==0)
        {
            break;
        }

        fseek(fptr,size+2,SEEK_CUR);
    }

    fseek(fptr,3,SEEK_CUR);

    char album[100];

    fread(album,1,size-1,fptr);
    album[size-1]='\0';

    printf(MAGENTA "Album      " RESET ": " YELLOW "%s\n" RESET, album);

}

// printing the the year //

void read_year(FILE *fptr)
{
    rewind(fptr);
    fseek(fptr,10,SEEK_SET);

    char frame[5];
    unsigned char size_arr[4];
    int size;

    while(1)
    {
        fread(frame,1,4,fptr);
        frame[4]='\0';

        fread(size_arr,1,4,fptr);

        size=(size_arr[0]<<24)|
             (size_arr[1]<<16)|
             (size_arr[2]<<8)|
              size_arr[3];

        if(strcmp(frame,"TYER")==0 || strcmp(frame,"TDRC")==0)
        {
            //printf("Year Frame Found : %s\n", frame);
            break;
        }

        fseek(fptr,size+2,SEEK_CUR);
    }

    fseek(fptr,3,SEEK_CUR);

    char year[50];

    fread(year,1,size-1,fptr);
    year[size-1]='\0';

    printf(MAGENTA "Year       " RESET ": " YELLOW "%s\n" RESET, year);
}
void read_content(FILE *fptr)
{
    rewind(fptr);
    fseek(fptr,10,SEEK_SET);

    char frame[5];
    unsigned char size_arr[4];
    int size;

    while(1)
    {
        fread(frame,1,4,fptr);
        frame[4] = '\0';

        fread(size_arr,1,4,fptr);

        size = (size_arr[0] << 24) |
               (size_arr[1] << 16) |
               (size_arr[2] << 8)  |
                size_arr[3];

        if(strcmp(frame,"TCON") == 0)
        {
            break;
        }

        fseek(fptr,size + 2,SEEK_CUR);
    }

    fseek(fptr,3,SEEK_CUR);

    char content[100];

    fread(content,1,size-1,fptr);
    content[size-1] = '\0';

    printf(MAGENTA "Content    " RESET ": " YELLOW "%s\n" RESET, content);
}
void read_composer(FILE *fptr)
{
    rewind(fptr);
    fseek(fptr,10,SEEK_SET);

    char frame[5];
    unsigned char size_arr[4];
    int size;

    while(fread(frame,1,4,fptr) == 4)
    {
        frame[4] = '\0';

        fread(size_arr,1,4,fptr);

        size = (size_arr[0] << 24) |
               (size_arr[1] << 16) |
               (size_arr[2] << 8)  |
                size_arr[3];

        if(strcmp(frame,"TCOM") == 0)
        {
            fseek(fptr,3,SEEK_CUR);

            char composer[100];

            fread(composer,1,size-1,fptr);
            composer[size-1] = '\0';

            printf(MAGENTA "Composer   " RESET ": " YELLOW "%s\n" RESET, composer);

            return;
        }

        fseek(fptr,size+2,SEEK_CUR);
    }

    printf(MAGENTA "Composer   " RESET ": " YELLOW "Not Available\n" RESET);
}
void read_comment(FILE *fptr)
{
    rewind(fptr);
    fseek(fptr,10,SEEK_SET);

    char frame[5];
    unsigned char size_arr[4];
    int size;

    while(1)
    {
        fread(frame,1,4,fptr);
        frame[4] = '\0';

        fread(size_arr,1,4,fptr);

        size = (size_arr[0] << 24) |
               (size_arr[1] << 16) |
               (size_arr[2] << 8)  |
                size_arr[3];

        if(strcmp(frame,"COMM") == 0)
        {
            break;
        }

        fseek(fptr,size + 2,SEEK_CUR);
    }

    fseek(fptr,3,SEEK_CUR);

    char comment[100];

    fread(comment,1,size-1,fptr);
    comment[size-1] = '\0';

    printf(MAGENTA "Comment    " RESET ": " YELLOW "%s\n" RESET, comment);
}


