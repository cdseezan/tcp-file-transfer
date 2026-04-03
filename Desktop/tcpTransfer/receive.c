#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/in.h>   // for AF_INET
#include <unistd.h> //for close() to close active sockets

//stream socket uses tcp while dgram uses udp
int main(){
    int sock= socket(AF_INET,SOCK_STREAM,0); //stream sockets use tcp, 0 automatically selects that
    if (sock<0) {
        perror("Socket doesnt exist");
        return 1;
    }

    //using preexisting struct which is from the netinet header file
    struct sockaddr_in address;
    address.sin_family=AF_INET;
    address.sin_port= htons(8000);
    address.sin_addr.s_addr=INADDR_ANY; //listening on all available interfaces: like wifi, ethernet,etc

    bind(sock,(struct sockaddr *) &address,sizeof(address)); // copied/pasted

    //listening
    int listening=listen(sock,5); //args:socket integer and connections in queue(waiting connections of cleints)
    if(listening<0) {
        perror("Error in listening");
        return 1;
    }
    printf("Listening on Port 8000 \n");


    //connecting to client
    int clientSocket=accept(sock,NULL,NULL); //two nulls in place of clients address and its size
    //accept gives new socket integers(of cleint) (sock is of the receiver)
    if(clientSocket<0){
        perror("Erorr in connecting to client \n");
        return 1;
    }
    printf("Connection established\n\n");
    //retrieving filename
    char fileName[20];
    char temp;
    int count=0;
    while(1){
    int n=recv(clientSocket,&temp,1,0); // 1 is the bytesize, 0 is a safe flag
    if(n<=0) {
        perror("Error retrieving file name");
        return 1;
    }
    if (temp=='\n') break;
    fileName[count]=temp;
    count++;
    }
    fileName[count]='\0';


    //recieving
    char buffer[1024];
    FILE *outputFile= fopen(fileName,"wb");
    if(outputFile==NULL){
        perror("Enter a filename");
        return 1;
    }
    while (1){
            int n=recv(clientSocket,buffer,1024,0);
            if(n>0){
                fwrite(buffer,1,n,outputFile);
            }
            else{
                 printf("File received\n\n");
                 break;
            }
    }
    
    close(clientSocket);
    close(sock);
    fclose (outputFile);



    



    return 0;
}


