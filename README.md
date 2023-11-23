# Sport JSON Parser

Un compilador para crear formaciones de deportes a partir de un JSON.
Basado en el compilador "Flex-Bison-Compiler" de Agustin Golmar: https://github.com/agustin-golmar/Flex-Bison-Compiler


## Grupo
* Mariano Agopian (62317)
* Matias Luchetti (62337)
* Santiago Medin (62076)
* Sofia Altman (62030)

## Sintaxis

```
 {
 "deporte" : "Futbol 5 || Futbol 8 || Futbol 11 ||  Hockey 8 || Hockey 11 || Basquet 3 || Basquet 5 "
 "probabilidades" : "XX-XX-XX" (linea opcional, donde XX es un entero de dos digitos)
 "equipos": [
       {
        "nombre": "Equipo 1",
        "formacion": "X-X-X" (donde cada X es un digito),
        "jugadores": [
          {
            "jugador": "Jugador 1"
          }, 
        {
            "jugador": "Jugador 2"
        } (repetido la cantidad de veces correspondiente a la cantidad de jugadores mencionadas en el deporte)
        ]
      },
      {  
        "nombre": "Equipo 1",
        "formacion": "X-X-X" (donde cada X es un digito),
        "jugadores": [
          {
            "jugador": "Jugador 1"
          }, 
        {
            "jugador": "Jugador 2"
        } (repetido la cantidad de veces correspondiente a la cantidad de jugadores mencionadas en el deporte)
        ]
      }
    ]
}

```


Observaciones: los whitespaces son ignorados, la cantidad de elementos dentro de jugadores debe coincidir con el deporte elegido

Ejemplo : (puede encontrar los casos de  en la carpeta de tests): 

```
{
    "deporte": "Futbol 5",
    "probabilidades": "60-20-20",
    "equipos": [
      {
        "nombre": "Equipo 1",
        "formacion": "2-2-1",
        "jugadores": [
          {
            "jugador": "Jugador 1"
          },
          {
            "jugador": "Jugador 2"
          },
          {
            "jugador": "Jugador 3"
          },
          {
            "jugador": "Jugador 4"
          },
          {
            "jugador": "Jugador 5"        
          }
        ]
      },
      {
        "nombre": "Equipo 2",
        "formacion": "1-2-1",
        "jugadores": [
          {
            "jugador": "Jugador 6"        
          },
          {
            "jugador": "Jugador 7"
          },
          {
            "jugador": "Jugador 8"
          },
          {
            "jugador": "Jugador 9"
          },
          {
            "jugador": "Jugador 10"
          }
        ]
      }
    ]
  }
```

## Requerimientos

Para construir el compilador, se requieren las siguientes dependencias:

* [Bison v3.8.2](https://www.gnu.org/software/bison/)
* [CMake v3.24.1](https://cmake.org/)
* [Flex v2.6.4](https://github.com/westes/flex)
* [GCC v11.1.0](https://gcc.gnu.org/)
* [Make v4.3](https://www.gnu.org/software/make/)

Si en lugar de trabajar con un entorno _Linux_, se está construyendo el proyecto sobre un entorno _Microsoft Windows_, se debe instalar _Microsoft Visual Studio 2022_ con las extensiones para desarrollar aplicaciones en _C/C++_, así como también las herramientas requeridas, con excepción del compilador _GCC_ y la herramienta _Make_.

## Construcción

Para construir el proyecto por completo, ejecute en la raíz del repositorio los siguientes comandos (en _Linux_):

```bash
user@machine:path/ $ chmod u+x --recursive script
user@machine:path/ $ script/build.sh
```

En un entorno _Microsoft Windows_, en cambio, se debe ejecutar:

```bash
user@machine:path/ $ script\build.bat
```

Luego se deberá abrir la solución generada `bin\Compiler.sln` con el IDE _Microsoft Visual Studio 2022_. Los ejecutables que este sistema construye se depositan dentro del directorio `bin\Debug` y `bin\Release`, según corresponda.

## Ejecución

Para compilar un programa, primero cree un archivo vacío denominado `program` (o el nombre que desee), con el siguiente contenido:

```
{
    "deporte": "Basquet 3",
    "probabilidades": "30-40-30",
    "equipos": [
      {
        "nombre": "Equipo 1",
        "formacion": "1-2",
        "jugadores": [
          {
            "jugador": "Jugador 1"
          },
          {
            "jugador": "Jugador 2"
          },
          {
            "jugador": "Jugador 3"
          }
        ]
      },
      {
        "nombre": "Equipo 2",
        "formacion": "2-1",
        "jugadores": [
          {
            "jugador": "Jugador 4"        
          },
          {
            "jugador": "Jugador 5"
          },
          {
            "jugador": "Jugador 6"
          }
        ]
      }
    ]
  }
```

Luego, ejecute el compilador desde el directorio raíz del proyecto, o desde cualquier otro lugar indicando el path hacia el script `start.sh` y pasando por parámetro el path hacia el programa a compilar:

```bash
user@machine:path/ $ script/start.sh program
```

En Windows:

```bash
user@machine:path/ $ script\start.bat program
```

## Cleam
Para limpiar los codigos objeto.

En Linux:

```bash
user@machine:path/ $ script/clean.sh 
```

En Windows:

```bash
user@machine:path/ $ script\clean.bat 
```


## Testing

En Linux:

```bash
user@machine:path/ $ script/test.sh
```

En Windows:

```bash
user@machine:path/ $ script\test.bat
```

Si desea agregar nuevos casos de uso, deberá crear un archivo por cada uno, que contenga el programa a testear dentro de las carpetas `test/accept` o `test/reject` según corresponda (es decir, si el mismo debe ser aceptado o rechazado por el compilador).

Si el programa se compila sin errores y pasa las verificaciones, se generara un archivo match.html dentro de la carpeta out en la raiz del proyecto.

