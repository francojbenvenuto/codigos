#include "fecha.h"

int main()
{

    Fecha fechaHoy = ingresarFecha();
    Fecha fechaFuturo, fechaPasado;
    int diaSumar,diaRestar,diasTotales,diasDiferencia;
    
/*
    puts("cuantos dias le sumamos y restamos a la fecha? (suma / resta) \n");
    scanf("%d/%d", &diaSumar,&diaRestar);
    fechaFuturo = sumarDiasAFecha(&fechaHoy, diaSumar);
    restarDiasAFecha (&fechaHoy, diaRestar,&fechaPasado);

    puts("fechas finales:\n");
    mostrarFecha(&fechaHoy);
    mostrarFecha(&fechaFuturo);
    mostrarFecha(&fechaPasado);

    puts("los dias totales del anio fueron: \n");
    diasTotales = diaDelAnio(&fechaHoy);
    printf("%d\n\n\n\n",diasTotales);
*/
    puts("ingresa una segunda fecha a comparar \n");
    Fecha fechaDos = ingresarFecha();
    diasDiferencia = difEntreFechas(&fechaHoy,&fechaDos);
    puts("la diferencie entre las fechas es de : \n");
    printf("%d\n",diasDiferencia);

    return 0;
}
