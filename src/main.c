#include "backend/support/shared.h"
#include "backend/code-generation/generator.h"
#include "backend/support/logger.h"
#include "frontend/syntactic-analysis/bison-parser.h"
#include <stdio.h>
#include "backend/semantic-analysis/symbol-table.h"
#include "backend/support/table-list.h"
// Estado de la aplicación.
CompilerState state = {false, 0, NULL};


// Punto de entrada principal del compilador.
const int main(const int argumentCount, const char ** arguments) {
	// Inicializar estado de la aplicación.

	state.program = NULL;
	state.result = 0;
	state.succeed = false;

	// Mostrar parámetros recibidos por consola.
	for (int i = 0; i < argumentCount; ++i) {
		LogInfo("Argumento %d: '%s'", i, arguments[i]);
	}

	symbolTableInit();

	// Compilar el programa de entrada.
	LogInfo("Compilando...\n");
	int result = yyparse();
	int preResult = result;
	switch (preResult) {
		case 0:
			// La variable "succeed" es la que setea Bison al identificar el símbolo
			// inicial de la gramática satisfactoriamente.
			if (state.succeed) {
				LogInfo("La compilacion fue exitosa.");
				int a = Generator(state.program);

				switch(a){
					case 0:
						LogInfo("Generacion exitosa");
						break;
					case -1:
						LogError("Error en tiempo de generacion de codigo");
						result = -1;
						break;
					default:
					LogInfo("tira error %d",a);
				}

				
			}
			else {
				LogError("Se produjo un error en la aplicacion.");
				return -1;
			}
			break;
		case 1:
			LogError("Bison finalizo debido a un error de sintaxis.");
			break;
		case 2:
			LogError("Bison finalizo abruptamente debido a que ya no hay memoria disponible.");
			break;
		default:
			LogError("Error desconocido mientras se ejecutaba el analizador Bison (codigo %d).", result);
	}
	symbolTableFree();

	LogInfo("Fin.");
	return result;
}
