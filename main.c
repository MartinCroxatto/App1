#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "csv_reader.h"
#include "metrics.h"
#include "utils.h"

// Estructura para mapear nombre de métrica con su función correspondiente
typedef struct {
    char *name;
    MetricFunction func;
} MetricMapping;

int main(int argc, char *argv[]) {
    // Verifica que se ingresen al menos 2 argumentos: archivo y al menos una métrica
    if (argc < 3) {
        printf("Uso: %s <archivo_csv> <metrica1> [metrica2 ...]\n", argv[0]);
        return 1;
    }

    const char *csv_file = argv[1];
    struct orden ordenes[ORDENES_MAXIMAS];
    
    // Lee el CSV y carga las órdenes
    int num_ordenes = leer_csv(csv_file, ordenes, ORDENES_MAXIMAS);
    if (num_ordenes <= 0) {
        printf("No se pudo leer el archivo o no hay datos.\n");
        return 1;
    }

    // Definición de las métricas disponibles
    MetricMapping mappings[] = {
        {"pms", pms},     // Pizza más vendida
        {"pls", pls},     // Pizza menos vendida
        {"dms", dms},     // Fecha con más ventas en dinero
        {"dls", dls},     // Fecha con menos ventas en dinero
        {"dmsp", dmsp},   // Fecha con más pizzas vendidas
        {"dlsp", dlsp},   // Fecha con menos pizzas vendidas
        {"apo", apo},     // Promedio de pizzas por orden
        {"apd", apd},     // Promedio de pizzas por día
        {"ims", ims},     // Ingrediente más vendido
        {"hp", hp}        // Cantidad de pizzas por categoría
    };
    int num_mappings = sizeof(mappings) / sizeof(MetricMapping);

    // Procesa cada métrica solicitada en la línea de comandos
    for (int i = 2; i < argc; i++) {
        char *metric_arg = argv[i];
        int found = 0;

        // Busca la métrica solicitada entre las disponibles
        for (int j = 0; j < num_mappings; j++) {
            if (strcmp(metric_arg, mappings[j].name) == 0) {
                char *result = mappings[j].func(&num_ordenes, ordenes);
                printf("%s\n", result);
                free(result); // liberar memoria reservada en la métrica
                found = 1;
                break;
            }
        }

        // Si la métrica no existe, lo informa
        if (!found) {
            printf("Métrica desconocida: %s\n", metric_arg);
        }
    }

    return 0;
}
