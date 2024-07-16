#include<iostream>
#include <thread>
#include <string>
#include "headers/tcp_server.h"
#include "headers/command_parser.h"
#include "libs/tcp_server.cpp"
#include "libs/buffer_history.cpp"
#include "libs/utils.cpp"
#include "libs/command_parser.cpp"

using namespace std;

CommandParser *parser;
TcpServer *server;

void on_message_received(char* message) {
    auto split_string = strsplit(message, ' ');
    parser->execute_command(split_string[0], split_string[1]);
}

void start_listener_thread(TcpServer *server, void (*callback)(char*)) {
    server->start_listen(callback);
}

void on_key_set(char *args) {
    cout << "Key set: " << args << endl;
}

void on_key_cleared(char *args) {
    cout << "Key cleared: " << args << endl;
}

void on_print_all() {
    server->get_buffer_history()->print_history();
}

void on_print_last() {
    auto message = server->get_buffer_history()->get_last_message();
    cout << message << endl;
}

void on_invalid() {
    cout << "Invalid command." << endl;
}

int main() {
    server = new TcpServer();
    parser = new CommandParser();

    parser->set_on_key_set(on_key_set);
    parser->set_on_key_cleared(on_key_cleared);
    parser->set_on_print_all(on_print_all);
    parser->set_on_print_last(on_print_last);
    parser->set_on_invalid_command(on_invalid);

    thread tcp_server_thread(start_listener_thread, server, on_message_received);

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
            int i = 1;
            for (auto cm = LOCAL_COMMAND_TYPE_MAPPING.begin(); cm != LOCAL_COMMAND_TYPE_MAPPING.end(); cm++)
            {
                cout << i << ". " << cm->first << endl;
                i++;
            }
        } else {
            parser->execute_local_command(command);
        }
    }

    return 0;
}
