# OrigamiSat1
## Summary
OrigamiSat1 is first nano satellite of [ORIGAMI PROJECT](http://www.origami.titech.ac.jp/)  
this is repository for management source code of OrigamiSat1  
this contains 5 project.

## Project Map
### OBC
role : Control & Data Handling   
Hardware : Nanomind ([GOM Space](https://gomspace.com/home.aspx))  
Language : C  
Compiler : Waf  
Editor : Eclipse  
Encoding : UTF-8 

### CIB_Tx
role : send downlink telemetry from EEPROM in UHF  
Hardware : PIC16F887 ([Microchip](http://www.microchip.com/ja))  
Datasheet : [PIC16F882/883/884/886/887 Data Sheet](http://ww1.microchip.com/downloads/en/DeviceDoc/41291D.pdf)  
Language : C  
Compiler : XC8  
Editor : MPLAB X IDE   
Encoding : Shift-JIS  

### CIB_Rx
role : receive uplink command in VHF & save to EEPROM  
Hardware : PIC16F886 ([Microchip](http://www.microchip.com/ja))     
Datasheet : [PIC16F882/883/884/886/887 Data Sheet](http://ww1.microchip.com/downloads/en/DeviceDoc/41291D.pdf)  
Language : C  
Compiler : XC8  
Editor : MPLAB X IDE   
Encoding : Shift-JIS  

### MDC
role : sampling inertia when membrain expansion & measure of membrane data     
Hardware : PIC18F25K80 ([Microchip](http://www.microchip.com/ja))  
Datasheet : [PIC18F66K80 Family Data Sheet](http://akizukidenshi.com/download/ds/microchip/pic18f66k80_family.pdf)  
Language : C  
Compiler : XC8  
Editor : MPLAB X IDE   
Encoding : Shift-JIS  

### 5R8G_Tx
role : downlink Photo & Movie in 5.8GHz  
Hardware : PIC16F886 ([Microchip](http://www.microchip.com/ja))  
Datasheet : [PIC16F882/883/884/886/887 Data Sheet](http://ww1.microchip.com/downloads/en/DeviceDoc/41291D.pdf)  
Language : C  
Compiler : XC8  
Editor : MPLAB X IDE   
Encoding : Shift-JIS  

