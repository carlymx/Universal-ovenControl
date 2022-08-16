  /***************************************************************  
    openELECTRO
    Home appliance control, based on arduino and other MPU

    https://github.com/carlymx/openELECTRO
    By surfzone, CaRLyMx
    jordi@surfzone.org, carlymx@gmail.com
    2022
***************************************************************/

String resistances_to_text(byte resist) {
    // TODO: OPTIMIZAR STRINGS
    //char aux[10];
    String res = (String)((resist & RESIST_UP) != 0 ? "UP " : "   ")
               + (String)((resist & RESIST_DOWN) != 0 ? "DO " : "   ")
               + (String)((resist & RESIST_REAR) != 0 ? "RE " : "   ");

    return res;
}