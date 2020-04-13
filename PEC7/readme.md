
Objetivos
● Saber modularizar el código utilizando acciones y funciones.
● Comprender la diferencia entre acción y función.
● Entender qué es un parámetro actual y distinguirlo del parámetro formal.
● Estructurar proyectos en Codelite.
Formato y fecha de entrega
Es necesario entregar la PEC antes del día ​20 de abril de 2020 a las 23:59​. Para la entrega se deberá entregar un archivo en formato ZIP, que contenga:
● Este documento con la respuesta del ejercicio 1 y el apartado b del ejercicio 2.
● El workspace de Codelite ​que contenga ​el proyecto y todas las carpetas creadas​ del ejercicio 2a
Hay que hacer la entrega en el apartado de entregas de EC del aula de teoría.
 
 __________________________ __________________________ __________________________ __________________________ __________________________

 Enunciado
 
En esta PEC continuaremos trabajando la modularidad dividiendo el código en acciones y funciones que nos permitan poderlo reutilizar. En este sentido, el ejercicio de codificación no se limita a traducir a C el ejercicio de lenguaje algorítmico. Se pide, además, estructurar el proyecto de Codelite en carpetas y ficheros.
Siguiendo con la ayuda que proporcionamos a UOCThemePark, la compañía nos ha pedido nuestra colaboración para seguir trabajando en el siguiente algoritmo, en lenguaje algorítmico, a medio diseñar.
type​
tFairgroundRideAccess = {FORBIDDEN, ALLOWED_WITH_COMPANION, ALLOWED} tFairgroundRideHeightRequirement =​ record
lessThan100: tFairgroundRideAccess; between100_120: tFairgroundRideAccess; between120_140: tFairgroundRideAccess; greaterThan140: tFairgroundRideAccess;
end record tFairgroundRide =​ record
name: ​string​;
accessHeight: tFairgroundRideHeightRequirement; durationTrip: ​integer​;
numPersonsTrip: ​integer​;
end record end type
algorithm ​UOCThemePark {algorithm to complete}
end algorithm
Ejercicio 1: Diseño en lenguaje algorítmico (40%)
Nota:​ En lenguaje algorítmico se dispone de las funciones siguientes: readFairgroundRideAccess()
readFairgroundRide()
yse acciones
copyFairgroundRide()
writeFairgroundRide()
que debéis utilizar sin necesidad de implementar.
 
 Apartado a: [25%] ​Diseña la función ​waitingTime ​que tiene un parámetro ​fRide de tipo ​tFairgroudRide y un parámetro ​people de tipo ​entero ​que indica el número de
personas que hay en la cola de la atracción, delante de nosotros. La función debe devolverun​enteroq​uerepresentaeltiempodeespera(ensegundos)hastaquenos toque subir. ​Este tiempo lo debemos calcular mirando el número de personas que entran en cada viaje a la atracción, el tiempo que dura la atracción, el tiempo que tarda en vaciarse (un tiempo constante de un minuto) y el tiempo que tarda en volver a subir toda la gente de un viaje a la atracción (también un tiempo constante de dos minutos). Sabemos que hay un 5% de las plazas en cada viaje que quedan vacías (este valor también es constante). Declara también las constantes que sean necesarias.
Apartado b: [25%] ​Diseña la función ​accessWithoutCompanion ​que tiene un parámetro ​fRide de tipo ​tFairgroudRide y un parámetro ​height de tipo ​entero ​que
indica la altura de una persona que quiere subir a la atracción. La función devuelve un​booleanoq​uenosindicasilapersonapuedesubirsolaalaatracción(true)osi debe subir acompañada (false). La función no contempla el caso de que no pueda subir, a la atracción.
Apartado c: [25%] ​Diseña la acción ​selectFairgroundRide que tiene dos parámetros de entrada ​fRide1 ​y fRide2 de tipo ​tFairgroundRide; ​tiene dos
parámetros de entrada más, ​people1 y ​people2, que son dos ​enteros que representan las personas que hay en la cola de la atracción ​fRide1 ​y fRide2, respectivamente​; y​ un parámetro de entrada ​height de tipo ​entero ​que indica la altura de una persona que quiere subir a las atracciones. La acción debe indicar, en un parámetro de salida ​myFairgroundRide ​de tipo ​tFairgroundRide, cuál es la atracción mejor para la altura entrada. Para determinar cuál es la mejor se siguen, como criterio de prioridad, los dos puntos siguientes y en este orden:
1. La atracción que permite ir solo tiene prioridad ante la atracción que obliga a ir acompañado (se asume que ninguna de las dos atracciones estarán prohibidas para la altura entrada).
2. Tiene prioridad la atracción que tiene menor tiempo de espera.
Por ejemplo, si una atracción permite ir solo y la otra no, ya no se comprueba el punto 2.
Nota: En caso de empate, la acción devolverá la atracción que ha entrado en el primer parámetro, ​fRide1​.
Nota:​ En esta acción debes utilizar las funciones de los dos apartados anteriores.
   
 Apartado d: [25%] ​Completa el algoritmo que tenemos a medio diseñar utilizando las acciones / funciones anteriores, para que haga lo siguiente:
● Lea la información de una atracción entrada desde el canal estándar y lea el número de personas que hay en la cola de esta atracción, también desde el canal estándar de entrada.
● Lea la información de otra atracción y lea el número de personas que hay en la cola de esta atracción, del canal estándar de entrada.
● Lea la altura de una persona que quiere subir a las atracciones, del canal estándar de entrada.
● A continuación, el algoritmo debe mostrar por el canal estándar de salida los campos de la atracción elegida según los criterios del apartado c (que priorizan el hecho de ir solo respecto a ir acompañado y, en caso de empate, la atracción que tiene tiempo de espera inferior).
Ejercicio 2: Programación en C [60%]
Apartado a: [80%] En este ejercicio hay que ​codificar en lenguaje C el ejercicio 1 y, además, estructurar el código en carpetas. Concretamente hay que hacer lo siguiente:
1. Crea un nuevo proyecto en Codelite llamado ​fairgroundRide. ​Crea una carpeta ​include y​ una carpeta ​src en este proyecto siguiendo las explicaciones que se pueden encontrar en la unidad de la XWiki ​Modularidad en Codelite​ de la asignatura.
2.Dentrodelacarpeta​include,c​reaunnuevoarchivollamado fairgroundRide.h que contenga la declaración del tipo estructurado tFairgroundRide, l​a de todos los tipos enumerados necesariosincluidoeltipo boolean, ​así como las constantes necesarias.
3. Copia las cabeceras de todas las acciones / funciones que tengas que usar (waitingTime,accessWithoutCompanion,selectFairgroundRide,etc.)e​n el archivo​ ​fairgroundRide.h.
4.Dentrodelacarpeta​src,c​reaunnuevoarchivo​fairgroundRide.c.​Ponel código de las acciones / funciones que tengas que utilizar ​(​waitingTime​, accessWithoutCompanion, selectFairgroundRide​, etc.)
5. Codifica el algoritmo del ejercicio 1, apartado d, dentro de la función principal
main.c
 Debemos asumir que ninguna de las las dos atracciones estarán prohibidas ara la altura que se ha introducido.
Nota:
  
 6. Comprueba que compila y funciona correctamente.
Nota: En lenguaje algorítmico disponemos de las funciones / acciones: readFairgroundRideAccess(), readFairgroundRide(), copyFairgroundRide() y writeFairgroundRide(). Para implementarlas en C, puedes cogerlas de la PEC anterior y adaptarlas a la nueva estructura de datos. Debes copiar las cabeceras en el archivo fairgroundRide.h​ ​y poner el código en el archivo ​fairgroundRide.c.
Apartado b [20%] ​Ejecuta y supera los juegos de prueba automáticos que hay en el entorno ACME.
Para ello debes utilizar exactamente los siguientes textos para la entrada y salida de literales, donde XX ​indica los valores entrados por el usuario en la lista ​Input data y los valores mostrados por la aplicación en ​output data​.
Input data:
ENTER FECHA FOR FIRST FAIRGROUND RIDE: NAME >>
XX
ACCES HEIGHT, LESSTHAN100 (0-FORBIDDEN, 1-ALLOWED_WITH_COMPANION, 2-allowed) >> XX
CCES HEIGHT, BETWEEN100_120 (0-FORBIDDEN, 1-ALLOWED_WITH_COMPANION, 2-allowed ) >>
XX
ACCES HEIGHT, BETWEEN120_140 (0-FORBIDDEN, 1-ALLOWED_WITH_COMPANION, 2-allowed) >>
XX
ACCES HEIGHT, GREATERTHAN140 (0-FORBIDDEN, 1-ALLOWED_WITH_COMPANION, 2-allowed) >>
XX
TRIP DURACIÓN >> >>
XX
NUMBER OF PERSONS ON A TRIP >>
XX
ENTER THE PEOPLE IN THE QUEUE OF FAIRGROUND RIDE 1 >> XX
ENTER FECHA FOR SECOND FAIRGROUND RIDE:
NAME >>
 
 XX
ACCES HEIGHT, LESSTHAN100 (0-FORBIDDEN, 1-ALLOWED_WITH_COMPANION, 2-allowed ) >>
XX
CCES HEIGHT, BETWEEN100_120 (0-FORBIDDEN, 1-ALLOWED_WITH_COMPANION, 2-allowed) >>
XX
ACCES HEIGHT, BETWEEN120_140 (0-FORBIDDEN, 1-ALLOWED_WITH_COMPANION, 2-allowed) >>
XX
ACCES HEIGHT, GREATERTHAN140 (0 -FORBIDDEN, 1-ALLOWED_WITH_COMPANION, 2-allowed) >>
XX
TRIP DURACIÓN >> >>
XX
NUMBER OF PERSONS ON A TRIP >>
XX
ENTER THE PEOPLE IN THE QUEUE OF FAIRG ROUND RIDE 2 >> XX
ENTER THE HEIGHT >>
Output data:
RESULT:
NAME: XX
ACCES HEIGHT, LESSTHAN100 (0-FORBIDDEN, 1-ALLOWED_WITH_COMPANION, 2-allowed): XX CCES HEIGHT, BETWEEN100_120 (0-FORBIDDEN, 1-ALLOWED_WITH_COMPANION, 2 -ALLOWED): XX ACCES HEIGHT, BETWEEN120_140 (0-FORBIDDEN, 1-ALLOWED_WITH_COMPANION, 2-allowed): XX ACCES HEIGHT, GREATERTHAN140 (0-FORBIDDEN, 1-ALLOWED_WITH_COMPANION, 2-allowed): XX
TRIP DURACIÓN: XX
NUMBER OF PERSONS ON A TRIP: XX

 Criterios de corrección:
En el ejercicio 1:
● Que sigue la notación algorítmica utilizada en la asignatura. Véase documento ​Nomenclator​ la XWiki de contenido.
● Que se adecua a las instrucciones dadas y el algoritmo responda al problema planteado.
● Que se diseña y se llama correctamente las acciones y funciones demandadas.
● Que se utilice correctamente la estructura alternativa y el tipo de datos estructurado.
● Que se razone correctamente la respuesta del apartado d de la primera pregunta.
En el ejercicio 2:
● Que el programa se adecua las indicaciones dadas.
● Que el programa compila y funciona de acuerdo con lo que se pide.
● Que se respetan los criterios de estilo de programación C. Véase la ​Guía de
estilo de programación en C q​ ue tiene en la Wiki de contenido.
● Que se implementa correctamente la modularización del proyecto, dividiendo
el código en carpetas y poniendo lo que corresponde a cada carpeta.
  
