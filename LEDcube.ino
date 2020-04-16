//#define RCLK_LATCH    (2)   // オレンジ_黄色 latchPin
//#define SRCLK_CLOCK   (3)   // 青_オレンジ clockPin
//#define SER_DATA     (4)   // 緑_赤 datapin

int dataPin     = 4;
int clockPin    = 3;
int latchPin    = 2;
int masterClear = 10; // RST

int layerPin[5] = {5, 6, 7, 8, 9};

byte cube[5][8] = {
  // Layer 1
  {0b00000000,  // Row 1
   0b00000000,  // Row 2
   0b00000000,  // Row 3
   0b00000000,  // Row 4
   0b00000000,  // Row 5
   0b00000000,  // Row 6
   0b00000000,  // Row 7
   0b00000000}, // Row 8
   
   // Layer 2
  {0b00000000,  // Row 1
   0b00000000,  // Etc ...
   0b00000000, 
   0b00000000,
   0b00000000,
   0b00000000, 
   0b00000000, 
   0b00000000},

   {0b00000000,  // Row 1
   0b00000000,  // Etc ...
   0b00000000, 
   0b00000000,
   0b00000000,
   0b00000000, 
   0b00000000, 
   0b00000000},

   {0b00000000,  // Row 1
   0b00000000,  // Etc ...
   0b00000000, 
   0b00000000,
   0b00000000,
   0b00000000, 
   0b00000000, 
   0b00000000},

   {0b00000000,  // Row 1
   0b00000000,  // Etc ...
   0b00000000, 
   0b00000000,
   0b00000000,
   0b00000000, 
   0b00000000, 
   0b00000000},
};

// Cube indicies
int rowIndex = 0;        // used for shifting out the data
int layerIndex = 0;
#define AXIS_X 1
#define AXIS_Y 2
#define AXIS_Z 3

void fill_cube(byte b) {
  int x , y;
  for (x=0; x<5; x++) {
    for (y=3; y < 8; y++) {
      cube[x][y] = b;
    }
  }
}
void all(){
  fill_cube(255);
}

void none(){
  fill_cube(0);
}


void allOff() {
  digitalWrite(masterClear, LOW);// RST shiftregister for killing ghost.
  delay(1);
  digitalWrite(masterClear, HIGH);
  for( int i= 0; i<5; i++) {
    digitalWrite(layerPin[i], LOW);// all layer turn off.
  }
}

void layerOn(int layer_num) {
  digitalWrite(layerPin[layer_num], LOW);// flash on layer_num.
  delay(1);
  digitalWrite(layerPin[layer_num], HIGH);
}

void layerOff(int layer_num) {
  digitalWrite(layerPin[layer_num], HIGH);
  delay(1);
  digitalWrite(layerPin[layer_num], LOW);// flash on layer_num.
}

//=====Numbers===================================================================================================================================
void number0(){
  for (int y=3;y < 8; y++) {
    none();
    cube[4][y] = 0b00011100;
    cube[3][y] = 0b00100010;
    cube[2][y] = 0b00100010;
    cube[1][y] = 0b00100010;
    cube[0][y] = 0b00011100;
    draw();
  }
}
void number1(){
  for (int y=3;y < 8; y++) {
    none();
    cube[4][y] = 0b00001000;
    cube[3][y] = 0b00011000;
    cube[2][y] = 0b00001000;
    cube[1][y] = 0b00001000;
    cube[0][y] = 0b00011100;
    draw();
  }
}
void number2(){
  for (int y=3;y < 8; y++) {
    none();
    cube[4][y] = 0b00011100;
    cube[3][y] = 0b00100010;
    cube[2][y] = 0b00001100;
    cube[1][y] = 0b00010000;
    cube[0][y] = 0b00111110;
    draw();
  }
}
void number3(){
  for (int y=3;y < 8; y++) {
    none();
    cube[4][y] = 0b00111100;
    cube[3][y] = 0b00000010;
    cube[2][y] = 0b00001100;
    cube[1][y] = 0b00100010;
    cube[0][y] = 0b00011100;
    draw();
  }
}
void number4(int y){
  cube[4][y] = 0b00100100;
  cube[3][y] = 0b00100100;
  cube[2][y] = 0b00111110;
  cube[1][y] = 0b00000100;
  cube[0][y] = 0b00000100;
}
void number5(int y){
  cube[4][y] = 0b00111110;
  cube[3][y] = 0b00100000;
  cube[2][y] = 0b00111100;
  cube[1][y] = 0b00000010;
  cube[0][y] = 0b00111100;
}
void number6(int y){
  cube[4][y] = 0b00011100;
  cube[3][y] = 0b00100000;
  cube[2][y] = 0b00111100;
  cube[1][y] = 0b00100010;
  cube[0][y] = 0b00011100;
}
void number7(int y){
  cube[4][y] = 0b00011100;
  cube[3][y] = 0b00010100;
  cube[2][y] = 0b00000100;
  cube[1][y] = 0b00000100;
  cube[0][y] = 0b00000100;
}
void number8(int y){
  cube[4][y] = 0b00011100;
  cube[3][y] = 0b00100010;
  cube[2][y] = 0b00011100;
  cube[1][y] = 0b00100010;
  cube[0][y] = 0b00011100;
}
void number9(int y){
  cube[4][y] = 0b00011100;
  cube[3][y] = 0b00100010;
  cube[2][y] = 0b00011100;
  cube[1][y] = 0b00000010;
  cube[0][y] = 0b00111100;
}

//=====box_zoom_1===================================================================================================================================
void box_1(){
  cube[0][3] = 0b00111110; cube[1][3] = 0b00100010; cube[2][3] = 0b00100010; cube[3][3] = 0b00100010; cube[4][3] = 0b00111110;
  cube[0][4] = 0b00100010; cube[1][4] = 0b00000000; cube[2][4] = 0b00000000; cube[3][4] = 0b00000000; cube[4][4] = 0b00100010; 
  cube[0][5] = 0b00100010; cube[1][5] = 0b00000000; cube[2][5] = 0b00000000; cube[3][5] = 0b00000000; cube[4][5] = 0b00100010; 
  cube[0][6] = 0b00100010; cube[1][6] = 0b00000000; cube[2][6] = 0b00000000; cube[3][6] = 0b00000000; cube[4][6] = 0b00100010; 
  cube[0][7] = 0b00111110; cube[1][7] = 0b00100010; cube[2][7] = 0b00100010; cube[3][7] = 0b00100010; cube[4][7] = 0b00111110;
}

void box_2(){
  cube[0][3] = 0b00000000; cube[1][3] = 0b00000000; cube[2][3] = 0b00000000; cube[3][3] = 0b00000000; cube[4][3] = 0b00000000;
  cube[0][4] = 0b00000000; cube[1][4] = 0b00011100; cube[2][4] = 0b00010100; cube[3][4] = 0b00011100; cube[4][4] = 0b00000000; 
  cube[0][5] = 0b00000000; cube[1][5] = 0b00010100; cube[2][5] = 0b00000000; cube[3][5] = 0b00010100; cube[4][5] = 0b00000000; 
  cube[0][6] = 0b00000000; cube[1][6] = 0b00011100; cube[2][6] = 0b00010100; cube[3][6] = 0b00011100; cube[4][6] = 0b00000000; 
  cube[0][7] = 0b00000000; cube[1][7] = 0b00000000; cube[2][7] = 0b00000000; cube[3][7] = 0b00000000; cube[4][7] = 0b00000000;
}

void box_3(){
  cube[0][3] = 0b00000000; cube[1][3] = 0b00000000; cube[2][3] = 0b00000000; cube[3][3] = 0b00000000; cube[4][3] = 0b00000000;
  cube[0][4] = 0b00000000; cube[1][4] = 0b00000000; cube[2][4] = 0b00000000; cube[3][4] = 0b00000000; cube[4][4] = 0b00000000; 
  cube[0][5] = 0b00000000; cube[1][5] = 0b00000000; cube[2][5] = 0b00001000; cube[3][5] = 0b00000000; cube[4][5] = 0b00000000; 
  cube[0][6] = 0b00000000; cube[1][6] = 0b00000000; cube[2][6] = 0b00000000; cube[3][6] = 0b00000000; cube[4][6] = 0b00000000; 
  cube[0][7] = 0b00000000; cube[1][7] = 0b00000000; cube[2][7] = 0b00000000; cube[3][7] = 0b00000000; cube[4][7] = 0b00000000;
}
//===========================================================================================================================================

//======box_zoom_2===========================================================================================================================
void box_4(){
  cube[0][3] = 0b00000000; cube[1][3] = 0b00000000; cube[2][3] = 0b00000000; cube[3][3] = 0b00000000; cube[4][3] = 0b00000000;
  cube[0][4] = 0b00011110; cube[1][4] = 0b00010010; cube[2][4] = 0b00010010; cube[3][4] = 0b00011110; cube[4][4] = 0b00000000; 
  cube[0][5] = 0b00010010; cube[1][5] = 0b00000000; cube[2][5] = 0b00000000; cube[3][5] = 0b00010010; cube[4][5] = 0b00000000; 
  cube[0][6] = 0b00010010; cube[1][6] = 0b00000000; cube[2][6] = 0b00000000; cube[3][6] = 0b00010010; cube[4][6] = 0b00000000; 
  cube[0][7] = 0b00011110; cube[1][7] = 0b00010010; cube[2][7] = 0b00010010; cube[3][7] = 0b00011110; cube[4][7] = 0b00000000;
}

void box_5(){
  cube[0][3] = 0b00000000; cube[1][3] = 0b00000000; cube[2][3] = 0b00000000; cube[3][3] = 0b00000000; cube[4][3] = 0b00000000;
  cube[0][4] = 0b00000000; cube[1][4] = 0b00000000; cube[2][4] = 0b00000000; cube[3][4] = 0b00000000; cube[4][4] = 0b00000000; 
  cube[0][5] = 0b00001110; cube[1][5] = 0b00001010; cube[2][5] = 0b00001110; cube[3][5] = 0b00000000; cube[4][5] = 0b00000000; 
  cube[0][6] = 0b00001010; cube[1][6] = 0b00000000; cube[2][6] = 0b00001010; cube[3][6] = 0b00000000; cube[4][6] = 0b00000000; 
  cube[0][7] = 0b00001110; cube[1][7] = 0b00001010; cube[2][7] = 0b00001110; cube[3][7] = 0b00000000; cube[4][7] = 0b00000000;
}

void box_6(){
  cube[0][3] = 0b00000000; cube[1][3] = 0b00000000; cube[2][3] = 0b00000000; cube[3][3] = 0b00000000; cube[4][3] = 0b00000000;
  cube[0][4] = 0b00000000; cube[1][4] = 0b00000000; cube[2][4] = 0b00000000; cube[3][4] = 0b00000000; cube[4][4] = 0b00000000; 
  cube[0][5] = 0b00000000; cube[1][5] = 0b00000000; cube[2][5] = 0b00000000; cube[3][5] = 0b00000000; cube[4][5] = 0b00000000; 
  cube[0][6] = 0b00000110; cube[1][6] = 0b00000110; cube[2][6] = 0b00000000; cube[3][6] = 0b00000000; cube[4][6] = 0b00000000; 
  cube[0][7] = 0b00000110; cube[1][7] = 0b00000110; cube[2][7] = 0b00000000; cube[3][7] = 0b00000000; cube[4][7] = 0b00000000;
}

void box_7(){
  cube[0][3] = 0b00000000; cube[1][3] = 0b00000000; cube[2][3] = 0b00000000; cube[3][3] = 0b00000000; cube[4][3] = 0b00000000;
  cube[0][4] = 0b00000000; cube[1][4] = 0b00000000; cube[2][4] = 0b00000000; cube[3][4] = 0b00000000; cube[4][4] = 0b00000000; 
  cube[0][5] = 0b00000000; cube[1][5] = 0b00000000; cube[2][5] = 0b00000000; cube[3][5] = 0b00000000; cube[4][5] = 0b00000000; 
  cube[0][6] = 0b00000000; cube[1][6] = 0b00000000; cube[2][6] = 0b00000000; cube[3][6] = 0b00000000; cube[4][6] = 0b00000000; 
  cube[0][7] = 0b00000010; cube[1][7] = 0b00000000; cube[2][7] = 0b00000000; cube[3][7] = 0b00000000; cube[4][7] = 0b00000000;
}
//===========================================================================================================================================

//=======box_zoom_3===========================================================================================================================
void box_8(){
  cube[0][3] = 0b00000000; cube[1][3] = 0b00000000; cube[2][3] = 0b00000000; cube[3][3] = 0b00000000; cube[4][3] = 0b00000000;
  cube[0][4] = 0b00111100; cube[1][4] = 0b00100100; cube[2][4] = 0b00100010; cube[3][4] = 0b00111100; cube[4][4] = 0b00000000; 
  cube[0][5] = 0b00100100; cube[1][5] = 0b00000000; cube[2][5] = 0b00000000; cube[3][5] = 0b00100100; cube[4][5] = 0b00000000; 
  cube[0][6] = 0b00100100; cube[1][6] = 0b00000000; cube[2][6] = 0b00000000; cube[3][6] = 0b00100100; cube[4][6] = 0b00000000; 
  cube[0][7] = 0b00111100; cube[1][7] = 0b00100100; cube[2][7] = 0b00100100; cube[3][7] = 0b00111100; cube[4][7] = 0b00000000;
}
void box_9(){
  cube[0][3] = 0b00000000; cube[1][3] = 0b00000000; cube[2][3] = 0b00000000; cube[3][3] = 0b00000000; cube[4][3] = 0b00000000;
  cube[0][4] = 0b00000000; cube[1][4] = 0b00000000; cube[2][4] = 0b00000000; cube[3][4] = 0b00000000; cube[4][4] = 0b00000000; 
  cube[0][5] = 0b00111000; cube[1][5] = 0b00101000; cube[2][5] = 0b00111000; cube[3][5] = 0b00000000; cube[4][5] = 0b00000000; 
  cube[0][6] = 0b00101000; cube[1][6] = 0b00000000; cube[2][6] = 0b00101000; cube[3][6] = 0b00000000; cube[4][6] = 0b00000000; 
  cube[0][7] = 0b00111000; cube[1][7] = 0b00101000; cube[2][7] = 0b00111000; cube[3][7] = 0b00000000; cube[4][7] = 0b00000000;
}
void box_10(){
  cube[0][3] = 0b00000000; cube[1][3] = 0b00000000; cube[2][3] = 0b00000000; cube[3][3] = 0b00000000; cube[4][3] = 0b00000000;
  cube[0][4] = 0b00000000; cube[1][4] = 0b00000000; cube[2][4] = 0b00000000; cube[3][4] = 0b00000000; cube[4][4] = 0b00000000; 
  cube[0][5] = 0b00000000; cube[1][5] = 0b00000000; cube[2][5] = 0b00000000; cube[3][5] = 0b00000000; cube[4][5] = 0b00000000; 
  cube[0][6] = 0b00110000; cube[1][6] = 0b00110000; cube[2][6] = 0b00000000; cube[3][6] = 0b00000000; cube[4][6] = 0b00000000; 
  cube[0][7] = 0b00110000; cube[1][7] = 0b00110000; cube[2][7] = 0b00000000; cube[3][7] = 0b00000000; cube[4][7] = 0b00000000;
}
void box_11(){
  cube[0][3] = 0b00000000; cube[1][3] = 0b00000000; cube[2][3] = 0b00000000; cube[3][3] = 0b00000000; cube[4][3] = 0b00000000;
  cube[0][4] = 0b00000000; cube[1][4] = 0b00000000; cube[2][4] = 0b00000000; cube[3][4] = 0b00000000; cube[4][4] = 0b00000000; 
  cube[0][5] = 0b00000000; cube[1][5] = 0b00000000; cube[2][5] = 0b00000000; cube[3][5] = 0b00000000; cube[4][5] = 0b00000000; 
  cube[0][6] = 0b00000000; cube[1][6] = 0b00000000; cube[2][6] = 0b00000000; cube[3][6] = 0b00000000; cube[4][6] = 0b00000000; 
  cube[0][7] = 0b00100000; cube[1][7] = 0b00000000; cube[2][7] = 0b00000000; cube[3][7] = 0b00000000; cube[4][7] = 0b00000000;
}
//===========================================================================================================================================

//=========wave()==============================================================================================================================
void wave_1(){
  cube[0][3] = 0b00100000; cube[1][3] = 0b00000000; cube[2][3] = 0b00000000; cube[3][3] = 0b00000000; cube[4][3] = 0b00000000;
  cube[0][4] = 0b00100000; cube[1][4] = 0b00000000; cube[2][4] = 0b00000000; cube[3][4] = 0b00000000; cube[4][4] = 0b00000000; 
  cube[0][5] = 0b00100000; cube[1][5] = 0b00000000; cube[2][5] = 0b00000000; cube[3][5] = 0b00000000; cube[4][5] = 0b00000000; 
  cube[0][6] = 0b00100000; cube[1][6] = 0b00000000; cube[2][6] = 0b00000000; cube[3][6] = 0b00000000; cube[4][6] = 0b00000000; 
  cube[0][7] = 0b00100000; cube[1][7] = 0b00000000; cube[2][7] = 0b00000000; cube[3][7] = 0b00000000; cube[4][7] = 0b00000000;
}
void wave_2(){
  cube[0][3] = 0b00110000; cube[1][3] = 0b00100000; cube[2][3] = 0b00000000; cube[3][3] = 0b00000000; cube[4][3] = 0b00000000;
  cube[0][4] = 0b00110000; cube[1][4] = 0b00100000; cube[2][4] = 0b00000000; cube[3][4] = 0b00000000; cube[4][4] = 0b00000000; 
  cube[0][5] = 0b00110000; cube[1][5] = 0b00100000; cube[2][5] = 0b00000000; cube[3][5] = 0b00000000; cube[4][5] = 0b00000000; 
  cube[0][6] = 0b00110000; cube[1][6] = 0b00100000; cube[2][6] = 0b00000000; cube[3][6] = 0b00000000; cube[4][6] = 0b00000000; 
  cube[0][7] = 0b00110000; cube[1][7] = 0b00100000; cube[2][7] = 0b00000000; cube[3][7] = 0b00000000; cube[4][7] = 0b00000000;
}
void wave_3(){
  cube[0][3] = 0b00111000; cube[1][3] = 0b00110000; cube[2][3] = 0b00100000; cube[3][3] = 0b00000000; cube[4][3] = 0b00000000;
  cube[0][4] = 0b00111000; cube[1][4] = 0b00110000; cube[2][4] = 0b00100000; cube[3][4] = 0b00000000; cube[4][4] = 0b00000000; 
  cube[0][5] = 0b00111000; cube[1][5] = 0b00110000; cube[2][5] = 0b00100000; cube[3][5] = 0b00000000; cube[4][5] = 0b00000000; 
  cube[0][6] = 0b00111000; cube[1][6] = 0b00110000; cube[2][6] = 0b00100000; cube[3][6] = 0b00000000; cube[4][6] = 0b00000000; 
  cube[0][7] = 0b00111000; cube[1][7] = 0b00110000; cube[2][7] = 0b00100000; cube[3][7] = 0b00000000; cube[4][7] = 0b00000000;
}
void wave_4(){
  cube[0][3] = 0b00111100; cube[1][3] = 0b00111000; cube[2][3] = 0b00110000; cube[3][3] = 0b00100000; cube[4][3] = 0b00000000;
  cube[0][4] = 0b00111100; cube[1][4] = 0b00111000; cube[2][4] = 0b00110000; cube[3][4] = 0b00100000; cube[4][4] = 0b00000000; 
  cube[0][5] = 0b00111100; cube[1][5] = 0b00111000; cube[2][5] = 0b00110000; cube[3][5] = 0b00100000; cube[4][5] = 0b00000000; 
  cube[0][6] = 0b00111100; cube[1][6] = 0b00111000; cube[2][6] = 0b00110000; cube[3][6] = 0b00100000; cube[4][6] = 0b00000000; 
  cube[0][7] = 0b00111100; cube[1][7] = 0b00111000; cube[2][7] = 0b00110000; cube[3][7] = 0b00100000; cube[4][7] = 0b00000000;
}
void wave_5(){
  cube[0][3] = 0b00111110; cube[1][3] = 0b00111100; cube[2][3] = 0b00111000; cube[3][3] = 0b00110000; cube[4][3] = 0b00100000;
  cube[0][4] = 0b00111110; cube[1][4] = 0b00111100; cube[2][4] = 0b00111000; cube[3][4] = 0b00110000; cube[4][4] = 0b00100000; 
  cube[0][5] = 0b00111110; cube[1][5] = 0b00111100; cube[2][5] = 0b00111000; cube[3][5] = 0b00110000; cube[4][5] = 0b00100000; 
  cube[0][6] = 0b00111110; cube[1][6] = 0b00111100; cube[2][6] = 0b00111000; cube[3][6] = 0b00110000; cube[4][6] = 0b00100000; 
  cube[0][7] = 0b00111110; cube[1][7] = 0b00111100; cube[2][7] = 0b00111000; cube[3][7] = 0b00110000; cube[4][7] = 0b00100000;
}

void wave_6(){
  cube[0][3] = 0b00111110; cube[1][3] = 0b00111110; cube[2][3] = 0b00111100; cube[3][3] = 0b00111000; cube[4][3] = 0b00010000;
  cube[0][4] = 0b00111110; cube[1][4] = 0b00111110; cube[2][4] = 0b00111100; cube[3][4] = 0b00111000; cube[4][4] = 0b00010000; 
  cube[0][5] = 0b00111110; cube[1][5] = 0b00111110; cube[2][5] = 0b00111100; cube[3][5] = 0b00111000; cube[4][5] = 0b00010000; 
  cube[0][6] = 0b00111110; cube[1][6] = 0b00111110; cube[2][6] = 0b00111100; cube[3][6] = 0b00111000; cube[4][6] = 0b00010000; 
  cube[0][7] = 0b00111110; cube[1][7] = 0b00111110; cube[2][7] = 0b00111100; cube[3][7] = 0b00111000; cube[4][7] = 0b00010000;
}

void wave_7(){
  cube[0][3] = 0b00111110; cube[1][3] = 0b00111110; cube[2][3] = 0b00111110; cube[3][3] = 0b00011100; cube[4][3] = 0b00001000;
  cube[0][4] = 0b00111110; cube[1][4] = 0b00111110; cube[2][4] = 0b00111110; cube[3][4] = 0b00011100; cube[4][4] = 0b00001000; 
  cube[0][5] = 0b00111110; cube[1][5] = 0b00111110; cube[2][5] = 0b00111110; cube[3][5] = 0b00011100; cube[4][5] = 0b00001000; 
  cube[0][6] = 0b00111110; cube[1][6] = 0b00111110; cube[2][6] = 0b00111110; cube[3][6] = 0b00011100; cube[4][6] = 0b00001000; 
  cube[0][7] = 0b00111110; cube[1][7] = 0b00111110; cube[2][7] = 0b00111110; cube[3][7] = 0b00011100; cube[4][7] = 0b00001000;
}

void wave_8(){
  cube[0][3] = 0b00111110; cube[1][3] = 0b00111110; cube[2][3] = 0b00011110; cube[3][3] = 0b00001110; cube[4][3] = 0b00000100;
  cube[0][4] = 0b00111110; cube[1][4] = 0b00111110; cube[2][4] = 0b00011110; cube[3][4] = 0b00001110; cube[4][4] = 0b00000100; 
  cube[0][5] = 0b00111110; cube[1][5] = 0b00111110; cube[2][5] = 0b00011110; cube[3][5] = 0b00001110; cube[4][5] = 0b00000100; 
  cube[0][6] = 0b00111110; cube[1][6] = 0b00111110; cube[2][6] = 0b00011110; cube[3][6] = 0b00001110; cube[4][6] = 0b00000100; 
  cube[0][7] = 0b00111110; cube[1][7] = 0b00111110; cube[2][7] = 0b00011110; cube[3][7] = 0b00001110; cube[4][7] = 0b00000100;
}

void wave_9(){
  cube[0][3] = 0b00111110; cube[1][3] = 0b00011110; cube[2][3] = 0b00001110; cube[3][3] = 0b00000110; cube[4][3] = 0b00000010;
  cube[0][4] = 0b00111110; cube[1][4] = 0b00011110; cube[2][4] = 0b00001110; cube[3][4] = 0b00000110; cube[4][4] = 0b00000010; 
  cube[0][5] = 0b00111110; cube[1][5] = 0b00011110; cube[2][5] = 0b00001110; cube[3][5] = 0b00000110; cube[4][5] = 0b00000010; 
  cube[0][6] = 0b00111110; cube[1][6] = 0b00011110; cube[2][6] = 0b00001110; cube[3][6] = 0b00000110; cube[4][6] = 0b00000010; 
  cube[0][7] = 0b00111110; cube[1][7] = 0b00011110; cube[2][7] = 0b00001110; cube[3][7] = 0b00000110; cube[4][7] = 0b00000010;
}
void wave_10(){
  cube[0][3] = 0b00011110; cube[1][3] = 0b00001110; cube[2][3] = 0b00000110; cube[3][3] = 0b00000010; cube[4][3] = 0b00000000;
  cube[0][4] = 0b00011110; cube[1][4] = 0b00001110; cube[2][4] = 0b00000110; cube[3][4] = 0b00000010; cube[4][4] = 0b00000000; 
  cube[0][5] = 0b00011110; cube[1][5] = 0b00001110; cube[2][5] = 0b00000110; cube[3][5] = 0b00000010; cube[4][5] = 0b00000000; 
  cube[0][6] = 0b00011110; cube[1][6] = 0b00001110; cube[2][6] = 0b00000110; cube[3][6] = 0b00000010; cube[4][6] = 0b00000000; 
  cube[0][7] = 0b00011110; cube[1][7] = 0b00001110; cube[2][7] = 0b00000110; cube[3][7] = 0b00000010; cube[4][7] = 0b00000000;
}
void wave_11(){
  cube[0][3] = 0b00101110; cube[1][3] = 0b00000110; cube[2][3] = 0b00000010; cube[3][3] = 0b00000000; cube[4][3] = 0b00000000;
  cube[0][4] = 0b00101110; cube[1][4] = 0b00000110; cube[2][4] = 0b00000010; cube[3][4] = 0b00000000; cube[4][4] = 0b00000000; 
  cube[0][5] = 0b00101110; cube[1][5] = 0b00000110; cube[2][5] = 0b00000010; cube[3][5] = 0b00000000; cube[4][5] = 0b00000000; 
  cube[0][6] = 0b00101110; cube[1][6] = 0b00000110; cube[2][6] = 0b00000010; cube[3][6] = 0b00000000; cube[4][6] = 0b00000000; 
  cube[0][7] = 0b00101110; cube[1][7] = 0b00000110; cube[2][7] = 0b00000010; cube[3][7] = 0b00000000; cube[4][7] = 0b00000000;
}
void wave_12(){
  cube[0][3] = 0b00110110; cube[1][3] = 0b00100010; cube[2][3] = 0b00000000; cube[3][3] = 0b00000000; cube[4][3] = 0b00000000;
  cube[0][4] = 0b00110110; cube[1][4] = 0b00100010; cube[2][4] = 0b00000000; cube[3][4] = 0b00000000; cube[4][4] = 0b00000000; 
  cube[0][5] = 0b00110110; cube[1][5] = 0b00100010; cube[2][5] = 0b00000000; cube[3][5] = 0b00000000; cube[4][5] = 0b00000000; 
  cube[0][6] = 0b00110110; cube[1][6] = 0b00100010; cube[2][6] = 0b00000000; cube[3][6] = 0b00000000; cube[4][6] = 0b00000000; 
  cube[0][7] = 0b00110110; cube[1][7] = 0b00100010; cube[2][7] = 0b00000000; cube[3][7] = 0b00000000; cube[4][7] = 0b00000000;
}
void wave_13(){
  cube[0][3] = 0b00111010; cube[1][3] = 0b00110000; cube[2][3] = 0b00100000; cube[3][3] = 0b00000000; cube[4][3] = 0b00000000;
  cube[0][4] = 0b00111010; cube[1][4] = 0b00110000; cube[2][4] = 0b00100000; cube[3][4] = 0b00000000; cube[4][4] = 0b00000000; 
  cube[0][5] = 0b00111010; cube[1][5] = 0b00110000; cube[2][5] = 0b00100000; cube[3][5] = 0b00000000; cube[4][5] = 0b00000000; 
  cube[0][6] = 0b00111010; cube[1][6] = 0b00110000; cube[2][6] = 0b00100000; cube[3][6] = 0b00000000; cube[4][6] = 0b00000000; 
  cube[0][7] = 0b00111010; cube[1][7] = 0b00110000; cube[2][7] = 0b00100000; cube[3][7] = 0b00000000; cube[4][7] = 0b00000000;
}
void wave_14(){
  cube[0][3] = 0b00111100; cube[1][3] = 0b00111000; cube[2][3] = 0b00110000; cube[3][3] = 0b00100000; cube[4][3] = 0b00000000;
  cube[0][4] = 0b00111100; cube[1][4] = 0b00111000; cube[2][4] = 0b00110000; cube[3][4] = 0b00100000; cube[4][4] = 0b00000000; 
  cube[0][5] = 0b00111100; cube[1][5] = 0b00111000; cube[2][5] = 0b00110000; cube[3][5] = 0b00100000; cube[4][5] = 0b00000000; 
  cube[0][6] = 0b00111100; cube[1][6] = 0b00111000; cube[2][6] = 0b00110000; cube[3][6] = 0b00100000; cube[4][6] = 0b00000000; 
  cube[0][7] = 0b00111100; cube[1][7] = 0b00111000; cube[2][7] = 0b00110000; cube[3][7] = 0b00100000; cube[4][7] = 0b00000000;
}
void wave_15(){
  cube[0][3] = 0b00111110; cube[1][3] = 0b00111100; cube[2][3] = 0b00111000; cube[3][3] = 0b00110000; cube[4][3] = 0b00100000;
  cube[0][4] = 0b00111110; cube[1][4] = 0b00111100; cube[2][4] = 0b00111000; cube[3][4] = 0b00110000; cube[4][4] = 0b00100000; 
  cube[0][5] = 0b00111110; cube[1][5] = 0b00111100; cube[2][5] = 0b00111000; cube[3][5] = 0b00110000; cube[4][5] = 0b00100000; 
  cube[0][6] = 0b00111110; cube[1][6] = 0b00111100; cube[2][6] = 0b00111000; cube[3][6] = 0b00110000; cube[4][6] = 0b00100000; 
  cube[0][7] = 0b00111110; cube[1][7] = 0b00111100; cube[2][7] = 0b00111000; cube[3][7] = 0b00110000; cube[4][7] = 0b00100000;
}
//===========================================================================================================================================

void draw(){
  // Repeat p many times before moving on to next frame 
  // change what p is less than; more for slower annimation, less for faster
  for(int p = 0; p < 6; p++){ 
    // Reset to first layer
    layerIndex = 0;
    for(int q = 0; q < 5; q++){
      // Reset to row 1
      rowIndex = 0;
      // Make shift registers accept new data
      digitalWrite(latchPin, LOW); 
      for(int t = 0; t < 8; t++){
        shiftOut(dataPin, clockPin, MSBFIRST, cube[layerIndex][rowIndex]);
        // Move onto the next row then repeat
        rowIndex++;                                                      
      }
      // Move onto the next layer and repeat
      layerOff(layerIndex-1);
      layerOn(layerIndex);
      layerIndex++;
      digitalWrite(latchPin, HIGH);
    }
    allOff();
  }
}

void setup() 
{
  // Setup the pin modes
  pinMode(dataPin,     OUTPUT);
  pinMode(clockPin,    OUTPUT);
  pinMode(latchPin,    OUTPUT);
  pinMode(masterClear, OUTPUT);

  // Clear the shift registers
  digitalWrite(masterClear, LOW);
  delay(10);
  digitalWrite(masterClear, HIGH);

  for (int i = 0; i < 5; i++) {
    pinMode(layerPin[i], OUTPUT);
  }
}

void loop() 
{
  
  number3();
  number2();
  number1();
  number0();
 

  for(int x = 0; x < 3; x++) {
    box_zoom_1();
  }
  for(int x = 0; x < 2; x++) {
    box_zoom_2();
    box_zoom_3(); 
  }
  // wall gose up
  for(int x = 4; x >=0; x--) {
    plane(x);
  }
  // wall gose down
  for(int x = 0; x < 5; x++) {
    plane(x);
  }
  wall_left();
  wall_right();
  allOff();
  wall_back();
  wall_front();
  for(int x = 0; x < 1; x++) {
    effect_rain (50);
  }
  wave();
}

void wall_left()
{
  fill_cube(0b00000010);
  draw();
  fill_cube(0b00000100);
  draw();
  fill_cube(0b00001000);
  draw();
  fill_cube(0b00010000);
  draw();
  fill_cube(0b00100000);
  draw();
}

void wall_right()
{
  fill_cube(0b00100000);
  draw();
  fill_cube(0b00010000);
  draw();
  fill_cube(0b00001000);
  draw();
  fill_cube(0b00000100);
  draw();
  fill_cube(0b00000010);
  draw();
}

void wall_front()
{
  for (int i=3;i < 8; i++) {
    none();
    for (int layer=0; layer < 5; layer++) {
      cube[layer][i] = 0b00111110;
    }
    draw();
  }
}
void wall_back()
{
  for (int i=7;i >= 3; i--) {
    none();
    for (int layer=0; layer < 5; layer++) {
      cube[layer][i] = 0b00111110;
    }
    draw();
  }
}

void plane(int i)
{
  none();
  for(int x=0;x<8;x++){
    cube[i][x]=0b11111111;
  }
  draw();
}

void box_zoom_1()
{
  box_1();
  draw();
  box_2();
  draw();
  box_3();
  draw();
  box_2();
  draw();
  box_1();
  draw();
}

void box_zoom_2()
{
  box_1();
  draw();
  box_4();
  draw();
  box_5();
  draw();
  box_6();
  draw();
  box_7();
  draw();
  box_6();
  draw();
  box_5();
  draw();
  box_4();
  draw();
  box_1();
  draw();
}

void box_zoom_3()
{
  box_1();
  draw();
  box_8();
  draw();
  box_9();
  draw();
  box_10();
  draw();
  box_11();
  draw();
  box_10();
  draw();
  box_9();
  draw();
  box_8();
  draw();
  box_1();
  draw();
}

void wave(){
  wave_1();
  draw();
  wave_2();
  draw();
  wave_3();
  draw();
  wave_4();
  draw();
  wave_5();
  draw();
  wave_6();
  draw();
  for (int i=0; i < 5; i++){
    wave_7();
    draw();
    wave_8();
    draw();
    wave_9();
    draw();
    wave_10();
    draw();
    wave_11();
    draw();
    wave_12();
    draw();
    wave_13();
    draw();
    wave_14();
    draw();
    wave_15();
    draw();
  }
}






//===========================================================================================================================================
void effect_rain (int iterations)
{
  int i, ii;
  int rnd_x;
  int rnd_y;
  int rnd_num;

  for (ii=0;ii<iterations;ii++)
  {
    rnd_num = rand()%4;

    for (i=0; i < rnd_num;i++)
    {
      rnd_x = rand()%8;
      rnd_y = rand()%8;
      setvoxel(rnd_x,rnd_y,0);
    }
    draw();
    delay_ms(10);
    shift(AXIS_Z,1);
  }
}
// Set a single voxel to ON
void setvoxel(int x, int y, int z)
{
  if (inrange(x,y,z))
    cube[z][y] |= (1 << x);
}


// Set a single voxel to ON
void clrvoxel(int x, int y, int z)
{
  if (inrange(x,y,z))
    cube[z][y] &= ~(1 << x);
}



// This function validates that we are drawing inside the cube.
unsigned char inrange(int x, int y, int z)
{
  if (x >= 0 && x < 8 && y >= 0 && y < 8 && z >= 0 && z < 5)
  {
    return 0x01;
  } else
  {
    // One of the coordinates was outside the cube.
    return 0x00;
  }
}

// Get the current status of a voxel
unsigned char getvoxel(int x, int y, int z)
{
  if (inrange(x,y,z))
  {
    if (cube[z][y] & (1 << x))
    {
      return 0x01;
    } else
    {
      return 0x00;
    }
  } else
  {
    return 0x00;
  }
}

// In some effect we want to just take bool and write it to a voxel
// this function calls the apropriate voxel manipulation function.
void altervoxel(int x, int y, int z, int state)
{
  if (state == 1)
  {
    setvoxel(x,y,z);
  } else
  {
    clrvoxel(x,y,z);
  }
}

// Flip the state of a voxel.
// If the voxel is 1, its turned into a 0, and vice versa.
void flpvoxel(int x, int y, int z)
{
  if (inrange(x, y, z))
    cube[z][y] ^= (1 << x);
}

// Makes sure x1 is alwas smaller than x2
// This is usefull for functions that uses for loops,
// to avoid infinite loops
void argorder(int ix1, int ix2, int *ox1, int *ox2)
{
  if (ix1>ix2)
  {
    int tmp;
    tmp = ix1;
    ix1= ix2;
    ix2 = tmp;
  }
  *ox1 = ix1;
  *ox2 = ix2;
}

// Sets all voxels along a X/Y plane at a given point
// on axis Z
void setplane_z (int z)
{
  int i;
  if (z>=0 && z<5)
  {
    for (i=0;i<8;i++)
      cube[z][i] = 0xff;
  }
}

// Clears voxels in the same manner as above
void clrplane_z (int z)
{
  int i;
  if (z>=0 && z<5)
  {
    for (i=0;i<8;i++)
      cube[z][i] = 0x00;
  }
}

void setplane_x (int x)
{
  int z;
  int y;
  if (x>=0 && x<8)
  {
    for (z=0;z<5;z++)
    {
      for (y=0;y<8;y++)
      {
        cube[z][y] |= (1 << x);
      }
    }
  }
}

void clrplane_x (int x)
{
  int z;
  int y;
  if (x>=0 && x<8)
  {
    for (z=0;z<5;z++)
    {
      for (y=0;y<8;y++)
      {
        cube[z][y] &= ~(1 << x);
      }
    }
  }
}

void setplane_y (int y)
{
  int z;
  if (y>=0 && y<8)
  {
    for (z=0;z<5;z++)
      cube[z][y] = 0xff;
  }
}

void clrplane_y (int y)
{
  int z;
  if (y>=0 && y<8)
  {
    for (z=0;z<5;z++)
      cube[z][y] = 0x00;
  }
}

void setplane (char axis, unsigned char i)
{
    switch (axis)
    {
        case AXIS_X:
            setplane_x(i);
            break;

       case AXIS_Y:
            setplane_y(i);
            break;

       case AXIS_Z:
            setplane_z(i);
            break;
    }
}

void clrplane (char axis, unsigned char i)
{
    switch (axis)
    {
        case AXIS_X:
            clrplane_x(i);
            break;

       case AXIS_Y:
            clrplane_y(i);
            break;

       case AXIS_Z:
            clrplane_z(i);
            break;
    }
}

// Fill a value into all 64 byts of the cube buffer
// Mostly used for clearing. fill(0x00)
// or setting all on. fill(0xff)
void fill (unsigned char pattern)
{
  int z;
  int y;
  for (z=0;z<5;z++)
  {
    for (y=0;y<8;y++)
    {
      cube[z][y] = pattern;
    }
  }
}



// Draw a box with all walls drawn and all voxels inside set
void box_filled(int x1, int y1, int z1, int x2, int y2, int z2)
{
  int iy;
  int iz;

  argorder(x1, x2, &x1, &x2);
  argorder(y1, y2, &y1, &y2);
  argorder(z1, z2, &z1, &z2);

  for (iz=z1;iz<=z2;iz++)
  {
    for (iy=y1;iy<=y2;iy++)
    {
      cube[iz][iy] |= byteline(x1,x2);
    }
  }

}

// Darw a hollow box with side walls.
void box_walls(int x1, int y1, int z1, int x2, int y2, int z2)
{
  int iy;
  int iz;

  argorder(x1, x2, &x1, &x2);
  argorder(y1, y2, &y1, &y2);
  argorder(z1, z2, &z1, &z2);

  for (iz=z1;iz<=z2;iz++)
  {
    for (iy=y1;iy<=y2;iy++)
    {
      if (iy == y1 || iy == y2 || iz == z1 || iz == z2)
      {
        cube[iz][iy] = byteline(x1,x2);
      } else
      {
        cube[iz][iy] |= ((0x01 << x1) | (0x01 << x2));
      }
    }
  }

}

// Draw a wireframe box. This only draws the corners and edges,
// no walls.
void box_wireframe(int x1, int y1, int z1, int x2, int y2, int z2)
{
  int iy;
  int iz;

  argorder(x1, x2, &x1, &x2);
  argorder(y1, y2, &y1, &y2);
  argorder(z1, z2, &z1, &z2);

  // Lines along X axis
  cube[z1][y1] = byteline(x1,x2);
  cube[z1][y2] = byteline(x1,x2);
  cube[z2][y1] = byteline(x1,x2);
  cube[z2][y2] = byteline(x1,x2);

  // Lines along Y axis
  for (iy=y1;iy<=y2;iy++)
  {
    setvoxel(x1,iy,z1);
    setvoxel(x1,iy,z2);
    setvoxel(x2,iy,z1);
    setvoxel(x2,iy,z2);
  }

  // Lines along Z axis
  for (iz=z1;iz<=z2;iz++)
  {  
    setvoxel(x1,y1,iz);
    setvoxel(x1,y2,iz);
    setvoxel(x2,y1,iz);
    setvoxel(x2,y2,iz);
  }

}

// Returns a byte with a row of 1's drawn in it.
// byteline(2,5) gives 0b00111100
char byteline (int start, int end)
{
  return ((0xff<<start) & ~(0xff<<(end+1)));
}

// Flips a byte 180 degrees.
// MSB becomes LSB, LSB becomes MSB.
char flipbyte (char byte)
{
  char flop = 0x00;

  flop = (flop & 0b11111110) | (0b00000001 & (byte >> 7));
  flop = (flop & 0b11111101) | (0b00000010 & (byte >> 5));
  flop = (flop & 0b11111011) | (0b00000100 & (byte >> 3));
  flop = (flop & 0b11110111) | (0b00001000 & (byte >> 1));
  flop = (flop & 0b11101111) | (0b00010000 & (byte << 1));
  flop = (flop & 0b11011111) | (0b00100000 & (byte << 3));
  flop = (flop & 0b10111111) | (0b01000000 & (byte << 5));
  flop = (flop & 0b01111111) | (0b10000000 & (byte << 7));
  return flop;
}

// Draw a line between any coordinates in 3d space.
// Uses integer values for input, so dont expect smooth animations.
void line(int x1, int y1, int z1, int x2, int y2, int z2)
{
  float xy; // how many voxels do we move on the y axis for each step on the x axis
  float xz; // how many voxels do we move on the y axis for each step on the x axis
  unsigned char x,y,z;
  unsigned char lasty,lastz;

  // We always want to draw the line from x=0 to x=7.
  // If x1 is bigget than x2, we need to flip all the values.
  if (x1>x2)
  {
    int tmp;
    tmp = x2; x2 = x1; x1 = tmp;
    tmp = y2; y2 = y1; y1 = tmp;
    tmp = z2; z2 = z1; z1 = tmp;
  }


  if (y1>y2)
  {
    xy = (float)(y1-y2)/(float)(x2-x1);
    lasty = y2;
  } else
  {
    xy = (float)(y2-y1)/(float)(x2-x1);
    lasty = y1;
  }

  if (z1>z2)
  {
    xz = (float)(z1-z2)/(float)(x2-x1);
    lastz = z2;
  } else
  {
    xz = (float)(z2-z1)/(float)(x2-x1);
    lastz = z1;
  }



  // For each step of x, y increments by:
  for (x = x1; x<=x2;x++)
  {
    y = (xy*(x-x1))+y1;
    z = (xz*(x-x1))+z1;
    setvoxel(x,y,z);
  }

}

// Delay loop.
// This is not calibrated to milliseconds,
// but we had allready made to many effects using this
// calibration when we figured it might be a good idea
// to calibrate it.
void delay_ms(uint16_t x)
{
  uint8_t y, z;
  for ( ; x > 0 ; x--){
    for ( y = 0 ; y < 90 ; y++){
      for ( z = 0 ; z < 6 ; z++){
        asm volatile ("nop");
      }
    }
  }
}



// Shift the entire contents of the cube along an axis
// This is great for effects where you want to draw something
// on one side of the cube and have it flow towards the other
// side. Like rain flowing down the Z axiz.
void shift (char axis, int direction)
{
  int i, x ,y;
  int ii, iii;
  int state;

  for (i = 0; i < 8; i++)
  {
    if (direction == -1)
    {
      ii = i;
    } else
    {
      ii = (5-i);
    }


    for (x = 0; x < 8; x++)
    {
      for (y = 0; y < 8; y++)
      {
        if (direction == -1)
        {
          iii = ii+1;
        } else
        {
          iii = ii-1;
        }

        if (axis == AXIS_Z)
        {
          state = getvoxel(x,y,iii);
          altervoxel(x,y,ii,state);
        }

        if (axis == AXIS_Y)
        {
          state = getvoxel(x,iii,y);
          altervoxel(x,ii,y,state);
        }

        if (axis == AXIS_X)
        {
          state = getvoxel(iii,y,x);
          altervoxel(ii,y,x,state);
        }
      }
    }
  }

  if (direction == -1)
  {
    i = 5;
  } else
  {
    i = 0;
  }

  for (x = 0; x < 8; x++)
  {
    for (y = 0; y < 8; y++)
    {
      if (axis == AXIS_Z)
        clrvoxel(x,y,i);

      if (axis == AXIS_Y)
        clrvoxel(x,i,y);

      if (axis == AXIS_X)
        clrvoxel(i,y,x);
    }
  }
}
