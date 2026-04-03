// Sender uses sockets, connects, sends file name, then reads into input file and sends the chunks
#include <stdio.h>      // printf, perror, fopen, fread, etc.
#include <string.h>     // strlen
#include <unistd.h>     // close
#include <sys/socket.h> // socket, connect, send
#include <netinet/in.h> // struct sockaddr_in, htons
#include <arpa/inet.h>  // inet_addr (converts "192.168.1.5" to binary)

int main(int argc, char * argv[]){ //pointer used as the cli contains multiple characters 
    if(argc<3){
        printf("Usage: ./send <ipaddr> <filename>");
        return 1;
    }
    //argv[0]=./send | argv[1]=IP_AddrOfReciever | argv[2]= <filename>

    //Socket Creation 
    int sock=socket(AF_INET,SOCK_STREAM,0);
    if (sock<0){
        perror("Error in socket creation");
        return 1;
    }

    //copied from receiver program
    struct sockaddr_in address;
    address.sin_family=AF_INET;
    address.sin_port= htons(8000);
    address.sin_addr.s_addr=inet_addr(argv[1]); //convertine string of ip address to 32bit integer //using ip address of the receiver machine


    //Connection with Receiver
    int connection=connect(sock,(struct sockaddr*)&address,sizeof(address)); //copied from bind of receiver program
    if (connection<0){
        perror("Error connecting to receiver\n");
        return 1;
    }

    //sending filename
    send(sock,argv[2],strlen(argv[2]),0);
    send(sock,"\n",1,0);

    //  sending file
    FILE *inputFile =fopen (argv[2],"rb");
    if(inputFile==NULL){
            printf("Error: File couldn't be opened\n");
            return 1;
        }
    unsigned char buffer[1024];




    //Only Progress Bar copied from DeepSeek
    fseek(inputFile, 0, SEEK_END);
    long total = ftell(inputFile);
    fseek(inputFile, 0, SEEK_SET);
    long sent = 0;

    
    

    while(1){
        size_t read_number=fread(buffer,1,1024,inputFile);
        if (read_number<=0){
            printf("Transfer successful\n\n");
            break;
        }
        else{
            send(sock,buffer,read_number,0);

            //Copied 4 lines for progressbar
            sent += read_number;
            int percent = (int)((sent * 100) / total);
            printf("\rProgress: %d%%", percent);
            fflush(stdout);
        }
    }
    printf("\n");
    close(sock);
    fclose(inputFile);

    return 0;
}