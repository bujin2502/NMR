#include <iostream>
#include <cstring>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>

#define IPV4 "127.0.0.1"
#define PORT "7890"
#define BUFFER_SIZE 1024

using namespace std;

int main() {
    struct addrinfo hints, *res;
    int sockfd;
    char buffer[BUFFER_SIZE] = {'\0'};
    int bytes_received;

    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;

    getaddrinfo(IPV4, PORT, &hints, &res);

    sockfd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
    connect(sockfd, res->ai_addr, res->ai_addrlen);

    send(sockfd, "SIMPLE TIME", strlen("SIMPLE TIME"), 0);
    bytes_received = recv(sockfd, buffer, BUFFER_SIZE, 0);
    if (bytes_received > 0) {
        buffer[bytes_received] = '\0';
        cout << "Odgovor na zahtjev za jednostavno vrijeme: " << buffer << endl;
    }

    close(sockfd);
    freeaddrinfo(res);

    return 0;
}