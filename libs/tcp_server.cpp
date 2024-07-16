#include "../headers/tcp_server.h"
#include<iostream>
#include<sys/socket.h>
#include<netinet/in.h>
#include <unistd.h>

using namespace std;

TcpServer::TcpServer() : history() {
    this->clear_status();
    this->buffer[0] = '\0';
}

void TcpServer::start_listen(void (*callback)(char*)) {
    server_fd = socket(AF_INET, SOCK_STREAM, 0);

    if (server_fd < 0) {
        set_status(ERROR, "Error creating socket");
        return;
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(DEFAULT_PORT);

    if (::bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        set_status(ERROR, "Error binding socket");
        return;
    }

    if (listen(server_fd, 3) < 0) {
        set_status(ERROR, "Error listening on socket");
        return;
    }

    int new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&address);
    if (new_socket < 0) {
        set_status(ERROR, "Error accepting connection");
        return;
    }

    while (true) {
        set_status(LISTENING);
        int valread = read(new_socket, buffer, BUFFER_SIZE);
        set_status(ACCEPTED);
        if (valread == 0) {
            set_status(CLOSED, "Connection closed");
            break;
        }

        history.add_to_history(buffer);

        callback(buffer);
        buffer[0] = '\0';
    }
}

ServerStatusPhase TcpServer::get_status() {
    return status.phase;
}

void TcpServer::set_status(ServerStatusPhase status, string message) {
    this->status.phase = status;
    this->status.message = message;
}

void TcpServer::set_status(ServerStatusPhase status) {
    this->set_status(status, "");
}

void TcpServer::clear_status()
{
    this->status.phase = NOT_STARTED;
    this->status.message = "";
}

BufferHistory *TcpServer::get_buffer_history()
{
    return &this->history;
}
