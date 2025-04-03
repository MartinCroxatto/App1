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


/*───────────────────────────────────────────────────────────────────────────*/
/*         FUNCIÓN GENERAL PARA FECHAS CON MÁS/MENOS PIZZAS    dmsp/dlsp     */
/*───────────────────────────────────────────────────────────────────────────*/
// Función general que calcula la fecha con más o menos pizzas vendidas.
// Se usa en dmsp (más) y dlsp (menos).
char* fecha_extrema_pizzas(int *cant_total_ordenes, struct orden *ordenes, int buscar_max) {
    // Estructura para almacenar cada fecha y la cantidad total de pizzas vendidas ese día
    typedef struct { char date[11]; int cantidad; } FechaPizzas;
    FechaPizzas fechas[100] = {0};  // Arreglo para almacenar hasta 100 fechas distintas
    int nFechas = 0;  // Contador de fechas únicas registradas

    // Recorremos todas las órdenes
    for (int i = 0; i < *cant_total_ordenes; i++) {
        int ya_existe = 0;  // Bandera para saber si ya registramos esta fecha

        // Verificamos si ya se ha contado esta fecha previamente
        for (int j = 0; j < nFechas; j++) {
            if (strcmp(fechas[j].date, ordenes[i].order_date) == 0) {
                fechas[j].cantidad += ordenes[i].cantidad;  // Sumamos las pizzas vendidas ese día
                ya_existe = 1;
                break;
            }
        }

        // Si la fecha no existe aún, la agregamos
        if (!ya_existe && nFechas < 100) {
            strcpy(fechas[nFechas].date, ordenes[i].order_date);  // Guardamos la fecha
            fechas[nFechas].cantidad = ordenes[i].cantidad;       // Guardamos la cantidad
            nFechas++;  // Aumentamos el número de fechas únicas
        }
    }

    // Inicializamos la fecha con la cantidad extrema (máxima o mínima)
    int valor_extremo = fechas[0].cantidad;
    char mejor_fecha[11];
    strcpy(mejor_fecha, fechas[0].date);  // Tomamos como referencia la primera fecha

    // Recorremos el arreglo para encontrar la mejor fecha (según buscar_max)
    for (int j = 1; j < nFechas; j++) {
        if ((buscar_max && fechas[j].cantidad > valor_extremo) ||
            (!buscar_max && fechas[j].cantidad < valor_extremo)) {
            valor_extremo = fechas[j].cantidad;         // Actualizamos el valor extremo
            strcpy(mejor_fecha, fechas[j].date);        // Guardamos la mejor fecha
        }
    }

    // Creamos el mensaje de resultado con la información encontrada
    char *resultado = malloc(100);
    sprintf(resultado, "Fecha %s pizzas vendidas: %s (cantidad: %d)",
            buscar_max ? "mas" : "menos",  // Dependiendo del valor de buscar_max se muestra "mas" o "menos"
            mejor_fecha,
            valor_extremo);
    return resultado;  // Retornamos el mensaje
}

// Función que retorna la fecha con más pizzas vendidas
char* dmsp(int *cant_total_ordenes, struct orden *ordenes) {
    return fecha_extrema_pizzas(cant_total_ordenes, ordenes, 1);
}

// Función que retorna la fecha con menos pizzas vendidas
char* dlsp(int *cant_total_ordenes, struct orden *ordenes) {
    return fecha_extrema_pizzas(cant_total_ordenes, ordenes, 0);
}


/*──────────────────────────────────────────────────────────────*/
/*    FUNCIONES PARA PROMEDIOS: POR ORDEN / POR DÍA   apo/apd   */
/*──────────────────────────────────────────────────────────────*/
char* promedio_pizzas(int *cant_total_ordenes, struct orden *ordenes, int por_dia) {
    if (por_dia) {
        // Si por_dia es verdadero (1), calculamos el promedio de pizzas por día

        // Estructura para agrupar las cantidades por fecha
        typedef struct { char date[11]; int cantidad; } FechaPizzas;
        FechaPizzas fechas[100] = {0};  // Arreglo que guarda fechas y total de pizzas vendidas por fecha
        int nFechas = 0;  // Contador de fechas únicas

        // Recorremos todas las órdenes
        for (int i = 0; i < *cant_total_ordenes; i++) {
            int ya_existe = 0;  // Bandera para saber si la fecha ya fue registrada

            // Revisamos si la fecha ya está en el arreglo
            for (int j = 0; j < nFechas; j++) {
                if (strcmp(fechas[j].date, ordenes[i].order_date) == 0) {
                    fechas[j].cantidad += ordenes[i].cantidad;  // Si existe, sumamos las pizzas
                    ya_existe = 1;
                    break;
                }
            }

            // Si no existe, la agregamos
            if (!ya_existe && nFechas < 100) {
                strcpy(fechas[nFechas].date, ordenes[i].order_date);      // Guardamos la fecha
                fechas[nFechas].cantidad = ordenes[i].cantidad;           // Guardamos la cantidad inicial
                nFechas++;
            }
        }

        // Sumamos todas las cantidades de pizzas agrupadas por fecha
        int total = 0;
        for (int j = 0; j < nFechas; j++) {
            total += fechas[j].cantidad;
        }

        // Calculamos el promedio: total de pizzas / cantidad de fechas distintas
        double promedio = (nFechas > 0) ? (double)total / nFechas : 0.0;

        // Reservamos memoria para el resultado y lo formateamos
        char *resultado = malloc(100);
        sprintf(resultado, "Promedio de pizzas por día: %.2f", promedio);
        return resultado;

    } else {
        // Si por_dia es falso (0), calculamos el promedio de pizzas por orden

        int total = 0;  // Acumulador de la cantidad total de pizzas
        for (int i = 0; i < *cant_total_ordenes; i++) {
            total += ordenes[i].cantidad;
        }

        // Calculamos el promedio: total de pizzas / total de órdenes
        double promedio = (*cant_total_ordenes > 0) ? (double)total / *cant_total_ordenes : 0.0;

        // Reservamos memoria para el resultado y lo formateamos
        char *resultado = malloc(100);
        sprintf(resultado, "Promedio de pizzas por orden: %.2f", promedio);
        return resultado;
    }
}

// Función específica para promedio por orden (llama a la función general con por_dia = 0)
char* apo(int *cant_total_ordenes, struct orden *ordenes) {
    return promedio_pizzas(cant_total_ordenes, ordenes, 0);
}

// Función específica para promedio por día (llama a la función general con por_dia = 1)
char* apd(int *cant_total_ordenes, struct orden *ordenes) {
    return promedio_pizzas(cant_total_ordenes, ordenes, 1);
}
