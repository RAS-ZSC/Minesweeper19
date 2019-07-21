#include <JoyControl.h>
JoyControl::JoyControl(HBridge& hbridge) : hbridge(hbridge) {

}

void JoyControl::handle(char code[]) {
   char signal[3][3];
   char delim[] = ",";
   char *token = strtok(code,delim);
   int j=0;
   while (token){
      int i=0;
      while (token[i]!='\0'){
          signal[j][i]=token[i];
          i++;
      }
      signal[j][++i]='\0';
      j++;
      token = strtok(NULL,delim);
    }
   
   /*TODO handle analog values*/
   /*if (code == 'Z')
      hbridge.move(x, y);*/
        
   if (signal[0][0] == 'L') 
      hbridge.left() ;

   else if (signal[0][0] == 'N') 
      hbridge.forward();

   else if (signal[0][0] == 'M')
      hbridge.right();

   else if (signal[0][0] == 'A') 
      hbridge.backward();
	
   else if (signal[0][0] == 'Q')
      hbridge.stop();

   else if(signal[0][0] == 'Z'){
      //TODO convert L,R into ints and pass them to hbridge
      int l = atoi(signal[1]);
      int r = atoi(signal[2]);
      hbridge.move(l, r);
      }
}
