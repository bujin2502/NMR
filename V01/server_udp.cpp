#include <iostream>
#include <string>
#include <cstring>
#include <arpa/inet.h>
#include <unistd.h>

#define MAX_MSG 10000

using namespace std;

int main(int argc, char *argv[]) {
    if (argc != 2) {
        cerr << "Krivi broj argumenata!\nUpotreba programa: " << argv[0] << " brojPorta" << endl;
        return 1;
    }

    int portNum = stoi(argv[1]);

    int udpSock = socket(AF_INET, SOCK_DGRAM, 0);
    if (udpSock == -1) {
        cerr << "Ne može se kreirati socket! Izlazak" << endl;
        return 1;
    }

    struct sockaddr_in servAddr, cliAddr;
    servAddr.sin_family = AF_INET;
    servAddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servAddr.sin_port = htons(portNum);
    int rc = bind(udpSock, reinterpret_cast<struct sockaddr *>(&servAddr), sizeof(servAddr));
    if (rc < 0) {
        cerr << "Ne može se povezati s portom broj " << portNum << endl;
        return 1;
    }

    cout << "Čekam podatke na UDP portu " << portNum << endl;

    char buffer[MAX_MSG];
    socklen_t cliLen = sizeof(cliAddr);

    while (true) {
        memset(buffer, 0, MAX_MSG);

        int n = recvfrom(udpSock, buffer, MAX_MSG, 0, reinterpret_cast<struct sockaddr *>(&cliAddr), &cliLen);

        if (n < 0) {
            cerr << "Greška pri prijemu podataka" << endl;
            continue;
        }

        cout << "Primljeno od " << inet_ntoa(cliAddr.sin_addr) << ":" << ntohs(cliAddr.sin_port) << ": " << buffer << endl;

        sendto(udpSock, buffer, n, 0, reinterpret_cast<struct sockaddr *>(&cliAddr), cliLen);
    }

    close(udpSock);

    return 0;
}
