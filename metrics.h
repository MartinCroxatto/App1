#ifndef METRICS_H
#define METRICS_H

#include "csv_reader.h"

typedef char* (*MetricFunction)(int *size, struct order *orders);

// Declaración de las funciones de métricas:
char* pms(int *size, struct order *orders);   // Pizza más vendida
char* pls(int *size, struct order *orders);   // Pizza menos vendida
char* dms(int *size, struct order *orders);   // Fecha con más ventas en dinero
char* dls(int *size, struct order *orders);   // Fecha con menos ventas en dinero
char* dmsp(int *size, struct order *orders);  // Fecha con más pizzas vendidas
char* dlsp(int *size, struct order *orders);  // Fecha con menos pizzas vendidas
char* apo(int *size, struct order *orders);   // Promedio de pizzas por orden
char* apd(int *size, struct order *orders);   // Promedio de pizzas por día
char* ims(int *size, struct order *orders);   // Ingrediente más vendido
char* hp(int *size, struct order *orders);    // Pizzas por categoría vendidas

#endif
