#ifndef TCP_SERVER_H
#define TCP_SERVER_H

#include<netinet/in.h>
#include <string>
#include "buffer_history.h"


#define DEFAULT_PORT        28320

enum ServerStatusPhase {
    NOT_STARTED,
    LISTENING,
    ACCEPTED,
    CLOSED,
    ERROR
};

struct ServerStatus {
    ServerStatusPhase phase;
    std::string message;
};

class TcpServer
{
public:
    TcpServer();
    void start_listen(void (*callback)(char *));
    ServerStatusPhase get_status();
    char *get_status_message();
    BufferHistory *get_buffer_history();

private:
    int server_fd;
    struct sockaddr_in address;
    ServerStatus status;
    BufferHistory history;
    char buffer[BUFFER_SIZE];
    void set_status(ServerStatusPhase status);
    void set_status(ServerStatusPhase status, std::string message);
    void clear_status();
};

#endif


