#use delay(clock=16000000)

//Variables de interrupcion
int FlagSerial=0,FlagMostrar=1, FlagEnter=0, FlagEcho=0;
int ContadorBuf=0;


//Declaracion de vectore
char Buffer[9]={""};
char CaracterRecibido;
/*Deacuerdo a la tarea enviada y el estado de la bandera mostrar es la tarea que mandara*/

int ContadorPunto=0;

#define __DEBUG_SERIAL__ 

#ifdef __DEBUG_SERIAL__
   #define TX_232        PIN_C6
   #define RX_232        PIN_C7
   #use RS232(BAUD=9600, XMIT=TX_232, BITS=8,PARITY=N, STOP=1,UART1,RCV=RX_232)
   #use fast_io(c)
#endif 

void mostrar (int &TareaPrograma, int &FlagMostrar);
void llenar(char Buffer, int &ContadorBuf, char CaracterRecibido, int *FlagEnter, int &TareaPrograma);

#INT_RDA
void isrRDA (void)
{
   FlagSerial=1;
   FlagEcho=1;
   CaracterRecibido = getc();  
   if(ContadorBuf<10)
   { 
      Buffer[ContadorBuf]= CaracterRecibido;
      ContadorBuf++; 
   }
}

void llenar (char Buffer[], int &ContadorBuf, char *CaracterRecibido, int *FlagEnter)
{
    
   if(*CaracterRecibido==0x0D)
   {
      *FlagEnter=1;
   }
   
   //Backspaces del teclado
   if(*CaracterRecibido==0x08)
   {
      Buffer[ContadorBuf-1]=0;
      Buffer[ContadorBuf-2]=0;
      ContadorBuf-=2;
   }
}

void mostrar (int &TareaPrograma, int &FlagMostrar)
{
         
         if(TareaPrograma==1&&FlagMostrar==1)
         {
            printf("\nIngresa Opción: \t\n");
            FlagMostrar=0;
         }
         else if(TareaPrograma==2&&FlagMostrar==1)
         {
            printf("\nIngresa Numero1: \t\n");
            FlagMostrar=0;
         }
         else if(TareaPrograma==3&&FlagMostrar==1)
         {
            printf("\nIngresa Numero2: \t\n");
            FlagMostrar=0;
         }
}
