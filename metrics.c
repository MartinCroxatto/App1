#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "metrics.h"

/*──────────────────────────────────────────────────────────────────────*/
/*       FUNCIÓN GENERAL PARA PIZZAS MÁS/MENOS VENDIDAS   pms/pls       */
/*──────────────────────────────────────────────────────────────────────*/
char* pizza_extrema(int *cant_total_ordenes, struct orden *ordenes, int buscar_max) {
    // Definimos una estructura local llamada 'cuenta' para agrupar pizzas y sus cantidades
    typedef struct { char nombre[30]; int total; } cuenta;    

    // Creamos un arreglo de cuentas, donde se almacenarán las pizzas únicas y su cantidad total
    cuenta cuentas[100] = {0};  
    int ncuentas = 0;  // Contador de cuántas pizzas distintas llevamos registradas

    // Recorremos todas las órdenes para agrupar cantidades por nombre de pizza
    for (int i = 0; i < *cant_total_ordenes; i++) {
        int ya_existe = 0; // Bandera que indica si la pizza ya fue registrada

        // Recorremos las pizzas registradas para ver si la actual ya existe
        for (int j = 0; j < ncuentas; j++) {
            if (strcmp(cuentas[j].nombre, ordenes[i].pizza_name) == 0) {
                cuentas[j].total += ordenes[i].cantidad;  // Si ya existe, sumamos la cantidad
                ya_existe = 1;
                break;
            }
        }

        // Si no existe, la agregamos como nueva pizza al arreglo
        if (!ya_existe && ncuentas < 100) {
            strcpy(cuentas[ncuentas].nombre, ordenes[i].pizza_name); // Copiamos el nombre
            cuentas[ncuentas].total = ordenes[i].cantidad;           // Guardamos su cantidad
            ncuentas++;  // Aumentamos el contador de pizzas distintas
        }
    }

    // Inicializamos el valor extremo (máximo o mínimo según se indique)
    int valor_extremo = cuentas[0].total;
    char mejor[30];
    strcpy(mejor, cuentas[0].nombre); // Tomamos la primera pizza como referencia inicial

    // Buscamos la pizza con más o menos cantidad vendida
    for (int j = 1; j < ncuentas; j++) {
        if ((buscar_max && cuentas[j].total > valor_extremo) || 
            (!buscar_max && cuentas[j].total < valor_extremo)) {
            valor_extremo = cuentas[j].total;            // Actualizamos el valor
            strcpy(mejor, cuentas[j].nombre);            // Guardamos el nombre
        }
    }

    // Creamos una cadena dinámica para devolver el resultado
    char *resultado = malloc(100);
    sprintf(resultado, "Pizza %s vendida: %s (cantidad: %d)",
            buscar_max ? "mas" : "menos",  // "mas" si buscar_max es 1, "menos" si es 0
            mejor,                         // nombre de la pizza
            valor_extremo);                // cantidad total
    return resultado;  // Devolvemos el mensaje con la pizza más o menos vendida
}

// Función que llama a pizza_extrema con buscar_max = 1 → pizza más vendida
char* pms(int *cant_total_ordenes, struct orden *ordenes) {
    return pizza_extrema(cant_total_ordenes, ordenes, 1);
}

// Función que llama a pizza_extrema con buscar_max = 0 → pizza menos vendida
char* pls(int *cant_total_ordenes, struct orden *ordenes) {
    return pizza_extrema(cant_total_ordenes, ordenes, 0);
}


/*─────────────────────────────────────────────────────────────────*/
/*       FUNCIÓN GENERAL PARA FECHAS MÁS/MENOS DINERO   dms/dls    */
/*─────────────────────────────────────────────────────────────────*/
char* fecha_extrema_dinero(int *cant_total_ordenes, struct orden *ordenes, int buscar_max) {
    typedef struct { char date[11]; double monto_total; } FechaVenta;
    FechaVenta fechas[100] = {0};  // Arreglo para almacenar fechas y montos totales
    int nFechas = 0;

    // Recorre todas las órdenes
    for (int i = 0; i < *cant_total_ordenes; i++) {
        int ya_existe = 0;

        // Busca si la fecha ya está en el arreglo `fechas`
        for (int j = 0; j < nFechas; j++) {
            if (strcmp(fechas[j].date, ordenes[i].order_date) == 0) {
                fechas[j].monto_total += ordenes[i].total_price;  // Suma el monto si ya existe
                ya_existe = 1;
                break;
            }
        }

        // Si no existe, agrega una nueva entrada en `fechas`
        if (!ya_existe && nFechas < 100) {
            strcpy(fechas[nFechas].date, ordenes[i].order_date);
            fechas[nFechas].monto_total = ordenes[i].total_price;
            nFechas++;
        }
    }

    // Encuentra la fecha con el valor extremo (máximo o mínimo)
    double valor_extremo = fechas[0].monto_total;
    char mejor_fecha[11];
    strcpy(mejor_fecha, fechas[0].date);

    for (int j = 1; j < nFechas; j++) {
        if ((buscar_max && fechas[j].monto_total > valor_extremo) || 
            (!buscar_max && fechas[j].monto_total < valor_extremo)) {
            valor_extremo = fechas[j].monto_total;
            strcpy(mejor_fecha, fechas[j].date);
        }
    }

    // Crea el resultado como una cadena dinámica
    char *resultado = malloc(150);
    sprintf(resultado, "Fecha %s ventas en dinero: %s (recaudado: %.2f)",
            buscar_max ? "mas" : "menos",
            mejor_fecha,
            valor_extremo);
    return resultado;  // Devuelve la cadena con el resultado
}

char* dms(int *cant_total_ordenes, struct orden *ordenes) {
    return fecha_extrema_dinero(cant_total_ordenes, ordenes, 1);
}

char* dls(int *cant_total_ordenes, struct orden *ordenes) {
    return fecha_extrema_dinero(cant_total_ordenes, ordenes, 0);
}

