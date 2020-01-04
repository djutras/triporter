// This #include statement was automatically added by the Particle IDE.


 
/*
 * Project MyProject
 * Description:
 * Author:
 * Date:
 */
     int LPWM=D1;
     int LEN=D2;
     int RPWM=D3;
     int REN=D4;
     int timeA=0;
     int timeR=0;
     int timeB=100;
     int i_command=0;
     
     String s_negatif="1";
     String s_front = "N/A";
     String s_stop = "0";
     
     uint32_t lastReset = 0;
     long l_beginCounter=0;
     long l_EndCounter=0;
     bool s_run = false;
     bool b_timeA = false;
    bool b_timeR = false;
    
    Servo serv;
    int pos = 0;

// setup() runs once, when the device is first turned on.
    void setup()
        {
        lastReset = millis();
          // Put initialization like pinMode and begin functions here.
        pinMode(LPWM,OUTPUT);
        pinMode(RPWM,OUTPUT);
        pinMode(LEN,OUTPUT);
        pinMode(REN,OUTPUT);
        
        digitalWrite(LEN,HIGH);
        digitalWrite(REN,HIGH);
        
        Particle.function("wakeup",ledToggle9);
            //  Particle.function("PosEncoder9",PosEncoder9);
        serv.attach(A4);
        Particle.function("setpos", setPos);
        Particle.variable("getpos", &pos, INT);
        }
        
    int setPos(String pstn) 
        {
          //  pos = pstn.toInt();
         // serv.setTrim(30);
            serv.write(pos);
            delay(15);   
            return pos;
        }

    int ledToggle9(String command) 
    {
        
        Particle.variable("command",command);  
        Particle.publish("command", command,PUBLIC);  
         
         i_command = command.toInt();
             
                if (command == "")
                    {
                         timeA=0;
                         timeR=0;
                       s_front = "Stop";
                               
                    }
                else if (i_command==0)
                    {
                       
                        timeA=0;
                        timeR=0;
                        s_front = "Stopn"; 
                    }
                    
                else if (i_command>0)
                    {
                        b_timeA=true;
                        timeA=i_command;
                        timeR=0;
                        s_front = "Frontn"; 
                    }
                    
                else if (i_command<0)
                    {
                        b_timeR=true;
                        timeA=0;
                        timeR=i_command * -1;
                        s_front = "Backn"; 
                    }
                    
            l_beginCounter= millis();          
            l_EndCounter = l_beginCounter + timeA + timeR;
            
            return i_command;
                   
          //  delay(500);   
            
           // String s_state = s_front + " timeA " + timeA + " timeR " + timeR + " l_beginCounter " + l_beginCounter + " l_EndCounter " + l_EndCounter ;
            
         //   Particle.variable("Front",s_state);  
         //   Particle.publish("Front", s_state,PUBLIC);  

          //i_leadAdv = i_intAdavance;
  }
  

  

// loop() runs over and over again, as quickly as it can execute.
    void loop()
    {
        
        l_beginCounter= millis();    
     
        if(l_beginCounter>l_EndCounter)
        {
            timeA=0;
            timeR=0;
            s_run = false;
            b_timeA=false;
            b_timeR=false;
        }
        else if (l_EndCounter>l_beginCounter)
        {
            s_run = true;
        }
        
        if (s_run)
        { 
            if(b_timeA)
                {
                    digitalWrite(RPWM,HIGH);
                    digitalWrite(LPWM,LOW);
                }
   
             if(b_timeR)
                {
                    digitalWrite(RPWM,LOW);
                    digitalWrite(LPWM,HIGH);
                }
        }
        
        else
        
        {
            digitalWrite(RPWM,LOW);
            digitalWrite(LPWM,LOW);
        }

        
            delay(500); 
            
            pos = pos + 1;
           
           if (pos>50) {pos=1;}
            
             serv.write(pos); 
            
            String s_state = s_front + " pos " + pos +  " s_run " + s_run + " timeA " + timeA + " timeR " + timeR + " LOOP b_timeA " + b_timeA + " b_timeR " + b_timeR + " l_beginCounter " + l_beginCounter + " l_EndCounter " + l_EndCounter ;
            
            Particle.variable("Front",s_state);  
            Particle.publish("Front", s_state,PUBLIC); 
            
       
    

    }