#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "metrics.h"

/* ---------------------- pms: Pizza más vendida ---------------------- */
char* pms(int *size, struct order *orders) {
    typedef struct { char type[30]; int total; } PizzaCount;
    PizzaCount counts[100];
    int count_types = 0;
    for (int i = 0; i < *size; i++) {
        int found = 0;
        // Se usa el nombre de la pizza, que ahora está en pizza_name
        for (int j = 0; j < count_types; j++) {
            if (strcmp(counts[j].type, orders[i].pizza_name) == 0) {
                counts[j].total += orders[i].quantity;
                found = 1;
                break;
            }
        }
        if (!found && count_types < 100) {
            strcpy(counts[count_types].type, orders[i].pizza_name);
            counts[count_types].total = orders[i].quantity;
            count_types++;
        }
    }
    int max = -1;
    char best[30] = "";
    for (int j = 0; j < count_types; j++) {
        if (counts[j].total > max) {
            max = counts[j].total;
            strcpy(best, counts[j].type);
        }
    }
    char *result = malloc(100);
    sprintf(result, "Pizza más vendida: %s (cantidad: %d)", best, max);
    return result;
}

/* ---------------------- pls: Pizza menos vendida ---------------------- */
char* pls(int *size, struct order *orders) {
    typedef struct { char type[30]; int total; } PizzaCount;
    PizzaCount counts[100];
    int count_types = 0;
    for (int i = 0; i < *size; i++) {
        int found = 0;
        for (int j = 0; j < count_types; j++) {
            if (strcmp(counts[j].type, orders[i].pizza_name) == 0) {
                counts[j].total += orders[i].quantity;
                found = 1;
                break;
            }
        }
        if (!found && count_types < 100) {
            strcpy(counts[count_types].type, orders[i].pizza_name);
            counts[count_types].total = orders[i].quantity;
            count_types++;
        }
    }
    int min = (count_types > 0) ? counts[0].total : 0;
    char best[30] = "";
    if (count_types > 0) strcpy(best, counts[0].type);
    for (int j = 1; j < count_types; j++) {
        if (counts[j].total < min) {
            min = counts[j].total;
            strcpy(best, counts[j].type);
        }
    }
    char *result = malloc(100);
    sprintf(result, "Pizza menos vendida: %s (cantidad: %d)", best, min);
    return result;
}

/* ---------------------- dms: Fecha con más ventas en dinero ---------------------- */
char* dms(int *size, struct order *orders) {
    typedef struct { char date[11]; double revenue; } DateRevenue;
    DateRevenue dates[100];
    int count_dates = 0;
    for (int i = 0; i < *size; i++) {
        int found = 0;
        // Se usa order_date en lugar de date
        for (int j = 0; j < count_dates; j++) {
            if (strcmp(dates[j].date, orders[i].order_date) == 0) {
                dates[j].revenue += orders[i].total_price;
                found = 1;
                break;
            }
        }
        if (!found && count_dates < 100) {
            strcpy(dates[count_dates].date, orders[i].order_date);
            dates[count_dates].revenue = orders[i].total_price;
            count_dates++;
        }
    }
    double max_rev = -1;
    char best_date[11] = "";
    for (int j = 0; j < count_dates; j++) {
        if (dates[j].revenue > max_rev) {
            max_rev = dates[j].revenue;
            strcpy(best_date, dates[j].date);
        }
    }
    char *result = malloc(100);
    sprintf(result, "Fecha con más ventas en dinero: %s (recaudado: %.2f)", best_date, max_rev);
    return result;
}

/* ---------------------- dls: Fecha con menos ventas en dinero ---------------------- */
char* dls(int *size, struct order *orders) {
    typedef struct { char date[11]; double revenue; } DateRevenue;
    DateRevenue dates[100];
    int count_dates = 0;
    for (int i = 0; i < *size; i++) {
        int found = 0;
        for (int j = 0; j < count_dates; j++) {
            if (strcmp(dates[j].date, orders[i].order_date) == 0) {
                dates[j].revenue += orders[i].total_price;
                found = 1;
                break;
            }
        }
        if (!found && count_dates < 100) {
            strcpy(dates[count_dates].date, orders[i].order_date);
            dates[count_dates].revenue = orders[i].total_price;
            count_dates++;
        }
    }
    double min_rev = (count_dates > 0) ? dates[0].revenue : 0;
    char best_date[11] = "";
    if (count_dates > 0) strcpy(best_date, dates[0].date);
    for (int j = 1; j < count_dates; j++) {
        if (dates[j].revenue < min_rev) {
            min_rev = dates[j].revenue;
            strcpy(best_date, dates[j].date);
        }
    }
    char *result = malloc(100);
    sprintf(result, "Fecha con menos ventas en dinero: %s (recaudado: %.2f)", best_date, min_rev);
    return result;
}

/* ---------------------- dmsp: Fecha con más pizzas vendidas ---------------------- */
char* dmsp(int *size, struct order *orders) {
    typedef struct { char date[11]; int pizzas; } DatePizzas;
    DatePizzas dates[100];
    int count_dates = 0;
    for (int i = 0; i < *size; i++) {
        int found = 0;
        // Se usa order_date
        for (int j = 0; j < count_dates; j++) {
            if (strcmp(dates[j].date, orders[i].order_date) == 0) {
                dates[j].pizzas += orders[i].quantity;
                found = 1;
                break;
            }
        }
        if (!found && count_dates < 100) {
            strcpy(dates[count_dates].date, orders[i].order_date);
            dates[count_dates].pizzas = orders[i].quantity;
            count_dates++;
        }
    }
    int max_pizzas = -1;
    char best_date[11] = "";
    for (int j = 0; j < count_dates; j++) {
        if (dates[j].pizzas > max_pizzas) {
            max_pizzas = dates[j].pizzas;
            strcpy(best_date, dates[j].date);
        }
    }
    char *result = malloc(100);
    sprintf(result, "Fecha con más pizzas vendidas: %s (cantidad: %d)", best_date, max_pizzas);
    return result;
}

/* ---------------------- dlsp: Fecha con menos pizzas vendidas ---------------------- */
char* dlsp(int *size, struct order *orders) {
    typedef struct { char date[11]; int pizzas; } DatePizzas;
    DatePizzas dates[100];
    int count_dates = 0;
    for (int i = 0; i < *size; i++) {
        int found = 0;
        for (int j = 0; j < count_dates; j++) {
            if (strcmp(dates[j].date, orders[i].order_date) == 0) {
                dates[j].pizzas += orders[i].quantity;
                found = 1;
                break;
            }
        }
        if (!found && count_dates < 100) {
            strcpy(dates[count_dates].date, orders[i].order_date);
            dates[count_dates].pizzas = orders[i].quantity;
            count_dates++;
        }
    }
    int min_pizzas = (count_dates > 0) ? dates[0].pizzas : 0;
    char best_date[11] = "";
    if (count_dates > 0) strcpy(best_date, dates[0].date);
    for (int j = 1; j < count_dates; j++) {
        if (dates[j].pizzas < min_pizzas) {
            min_pizzas = dates[j].pizzas;
            strcpy(best_date, dates[j].date);
        }
    }
    char *result = malloc(100);
    sprintf(result, "Fecha con menos pizzas vendidas: %s (cantidad: %d)", best_date, min_pizzas);
    return result;
}

/* ---------------------- apo: Promedio de pizzas por orden ---------------------- */
char* apo(int *size, struct order *orders) {
    int total = 0;
    for (int i = 0; i < *size; i++) {
        total += orders[i].quantity;
    }
    double avg = (*size > 0) ? (double)total / *size : 0.0;
    char *result = malloc(100);
    sprintf(result, "Promedio de pizzas por orden: %.2f", avg);
    return result;
}

/* ---------------------- apd: Promedio de pizzas por día ---------------------- */
char* apd(int *size, struct order *orders) {
    typedef struct { char date[11]; int pizzas; } DatePizzas;
    DatePizzas dates[100];
    int count_dates = 0;
    for (int i = 0; i < *size; i++) {
        int found = 0;
        for (int j = 0; j < count_dates; j++) {
            if (strcmp(dates[j].date, orders[i].order_date) == 0) {
                dates[j].pizzas += orders[i].quantity;
                found = 1;
                break;
            }
        }
        if (!found && count_dates < 100) {
            strcpy(dates[count_dates].date, orders[i].order_date);
            dates[count_dates].pizzas = orders[i].quantity;
            count_dates++;
        }
    }
    int total = 0;
    for (int j = 0; j < count_dates; j++) {
        total += dates[j].pizzas;
    }
    double avg = (count_dates > 0) ? (double)total / count_dates : 0.0;
    char *result = malloc(100);
    sprintf(result, "Promedio de pizzas por día: %.2f", avg);
    return result;
}

/* ---------------------- ims: Ingrediente más vendido ---------------------- */
char* ims(int *size, struct order *orders) {
    typedef struct { char ingredient[50]; int count; } IngredientCount;
    IngredientCount counts[100];
    int count_ing = 0;
    for (int i = 0; i < *size; i++) {
        int found = 0;
        // Se usa pizza_ingredients en lugar de ingredients
        for (int j = 0; j < count_ing; j++) {
            if (strcmp(counts[j].ingredient, orders[i].pizza_ingredients) == 0) {
                counts[j].count += orders[i].quantity;
                found = 1;
                break;
            }
        }
        if (!found && count_ing < 100) {
            strcpy(counts[count_ing].ingredient, orders[i].pizza_ingredients);
            counts[count_ing].count = orders[i].quantity;
            count_ing++;
        }
    }
    int max_count = -1;
    char best[50] = "";
    for (int j = 0; j < count_ing; j++) {
        if (counts[j].count > max_count) {
            max_count = counts[j].count;
            strcpy(best, counts[j].ingredient);
        }
    }
    char *result = malloc(100);
    sprintf(result, "Ingrediente más vendido: %s (cantidad: %d)", best, max_count);
    return result;
}

/* ---------------------- hp: Pizzas por categoría vendidas ---------------------- */
char* hp(int *size, struct order *orders) {
    typedef struct { char category[30]; int total; } CategoryCount;
    CategoryCount counts[100];
    int count_cat = 0;
    for (int i = 0; i < *size; i++) {
        int found = 0;
        // Se usa pizza_category en lugar de category
        for (int j = 0; j < count_cat; j++) {
            if (strcmp(counts[j].category, orders[i].pizza_category) == 0) {
                counts[j].total += orders[i].quantity;
                found = 1;
                break;
            }
        }
        if (!found && count_cat < 100) {
            strcpy(counts[count_cat].category, orders[i].pizza_category);
            counts[count_cat].total = orders[i].quantity;
            count_cat++;
        }
    }
    char *result = malloc(300);
    result[0] = '\0';
    for (int j = 0; j < count_cat; j++) {
        char buffer[50];
        sprintf(buffer, "%s: %d; ", counts[j].category, counts[j].total);
        strcat(result, buffer);
    }
    return result;
}
