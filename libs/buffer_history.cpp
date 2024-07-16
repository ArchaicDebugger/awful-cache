#include "../headers/buffer_history.h"
#include <cstring>
#include <iostream>
#include <vector>

BufferHistory::BufferHistory() : history(HISTORY_CAPACITY) {

}

void BufferHistory::add_to_history(char *message) {
    if (this->history.size() == HISTORY_CAPACITY) {
        delete[] this->history[0];
        this->history.erase(this->history.begin());
    }

    char *new_message = new char[strlen(message) + 1];
    strcpy(new_message, message);
    this->history.push_back(new_message);
}

void BufferHistory::clear_history() {
    for (int i = 0; i < this->history.size(); i++) {
        delete[] this->history[i];
    }
    this->history.clear();
}

void BufferHistory::print_history() {
    for (int i = 0; i < this->history.size(); i++) {
        std::cout << this->history[i] << std::endl;
    }
}

char *BufferHistory::get_last_message() {
    return this->history.back();
}

char *BufferHistory::get_history() {
    char *history = new char[MAX_HISTORY_SIZE];
    history[0] = '\0';

    for (int i = 0; i < this->history.size(); i++) {
        strcat(history, this->history[i]);
        strcat(history, "\n");
    }

    return history;
}

char *BufferHistory::get_message(int index) {
    return this->history[index];
}

int BufferHistory::get_history_size() {
    return this->history.size();
}
