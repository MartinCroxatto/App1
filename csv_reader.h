#ifndef CSV_READER_H           // Si CSV_READER_H no está definido, continúa con la siguiente línea.
#define CSV_READER_H           // Define CSV_READER_H para evitar que este header se incluya más de una vez.
#define ORDENES_MAXIMAS 1000  // Define la cantidad máxima de órdenes que se pueden leer del CSV.

// Estructura que representa una orden con los 12 campos del CSV.
struct orden {
    double pizza_id;          // Identificador de la pizza (ejemplo: 1.00).
    double order_id;          // Identificador de la orden (ejemplo: 1.00).
    char pizza_name_id[30];   // Identificador del nombre de la pizza (cadena, ejemplo: "hawaiian_m").
    int cantidad;             // Cantidad de pizzas en la orden; se lee como número decimal y se convierte a entero.
    char order_date[11];      // Fecha de la orden (cadena, ejemplo: "1/1/2015"). Espacio para 10 caracteres más el terminador nulo.
    char order_time[9];       // Hora de la orden (cadena, ejemplo: "11:38:36"). Espacio para 8 caracteres más el terminador nulo.
    double unit_price;        // Precio unitario de la pizza (ejemplo: 13.25).
    double total_price;       // Precio total de la orden (ejemplo: 13.25).
    char pizza_size[10];      // Tamaño de la pizza (cadena, ejemplo: "M" para mediana).
    char pizza_category[30];  // Categoría de la pizza (cadena, ejemplo: "Classic").
    char pizza_ingredients[100]; // Ingredientes de la pizza (cadena, ejemplo: "Sliced Ham, Pineapple, Mozzarella Cheese").
    char pizza_name[30];
    char orden_date[11];      
};

// Declaración de la función read_csv.
// Parámetros:
//   - Nombre_archivo: Nombre del archivo CSV a leer.
//   - ordenes: Arreglo de estructuras 'orden' donde se almacenarán las órdenes leídas.
//   - ordenes_maximas: Número máximo de órdenes que se pueden leer (definido por ORDENES_MAXIMAS).
// La función retorna el número de órdenes que se han leído correctamente.
int leer_csv(const char *nombre_archivo, struct orden ordenes[], int ordenes_maximas);

#endif // CSV_READER_H
