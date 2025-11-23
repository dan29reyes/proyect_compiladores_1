# proyect_compiladores_1

Este es un proyecto de ejemplo para la materia de Compiladores 1. El objetivo de este proyecto es desarrollar un compilador simple que pueda traducir un lenguaje de programación básico a código máquina.

## Ejecución del Proyecto

Para ejecutar el proyecto, sigue estos pasos:

1. Clona el repositorio en tu máquina local:
   ```bash
   git clone https://github.com/dan29reyes/proyect_compiladores_1.git
   ```
2. Navega al directorio del proyecto:
   ```bash
    cd proyect_compiladores_1
   ```
3. Compila el código fuente utilizando el compilador de tu elección (por ejemplo, GCC para C/C++):

   ```bash
   #Para Macos
   clang++ -std=c++17 -Wall -Wextra -g main.cpp ErrorHandler.cpp Parser/Parser.cpp Lexer/Lexer.cpp -o my_program

   #Para Windows
   g++ Lexer/Lexer.cpp ErrorHandler.cpp Parser/Parser.cpp main.cpp -o my_program
   ```

4. Ejecuta el programa compilado:
   ```bash
   #Para Macos y Windows
   ./my_program test.txt
   ```
