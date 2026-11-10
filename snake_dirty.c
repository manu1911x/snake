#include <stdio.h>
#include <conio.h>
#include <windows.h>

#define ANCHO 80
#define ALTO  80

void mcursor(int fila, int col) {
  COORD position = {(SHORT)(col - 1), (SHORT)(fila - 1)};
  SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), position);
}

void init_terminal(int trigger) {
  static CONSOLE_CURSOR_INFO original_cursor;
  static HANDLE console;

  if (trigger) {
    console = GetStdHandle(STD_OUTPUT_HANDLE);
    GetConsoleCursorInfo(console, &original_cursor);

    CONSOLE_CURSOR_INFO cursor = original_cursor;
    cursor.bVisible = FALSE;
    SetConsoleCursorInfo(console, &cursor);

    COORD size = {(SHORT)ANCHO, (SHORT)ALTO};
    SMALL_RECT window = {0, 0, (SHORT)(ANCHO - 1), (SHORT)(ALTO - 1)};
    SetConsoleScreenBufferSize(console, size);
    SetConsoleWindowInfo(console, TRUE, &window);

    DWORD cells = (DWORD)ANCHO * ALTO;
    DWORD written;
    COORD origin = {0, 0};
    FillConsoleOutputCharacterA(console, ' ', cells, origin, &written);
    FillConsoleOutputAttribute(console, FOREGROUND_RED | FOREGROUND_GREEN |
                                        FOREGROUND_BLUE,
                               cells, origin, &written);

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
    CONSOLE_CURSOR_INFO cursor = original_cursor;
    SetConsoleCursorInfo(console, &cursor);
    COORD origin = {0, 0};
    SetConsoleCursorPosition(console, origin);
    DWORD cells = (DWORD)ANCHO * ALTO;
    DWORD written;
    FillConsoleOutputCharacterA(console, ' ', cells, origin, &written);
    fflush(stdout);
  }
}

int init_menu(void) {
  int sel = 0; // 0 = Jugar, 1 = Salir
  while (1) {
    mcursor(ALTO / 2 -8, (ANCHO - 5) / 2);
    printf("SNAKE");

    mcursor(ALTO / 2 - 4, (ANCHO - 9) / 2);
    printf("%s JUGAR ", (sel == 0) ? ">" : " ");

    mcursor(ALTO / 2, (ANCHO - 9) / 2);
    printf("%s SALIR ", (sel == 1) ? ">" : " ");
    fflush(stdout);

    int key = _getch();
    if (key == 0 || key == 224) {
      key = _getch();
      if (key == 72 || key == 80) sel = !sel;
    } else if (key == '\r' || key == '\n') {
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
