// 2) Write C programs to implement a simple client-server application .A client
// will send n integers to the server ,which will sort the integers and send back
// to client .The client will print the result .Use Unix File socket for 
//communication 

#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <sys/un.h>
#include <unistd.h>
#include <stdlib.h>

int main(){
    int sockfd;
    int len;
    struct sockaddr_un address;
    int result;
    int size;
    sockfd = socket(AF_UNIX, SOCK_STREAM, 0);
    address.sun_family = AF_UNIX;
    strcpy(address.sun_path, "server_socket");
    len = sizeof(address);
    result = connect(sockfd, (struct sockaddr *)&address, len);

    //Connect to the server
    if(result == -1){
        perror("Connection failed!!");
        exit(1);
    }
    printf("Connected\n");

    //user input
    printf("Enter the number of integers you want to send: ");
    scanf("%d",&size);
    int numbers[size];
    int sortedNumbers[size];
    printf("Enter %d numbers: ", size);
    
    for(int i=0;i<size;i++){
        scanf("%d",&numbers[i]);
    }

    //read and write via sockfd
    write(sockfd,&size,sizeof(int));
    write(sockfd,&numbers,size*sizeof(int));
    printf("Numbers sent\n");
    printf("Waiting for the server...\n");
    read(sockfd,&sortedNumbers,size*sizeof(int));
    printf("Numbers received: ");

    for(int i=0;i<size;i++){
        printf("%d ",sortedNumbers[i]);
    }
    printf("\n");

    // close the socket connection
    close(sockfd);
    exit(0);
    return 0;
}