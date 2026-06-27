#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>

#include "utils.h"

char* ReadBinaryFile(const char* fileName, int& size){
    FILE* f = fopen(fileName, "rb");
    
    if (!f){
        printf("Error opening '%s'", fileName); 
        exit(0);
    }

    struct stat statBuf;
    int error = stat(fileName, &statBuf);

    if (error){
        printf("Error getting file stats: %s\n", strerror(errno));
        return NULL;
    }

    size = statBuf.st_size;
    char* p = (char*)malloc(size);
    //assert(p);

    size_t bytesRead = fread(p, 1, size, f);

    if (bytesRead != size){
        printf("Read file eror file: %s\n", strerror(errno));
        exit(0);
    }

    fclose(f);
    return p;
}
