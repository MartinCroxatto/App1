#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "csv_reader.h"
#include "metrics.h"
#include "utils.h"

typedef struct {
    char *name;
    MetricFunction func;
} MetricMapping;

int main(int argc, char *argv[]) {
    if (argc < 3) {
        printf("Uso: %s <archivo_csv> <metrica1> [metrica2 ...]\n", argv[0]);
        return 1;
    }
    const char *csv_file = argv[1];
    struct order orders[MAX_ORDERS];
    int num_orders = read_csv(csv_file, orders, MAX_ORDERS);
    if (num_orders <= 0) {
        printf("No se pudo leer el archivo o no hay datos.\n");
        return 1;
    }

    // Definición de las métricas disponibles
    MetricMapping mappings[] = {
        {"pms", pms},
        {"pls", pls},
        {"dms", dms},
        {"dls", dls},
        {"dmsp", dmsp},
        {"dlsp", dlsp},
        {"apo", apo},
        {"apd", apd},
        {"ims", ims},
        {"hp", hp}
    };
    int num_mappings = sizeof(mappings) / sizeof(MetricMapping);

    // Procesa cada métrica solicitada en la línea de comandos
    for (int i = 2; i < argc; i++) {
        char *metric_arg = argv[i];
        int found = 0;
        for (int j = 0; j < num_mappings; j++) {
            if (strcmp(metric_arg, mappings[j].name) == 0) {
                char *result = mappings[j].func(&num_orders, orders);
                printf("%s\n", result);
                free(result);
                found = 1;
                break;
            }
        }
        if (!found) {
            printf("Métrica desconocida: %s\n", metric_arg);
        }
    }
    return 0;
}

