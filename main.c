#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <winsock2.h>
#pragma GCC optimize ("-fno-stack-protector")
#define _CRT_SECURE_NO_WARNINGS

#ifdef _WIN64
typedef unsigned __int64 socklen_t;
#else
typedef unsigned int socklen_t;
#endif

#pragma comment(lib, "ws2_32.lib")

#define PORT 8080
#define MAX_CONNECTIONS 10
#define MAX_USERNAME_LEN 5
#define MAX_PASSWORD_LEN 5

struct User {
    bool is_authenticated;
    char username[MAX_USERNAME_LEN + 1];
    char password[MAX_PASSWORD_LEN + 1];
};

struct User users[MAX_CONNECTIONS];

void send_response(SOCKET client_socket, const char* response) {
    char message[1024];
    snprintf(message, sizeof(message), "HTTP/1.1 200 OK\nContent-Length: %lu\n\n%s", strlen(response), response);
    send(client_socket, message, strlen(message), 0);
}

void send_error(SOCKET client_socket) {
    char* error_message = "HTTP/1.1 404 Not Found\nContent-Length: 16\n\n404 Not Found\n";
    send(client_socket, error_message, strlen(error_message), 0);
}

void handle_request(SOCKET client_socket) {
    char request[1024];
    bool is_authenticated = false;
    char username[MAX_USERNAME_LEN + 1];
    char password[MAX_PASSWORD_LEN + 1];


    // receive the request from the client
    int bytes_received = recv(client_socket, request, sizeof(request), 0);

    if (bytes_received == SOCKET_ERROR) {
        printf("Error: recv failed with error code %d\n", WSAGetLastError());
        return;
    }

    // null-terminate the request string
    request[bytes_received] = '\0';

    // parse the request to extract the username and password
    //if (sscanf_s(request, "GET /login?username=%[^&]&password=%s HTTP/1.1", username, (unsigned)sizeof(username), password, (unsigned)sizeof(password)) != 2) {
    if (sscanf(request, "GET /login?username=%[^&]&password=%s HTTP/1.1", username, password) != 2) {
        if (strcmp(request, "GET / HTTP/1.1") == 0) {
            send_response(client_socket, "YUVAL");
        }
        else {
            send_error(client_socket);
        }
        return;
    }

    // check if the username and password match a registered user
    for (int i = 0; i < MAX_CONNECTIONS; i++) {
        if (strcmp(users[i].username, username) == 0 && strcmp(users[i].password, password) == 0) {
            users[i].is_authenticated = true;
            is_authenticated = true;
            send_response(client_socket, "Welcome to your page!");
            break;
        }
    }

    // if the username and password don't match a registered user, send an error response
    if (!is_authenticated) {
        send_error(client_socket);
    }
}


int main(int argc, char const* argv[]) {
    char password[8];
    bool is_authenticated = false;

    printf("Enter password: ");
    scanf("%s", password);

    if (strcmp(password, "password") == 0) {
        is_authenticated = true;
    }

    if (is_authenticated) {
        printf("Access granted!\n");
    }
    else {
        printf("Access denied.\n");
    }

    return 0;
    /*
    struct User john;
    john.username[4] = ("j","o","h","n");
    john.password[4] = ("1", "2", "3", "4");
    john.is_authenticated = false;
    users[0] = john;

    for (int i = 1; i < MAX_CONNECTIONS; i++) {
        users[i].is_authenticated = false;
    }
    WSADATA wsaData;
    SOCKET server_socket, client_socket;
    struct sockaddr_in server_address, client_address;
    int addrlen = sizeof(server_address);

    // initialize the users array
// initialize the users array
    for (int i = 0; i < MAX_CONNECTIONS; i++) {
        users[i].is_authenticated = false;
    }

    // initialize Winsock
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        printf("Error: WSAStartup failed with error code %d\n", WSAGetLastError());
        return 1;
    }

    // create the server socket
    server_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    if (server_socket == INVALID_SOCKET) {
        printf("Error: socket failed with error code %d\n", WSAGetLastError());
        return 1;
    }

    // set up the server address struct
    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = INADDR_ANY;
    server_address.sin_port = htons(PORT);

    // bind the server socket to the server address
    if (bind(server_socket, (struct sockaddr*)&server_address, sizeof(server_address)) == SOCKET_ERROR) {
        printf("Error: bind failed with error code %d\n", WSAGetLastError());
        return 1;
    }

    // start listening for client connections
    if (listen(server_socket, MAX_CONNECTIONS) == SOCKET_ERROR) {
        printf("Error: listen failed with error code %d\n", WSAGetLastError());
        return 1;
    }

    while (true) {
        int addrlen = sizeof(client_address);
        client_socket = accept(server_socket, (struct sockaddr*)&client_address, &addrlen);

        //// accept a client connection
        //client_socket = accept(server_socket, (struct sockaddr*)&client_address, (socklen_t*)&addrlen);

        if (client_socket == INVALID_SOCKET) {
            printf("Error: accept failed with error code %d\n", WSAGetLastError());
            return 1;
        }

        // handle the client request
        handle_request(client_socket);

        // close the client socket
        closesocket(client_socket);
    }

    // clean up Winsock
    WSACleanup();

    return 0;
    */
}