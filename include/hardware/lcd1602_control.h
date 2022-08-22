/***************************************************************  
    openELECTRO
    Home appliance control, based on arduino and other MPU

    https://github.com/carlymx/openELECTRO
    jordi@surfzone.org, carlymx@gmail.com
    2022
***************************************************************/

String _screen_text = "";
byte _screen_text_index = 0;
byte _screen_text_index_zero = 0;
byte _screen_resist = 0;
String _screen_info = "";
byte _screen_info_index = 0;
byte _screen_info_index_zero = 0;
int _screen_current_temp = 0;
int _screen_prog_temp = 0;

#define RESSTR_MONITOR "Mon "

inline int min_i(int a, int b) { return a < b ? a : b; };

// Funciones que definiremos en cada driver de pantalla
void screen_lines_write();
void screen_clear();
void screen_resist_write();
void screen_write_xy(int x, int y, char *msg, int len);

void screen_text_write() {
    char aux[LCD_LEN_TXT + 1]; 
    int len = min_i(_screen_text.length(), LCD_LEN_TXT);
    _screen_text.substring(_screen_text_index).toCharArray(aux, len + 1);
    for(int i = len; i < LCD_LEN_TXT; i++) aux[i] = ' ';
    aux[LCD_LEN_TXT] = 0;
    screen_write_xy(LCD_POS_TXT_X, LCD_POS_TXT_Y, aux, LCD_LEN_TXT);
    screen_lines_write();
}

void screen_info_write() {
    char aux[LCD_LEN_INFO + 1]; 
    //memset(aux, ' ', sizeof(aux));

    if(_screen_info != "") {
        int len = min_i(_screen_info.length(), LCD_LEN_INFO);
        _screen_info.substring(_screen_info_index).toCharArray(aux, len + 1);
    } else {
        if(_screen_prog_temp != 0)
            sprintf(aux, " %3d/%3d%s", _screen_current_temp, _screen_prog_temp, " C");
        else 
            sprintf(aux, "     %3d%s", _screen_current_temp, " C");        

    }

    for(int i = strlen(aux); i < LCD_LEN_INFO; i++) aux[i] = ' ';
    aux[LCD_LEN_INFO] = 0;

    screen_write_xy(LCD_POS_INFO_X, LCD_POS_INFO_Y, aux, LCD_LEN_INFO);
    screen_lines_write();
}

void screen_refresh(){
  if(_screen_text.length() > LCD_LEN_TXT) {
    _screen_text_index_zero++;
    if (_screen_text_index_zero > 2){
      _screen_text_index++;
      if (_screen_text.length() - _screen_text_index < LCD_LEN_TXT) {
        _screen_text_index = 0;
        _screen_text_index_zero = 0;
      }

      screen_text_write();
    }
  }

  if(_screen_info.length() > LCD_LEN_INFO) {
    _screen_info_index_zero++;
    if (_screen_info_index_zero > 2){
      _screen_info_index++;
      if (_screen_info.length() - _screen_info_index < LCD_LEN_INFO) {
        _screen_info_index = 0;
        _screen_info_index_zero = 0;
      }

      screen_info_write();
    }
  }
}

void screen_write(byte x, byte y, String msg){
    char aux[LCD_LEN_LINE + 1]; 
    int len = min_i(msg.length(), LCD_LEN_LINE);
    msg.toCharArray(aux, len + 1);
    screen_write_xy(x, y, aux, len);
    screen_lines_write();
}

void screen_text(String msg){
    _screen_text = msg;
    _screen_text_index = 0;
    _screen_text_index_zero = 0;
    screen_text_write();    
}

void screen_info(String msg){
    _screen_info = msg;
    _screen_info_index = 0;
    _screen_info_index_zero = 0;
    screen_info_write();    
}

void screen_resistances(byte resist){
    _screen_resist = resist;
    screen_resist_write();    
}

void screen_print_temp(int ctemp, int ptemp){
    char buff[10];

    if(ptemp != 0)
        sprintf(buff, "%3d/%3d%s", ctemp, ptemp, " C");
    else 
        sprintf(buff, "    %3d%s", ctemp, " C");

    buff[9] = 0;

    screen_info(buff);
}

void screen_current_temp(int temp){
    _screen_current_temp = temp;
    screen_info_write();    
}

void screen_prog_temp(int temp){
    _screen_prog_temp = temp;
    screen_info_write();    
}
