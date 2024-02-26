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
#define maxSize 100


//swap for sort function
void swap(int* ip, int* jp){
    int temp = *ip;
    *ip = *jp;
    *jp = temp;
}
// sorting the given integers using selection sort
void sortIntegers(int arr[], int n){
    int i, j, min_idx;

    for (i=0; i<n - 1; i++) {
        //find the index of minimum element in unsorted array
        min_idx = i;
        for (j = i + 1; j < n; j++){
            if (arr[j] < arr[min_idx]){
                min_idx = j;
            }
        }

        //swap the minimum element with the first element
        swap(&arr[min_idx], &arr[i]);
    }
}
int main(){
    int server_sockfd, client_sockfd;
    int server_len, client_len;
    struct sockaddr_un server_address;
    struct sockaddr_un client_address;

    unlink("server_socket");

    server_sockfd = socket(AF_UNIX, SOCK_STREAM, 0);
    //This socket family is used to communicate between processes on the same machine.
    server_address.sun_family = AF_UNIX;
    strcpy(server_address.sun_path, "server_socket");
    server_len = sizeof(server_address);

    // bind a name to a socket
    bind(server_sockfd,(struct sockaddr *)&server_address, server_len);

    //listen the requests comming from the client
    listen(server_sockfd, 5);
    while(1){
        int n;
        printf("Server waiting.....\n");
        client_len = sizeof(client_address);
        //connection gets established here
        client_sockfd = accept(server_sockfd,(struct sockaddr *)&client_address,&client_len);
        //read
        read(client_sockfd,&n,sizeof(int));
        int receivedMessage[n];
        read(client_sockfd,&receivedMessage,n*sizeof(int));
        printf("Numbers received: ");
        for(int i=0;i<n;i++){
            printf("%d ",receivedMessage[i]);
        }
        printf("\n");
        //perform operation
        sortIntegers(receivedMessage,n);
        printf("Numbers sent: ");
        for(int i=0;i<n;i++){
            printf("%d ",receivedMessage[i]);
        }
        printf("\n");
        //write
        write(client_sockfd,&receivedMessage,n*sizeof(int));
        // close the socket connection
        close(client_sockfd);
    }
    return 0;
}