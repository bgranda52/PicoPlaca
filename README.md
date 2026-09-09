# PicoPlaca

Ejercicio de consola de pico y placa (Quito clasico de laboratorio).

Archivo principal: `pico_placa.cpp` (menu, texto en espanol, colores ANSI).

## Compilar y ejecutar

Linux / macOS / MSYS2:

```bash
g++ -o pico_placa pico_placa.cpp
./pico_placa
```

Windows (MSYS2 UCRT64):

```bash
g++ -o pico_placa.exe pico_placa.cpp
./pico_placa.exe
```

## Menu

1. Consultar si puede circular (placa, dia, hora)
2. Ver reglas
3. Salir

## Regla del ejercicio

| Dia | Digitos que no circulan |
|---|---|
| Lunes | 1 y 2 |
| Martes | 3 y 4 |
| Miercoles | 5 y 6 |
| Jueves | 7 y 8 |
| Viernes | 9 y 0 |
| Sabado y domingo | sin restriccion |

Horario restringido: 07:00-09:00 y 16:00-19:00.

Esta es la regla academica de esa epoca, no la normativa vigente de cada ciudad.
