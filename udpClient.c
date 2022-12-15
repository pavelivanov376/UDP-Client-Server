#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <linux/in.h>
#include <sys/socket.h>
#include <sys/select.h>

#define PORT 9999

int main() 
{
  int sock;
  int yes = 1;
  struct sockaddr_in broadcast_addr;
  struct sockaddr_in server_addr;
  int addr_len;
  int count;
  int ret;
  fd_set readfd;
  char buffer[1024];
  int i;
  
  // Creating a socket
  sock = socket(AF_INET, SOCK_DGRAM, 0);

  //Set using broadcast
  ret = setsockopt(sock, SOL_SOCKET, SO_BROADCAST, (char*)&yes, sizeof(yes));

  addr_len = sizeof(struct sockaddr_in);

  memset((void*)&broadcast_addr, 0, addr_len);
  broadcast_addr.sin_family = AF_INET;
  broadcast_addr.sin_addr.s_addr = htonl(INADDR_BROADCAST);
  broadcast_addr.sin_port = htons(PORT);
  
  char* msg = "Is someone there?"; 
  
  //Sending a message
  ret = sendto(sock, msg, strlen(msg), 0, (struct sockaddr*) &broadcast_addr, addr_len);
}