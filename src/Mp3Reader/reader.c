#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct mp3Tag
{
    char tag[3];
    char title[30];
    char artist[30];
    char album[30];
    char year[4];
    char comment[30];
    int genre;
};

int fileNameLength = 1024;
int mp3TagSize = 128;

char* substring(char* buffer, int startingPoint, int finishingPoint)
{
    char* str = malloc(strlen(buffer));

    return strncpy(str, buffer + startingPoint, finishingPoint+1);
}

int main()
{
    struct mp3Tag* tagStruct = {0};
    char fileName[fileNameLength + 1];
    FILE* mp3File;
    char buffer[mp3TagSize + 1];

    strcpy(fileName, "breathe-ft-jem-cooke.mp3");

    mp3File = fopen(fileName, "rb");
    buffer[mp3TagSize] = '\0';  //just a precaution

    if (mp3File)
    {
        printf("Successful open of %s \n", fileName);
    }
    else
    {
        printf("***Aborting*** Could not open %s \n", fileName);
        return 1;
    }

//move file pointer to 128 bytes off the end of the file.
    fseek(mp3File, -(mp3TagSize), SEEK_END);
    if(mp3File == NULL)
    {
        printf("Could not seek, Aborting \n");
        return 1;
    }

//get the data
    if(fgets(buffer, mp3TagSize, mp3File) != NULL)
    {
        printf("\n\nTag: %0.3s\n",substring(buffer, 0, 2));
        printf("Title: %0.30s\n",substring(buffer, 3, 32));
        printf("Artist: %0.30s\n",substring(buffer, 33, 62));
        printf("Album: %0.30s\n",substring(buffer, 63, 92));
        printf("Year: %0.4s\n",substring(buffer, 93, 96));
        printf("Comment: %0.30s\n",substring(buffer, 97, 124));
        printf("Track: %d\n",substring(buffer, 125, 125));
        printf("Track Number: %d\n",substring(buffer, 126, 126));
        printf("Genre: %d\n",substring(buffer, 127, 127));

    }
    else{
        printf("Error reading the ID3V1 tag.");
        return 1;
    }

    fclose(mp3File);
    return 0;
}
