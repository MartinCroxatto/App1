#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "csv_reader.h"

int read_csv(const char *filename, struct order orders[], int max_orders) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("No se pudo abrir el archivo");
        return 0;
    }
    
    char line[2048];  // Buffer suficientemente grande para cada línea.
    int count = 0;
    
    // Leer y descartar la línea de encabezado.
    if (fgets(line, sizeof(line), file) == NULL) {
        fclose(file);
        return 0;
    }
    
    // Leer línea a línea el archivo CSV.
    while (count < max_orders && fgets(line, sizeof(line), file)) {
        double temp_quantity;
        // Se usa un formato que reconoce el campo pizza_ingredients entre comillas.
        int fields = sscanf(line, "%lf,%lf,%29[^,],%lf,%10[^,],%8[^,],%lf,%lf,%9[^,],%29[^,],\"%99[^\"]\",%29[^\n]",
            &orders[count].pizza_id,
            &orders[count].order_id,
            orders[count].pizza_name_id,
            &temp_quantity,
            orders[count].order_date,
            orders[count].order_time,
            &orders[count].unit_price,
            &orders[count].total_price,
            orders[count].pizza_size,
            orders[count].pizza_category,
            orders[count].pizza_ingredients,
            orders[count].pizza_name);
        
        if (fields == 12) {
            orders[count].quantity = (int)temp_quantity;
            count++;
        } else {
            fprintf(stderr, "Error al parsear la línea: %s\n", line);
        }
    }
    fclose(file);
    return count;
}
