#include<iostream>
#include <thread>
#include "headers/tcp_server.h"
#include "libs/tcp_server.cpp"
#include "libs/buffer_history.cpp"

using namespace std;

void on_message_received(char* message) {
    cout << message;
}

void start_listener_thread(TcpServer *server, void (*callback)(char*)) {
    server->start_listen(callback);
}

int main() {
    TcpServer server;

    thread tcp_server_thread(start_listener_thread, &server, on_message_received);

    tcp_server_thread.detach();

    char command[100];

    while (true)
    {
        cin >> command;
        bool exit_command = strcasecmp(command, "exit") == 0;

        if(exit_command) {
            break;
        }

        if(strcasecmp(command, "--help") == 0) {
            cout << "Here's what you can do: " << endl;
            cout << "NOTHING";
        }
    }

    return 0;
}
