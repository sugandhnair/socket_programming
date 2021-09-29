#include <stdio.h>
#include <stdlib.h>

#include <sys/types.h>
#include <sys/socket.h>

#include <netinet/in.h>

int main()
{
    //create a socket
    int client_socket;
    client_socket = socket(AF_INET,SOCK_STREAM,0);

    //specify address for the socket
    struct sockaddr_in  server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(9002);
    server_address.sin_addr.s_addr = INADDR_ANY;

    int connection_status = connect(client_socket,(struct sockaddr *)&server_address,sizeof(server_address));

    //Check for connection
    if(connection_status == -1){
        printf("Connection Failed \n");
    }
    else{
        printf("Connection Established\n");
    }    

    //Recieve data from the server
    char server_response[256];
    recv(client_socket,&server_response,sizeof(server_response),0);

    printf("Recieved : %s\n",server_response);

    //close the soket
    close(client_socket);
    return 0;
}
