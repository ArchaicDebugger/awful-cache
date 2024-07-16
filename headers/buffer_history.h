#ifndef BUFFER_HISTORY_H
#define BUFFER_HISTORY_H

#include<vector>

#define HISTORY_CAPACITY    20
#define MAX_HISTORY_SIZE    1024
#define BUFFER_SIZE         1024

class BufferHistory
{
public:
    BufferHistory();
    void add_to_history(char *message);
    void clear_history();
    void print_history();
    char *get_last_message();
    char *get_history();
    char *get_message(int index);
    int get_history_size();

private:
    std::vector<char *> history;
};

#endif
