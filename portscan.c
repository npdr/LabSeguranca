#include <arpa/inet.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>

// Prints the information about the port
// choosen in the function parameter
void printInfo(int port) {
    struct servent *sp;
		printf("\n");

    if (!(sp = getservbyport(htons(port), NULL)))
        printf("\rerror: port not found\n");
    else{
        printf("\r	Open port found:	%s\t%d/%s [OPEN]\n", sp->s_name, ntohs(sp->s_port), sp->s_proto);
		}
}

int main(int argc, char *argv[]) {
    if(argc < 4) {
        printf("input form: ./scan 'ip' 'from_port' 'to_port'\n");
        exit(1);
    }

    struct sockaddr_in target;
    int sock, connection;
    char* ip = argv[1];
    char* firstPort = argv[2];
    char* lastPort = argv[3];
		struct timeval tv;
		fd_set fdset;

    for (int i = atoi(firstPort); i <= atoi(lastPort); i++) {
				printf("\rScanning %d...", i);
        sock = socket(AF_INET, SOCK_STREAM, 0);
				fcntl(sock, F_SETFL, O_NONBLOCK);
        target.sin_family = AF_INET;
        target.sin_port = htons(i);
        target.sin_addr.s_addr = inet_addr(ip);
        
				connect(sock, (struct sockaddr *)&target, sizeof(target));
				FD_ZERO(&fdset);
				FD_SET(sock, &fdset);
				tv.tv_sec = 1;
				tv.tv_usec = 0;
				if (select(sock + 1, NULL, &fdset, NULL, &tv) == 1){
					int so_error;
					socklen_t len = sizeof so_error;
					getsockopt(sock, SOL_SOCKET, SO_ERROR, &so_error, &len);
					if (so_error == 0) printInfo(i);
				}

        close(sock);
        close(connection);
    }
		printf("\n");

    return 0;
}
