    #include <stdio.h>
    int main(int argc,char * argv[]){
        //Check1: if file argument is entered in shell
        if (argc<2){
            printf("Usage: ./<method> <filename.format>");
            return 1;
        }
        
        FILE *inputFile;
        inputFile=fopen(argv[1],"rb");
        //Check2: if the file is opened or not
        if(inputFile==NULL){
            printf("Error: File couldn't be opened\n");
            return 1;
        }

        //creating chunks and writing them into a new chunks file
        unsigned char buffer[1024];
        int count =1;
        char fileName[20];

        while(1){
           size_t number_read=fread(buffer,1,1024,inputFile) ;
           if (number_read>0){
           sprintf(fileName,"chunk_%d.bin",count);
           FILE *chunk=fopen(fileName,"wb");
           fwrite(buffer,1,number_read,chunk);
           fclose(chunk);

            count++;
           }
           else{
            break;
           }
        }
        fclose(inputFile);
        printf("Splitted %s into %d chunks\n",argv[1],count-1);

        
        


        return 0;
    }