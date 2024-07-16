#include "../headers/command_parser.h"
#include <iostream>
#include "utils.cpp"

void CommandParser::execute_command(char *c, char *args)
{
    if (!this->is_callback_setup_valid())
    {
        throw "Wrong setup, missing callbacks";
    }

    auto command = to_command_type(c);

    switch (command)
    {
    case CommandType::SET:
        this->on_key_set(args);
        break;
    case CommandType::CLEAR:
        this->on_key_cleared(args);
        break;
    default:
        break;
    }
}

void CommandParser::set_on_key_set(void (*callback)(char *))
{
    this->on_key_set = callback;
}

void CommandParser::set_on_key_cleared(void (*callback)(char *))
{
    this->on_key_cleared = callback;
}

bool CommandParser::is_callback_setup_valid()
{
    return this->on_key_set != nullptr && this->on_key_cleared != nullptr;
}

void CommandParser::set_on_print_all(void (*callback)())
{
    this->on_print_all = callback;
}

void CommandParser::set_on_print_last(void (*callback)())
{
    this->on_print_last = callback;
}

void CommandParser::execute_local_command(char *c)
{
    if(!this->is_local_callback_setup_valid())
    {
        throw "Wrong local setup, missing callbacks";
    }

    auto command = to_local_command_type(c);

    switch (command)
    {
    case LocalCommandType::PRINT_ALL:
        this->on_print_all();
        break;
    case LocalCommandType::PRINT_LAST:
        this->on_print_last();
        break;
    case LocalCommandType::INVALID_LC:
        this->on_invalid_command();
    default:
        break;
    }
}

bool CommandParser::is_local_callback_setup_valid()
{
    return this->on_print_all != nullptr && this->on_print_last != nullptr && this->on_invalid_command != nullptr;
}

void CommandParser::set_on_invalid_command(void (*callback)()) {
    this->on_invalid_command = callback;
}
