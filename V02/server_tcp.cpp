#include <iostream>
#include <cstring>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <ctime>

#define IPV4 "127.0.0.1"
#define PORT "7890"
#define BUFFER_SIZE 1024

using namespace std;

string getCurrentDateTime() {
    time_t now = time(0);
    tm *ltm = localtime(&now);
    char buffer[50];
    sprintf(buffer, "%d.%d.%d %02d:%02d", ltm->tm_mday, ltm->tm_mon + 1, ltm->tm_year + 1900, ltm->tm_hour, ltm->tm_min);
    return string(buffer);
}

string processRequest(const string &request) {
    if (request == "SIMPLE TIME") {
        cout << "Primljen je zahtjev za jednostavno vrijeme." << endl;
        string response = getCurrentDateTime();
        cout << "Odgovor poslan: " << response << endl;
        return response;
    } else if (request.find("GET") != string::npos) {
        cout << "Primljen HTTP GET zahtjev." << endl;
        string response = "HTTP/1.1 200 OK\r\n\r\n <!DOCTYPE html> <body> " + getCurrentDateTime() + " </body> </html>";
        cout << "Odgovor poslan: " << response << endl;
        return response;
    } else {
        cout << "Primljen nepoznat zahtjev." << endl;
        return "Nepoznat zahtjev";
    }
}

int main() {
    struct addrinfo hints, *res;
    int sockfd, client_fd;
    char buffer[BUFFER_SIZE] = {'\0'};
    int bytes_received;

    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;

    getaddrinfo(IPV4, PORT, &hints, &res);

    sockfd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
    bind(sockfd, res->ai_addr, res->ai_addrlen);
    listen(sockfd, 5);

    cout << "Server je pokrenut. Čeka se zahtjev..." << endl;

    while (true) {
        client_fd = accept(sockfd, nullptr, nullptr);
        bytes_received = recv(client_fd, buffer, BUFFER_SIZE, 0);
        if (bytes_received > 0) {
            buffer[bytes_received] = '\0';
            string request(buffer);
            string response = processRequest(request);
            send(client_fd, response.c_str(), response.size(), 0);
        }
        close(client_fd);
    }

    close(sockfd);
    freeaddrinfo(res);

    return 0;
}