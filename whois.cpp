#include<stdio.h> //printf
#include<string.h> //memset
#include<stdlib.h> //exit(0);
#include<arpa/inet.h>
#include<sys/socket.h>


#define BACNET_PORT 47808
#define BROADCAST_ADDR "10.169.95.255"
#define BUFFER_LENGTH 256


int main(){
    int sockfd;
    int broadcast_permission = 1;
    struct sockaddr_in broadcast_addr;
    uint8_t buff[BUFFER_LENGTH];
    int buff_len = 0;

    // create socket
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == -1){
        perror("socket() failed");
        exit(1);
    }

    if (setsockopt(sockfd, SOL_SOCKET, SO_BROADCAST, (void* ) &broadcast_permission, sizeof(broadcast_permission)) == -1){
        perror("setsocopt() failed.");
        exit(1);
    }

    bzero((char* )&broadcast_addr, sizeof(broadcast_addr));
    broadcast_addr.sin_family = AF_INET;
    broadcast_addr.sin_port = htons(BACNET_PORT);
    broadcast_addr.sin_addr.s_addr = inet_addr(BROADCAST_ADDR);

    //while(1){
    
        // BVCL
    buff[0] = 0x81; // bvcl_type_bacnet_ip
    buff[1] = 0x0b; // bvcl_original_broadcast_npdu
    buff[2] = 0x00;
    buff[3] = 0x14;

    // NPDU
    buff[4] = 0x01;
    buff[5] = 0x20;
    buff[6] = 0xff; // unconfirmed_request
    buff[7] = 0xff; // who is
    buff[8] = 0x00; // low limit
    buff[9] = 0xff;

    // APDU
    buff[10] = 0x10;
    buff[11] = 0x08;
    buff[12] = 0x09;
    buff[13] = 0x00;
    buff[14] = 0x1b;
    buff[15] = 0xff;
    buff[16] = 0xfe;





    if (sendto(sockfd, buff, 12, 0, (struct sockaddr *) &broadcast_addr, sizeof(broadcast_addr)) == -1){
        perror("sendto() failed.");
        exit(1);
    }
   // }

    //fclose(sockfd);
    return 0;
}
         