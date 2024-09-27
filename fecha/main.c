#include "fecha.h"

int main()
{
    puts("ingresa fecha de hoy \n");
    Fecha fechaHoy = ingresarFecha();
    Fecha fechaFuturo, fechaPasado;
    int diaSumar,diaRestar,diasTotales,diasDiferencia,edad;
    
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
    puts("ingresa fecha de tu cumple \n");
    Fecha fechaDos = ingresarFecha();
    edad = calcularEdad (&fechaDos,&fechaHoy);
    puts("la diferencie entre las fechas es de : \n");
    printf("%d\n",edad);


    return 0;
}
