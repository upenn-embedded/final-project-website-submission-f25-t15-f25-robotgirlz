#include <i2cdriver.h>
#include <math.h>

#define Taddr 0x3A

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

 //  DEclare these in the main file ?? and then the functions jsut update them 
 
   int32_t Fa32;
int32_t Fb32;
int32_t Ga32;        
int16_t Ha16;
int16_t Hb16;
int16_t Gb16;
int32_t PR32;
int32_t PG32;
int32_t PO32;
int32_t PT32;
int16_t Ka16;
     
  /*  uint8_t tmeas52 = [2];
    uint8_t tmeas53 = [2];
    uint8_t tmeas54 = [2];  // Or should these be inthe main file and the just like updated in the function? 
    uint8_t tmeas55 = [2];
    uint8_t tmeas56 = [2];
    uint8_t tmeas57 = [2];
    uint8_t tmeas58 = [2];
    uint8_t tmeas59 = [2];
    uint8_t tmeas60 = [2];*/
    
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

    /*float To = 25; //temp var*/

void calibrate();



void tempint();


//void setrefreshrate(uint8_t u); // I think we can just use the default because I don't want to write to eeprom  .5 s is default which meets our SRS
void startmeas();

/*  uint8_t tmeas1 = [2]; // 2 bytes
    uint8_t tmeas2 = [2]; all of the input should eb length 2
    uint8_t tmeas3 = [2];*/

void measurement(uint16_t addr1,uint16_t addr2, uint16_t addr3, uint8_t *tmeas1, uint8_t *tmeas2, uint8_t *tmeas3);//To?  when shoud I declare that should it be an input 

float gettemp();


//adress adn what not i2c to get the temperature 


 

