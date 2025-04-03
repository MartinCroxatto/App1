#include <stdio.h>      // Biblioteca para entrada/salida estándar.
#include <stdlib.h>     // Biblioteca para funciones de conversión y manejo de memoria.
#include <string.h>     // Biblioteca para manipulación de cadenas.
#include <ctype.h>      // Biblioteca para funciones de clasificación de caracteres (como isspace).
#include "csv_reader.h" // Incluye el header donde se define la estructura 'order' y el prototipo de leer_csv.

int leer_csv(const char * nombre_archivo, struct orden ordenes[], int ordenes_maximas) {
    // Abrir el archivo en modo lectura ("r").
    FILE * archivo = fopen(nombre_archivo, "r");
    if (!archivo) {
        // Si no se pudo abrir, imprimir mensaje de error y retornar 0.
        perror("No se pudo abrir el archivo");
        return 0;
    }
    
    char linea[2048];  // Buffer para almacenar cada línea del archivo.
    int contador = 0;    // Contador para la cantidad de órdenes leídas.
    
    // Leer y descartar la línea de encabezado (la primera línea del CSV).
    if (fgets(linea, sizeof(linea), archivo) == NULL) {
        fclose(archivo);
        return 0; // Si no se pudo leer el encabezado, retorna 0.
    }
    
    // Bucle para leer cada línea restante del archivo CSV.
    while (contador < ordenes_maximas && fgets(linea, sizeof(linea), archivo)) {
        // Verificar si la línea está vacía o contiene solo espacios.
        int espacio_en_blanco = 1;
        for (int i = 0; linea[i] != '\0'; i++) {
            if (!isspace((unsigned char)linea[i])) {
                espacio_en_blanco = 0;
                break;
            }
        }
        if (espacio_en_blanco) continue;  // Si la línea es vacía, salta a la siguiente iteración.

        double lector_cantidad; // Variable temporal para almacenar el campo cantidad como número.
        
        // Usamos sscanf para extraer los 12 campos de la línea, siguiendo el formato:
        // %lf        → Lee un double (para pizza_id y order_id, etc.)
        // %29[^,]   → Lee una cadena de hasta 29 caracteres, hasta encontrar una coma (para pizza_name_id)
        // %10[^,]   → Lee la fecha (order_date) con hasta 10 caracteres
        // %8[^,]    → Lee la hora (order_time) con hasta 8 caracteres
        // %9[^,]    → Lee pizza_size (hasta 9 caracteres)
        // %29[^,]   → Lee pizza_category (hasta 29 caracteres)
        // "\"%99[^\"]\"  → Lee la cadena pizza_ingredients que está entre comillas (hasta 99 caracteres)
        // %29[^\n]  → Lee pizza_name hasta el final de la línea (hasta 29 caracteres)
        int encabezados = sscanf(linea, 
            "%lf,%lf,%29[^,],%lf,%10[^,],%8[^,],%lf,%lf,%9[^,],%29[^,],\"%99[^\"]\",%29[^\n]",
            &ordenes[contador].pizza_id,        // Primer campo: pizza_id (double).
            &ordenes[contador].order_id,         // Segundo campo: order_id (double).
            ordenes[contador].pizza_name_id,      // Tercer campo: pizza_name_id (cadena).
            &lector_cantidad,                  // Cuarto campo: cantidad (se lee como double, luego se convierte a int).
            ordenes[contador].order_date,        // Quinto campo: order_date (cadena).
            ordenes[contador].order_time,        // Sexto campo: order_time (cadena).
            &ordenes[contador].unit_price,       // Séptimo campo: unit_price (double).
            &ordenes[contador].total_price,      // Octavo campo: total_price (double).
            ordenes[contador].pizza_size,        // Noveno campo: pizza_size (cadena).
            ordenes[contador].pizza_category,    // Décimo campo: pizza_category (cadena).
            ordenes[contador].pizza_ingredients, // Undécimo campo: pizza_ingredients (cadena entre comillas).
            ordenes[contador].pizza_name);       // Duodécimo campo: pizza_name (cadena).
        
        // Si se han leído correctamente los 12 campos:
        if (encabezados == 12) {
            ordenes[contador].cantidad = (int)lector_cantidad; // Convierte la cantidad a entero.
            contador++;  // Incrementa el contador de órdenes leídas.
        } else {
            // Si no se pudieron leer 12 campos, imprime un mensaje de error con la línea problematica.
            fprintf(stderr, "Error al parsear la línea: %s\n", linea);
        }
    }
    fclose(archivo);   // Cierra el archivo.
    return contador;   // Retorna el número total de órdenes leídas.
}
