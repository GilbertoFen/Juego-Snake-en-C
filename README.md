# Juego Snake en C

Este proyecto es una implementación del clásico juego Snake utilizando el lenguaje de programación C. El objetivo del juego es controlar una serpiente que se desplaza por la pantalla, comiendo comida para crecer y evitando chocar contra las paredes o su propio cuerpo.

## Características

- **Interfaz de usuario**: Basada en la terminal, lo que permite su ejecución en sistemas operativos Linux y Windows.
- **Controles**: Utiliza las teclas de flechas para mover la serpiente en las direcciones correspondientes.

## Requisitos

- Un compilador de C (como `gcc` en Linux o Windows con MinGW).
- Sistema operativo:
  - **Linux**: Soporte para funciones específicas de la terminal, como `gotoxy` y `kbhit`.
  - **Windows**: Es posible que se requieran algunas modificaciones para compatibilidad completa.

## Compilación e instalación

Sigue estos pasos para compilar y ejecutar el juego en tu sistema:

1. **Clonar el repositorio**:

   ```bash
   git clone https://github.com/GilbertoFen/Juego-Snake-en-C.git
   cd Juego-Snake-en-C

2. **Ejecutar el codigo fuente**
   Para Linux:
   ```bash
    gcc -o snake juego_snake.c
  Para Windows 
  ```bash
  ./snake
