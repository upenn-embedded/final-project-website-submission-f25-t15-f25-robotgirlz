#include "i2cdriver.h"
#include <math.h>
#include "tempi2c.h"

#define Taddr 0x3A //deviceaddress for the snesor 

// data register addresses for extended object measuremnet (the measurement that we want )

#define RAM52 0x4033
#define RAM53 0x4034
#define RAM54 0x4035
#define RAM55 0x4036
#define RAM56 0x4037
#define RAM57 0x4038
#define RAM58 0x4039
#define RAM59 0x403A
#define RAM60 0x403B

#define REG_CTRL   0x3001 /**< Control Register address */
#define EE_CTRL    0x24d4 /**< Control register initial value */

#define EE_P_R     0x240c /**< Calibration constant ambient reference register 32bit */
#define EE_P_G     0x240e /**< Calibration constant ambient gain register 32bit */
#define EE_P_T     0x2410 /**< Calibration constant ambient tc2 register 32bit */
#define EE_P_O     0x2412 /**< Calibration constant ambient offset register 32bit */
#define EE_Aa      0x2414 /**< Aa calibration const register 32bit */
#define EE_Ab      0x2416 /**< Ab calibration const register 32bit */
#define EE_Ba      0x2418 /**< Ba calibration const register 32bit */
#define EE_Bb      0x241a /**< Bb calibration const register 32bit */
#define EE_Ca      0x241c /**< Ca calibration const register 32bit */
#define EE_Cb      0x241e /**< Cb calibration const register 32bit */
#define EE_Da      0x2420 /**< Da calibration const register 32bit */
#define EE_Db      0x2422 /**< Db calibration const register 32bit */
#define EE_Ea      0x2424 /**< Ea calibration constant register 32bit */
#define EE_Eb      0x2426 /**< Eb calibration constant register 32bit */
#define EE_Fa      0x2428 /**< Fa calibration constant register 32bit */
#define EE_Fb      0x242a /**< Fb calibration constant register 32bit */
#define EE_Ga      0x242c /**< Ga calibration constant register 32bit */
#define EE_Gb      0x242e /**< Ambient Beta calibration constant 16bit */
#define EE_Ka      0x242f /**< IR Beta calibration constant 16bit */
#define EE_Ha      0x2481 /**< Ha customer calibration value register 16bit */
#define EE_Hb      0x2482 /**< Hb customer calibration value register 16bit */


//imjust defining the calbis as numbers rn? maybe nto 

 //  DEclare these in the main file ?? and then the functions jsut update them 

    uint8_t tmeas52[2];
     uint8_t tmeas53[2];
      uint8_t tmeas54[2]; // Or should these be inthe main file and the just like updated in the function? 
    uint8_t tmeas55[2];
     uint8_t tmeas56[2]; 
     uint8_t tmeas57[2]; 
     uint8_t tmeas58[2]; 
     uint8_t tmeas59[2]; 
     uint8_t tmeas60[2];
     
 int32_t Fa32 = 0x039A30D8;
int32_t Fb32 = 0xFCF549F8;
int32_t Ga32 = 0xFDDABC7C;        
int16_t Ha16 = 0x7575;
int16_t Hb16 = 0x0000;
int16_t Gb16 = 0x2A00;
int32_t PR32 = 0x0058E110;
int32_t PG32 = 0x04AF8888;
int32_t PO32 = 0x00001900;
int32_t PT32 = 0x00000000;
int16_t Ka16 = 0x2A00;

uint8_t EFa[4];
    uint8_t EFb[4];  
    uint8_t EGa[4];
    uint8_t EGb[2];
    uint8_t EHa[2];
    uint8_t EHb[2]; // set up data arrays for each of the calibrations 
    uint8_t EPG[4];
    uint8_t EPR[4];
    uint8_t EPT[4];
    uint8_t EPO[4];
    uint8_t EKa[2];
float PrevTo = 25.0;

void calibrate(void){
    I2C1_readfromregister(Taddr,EE_Fa,EFa,4);
    I2C1_readfromregister(Taddr,EE_Fb,EFb,4);
    I2C1_readfromregister(Taddr,EE_Ga,EGa,4);
    I2C1_readfromregister(Taddr,EE_Gb,EGb,2);
    I2C1_readfromregister(Taddr,EE_Ha,EHa,2);
    I2C1_readfromregister(Taddr,EE_Ka,EKa,2);
    I2C1_readfromregister(Taddr,EE_Hb,EHb,2);
    I2C1_readfromregister(Taddr,EE_P_G,EPG,4);
    I2C1_readfromregister(Taddr,EE_P_R,EPR,4);
    I2C1_readfromregister(Taddr,EE_P_T,EPT,4);
    I2C1_readfromregister(Taddr,EE_P_O,EPO,4);

    Fa32 = ((int32_t)EFa[0]<<24) | ((int32_t)EFa[1]<<16) | ((int32_t)EFa[2]<<8) | ((int32_t)EFa[3]);
    Fb32 = ((int32_t)EFb[0]<<24) | ((int32_t)EFb[1]<<16) | ((int32_t)EFb[2]<<8) | ((int32_t)EFb[3]);
    Ga32 = ((int32_t)EGa[0]<<24) | ((int32_t)EGa[1]<<16) | ((int32_t)EGa[2]<<8) | ((int32_t)EGa[3]);
    Gb16 = ((int16_t)EGb[0]<<8) | ((int16_t)EGb[1]);
    Ha16 = ((int16_t)EHa[0]<<8) | ((int16_t)EHa[1]);
    Ka16 = ((int16_t)EKa[0]<<8) | ((int16_t)EKa[1]);
    Hb16 = ((int16_t)EHb[0]<<8) | ((int16_t)EHb[1]);
    PG32 = ((int32_t)EPG[0]<<24) | ((int32_t)EPG[1]<<16) | ((int32_t)EPG[2]<<8) | ((int32_t)EPG[3]);
    PR32 = ((int32_t)EPR[0]<<24) | ((int32_t)EPR[1]<<16) | ((int32_t)EPR[2]<<8) | ((int32_t)EPR[3]);
    PT32 = ((int32_t)EPT[0]<<24) | ((int32_t)EPT[1]<<16) | ((int32_t)EPT[2]<<8) | ((int32_t)EPT[3]);
    PO32 = ((int32_t)EPO[0]<<24) | ((int32_t)EPO[1]<<16) | ((int32_t)EPO[2]<<8) | ((int32_t)EPO[3]);
}

void tempint(void){
    uint8_t CTRL[2];

    I2C1_readfromregister(Taddr, REG_CTRL, CTRL, 2);
  

    // CTRLl |= 0b10001010;  
    // CTRLl &= 0b10001101;

    // CTRLm |= 0b00000001;
    // CTRLm &= 0b11111111;

    // uint8_t ctrlset[2] = {CTRLm, CTRLl};
   uint8_t CTRLInt[2] = {0x25,0x14};
    I2C1_writetoregister(Taddr, REG_CTRL, CTRLInt, 2);
    I2C1_readfromregister(Taddr, REG_CTRL, CTRL, 2);
}



//void setrefreshrate(uint8_t u){}; // I think we can just use the default because I don't want to write to eeprom  .5 s is default which meets our SRS
void startmeas(void){
    uint8_t ctrl[2];
    I2C1_readfromregister(Taddr, REG_CTRL, ctrl, 2);

    ctrl[1] |= 0b00001000;   // set SOC bit

    I2C1_writetoregister(Taddr, REG_CTRL, ctrl, 2);
}


/*  uint8_t tmeas1 = [2]; // 2 bytes
    uint8_t tmeas2 = [2]; all of the input should eb length 2
    uint8_t tmeas3 = [2];*/

void measurement(uint16_t addr1,uint16_t addr2, uint16_t addr3, uint8_t *tmeas1, uint8_t *tmeas2, uint8_t *tmeas3){
   
    I2C1_readfromregister(Taddr,addr1,tmeas1,2);
    I2C1_readfromregister(Taddr,addr2,tmeas2,2); // read 2 bytes at 3 differnet addresses
    I2C1_readfromregister(Taddr,addr3,tmeas3,2);
    }   

float tmath(  uint16_t M52, uint16_t M53, uint16_t M54,  uint16_t M55, uint16_t M56, uint16_t M57,  uint16_t M58, uint16_t M59, uint16_t M60, float prevTo) // pass previous To value) {
   { float fM52 = (float)M52;
    float fM53 = (float)M53; // make everythign a float so it stops getting mad 
    float fM54 = (float)M54;
    float fM55 = (float)M55;
    float fM56 = (float)M56;
    float fM57 = (float)M57;
    float fM58 = (float)M58;
    float fM59 = (float)M59;
    float fM60 = (float)M60;

// Im justing gonna make them numbers 
    float fFa = ((float)Fa32) * powf(2.0f, -46.0f) ;//  .00000079f;          
    float fFb = ((float)Fb32) * powf(2.0f, -36.0f);  //-.00045f;
    float fGa = ((float)Ga32) * powf(2.0f, -36.0f);//-.00049f;
    float fGb = ((float)Gb16) * powf(2.0f, -10.0f); //9.5f;
    float fHa = ((float)Ha16) * powf(2.0f, -14.0f);//1.0f;
    float fHb = ((float)Hb16) * powf(2.0f,-10.0f);//0.0f;
    float fKa = ((float)Ka16) * powf(2.0f, -10.0);//10.5f;
    float fPR = ((float)PR32) * powf(2.0f, -8.0f); //23809.01f;
    float fPO = ((float)PO32) * powf(2.0f, -8.0f); //25.0f;
    float fPT = 0.0f;
    float fPG = ((float)PG32) * powf(2.0f,20.0f);//81.1125f;

    // --- Compute S safely ---
    float S = ((fM52 - fM53 - fM55 + fM56)/2.0f) + fM58 + fM59;

    // --- Compute Vto, Vta, amb safely ---
    float Vto = fM57 + (fKa) * (fM54 / 12.0f);   
    float Sto = ((S / 12.0f) / Vto) * (524288.0f);           //2^19 = 524288
    float Vta = fM57 + fGb * (fM54 / 12.0f);
    float amb = ((fM54 / 12.0f) / Vta) * 524288.0f;               // 2^19

    // --- Compute ambient temperature safely ---
    float Ta = fPO  + ((amb - fPR) / (fPG)) + (fPT * powf((amb - fPR ), 2));  
    // 2^-8 = 1/256, 2^-20 = 1/1048576, 2^-44 ≈ 1/1.759e13

    // --- Initialize previous To safely ---
    float To_prev = prevTo > 0.0f ? prevTo : Ta;  // avoid using uninitialized To

    // --- Compute object temperature safely ---
    float denominator = 0.5f * (fFa) * (fHa) * (1.0f + fGa * (To_prev - 25.0f)  + fFb * (Ta - 25.0f));

    float tmp = (Sto / denominator) + powf(Ta + 273.15f, 4.0f);

    if(tmp < 0.0f) tmp = 0.0f;  // prevent NaN

    float To = powf(tmp, 0.25f) - 273.15f - fHb;

    return To;
}

// float tmath(uint16_t M52, uint16_t M53, uint16_t M54, uint16_t M55, uint16_t M56, uint16_t M57, uint16_t M58, uint16_t M59, uint16_t M60){
//     /*floats adn whatnot*/
//     float Fa = Fa32 * (1.0f / powf(2,46));  // 
//     float Fb = (float)Fb32;
//     float Ga = (float)Ga32;
//     float Gb = (float)Gb16;
//     float Ha = (float)Ha16;
//     float Hb = (float)Hb16;
//     float Ka = (float)Ka16;
//     float PR = (float)PR32;
//     float PO = (float)PO32;
//     float PT = (float)PT32;
//     float PG = (float)PG32;
   
    
//     float S = ((float)M52-(float)M53-(float)M55+(float)M56)/2.0f + M58 + M59;
//     float Vto = (float)M57 + (Ka * (1.0f / 1024.0f)) * ((float)M54 / 12.0f);
//     float Sto = ((S/12.0f)/Vto) * (1.0f / 524288.0f);  // 2^19 = 524288
//     float Vta = (float)M57 + Gb*pow(2,-10)*(M54/12);
//     float amb = (((float)M54)/12.0f / Vta) * 524288.0f;  // 2^19
//     float Ta = (float)PO*pow(2,-8)+((amb - PR*pow(2,-8))/(PG*pow(2,-20)))+(PT*pow(2,-44))*pow((amb - PR*pow(2,-8)),2); // actually you need ot redefeine TA 
//     float Tak = (float) Ta +273;
//     float Tokelv = (float) (Sto)/(.5*(Fa*pow(2,-46))*(Ha*pow(2,-14))*(1+(Ga*pow(2,-36))*(To - 25)+(Fa*pow(2,-46))*(Ta-25)))+pow(Tak,4); //-273.15 - Hb; // oh golly the To 
//      To = powf(Tokelv, 0.25f) - 273.15f - Hb;
//     return To;
// } //To?  when shoud I declare that should it be an input 

float gettemp(void){
    startmeas();
    _delay_ms(50);
    measurement(RAM52,RAM53,RAM54,tmeas52, tmeas53, tmeas54);
    _delay_ms(10);

    measurement(RAM55,RAM56,RAM57,tmeas55, tmeas56, tmeas57);
    _delay_ms(10);

    measurement(RAM58,RAM59,RAM60,tmeas58, tmeas59, tmeas60);
    _delay_ms(10);

    uint16_t Stmeas52 = (tmeas52[0]<<8)|tmeas52[1];
    uint16_t Stmeas53 = (tmeas53[0]<<8)|tmeas53[1];
    uint16_t Stmeas54 = (tmeas54[0]<<8)|tmeas54[1];
    uint16_t Stmeas55 = (tmeas55[0]<<8)|tmeas55[1];
    uint16_t Stmeas56 = (tmeas56[0]<<8)|tmeas56[1];
    uint16_t Stmeas57 = (tmeas57[0]<<8)|tmeas57[1];
    uint16_t Stmeas58 = (tmeas58[0]<<8)|tmeas58[1];
    uint16_t Stmeas59 = (tmeas59[0]<<8)|tmeas59[1];
    uint16_t Stmeas60 = (tmeas60[0]<<8)|tmeas60[1];

    float obtemp = tmath(
        Stmeas52, Stmeas53, Stmeas54,
        Stmeas55, Stmeas56, Stmeas57,
        Stmeas58, Stmeas59, Stmeas60, 25.0);
//PrevTo = obtemp;

    return obtemp;
}




//adress adn what not i2c to get the temperature