         //Variáveis...
int           ReadClock;       //variável que irá ler a porta A0.
unsigned long mili;            //variável que carrega o tempo em milisegundos.
long int      clement = 1000;  // variável usada para saber quantos milisegundos se passou, a cada 1000.
int           mili2 = 0 , block = 0 , hz = 0; //mili2 recebe a quantidade de Hz. | block usado para regular melhor a contagem de Hz | hz recebe o valor exato da quantidade de Hz.
byte blockOnBluethoot = 0;     // Bloqueia a tentativa de ligar ou desligar o fone acidentalmente.

void setup() {
  pinMode( A0 , INPUT );    // Configuração das portas do Arduino.
  pinMode( 2 , OUTPUT );    // 2 - Para o LED Azul - sinaliza a quantidade de Hz.
  pinMode( 3 , OUTPUT );    // 3 - Para o BC547 / Ligar automaticamente o Fone.
  pinMode( 13 , OUTPUT );   // 13 - Para o LED Amarelo / Representa uma lãmpada a ser ligada por Bluetooth.
  Serial.begin(9600);       // Configuração de comunicação Serial.
}

void loop() {

  ReadClock = analogRead( A0 );   // Analiza/lê o nível de corrente na porta A0

  if( blockOnBluethoot == 0 ){    // LIgando o Fone Bluetooth por 3 segundos.
    digitalWrite( 3 , 1 );
    Serial.println( "LIGANDO BLUETOOTH..." );
    delay(3000);                  //Depois de 3 segundos, desliga porta 3.
    digitalWrite( 3 , 0 );
    blockOnBluethoot = 1 ;        // blockOnBluethoot se torna 1 para bloquear a tentativa de usar a porta 3 novamente.
  }

  mili = millis();                // A contagem em milisegundos se inicia depois dos 3 segundos, após ligar o Fone.
  
  if( mili >= clement ){          // Este If entra em ação toda vez que passa 1 segundo, quando a variável mili chega ao valor da variável clement, ou seja 1000 milisegundos.
    hz = mili2;                   // Variável hz recebe o valor de frêquencia da variável mili2.
    mili2=0;                      // Depois de passar o valor, mili2 é zerada.
    clement+=1000;                // Variável clement recebe mais 1000 em seu valor para continuar com que este If entre em ação a cada 1 segundo.

    Serial.print( "hz: " );       //É enviado para a comunicação serial o valor de frêquencia.
    Serial.println( hz );
  
    //control                     //Aqui é onde se usa If para ligar uma porta com uma determinada frêquancia.

    if( hz == 2 ) {               // Se a frêquancia é igual a 2...
        digitalWrite( 13 , 1 );   // Liga LED amarelo
    }else{                        // Se não/diferente...
        digitalWrite( 13 , 0 );   // Não é ligado / Desliga.
    }
    
  }

  if( ReadClock > 10 ){          // If que analiza se o valor da variável ReadBlock, que esta analizando a porta A0 é maior que 10.
    if( block == 0 ){             // Para uma leitura mais fixa foi criado este If onde se a variável block for igual a 0 entra em ação.
      digitalWrite( 2 , 1 );      // Liga o LED azul , dizendo que há 1Hz passando neste exato momento na porta A0.
      mili2+=1;                   // Variável mili2 adiciona mais 1, ou seja , esta contando o número de Hz para depois passar para a variável hz.
      block = 1 ;                 // Variável block bloqueia.
    }
  }else{                          // Variáveis block e hz são zeradas, e a porta 2, LED azul , é desligado, dizendo que não há 1Hz passado na porta A0.
    block = 0; 
    hz = 0; 
    digitalWrite( 2 , 0 );
  } 

}