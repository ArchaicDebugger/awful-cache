#ifndef UTILS
#define UTILS

#include <iostream>
#include "../headers/command_parser.h"

char *to_uppercase(char *s) {
    for (int i = 0; s[i] != '\0'; i++) {
        s[i] = (char)toupper(s[i]);
    }

    return s;
}

char **strsplit(char *s, char delimiter) {
    int delimiter_ix = -1;
    char** ret_val;

    ret_val = new char*[2];

    for (int i = 0; s[i] != '\0'; i++)
    {
        if (s[i] == delimiter) {
            delimiter_ix = i;
            s[i] = '\0';
            ret_val[0] = s;
        }
    }

    if (delimiter_ix > -1) {
        ret_val[1] = s + delimiter_ix + 1;
    }

    return ret_val;
}

CommandType to_command_type(char *s) {
    auto parsed = COMMAND_TYPE_MAPPING.find(to_uppercase(s));
    if(parsed == COMMAND_TYPE_MAPPING.end())
        return CommandType::INVALID_C;

    return parsed->second;
}

LocalCommandType to_local_command_type(char *s) {
    auto parsed = LOCAL_COMMAND_TYPE_MAPPING.find(to_uppercase(s));
    if(parsed == LOCAL_COMMAND_TYPE_MAPPING.end())
        return LocalCommandType::INVALID_LC;

    return parsed->second;
}

#endif
