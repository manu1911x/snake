#ifndef MENU_H
#define MENU_H

#define ANCHO 80
#define ALTO  40

// Inicializa la consola y dibuja el marco (activar=1), o la restaura (activar=0)
void init_terminal(int trigger);

// Mueve el cursor a una coordenada (1-indexada)
void mcursor(int fila, int col);

// Ejecuta el menú interactivo. Retorna 0 (Jugar) o 1 (Salir)
int init_menu();

#endif
