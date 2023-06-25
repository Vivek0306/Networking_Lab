#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <ctype.h>
#include <arpa/inet.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>

#define W 5
#define P1 50
#define P2 10

char client_message[20];
char b[20];

void alpha9(int);


int main(){

    struct sockaddr_in client_addr, server_addr;
    int socket_desc, client_sock;
    int i, j, c = 1, f, n;

    socket_desc = socket(AF_INET, SOCK_STREAM, 0);
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(3000);
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    bind(socket_desc, (struct sockaddr *)&server_addr, sizeof(server_addr));

    listen(socket_desc, 1);
    n = sizeof(client_addr);
    client_sock = accept(socket_desc, (struct sockaddr *)&client_addr, &n);

    printf("TCP Connection establised\n");

    unsigned int s1;
    s1 = (unsigned int)time(NULL);
    srand(s1);
    strcpy(b, "Time Out");
    
    recv(client_sock, client_message, sizeof(client_message), 0);
    f = atoi(client_message);

    while(1){
        for(i=0; i < W; i++){
            recv(client_sock, client_message, sizeof(client_message), 0);
            if (strcmp(client_message, b) == 0){
                break;
            }
        }
        i= 0;
        while(i < W){
            j = rand()%P1;
            if (j < P2){
                send(client_sock, b, sizeof(b), 0);
                break;
            }
            else{
                alpha9(c);
                if (c <= f){
                    printf("\nFrame %s received", client_message);
                    send(client_sock, client_message, sizeof(client_message), 0);
                }
                else{
                    break;
                }
                c++;
            }
            if ( c > f){
                break;
            }
            i++;
        }
    }
    close(socket_desc);
    close(client_sock);
    return 0;
}


void alpha9(int z){
    int k, i = 0, j, g;
    k = z;
    while(k > 0){
        i++;
        k = k / 10;
    }
    g = i;
    i--;
    while(z > 0){
        k = z % 10;
        client_message[i]= k + 48;
        i--;
        z = z / 10;
    }
    client_message[g] = '\0';
}