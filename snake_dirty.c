#include <stdio.h>
#include <unistd.h>
#include <termios.h>

#define ANCHO 80
#define ALTO  80

void mcursor(int fila, int col) {
  printf("\033[%d;%dH", fila, col);
}

void init_terminal(int trigger) {
  static struct termios orig;

  if (trigger) {
    // Configurar terminal y ocultar cursor
    tcgetattr(0, &orig);
    struct termios raw = orig;
    raw.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(0, TCSANOW, &raw);
    printf("\033[?25l");

    // Fijar resolucion y limpiar pantalla
    printf("\033[8;%d;%dt\033[2J\033[H", ALTO, ANCHO);

    // Dibujar bordes horizontales
    mcursor(1, 1);
    putchar('+');
    for (int i = 2; i < ANCHO; i++) putchar('-');
    putchar('+');

    mcursor(ALTO, 1);
    putchar('+');
    for (int i = 2; i < ANCHO; i++) putchar('-');
    putchar('+');

    // Dibujar bordes laterales
    for (int j = 2; j < ALTO; j++) {
      mcursor(j, 1);     putchar('|');
      mcursor(j, ANCHO); putchar('|');
    }
    fflush(stdout);
  } else {
    // Restaurar terminal y mostrar cursor
    tcsetattr(0, TCSANOW, &orig);
    printf("\033[?25h\033[2J\033[H");
    fflush(stdout);
  }
}

int init_menu(void) {
  int sel = 0; // 0 = Jugar, 1 = Salir
  char c;

  while (1) {

    // Imprime menu centrado
    mcursor(ALTO / 2 -8, (ANCHO - 5) / 2);
    printf("SNAKE");

    mcursor(ALTO / 2 - 4, (ANCHO - 9) / 2);
    printf("%s JUGAR ", (sel == 0) ? ">" : " ");

    mcursor(ALTO / 2, (ANCHO - 9) / 2);
    printf("%s SALIR ", (sel == 1) ? ">" : " ");
    fflush(stdout);

    // Lectura dinamica de inputs (tiempo real)
    read(0, &c, 1);
    if (c == '\033') {
      // Las flechas dan como output codigo ANSI que se debe leer de manera diferente
      char seq[2];
      read(0, &seq[0], 1);
      read(0, &seq[1], 1);
      if (seq[0] == '[' && (seq[1] == 'A' || seq[1] == 'B')) {
        // Se alterna el valor de seleccion entre 0 y 1
        sel = !sel;
      }
    } else if (c == '\n' || c == '\r') {
      return sel;
    }
  }
}

int main() {
  init_terminal(1); 

  int opcion = init_menu();

  init_terminal(0);
  printf("Opcion seleccionada: %d\n", opcion);
  return 0;
}
