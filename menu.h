#ifndef MENU_H
#define MENU_H

#define ANCHO 80
#define ALTO  40

// Inicializa tamaño, modo raw y dibuja marco (activar=1), o restaura terminal (activar=0)
void init_terminal(int trigger);

// Mueve el cursor a una coordenada (1-indexada)
void mcursor(int fila, int col);

// Ejecuta el menú interactivo. Retorna 0 (Jugar) o 1 (Salir)
int init_menu();

#endif
