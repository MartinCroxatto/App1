################################################################################################
# 1.
# Se define CC = gcc, 
# Lo que significa que se usará el compilador gcc 
# Esto nos permite compilar todos los archivos fuente para generar un ejecutable.
CC = gcc

################################################################################################
# 2.
# se define un objetivo "all" que depende de "app1".
# El objetivo del Makefile al fin y al cabo es generar un ejecutable llamado "app1".
all: app1

################################################################################################
# 3.
# Regla para construir el ejecutable "app1".
# Se especifican los archivos que se necesitan (main.o, csv_reader.o, metrics.o y utils.o.) para generar el ejecutable "app1".
# La línea siguiente ($(CC)...) indica que se llama a gcc para enlazar esos archivos objeto y producir el ejecutable "app1".
app1: main.o csv_reader.o metrics.o utils.o
	$(CC) -o app1 main.o csv_reader.o metrics.o utils.o

################################################################################################
# 4.
# Regla para compilar "main.c" y generar "main.o".
# indica que "main.o" depende de "main.c" y de los archivos de cabecera necesarios (csv_reader.h, metrics.h, utils.h).
# La línea $(CC)... compila "main.c" en "main.o" sin realizar el enlace final
main.o: main.c csv_reader.h metrics.h utils.h
	$(CC) -c main.c


# Regla para compilar "csv_reader.c" y generar "csv_reader.o".
# similarmente al punto anterior, indica que se compila "csv_reader.c" (que depende de su header) en "csv_reader.o"
csv_reader.o: csv_reader.c csv_reader.h
	$(CC) -c csv_reader.c


# Regla para compilar "metrics.c" y generar "metrics.o".
# Se compila "metrics.c" (con dependencia de "metrics.h" y "csv_reader.h") en "metrics.o"
metrics.o: metrics.c metrics.h csv_reader.h
	$(CC) -c metrics.c


# Regla para compilar "utils.c" y generar "utils.o".
# Se compila "utils.c" (con dependencia de "utils.h") en "utils.o"
utils.o: utils.c utils.h
	$(CC) -c utils.c

################################################################################################
# 5.
# Regla para limpiar (borrar) los archivos objeto y el ejecutable generado.
# Aqui en caso de que se necesite se borran todos los archivos con extensión .o y el archivo "app1"
# permitiéndo realizar una compilación limpia la próxima vez, esto es útil cuando se realizan cambios en el código fuente.
clean:
	rm -f *.o app1











