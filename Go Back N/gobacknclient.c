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
    int i, f, j, c = 1, wl, a, e=0, p = 0;

    socket_desc = socket(AF_INET, SOCK_STREAM, 0);
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(3000);
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    connect(socket_desc, (struct sockaddr *)&server_addr, sizeof(server_addr));

    printf("TCP Connection establised\n");
    printf("Enter the number of frames: ");
    scanf("%d", &f);
    alpha9(f);

    send(socket_desc, client_message, sizeof(client_message), 0);

    strcpy(b, "Time Out");
    while(1){
        for(i = 0; i < W; i++){
            alpha9(c);
            send(socket_desc, client_message, sizeof(client_message), 0);
            if(c <= f){
                printf("\nFrame %d Sent", c);
                c++;
            }
        }
        i = 0;
        wl = W;
        while(i < W){
            recv(socket_desc, client_message, sizeof(client_message), 0);
            p = atoi(client_message);
            if(strcmp(client_message, b) == 0){
                e = c - wl;
                if(e < f){
                    printf("\n Time out, Resent Frame %d onwards", e);
                }
                break;
            }
            else{
                if(p <= f){
                    printf("\nFrame %s Acknowledged", client_message);
                    wl --;
                }
                else{
                    break;
                }
            }
            if(p > f){
                break;
            }
            i++;
        }
        if(wl == 0 && c > f){
            send(socket_desc, b, sizeof(b), 0);
            break;
        }
        else{
            c = c - wl;
            wl = W;
        }
    }
    close(socket_desc);
    return 0;

}

void alpha9(int z){
    int k, i = 0, g, e;
    k = z;
    while(k > 0){
        i++;
        k = k / 10;
    }
    g = i;
    i--;
    while(z > 0){
        k = z % 10;
        client_message[i] = k + 48;
        i--;
        z = z/ 10;
    }
    client_message[g] = '\0';
}