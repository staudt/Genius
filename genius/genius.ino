#define REST 0
#define NB0  31
#define NC1  33
#define NCS1 35
#define ND1  37
#define NDS1 39
#define NE1  41
#define NF1  44
#define NFS1 46
#define NG1  49
#define NGS1 52
#define NA1  55
#define NAS1 58
#define NB1  62
#define NC2  65
#define NCS2 69
#define ND2  73
#define NDS2 78
#define NE2  82
#define NF2  87
#define NFS2 93
#define NG2  98
#define NGS2 104
#define NA2  110
#define NAS2 117
#define NB2  123
#define NC3  131
#define NCS3 139
#define ND3  147
#define NDS3 156
#define NE3  165
#define NF3  175
#define NFS3 185
#define NG3  196
#define NGS3 208
#define NA3  220
#define NAS3 233
#define NB3  247
#define NC4  262
#define NCS4 277
#define ND4  294
#define NDS4 311
#define NE4  330
#define NF4  349
#define NFS4 370
#define NG4  392
#define NGS4 415
#define NA4  440
#define NAS4 466
#define NB4  494
#define NC5  523
#define NCS5 554
#define ND5  587
#define NDS5 622
#define NE5  659
#define NF5  698
#define NFS5 740
#define NG5  784
#define NGS5 831
#define NA5  880
#define NAS5 932
#define NB5  988
#define NC6  1047
#define NCS6 1109
#define ND6  1175
#define NDS6 1245
#define NE6  1319
#define NF6  1397
#define NFS6 1480
#define NG6  1568
#define NGS6 1661
#define NA6  1760
#define NAS6 1865
#define NB6  1976
#define NC7  2093
#define NCS7 2217
#define ND7  2349
#define NDS7 2489
#define NE7  2637
#define NF7  2794
#define NFS7 2960
#define NG7  3136
#define NGS7 3322
#define NA7  3520
#define NAS7 3729
#define NB7  3951
#define NC8  4186
#define NCS8 4435
#define ND8  4699
#define NDS8 4978

#define MAX_PONTOS 17

int speaker_pin = 7;
int btn_pin[] = {3, 4, 5, 6};
int led_pin[] = {8, 9, 10, 11};
int btn_tone[] = {NA3, ND4, NE5, NB6};

void melodia(int tamanho, int sequencia[], int tempo[]) {
  int tempo_ms;
  bool leds_lit = false;
  for(int i=0;i<tamanho; i++) {
    tempo_ms = (int)1000/tempo[i];
    leds_lit = !leds_lit;
    for(int i=0;i<4;i++)
      digitalWrite(led_pin[i], leds_lit ? HIGH : LOW);
    tone(speaker_pin, sequencia[i], tempo_ms);
    delay((int)tempo_ms*1.30);
  }
  for(int i=0;i<4;i++)
    digitalWrite(led_pin[i], LOW);
}

void toca_abertura() {
  int sequencia[] = {NE7,NE7,0,NE7,0,NC7,NE7,0, NG7,0,0,0,NG6,0,0,0};
  int tempo[] = {12,12,12,12,12,12,12,12, 12,12,12,12,12,12,12,12};
  melodia(16, sequencia, tempo);
}

void toca_inicio_jogo() {
  int sequencia[] = {NA5, NA6, NA7};
  int tempo[] = {6, 6, 4};
  melodia(3, sequencia, tempo);
}

void toca_fracasso() {
  int sequencia[] = {NA3, NA2, NA1};
  int tempo[] = {6, 4, 1};
  delay(200);
  melodia(3, sequencia, tempo);
}

void toca_acerto() {
  delay(200);
  toca_inicio_jogo(); // trocar por algo diferente?
  delay(400);
}

void toca_final() {
  int sequencia[] = {NG4,NC5,NC5,ND5,NC5,NB4,NA4,NA4, NA4,ND5,ND5,NE5,ND5,NC5,NB4,NG4, NG4,NE5,NE5,NF5,NE5,ND5,NC5,NA5,NG4,NG4,NA4,ND5,NB4,NC5};
  int tempo[] = {4,4,8,8,8,8,4,4, 4,4,8,8,8,8,4,4, 4,4,8,8,8,8,4,4,8,8,4,4,4,2};
  melodia(30, sequencia, tempo);
}

void espera_qualquer_botao() {
  bool pressed;
  int led_lit=0;
  bool led_invert=false;
  while(true) { 
    // LED animation
    digitalWrite(led_pin[led_lit], led_invert ? LOW : HIGH);
    led_lit++;
    if (led_lit>3) {
      led_lit = 0;
      led_invert = !led_invert;
    }
    // Wait for key press and release
    for(int i=0;i<4;i++) {
      pressed = !digitalRead(btn_pin[i]);
      if (pressed) {
        tone(speaker_pin, btn_tone[i]);
        for(int i=0;i<4;i++)
          digitalWrite(led_pin[i], LOW);
        digitalWrite(led_pin[i], HIGH);
        while(pressed) {
          pressed = !digitalRead(btn_pin[i]);
          delay(20);
        }
        digitalWrite(led_pin[i], LOW);
        noTone(speaker_pin);
        return;
      }
      delay(20);
    }
  }
}

int espera_um_botao() {
  bool pressed;
  while(true) {
    for(int i=0;i<4;i++) {
      pressed = !digitalRead(btn_pin[i]);
      if (pressed) {
        tone(speaker_pin, btn_tone[i]);
        digitalWrite(led_pin[i], HIGH);
        while(pressed) {
          pressed = !digitalRead(btn_pin[i]);
          delay(20);
        }
        digitalWrite(led_pin[i], LOW);
        noTone(speaker_pin);
        return i;
      }
      delay(20);
    }
  }
}


void setup() {
  Serial.begin(9600);
  randomSeed(analogRead(5));
  pinMode(speaker_pin, OUTPUT);
  for(int i=0;i<4;i++) {
    pinMode(btn_pin[i], INPUT);
    digitalWrite(btn_pin[i], HIGH);
    pinMode(led_pin[i], OUTPUT);
  }
  delay(200);
  toca_abertura();
}


void loop() {
  int sequencia[MAX_PONTOS];
  int pontos = 3;

  for(int i=0;i<MAX_PONTOS;i++)
    sequencia[i] = (int)random(4);

  Serial.println("Espera tecla");
  espera_qualquer_botao();
  Serial.println("Inicio de jogo");
  toca_inicio_jogo();
  while(pontos<MAX_PONTOS) {
    delay(200);
    // toca sequencia
    Serial.println("Tocando sequencia");
    for(int i=0;i<pontos;i++) {
      digitalWrite(led_pin[sequencia[i]], HIGH);
      tone(speaker_pin, btn_tone[sequencia[i]]);
      delay(600);
      noTone(speaker_pin);
      digitalWrite(led_pin[sequencia[i]], LOW);
      delay(200);
    }
    // Le a sequencia do jogador
    Serial.println("Le sequencia do jogador");
    for(int i=0;i<pontos;i++) {
      if (espera_um_botao() != sequencia[i]) {
        Serial.println("Errou!");
        toca_fracasso();
        return; // Errou! Acaba o jogo e volta pro estado inicial
      }
    }
    // Acertou a sequencia!
    Serial.println("Acertou!");
    pontos++;
    if(pontos==MAX_PONTOS) { // Finalizou o jogo!
      toca_final();
      return;
    }
    toca_acerto();
  }
}

