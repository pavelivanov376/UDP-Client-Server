#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
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
  struct sockaddr_in client_addr;
  struct sockaddr_in server_addr;
  int addr_len;
  int count;
  int ret;
  fd_set readfd;
  char buffer[1024];

 //Creating the socket
  sock = socket(AF_INET, SOCK_DGRAM, 0);

  addr_len = sizeof(struct sockaddr_in);

  memset((void*)&server_addr, 0, addr_len);
  server_addr.sin_family = AF_INET;
  server_addr.sin_addr.s_addr = htons(INADDR_ANY);
  server_addr.sin_port = htons(PORT);

 //Binding to a port
  ret = bind(sock, (struct sockaddr*)&server_addr, addr_len);

  while (1) 
  {
    // Listening for a message
    count = recvfrom(sock, buffer, 1024, 0, (struct sockaddr*)&client_addr, &addr_len);
    log(buffer);
  }
}

int log(char* msg)
{
  FILE *fp;
  char* filename = "log.txt";
  
  // Open file in write mode
  fp = fopen(filename,"w+");
   
  fputs(msg,fp);
    
  fclose(fp);
  return(0);
}