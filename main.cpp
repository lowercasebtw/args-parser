#include <stdio.h>
#include <string.h>
#include <map>

#include "ptsd.h"

class Argument {
public:
    Argument()         
        : m_name(nullptr),
          m_value(nullptr),
          m_has_value(false),
          m_is_default(false) {}

    Argument(char* value, bool is_default) 
        : m_name(nullptr),
          m_value(value),
          m_has_value(true),
          m_is_default(is_default) {}

    Argument(char* name, char* value) 
        : m_name(name),
          m_value(value),
          m_has_value(true),
          m_is_default(false) {}

    Argument(char* name) 
        : m_name(name),
          m_value(nullptr),
          m_has_value(false),
          m_is_default(false) {}

    char* getName() {
        return m_name;
    }

    char* getString() {
        return m_value;
    }

    bool getBool() {
        if (!hasValue())
            return false;
        char* value = getString();
        if (strcmp(value, "true") == 0)
            return true;
        return false;
    }

    bool hasValue() {
        return m_has_value;
    }

    bool isDefault() {
        return m_is_default;
    }

private:
    char* m_name;
    char* m_value;
    bool m_has_value;
    bool m_is_default;
};

class ArgumentParser {
public:
    ArgumentParser(int argc, char** argv) :
        m_argc(argc),
        m_args(argv) {
            m_arguments = std::map<int, Argument>();
            m_arguments_length = 0;
        }

    bool parse() {
        if (m_argc == 0)
            return true;

        int index = 1;
        while (m_argc-- > 1) {
            char* arg = m_args[index++];
            int arg_len = strlen(arg);
            if (arg[0] != '-') {
                m_arguments[m_arguments_length++] = Argument(arg, true);
                continue;
            }
            if (arg[0] == '-' && arg_len == 1)
                return false;
            char* name = ptsd::strslice(arg, 1, arg_len);
            int name_len = strlen(name);
            if (name_len == 0) 
                continue;
            int eqIndex = ptsd::strindexof(name, '=');
            if (eqIndex >= 0) {
                char* value = ptsd::strslice(name, eqIndex + 1, name_len);
                name = ptsd::strslice(name, 0, eqIndex);
                m_arguments[m_arguments_length++] = Argument(name, value);
                continue;
            }
            m_arguments[m_arguments_length++] = Argument(name);
        }

        return true;
    }

    bool get(char* name, Argument* argument) {
        if (m_arguments.empty())
            return false;
        for (int i = 0; i < m_arguments_length; ++i) {
            Argument arg = m_arguments[i];
            char* arg_name = arg.getName();
            if (arg_name != nullptr && strcmp(arg_name, name) == 0) {
                *argument = arg;
                return true;
            }
        }
        return false;
    }

    bool get(int index, Argument* argument) {
        if (index < 0 || index > m_arguments_length)
            return false;
        *argument = m_arguments[index];
        return true;
    }

    int size() {
        return m_arguments_length;
    }

private:
    std::map<int, Argument> m_arguments;
    int m_arguments_length;

    int m_argc;
    char** m_args;
};

int main(int argc, char** argv) {
    ArgumentParser arguments = ArgumentParser(argc, argv);
    if (!arguments.parse()) {
        fprintf(stderr, "ERROR: Failed to parse program arguments..\n");
        return 1;
    }

    for (int i = 0; i < arguments.size(); ++i) {
        Argument arg;
        if (!arguments.get(i, &arg)) {
            fprintf(stderr, "ERROR: failed to get argument by index\n");
            return -1;
        }
        printf("Name: %s\n", arg.getName());
        printf("Has Value: %s\n", arg.hasValue() ? "true" : "false");
        if (arg.hasValue()) 
            printf("  Value: %s\n", arg.getString());
        printf("Is Default: %s\n", arg.isDefault() ? "true" : "false");
    }

    //     char* m_name;
    //     char* m_value;
    //     bool m_has_value;
    //     bool m_is_default;

    // bool show_help = false;
    // Argument help_arg;
    // if (arguments.get((char*) "help", &help_arg) || arguments.get((char*) "h", &help_arg)) {
    //     show_help = help_arg.hasValue() ? help_arg.getBool() : true;
    // }

    // if (show_help) {
    //     printf("usage %s [-h]\n", argv[0]);
    //     return 0;
    // }

    printf("Hello, world!\n");
    return 0;
}