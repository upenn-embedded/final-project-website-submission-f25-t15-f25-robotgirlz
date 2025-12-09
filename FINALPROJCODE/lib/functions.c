/*
output functions defined 
*/
#include <TEMPSENSOR/tempi2c.h>
#include <TEMPSENSOR/gettempfuntionc.h>
#include <WLsensor/disancei2c.h> 
#include <lib/LCD_GFX.h> 

void drawtemp(){
    Drawchar(x, y, degtemp);// UPDATE LCD with current temperature 
    drawcirc(/*right next to the degrees */);

}

void drawwL(){
    //update LCD with most recent total water drank change 
    Drawchar(x,y, wtot);
    drawchar(x,y);


}

void yell(){
   
    // if yell flag set then ... play audio 
     //play audio 
}

void face(){
   // drawFace
   // depending on bvbutton press mod 4 change displayed face 
   // use call face function
}



void LEDupdate(){
    if (deg> 80) {
        /*LED red */
    }
    if (45 < deg < 80){
        /*LED CYAN */

    }
    if ( deg < 20 ){
        /* LED BLUE */
    }


}




