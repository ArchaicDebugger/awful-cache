#ifndef COMMAND_PARSER_H
#define COMMAND_PARSER_H

#include <map>

enum CommandType
{
    SET,
    GET,
    CLEAR,
    INVALID_C
};

static std::unordered_map<std::string, CommandType> const COMMAND_TYPE_MAPPING = {
    {"SET", CommandType::SET},
    {"GET", CommandType::GET},
    {"CLEAR", CommandType::CLEAR}};

enum LocalCommandType
{
    PRINT_ALL,
    PRINT_LAST,
    INVALID_LC
};

static std::unordered_map<std::string, LocalCommandType> const LOCAL_COMMAND_TYPE_MAPPING = {
    {"PRINT_ALL", LocalCommandType::PRINT_ALL},
    {"PRINT_LAST", LocalCommandType::PRINT_LAST}};

class CommandParser
{
public:
    void execute_command(char *, char *);
    void execute_local_command(char *);
    void set_on_key_set(void (*callback)(char *));
    void set_on_key_cleared(void (*callback)(char *));
    void set_on_print_all(void (*callback)());
    void set_on_print_last(void (*callback)());
    void set_on_invalid_command(void (*callback)());

private:
    void (*on_key_set)(char *);
    void (*on_key_cleared)(char *);
    void (*on_print_all)();
    void (*on_print_last)();
    void (*on_invalid_command)();

    bool is_callback_setup_valid();
    bool is_local_callback_setup_valid();
    bool is_local_call(char *);
};

#endif
