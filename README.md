# Custom Segmented Display

This project is a customizable Segmented display, consisting of a PCB and a top 3d printed diffuser part.
It comes with 32 0603 LEDs arranged in 3 digits, 5-LED light bar and 4 custom indicators. For the top cover, it's mainly a 3d printed part, with tracing paper acting as a diffuser. I'm using double sided adhesive sheets to place the diffusing film on top of the 3d print. The top cover can be attached to the PCB with 4 Philipps head screws. (4 threaded inserts would have been added to the 3d printed part beforehand.

<img width="1482" height="726" alt="RENDER CAD 2" src="https://github.com/user-attachments/assets/dc2f262f-0ff8-4c1c-8655-454451748dbf" />

# Key features:
- **32 LEDs**
- **3 digits** (7 segment digit) including two dots
- 5-LED bar on the bottom left corner
- based on **2 AW9523** ICs: cheap and efficient
- **I²C** communication: up to 2 modules on the same I²C bus
- each LED is driven in **constant current**, with **256 levels of brightness**
- The top diffuser 3d printed part can be swapped with a custom made diffuser, so multiple segmented displays fonts can be achieved. Here is a link of an awesome video made by Pozy, exploring custom Segmented Display fonts: *Segmented Displays* link: https://www.youtube.com/watch?v=RTB5XhjbgZA&t=301s. I designed a top cover taking inspiration from the ***Seamless*** font (4:35)
- Pins accessibles via **Dupont Headers** or **FPC 6P**
- PCB size: 80mm by 25mm
  
# Pinout:

- ***GND***
- ***N.RST*** (negative Reset) Pull LOW to reset the two AW9523 ICs
- ***N.EN*** (negative LED enable) Pull LOW to enable VCC.LED: Only when the AW9523 are well initialized.
- ***SCL***
- ***SDA***
- ***VCC*** 5.0V or 3.3V: 3.3V only possible if the 0603 LEDs used have a forward voltage low enough (if powered with 3.3V, prefer using RED LEDs)

# Sofware

I made an Arduino code, which while not being the most optimized one, should be sufficient for testing...

# PCB design:

2 Layer PCB designed in EASYEDA (Pro edition)

# Schematic:

<img src="CUSTOM SEGMENTED DISPLAY Schematic.svg" alt="SCHEMATIC" width="2300"/>

# PCB Layout: 

<img src="PCB/PCB Routing PART4 1.png" alt="SCHEMATIC" width="2300"/>
<img src="PCB/PCB Routing PART4 2.png" alt="SCHEMATIC" width="2300"/>

# CAD (Top cover diffuser):

<img width="1482" height="726" alt="RENDER CAD 2" src="https://github.com/user-attachments/assets/dc2f262f-0ff8-4c1c-8655-454451748dbf" />
<img width="1463" height="692" alt="RENDER CAD 1" src="https://github.com/user-attachments/assets/688825b6-e411-4416-a10c-22e6186966e5" />

# Renders:
<img width="1274" height="627" alt="PCB Routing Part3 iso" src="https://github.com/user-attachments/assets/47f66358-05c6-4513-ae33-b5b73212d1b3" />
<img width="1432" height="731" alt="RENDER 1B" src="https://github.com/user-attachments/assets/06c9bb62-aed5-464a-91cf-44cd3666ffe3" />
<img width="1542" height="726" alt="RENDER 1" src="https://github.com/user-attachments/assets/31445e6a-66cc-4ffe-b2f6-c95ec316541c" />
<img width="1453" height="661" alt="RENDER 2" src="https://github.com/user-attachments/assets/daac1d51-633f-4745-aa84-cdc07ed9ab3e" />
<img width="1514" height="724" alt="RENDER 3" src="https://github.com/user-attachments/assets/0aa43e95-922e-4c94-9e4f-74862757806f" />
<img width="1555" height="738" alt="RENDER 4" src="https://github.com/user-attachments/assets/1eba6f20-6396-4edf-8d9a-badfce195616" />
<img width="1662" height="677" alt="RENDER 5" src="https://github.com/user-attachments/assets/15e8a08e-b99d-4fc5-90da-1ee161ced12f" />
<img width="1746" height="710" alt="RENDER 6" src="https://github.com/user-attachments/assets/7be30292-efe8-449f-9677-4faade7cd84c" />
<img width="1463" height="692" alt="RENDER CAD 1" src="https://github.com/user-attachments/assets/ef1e1c57-6ea7-4b4e-b6ff-71dd88d74f75" />
<img width="1482" height="726" alt="RENDER CAD 2" src="https://github.com/user-attachments/assets/43eb3741-b273-469a-88bd-b4a8b7b441d1" />
<img width="1367" height="778" alt="RENDER CAD 3" src="https://github.com/user-attachments/assets/adb4f84f-f4b9-45ad-a2fa-405f53d29afc" />
<img width="1208" height="655" alt="RENDER CAD 4" src="https://github.com/user-attachments/assets/63e87431-68f9-4a84-806e-ee255c50217d" />
<img width="1446" height="711" alt="RENDER CAD 5" src="https://github.com/user-attachments/assets/a8ad67f6-2596-4868-85e3-3edd119141dd" />
<img width="1036" height="767" alt="RENDER CAD 7" src="https://github.com/user-attachments/assets/80528892-1127-4dcf-8e2b-7c639555b992" />
<img width="1636" height="732" alt="RENDER CAD 6" src="https://github.com/user-attachments/assets/2a75fea4-b414-4d77-996d-88e5dd470325" />

# Building the display:

Here are the PCB soldered:

![IMG_20260120_084108248](https://github.com/user-attachments/assets/9b6b00d0-b99a-48e7-8b32-548f43b55ac0)
![IMG_20260118_152902002](https://github.com/user-attachments/assets/c0605228-e953-4574-84b3-06f53e66e431)

## Top diffuser:
The parts are 3d printed in a black filament, so that light cannot pass through, resulting in sharp segments.
The 4 tiles didn't came out perfect, the 3d printed walls almost fused together so the icons aren't really visible, maybe in a V2 I'll increase the groove size.
Other than that, the 3d printed top cover was looking really good, and after sanding down the two top and bottom surfaces, adding the 4 threaded inserts, and placing tracing paper on top with the help of double sided translucent adhesive, the top diffuser was ready to go. Here is the result:

![IMG_20260125_152223236](https://github.com/user-attachments/assets/afd3dea1-b8d6-4129-a48c-09cde3fd0810)

![IMG_20260125_152235029](https://github.com/user-attachments/assets/2b8821ce-6548-46fc-a919-ec263d6d5f9b)

![IMG_20260125_181209068](https://github.com/user-attachments/assets/15dc2e06-0248-4f83-9d8b-663ee5c99850)
![IMG_20260125_181136340](https://github.com/user-attachments/assets/13cd3241-4502-4c44-9f2a-c738ab59c2fb)
![IMG_20260125_181049986](https://github.com/user-attachments/assets/3388c732-90e4-491f-ad94-12f10cef883b)
![IMG_20260125_181048940](https://github.com/user-attachments/assets/dfafe378-8d4d-4b21-a290-7c7312dd2647)
![IMG_20260125_181024657](https://github.com/user-attachments/assets/c66e6a7c-e344-47a1-81b5-1a1a8ff88fbc)
![IMG_20260125_180919923](https://github.com/user-attachments/assets/ccd161fa-2dac-4d7f-a1e9-65f9b7302f46)





