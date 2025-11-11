#include <stdio.h>
#include <locale.h>

int main() {
    setlocale(LC_ALL, "");

    printf("%c%c%c%c%c\n", 218, 196, 196, 196, 191);
    printf("%c   %c\n", 179, 179);
    printf("%c%c%c%c%c\n\n", 192, 196, 196, 196, 217);

    return 0;
}
