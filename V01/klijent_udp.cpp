#include <iostream>
#include <string>
#include <cstring>
#include <arpa/inet.h>
#include <unistd.h>

using namespace std;

#define SERVER_IP "127.0.0.1"

int main(int argc, char *argv[]) {
    if (argc != 2) {
        cerr << "Krivi broj argumenata!\nUpotreba programa: " << argv[0] << " SERVER_PORT" << endl;
        return 1;
    }

    int clientSocket = socket(AF_INET, SOCK_DGRAM, 0);
    if (clientSocket == -1) {
        cerr << "Ne moze se kreirati socket! Izlazak" << endl;
        return 1;
    }

    struct sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(stoi(argv[1]));
    inet_pton(AF_INET, SERVER_IP, &serverAddr.sin_addr);

    while (true) {
        cout << "Unesi poruku za slanje: ";
        string message;
        getline(cin, message);

        sendto(clientSocket, message.c_str(), message.size() + 1, 0, (struct sockaddr*)&serverAddr, sizeof(serverAddr));

        char buf[1024];
        ssize_t bytesReceived = recvfrom(clientSocket, buf, sizeof(buf), 0, nullptr, nullptr);
        if (bytesReceived == -1) {
            cerr << "Greska pri prijemu! Prestanak rada" << endl;
            break;
        }

        cout << "Odgovor servera: " << string(buf, bytesReceived) << endl;
    }

    close(clientSocket);

    return 0;
}
