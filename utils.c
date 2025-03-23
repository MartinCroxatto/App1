#include <string.h>
#include "utils.h"

char* trim_newline(char *str) {
    char *pos;
    if ((pos = strchr(str, '\n')) != NULL)
        *pos = '\0';
    return str;
}
