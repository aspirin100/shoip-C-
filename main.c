#include<stdio.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netdb.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<string.h>

int main(int argc, char* argv[])
{	
	struct addrinfo src, *head, *temp;
	char ip_addr[INET6_ADDRSTRLEN];
	int status;


	memset(&src, 0, sizeof(src));
	src.ai_family = AF_UNSPEC;
	src.ai_socktype = SOCK_STREAM;


	if(argc != 2)
	{
		fprintf(stderr, "wrong argument number, error\n");
		return -1;
	}
	if((status = getaddrinfo(argv[1], NULL, &src, &head)) != 0)
	{
		fprintf(stderr, "getaddrinfo error:%s\n", gai_strerror(status));
		return -1;
	}
	else
	{
		temp = head;
		while(temp != NULL)
		{    	
			void* addr;
			if(temp->ai_family == AF_INET)
			{
				struct sockaddr_in* ip_type = (struct sockaddr_in*)temp->ai_addr;
				addr = &(ip_type->sin_addr);
			}else
			{
				struct sockaddr_in6* ip_type = (struct sockaddr_in6*)temp->ai_addr;
				addr = &(ip_type->sin6_addr);
			}
			
			inet_ntop(temp->ai_family, addr, ip_addr, INET6_ADDRSTRLEN);
			printf("ip: %s\n", ip_addr);

			temp = temp->ai_next;
		}
	}
	
	freeaddrinfo(head);
	return 0;
}
