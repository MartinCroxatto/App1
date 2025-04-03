#include <string.h> // Se incluye la biblioteca estándar para manipulación de cadenas.
#include "utils.h"  // Se incluye el archivo de cabecera "utils.h", que probablemente contiene la declaración de la función `trim_newline`.

char* trim_newline(char *str) {
    char *pos; // Se declara un puntero `pos` que se usará para localizar el carácter de nueva línea ('\n') en la cadena.
    
    // `strchr` busca la primera aparición del carácter '\n' en la cadena `str`.
    // Si encuentra el carácter, devuelve un puntero a su posición; de lo contrario, devuelve NULL.
    if ((pos = strchr(str, '\n')) != NULL)
        *pos = '\0'; // Si se encuentra '\n', se reemplaza por el carácter nulo ('\0'), terminando la cadena en esa posición.
    
    return str; // Se devuelve la cadena modificada.
}
