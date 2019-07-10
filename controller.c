#include <stdio.h>
#include <stdlib.h>
#include "LinkedList.h"
#include "revelado.h"
#include "parser.h"
#include "utn.h"

/** \brief Carga los datos de las revelados desde el archivo data (modo texto).
 *
 * \param path char* puntero al archivo a cargar
 * \param pArrayListrevelados LinkedList* puntero al array de revelados.
 * \return int ret -1 si el puntero path es NULL o el puntero pArrayListrevelados es NULL,
                    0 si logra cargar los datos.
 *
 */
int controller_loadFromText(char* path, LinkedList* pArrayListRevelados)
{
    int ret = -1;
    FILE* pFileAux = NULL;

    if(path != NULL && pArrayListRevelados != NULL)
    {
        pFileAux = fopen(path, "r");
        if(pFileAux != NULL)
        {
            if(!parser_ReveladoFromText(pFileAux, pArrayListRevelados))
            {
                printf("\tCARGA EXITOSA!\n");
                ret = 0;
            }
        }
    }
    return ret;
}

/** \brief Listar revelados
 *
 * \param pArrayListRevelados LinkedList* puntero al array de revelados.
 * \return int ret -1 si no puede mostar toda la lista de los revelados,
                    0 si logra mostar toda la lista de los revelados.
 *
 */
/*int controller_ListRevelados(LinkedList* pArrayListRevelados)
{
    int ret = -1;
    Revelado * pRevelado = NULL;
    char bufferId[400];
    char bufferTipo[400];
    int bufferCantidad;
    float bufferImporte;

    for(int i=0; i<ll_len(pArrayListRevelados); i++)
    {
        pRevelado = ll_get(pArrayListRevelados, i);//guardar en un puntero a empleado
        if(pRevelado != NULL)
        {
            if(!revelado_getIdStr(pRevelado, bufferId) &&
                    !revelado_getTipo(pRevelado,bufferTipo) &&
                    !revelado_getCantidad(pRevelado, &bufferCantidad) &&
                    !revelado_getImporte(pRevelado, &bufferImporte))
            {
                printf("ID:%s TIPO: %s CANTIDAD: %d IMPORTE: %.2f\n", bufferId, bufferTipo, bufferCantidad, bufferImporte);
                ret = 0;
            }
        }

    }
    return ret;
}*/


/** \brief Guarda los datos de las revelados en el archivo informes.txt (modo texto).
 *
 * \param path char* puntero al archivo a guardar
 * \param pArrayListRevelados LinkedList* puntero al array de revelados.
 * \return int ret -1 si el puntero si no puede guardar los datos,
 *                  0 si logra guardar los datos.
 *
 */
int controller_saveAsText(char* path, LinkedList* pArrayListRevelados)
{
    int ret = -1;
    FILE* pFileAux = NULL;
    int cantidadTotaRevelados;
    LinkedList* ventasMayores150 = ll_newLinkedList();
    LinkedList* ventasMayores300 = ll_newLinkedList();
    int cantidadMayores150;
    int cantidadMayores300;
    LinkedList* fotosPilaroid = ll_newLinkedList();
    int cantidadPolaroid;


    if(path != NULL && pArrayListRevelados != NULL)
    {
        pFileAux = fopen(path, "w");
        if(pFileAux != NULL)
        {
            revelado_cantidadFotos(pArrayListRevelados, &cantidadTotaRevelados);

            ventasMayores150 = ll_filter(pArrayListRevelados, revelado_ventasMAyor150);
            cantidadMayores150 = ll_len(ventasMayores150);

            ventasMayores300= ll_filter(pArrayListRevelados, revelado_ventasMAyor150);
            cantidadMayores300 = ll_len(ventasMayores300);

            fotosPilaroid = ll_filter(pArrayListRevelados, revelado_polaroid);
            cantidadPolaroid = ll_len(fotosPilaroid);


            fprintf(pFileAux,"\t\tINFORME DE ENTREGASº\n\n");
            fprintf(pFileAux,"- Cantidad total de fotos revelados: %d\n", cantidadTotaRevelados );
            fprintf(pFileAux,"- Cantidad de ventas monto mayor a $150: %d \n", cantidadMayores150);
            fprintf(pFileAux,"- Cantidad de ventas monto mayor a $300: %d \n", cantidadMayores300);
            fprintf(pFileAux,"- Cantidad de fotos polaroid reveladas: %d \n", cantidadPolaroid);

        }
        fclose(pFileAux);
    }
    return ret;
}
