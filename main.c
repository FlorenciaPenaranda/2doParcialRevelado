#include <stdio.h>
#include <stdlib.h>
#include "linkedList.h"
#include "controller.h"
#include "revelado.h"
#include "parser.h"


int main()
{

    LinkedList* listaRevelado = ll_newLinkedList();



    controller_loadFromText("data.csv", listaRevelado);

    controller_saveAsText("informes.txt", listaRevelado);

    return 0;
}
