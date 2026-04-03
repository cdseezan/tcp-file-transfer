#include <stdio.h>

int main(int argc,char *argv[]){

    //Check 0: making sure new file doesnot overwrite original file
    FILE *check = fopen(argv[1], "rb");
    if (check != NULL) {
        fclose(check);
        printf("Error: Output file '%s' already exists. Choose a different name to avoid overwriting.\n", argv[1]);
        return 1;
    }

    //Check1: if file argument is entered in shell
    if(argc<2){
            printf("Usage: ./<method> <filename.format>");
            return 1;
        }
    FILE *outputFile=fopen(argv[1],"wb");
    if (outputFile == NULL) {
    printf("Error: Cannot create output file\n");
    return 1;
    }

    //Check2 not necessary cuz we are just rewriting the chunks into an empty output file

    //creating buffer placeholder for chunksName;
    
    unsigned char buffer[1024];
    int count=1;
    char chunkName[20];


    while(1){

        sprintf(chunkName,"chunk_%d.bin",count);
        FILE *chunk= fopen(chunkName,"rb");
        if(chunk==  NULL){
        break;
        }
        
        size_t number_read= fread(buffer,1,1024,chunk);
        if (number_read==0){
             break;
             printf("Combine Succesfful");
        }
        fwrite(buffer,1,number_read,outputFile);

        fclose(chunk);
        remove(chunkName);
        count++;    
    }
    fclose(outputFile);
    printf("Combine Succesfful\n");    



    return 0;
}