//Librerias Incluidas
#include <matematica.h>
#include <18F4620.h>
#include <stdlib.h>
#include <serial.c>

#fuses HS, NOFCMEN, NOIESO, PUT, NOBROWNOUT, NOWDT, NOPBADEN, NOMCLR, STVREN, NOLVP, NODEBUG //Fuses a utilizar
#use delay(clock=16000000)                                                                   //16000000

char OpcionIngresada;
int TareaPrograma=1;
char Bandera;

float num1,num2,resultado;
#bit FlagSerial = Bandera.0

void main (void)
{
   set_tris_c(0x80); 
   
   enable_interrupts(INT_RDA);
   enable_interrupts(GLOBAL);
   
   printf("\n(S)uma\n(R)esta\n(M)Multiplicacion\n(D)Division: \n"); //Menu de opciones
   
   while(1)//Inicio del ciclo
   {
         if(FlagEcho==1)
         {
            putc(CaracterRecibido);
            FlagEcho=0;
         }
         if(FlagSerial == 1)
         {
            llenar(Buffer, ContadorBuf, &CaracterRecibido, &FlagEnter);
         }
         mostrar(TareaPrograma,FlagMostrar);
         
         
         if(FlagSerial==1&&FlagEnter==1)
         {
            if(TareaPrograma==1)
            {
               OpcionIngresada=Buffer[0];
               if(OpcionIngresada==('s'||'S')||OpcionIngresada==('r'||'R')||OpcionIngresada==('d'||'D')||OpcionIngresada==('m'||'M')) //Validar mayusculas o minusculas
               {
                  TareaPrograma=2;
                  
               }
               else 
               {
                  TareaPrograma=1;
               }
               ContadorBuf=0;
               FlagSerial=0;
               FlagEnter=0;
               FlagMostrar=1;              
            }
            
            //.................................................................
            else if(TareaPrograma==2)
            {
            if(ContadorBuf>9)
            {
            
                TareaPrograma=2;
            }
            else
            {
                for(int i=0; i<=9; i++)
                {
                    if(Buffer[i]>=65 && Buffer[i]<=122)
                    {
                        printf("ERROR");
                    }
                }
              }
               num1=Conversion(Buffer,9);
               TareaPrograma=3;
            }
               ContadorBuf=0;
               FlagSerial=0;
               FlagEnter=0;
               FlagMostrar=1;           
            }
            //.................................................................
            
            
            //.................................................................
            else if(TareaPrograma==3)
            {
            if(ContadorBuf>9)
            {
                TareaPrograma=3;
            }
            else
            {
                for(int i=0; i<=9; i++)
                {
                    if(Buffer[i]>=65 && Buffer[i]<=122)
                    {
                        printf("Error");
                    }
                }
            }
               num2=Conversion(Buffer,9);
               TareaPrograma=4;
               
               if((OpcionIngresada=='d'||OpcionIngresada=='D')&&(num2==0))
               {  
                  printf("Error, operacion invalida");
               }
               ContadorBuf=0;
               FlagMostrar=1;
               FlagSerial=0;
               FlagEnter=0;
               
            }
            //.................................................................
            
            
            //.................................................................
            else if(TareaPrograma==4)
            {
               resultado=operacion(OpcionIngresada,num1,num2);
               printf("\nEl resultado es: %.4f\n",resultado);
               TareaPrograma=1;
               ContadorBuf=0;
               FlagMostrar=1;
               FlagSerial=0;
               FlagEnter=0;
            }
            //.................................................................
         }
   }
