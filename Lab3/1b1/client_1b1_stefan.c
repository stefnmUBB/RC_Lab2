/*
Un client trimite unui server un sir de numere. Serverul va returna clientului suma numerelor primite.
*/
#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <string.h>

int main(int argc, char** argv){	

	int n;
	struct sockaddr_in server;
	int c;
	c = socket(AF_INET, SOCK_STREAM, 0);
	if(c < 0){
	   printf("Eroare la crearea socket-ului client/n");
	   return 1;
	}   
	
	if(argc!=3) 
	{
		printf("Invalid arguments...\n");
		return -1;		
	}

	memset(&server, 0, sizeof(server));
	server.sin_port = htons(atoi(argv[2]));
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = inet_addr(argv[1]);

	if (connect(c, (struct sockaddr *) &server, sizeof(server)) < 0) {
	 printf("Eroare la conectarea la server\n");
	 return 1;
	}
	
	//n=10;	
	scanf("%i",&n);
	int m = n;	
	n = htons(n);
	send(c, &n, sizeof(n), 0);   
	  
	for(int i=0;i<m;i++)
	{
		int nr;
		scanf("%i",&nr);
		nr = htons(nr);
		send(c, &nr, sizeof(nr), 0);		
	}
	  
	printf("Suma nr este");
	int suma;
	recv(c, &suma, sizeof(suma), MSG_WAITALL);
	suma = ntohs(suma);
	printf("Suma nr este %d", suma);

	close(c);

}
