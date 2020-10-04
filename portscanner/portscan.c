#include <arpa/inet.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

// Prints the information about the port
// choosen in the function parameter
void printInfo(int port) {
    struct servent *sp;

    if (!(sp = getservbyport(htons(port), NULL)))
        printf("error: port not found\n");
    else
        printf("%s\t%d/%s [OPEN]\n", sp->s_name, ntohs(sp->s_port), sp->s_proto);
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

    for (int i = atoi(firstPort); i <= atoi(lastPort); i++) {
        sock = socket(AF_INET, SOCK_STREAM, 0);
        target.sin_family = AF_INET;
        target.sin_port = htons(i);
        target.sin_addr.s_addr = inet_addr(ip);
        
        connection = connect(sock, (struct sockaddr *)&target, sizeof(target));

        if (!connection)
            printInfo(i);

        close(sock);
        close(connection);
    }

    return 0;
}