#ifndef METRICS_H
#define METRICS_H

#include "csv_reader.h"

// Tipo de puntero a función para todas las métricas
// Recibe un puntero a int (cantidad de órdenes) y un arreglo de estructuras orden
// Retorna un puntero a char (mensaje con el resultado de la métrica)
typedef char* (*MetricFunction)(int *size, struct orden *ordenes);

// ───────────── Declaración de funciones de métricas ─────────────

// Métricas de ventas por pizza
char* pms(int *size, struct orden *ordenes);    // Pizza más vendida
char* pls(int *size, struct orden *ordenes);    // Pizza menos vendida

// Métricas de ventas por dinero
char* dms(int *size, struct orden *ordenes);    // Fecha con más ventas en dinero
char* dls(int *size, struct orden *ordenes);    // Fecha con menos ventas en dinero

// Métricas de ventas por cantidad de pizzas
char* dmsp(int *size, struct orden *ordenes);   // Fecha con más pizzas vendidas
char* dlsp(int *size, struct orden *ordenes);   // Fecha con menos pizzas vendidas

// Métricas de promedios
char* apo(int *size, struct orden *ordenes);    // Promedio de pizzas por orden
char* apd(int *size, struct orden *ordenes);    // Promedio de pizzas por día

// Métrica de ingredientes
char* ims(int *size, struct orden *ordenes);    // Ingrediente más vendido

// Métrica por categoría
char* hp(int *size, struct orden *ordenes);     // Pizzas por categoría vendidas

#endif
