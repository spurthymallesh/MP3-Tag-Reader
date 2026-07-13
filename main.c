#include <stdio.h>
#include <string.h>

#include "mp3tag.h"
#include "view.h"
#include "edit.h"

#define RED     "\033[1;31m"
#define GREEN   "\033[1;32m"
#define YELLOW  "\033[1;33m"
#define BLUE    "\033[1;34m"
#define CYAN    "\033[1;36m"
#define RESET   "\033[0m"

void print_help(void);

int main(int argc, char *argv[])
{
    TagInfo tag;

    if(argc < 2)
    {
        print_help();
        return 0;
    }

    if(strcmp(argv[1], "-v") == 0)
    {
        if(argc != 3)
        {
            printf(RED"ERROR : Pass MP3 file\n"RESET);
            return 0;
        }

        tag.filename = argv[2];

        view_tag(&tag);
    }
    else if(strcmp(argv[1],"-e")==0)
    {
         if(argc != 5)
    {
        printf(YELLOW"Edit:\n"RESET);
        printf(YELLOW"./a.out -e <option> <value> <file.mp3>\n"RESET);
        return 0;
    }

    if(strcmp(argv[2],"-t") &&
   strcmp(argv[2],"-a") &&
   strcmp(argv[2],"-A") &&
   strcmp(argv[2],"-y") &&
   strcmp(argv[2],"-c") &&
   strcmp(argv[2],"-m") &&
   strcmp(argv[2],"-C"))
{
    printf(RED"ERROR : Invalid Edit Option\n"RESET);
    return 0;
}

    tag.modify_option = argv[2];
    tag.modify_value = argv[3];
    tag.filename = argv[4];

    edit_tag(&tag);
    }
    else if(strcmp(argv[1], "--help") == 0)
    {
        print_help();
    }
    else
    {
        printf(RED"ERROR : Invalid Option\n"RESET);
    }

    return 0;
}


void print_help(void)
{
    printf(YELLOW"MP3 Tag Reader And Editor\n\n"RESET);

    printf("./a.out -v sample.mp3\n");
    printf("View MP3 Tags\n\n");

    printf("./a.out -e -t \"Title\" sample.mp3\n");
    printf("Edit Title\n\n");

    printf("./a.out -e -a \"Artist\" sample.mp3\n");
    printf("Edit Artist\n\n");

    printf("./a.out -e -A \"Album\" sample.mp3\n");
    printf("Edit Album\n\n");

    printf("./a.out -e -y \"Year\" sample.mp3\n");
    printf("Edit Year\n\n");

    printf("./a.out -e -c \"Melody\" sample.mp3\n");
    printf("Edit Content Type\n\n");

    printf("./a.out -e -C \"Anirudh\" sample.mp3\n");
    printf("Edit Composer\n\n");

    printf("./a.out -e -m \"Nice Song\" sample.mp3\n");
    printf("Edit Comment\n\n");
}