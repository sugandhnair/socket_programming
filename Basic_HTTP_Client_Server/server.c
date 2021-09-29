#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/types.h>
#include <sys/socket.h>

#include <netinet/in.h>

int main()
{
    //Open a file to server
    FILE *html_data;
    html_data = fopen("index.html","r");

    char response_buffer[1024];
    fgets(response_buffer,sizeof(response_buffer),html_data);

    char http_header[2048] = "HTTP/1.1 200 OK\r\n\n";
    strcat(http_header,response_buffer);

    //Create a sevrver socket
    int server_socket = socket(AF_INET,SOCK_STREAM,0);

    //Define the address
    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(9002);
    server_address.sin_addr.s_addr = INADDR_ANY;

    //Bind the socket
    bind(server_socket,(struct sockaddr *)&server_address,sizeof(server_address));

    //Listen for clients
    listen(server_socket,5);

    //Connect to a client
    int client_socket;
    
    while(1){
        client_socket = accept(server_socket,NULL,NULL);
        send(client_socket,http_header,sizeof(http_header),0);
        close(client_socket);
    }

    return 0;
}
