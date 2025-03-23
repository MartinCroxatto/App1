#ifndef CSV_READER_H
#define CSV_READER_H

#define MAX_ORDERS 1000

// Estructura que representa una orden con los 12 campos del CSV.
struct order {
    double pizza_id;          // Ejemplo: 1.00
    double order_id;          // Ejemplo: 1.00
    char pizza_name_id[30];   // Ejemplo: hawaiian_m
    int quantity;             // Se lee como 1.00 y se convierte a 1
    char order_date[11];      // Ejemplo: 1/1/2015
    char order_time[9];       // Ejemplo: 11:38:36
    double unit_price;        // Ejemplo: 13.25
    double total_price;       // Ejemplo: 13.25
    char pizza_size[10];      // Ejemplo: M
    char pizza_category[30];  // Ejemplo: Classic
    char pizza_ingredients[100]; // Ejemplo: Sliced Ham, Pineapple, Mozzarella Cheese
    char pizza_name[30];      // Ejemplo: The Hawaiian Pizza
};

int read_csv(const char *filename, struct order orders[], int max_orders);

#endif

