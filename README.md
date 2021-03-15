# <p align="center">Indoor-Object-Tracking-using-UWB </p>
## Introduction

<p align= "justify" > The objective of this project was to create an accurate general-purpose indoor localization system. Ultra-wideband(UWB) a wireless radio technology was chosen to achieve this. UWB offers high accuracy of localization, low latency, minimal interference and noise, and large bandwidth. DW1000 is an RF TX/RX IC manufactured by Decawave for UWB applications. This project uses the DW1000 IC in the form factor of module DWM1000. The hardware for the project was designed around this module with a few preferable features like access to the internet using an ESP8266-12E and programming support using the Arduino IDE. The system uses the Two-Way Ranging(TWR) technique for localization. The position computing is done by trilateration on the tag which is coupled with the object being tracked. A localization accuracy of about 12cm was achieved in a room of size 3x3m.</p>

## System Design

<p align="center">
  <img width="580" height="350" src="https://bn1301files.storage.live.com/y4mACFo4Qf8LCkyHl3mySvm_n0q6XDeH7vv6lPnnNykzJFxA04JsfzAioNCAqXaTc7JRgvMPfwYyWmxGJs0OoGd-kC4ZQSiLUVnqKldu9HBdwvddzOO3hC1dSdNuuJrfWmDwHoBK-LBswAhwjgYfkq5lwcujGLHzE2dtPFRzp9QRiUTTzSLLT_KG2dnhEdtybyT?width=660&height=425&cropmode=none">
</p>
<p align= "justify" > In order to track an object, a device addressed "Tag" is attached to it. Devices callled "Anchors" are placed around the indoor environment to provide a spatial reference for the tag. Before the system starts tracking, the anchors should be fixed at different locations in the room and their coordinates are programmed in the tag. As shown in the above block diagram, the anchors are placed at (x1,y1),(x2,y2) and (x3,y3) respectively. Calibration of the DWM1000 is then done to accomodate for the slight difference in the radiation pattern of each antenna as mentioned in the datasheet of the module.</p>

## Working

<p align= "justify" > Once the setup is ready, the tag performs Two-Way Ranging to determine its distance from each anchor. The three distances are then substituted into the trilateration formula to determine the exact position. This data may then be shared with an anchor with a Wi-Fi module called the master anchor. The master anchor can then update the data anywhere over the internet. In this project, a dynamic webpage hosted on the ESP8266 displays the coordinates of the object. This entire cycle is repeated to track the position of the tag(in turn the object) in real time. A flow chart of the process is shown below:</p>
<p align="center"><img src="https://bn1301files.storage.live.com/y4mkzdmsu1vIRshEtksLIzr8k7BsEPowD9S-C9dvZKQr63lDwPMPNK2WSq80fwYsNF7hYItmkjVeZ4xntY5IYlk4IscYCvAZYoPUbrCpb7B4wp27PevtakhWdmKKNiDE6IQD6U9iUMKUb80BIJqPHVkvhvjReWIjzWWiHE7QOne9CLCMZLhfxRcUWeoTKO3X46G?width=873&height=577&cropmode=none" width="572" height="380" /></p>

## Hardware
### PCB: Version 1

<p align= "justify" > As stated in the introduction, the hardware was designed around the DWM1000 module. Since the module operates between 2.8-3.6v, the system voltage was fixed to be 3v3. This also provided the convinience of using a handy single cell 750mah lipo battery. ATmega328P was chosen as the microcontroller due to my familiarity with it. An external 8MHz crystal oscillator was connected to ensure the microcontroller is clocked at the fastest possible speed at 3v3. The minimal circuit required for ESP8266 was designed and interfaced with the ATmega328P over the I2C bus while the DWM1000 uses SPI. IC MIC5219 a low cost 500mA LDO was used to regulate the supply voltage to 3v3 from the battery. Additionally, reverse polarity protection using a diode is added. Switches were provided to control power and reset of ATmega328P and ESP8266, while LED's were provided to indicate the status of power and DWM1000.</p>

<p align="center"><img src="https://bn1301files.storage.live.com/y4m8y42SlVM56QD3faSpc-4crdSRqCrOUDG4_lckvUjKLgnuBPMVQZMs0kDkTP4IN-ot2-2nidGflojElBNsFw1WFW-pr5GWJYr0QHtenxrttRZGPJQWGSDb1QK3LzyBnsxLx4Q3CjzPztN1R9offze9Xvk54DNBfbkmYGVsULJqStqNMzYXIz4kNM0-QHgf508?width=660&height=495&cropmode=none" width="660" height="495" /></p>

<p align= "justify" > The above PCB was designed in Autodesk Eagle. The design files can be found in the folder Master_V1 under the Hardware section of this repository. </p>

### PCB: Version 2

<p align= "justify" > The major feature of version 2 addition of programming over the USB. In the previous version, the bootloader was initally burned using an ATMEL ICE debugger and the program written over UART using an Arduino Uno performing USB-TTL conversion. However, I found it very inconvienient to interconnect the Uno everytime, reset it during programming and reading the data serially. Hence, the popular USB-TTL converter CH340G was added to support quicker programming and access to serial monitor. Pads were placed on the bottom to burn the bootloader using pogo pins. I also reduced the size of the crystals and switches to achieve the smallest possible form factor. </p>

<p align="center"><img src="https://bn1301files.storage.live.com/y4mreqN2rJIjqIycZhfIGRfPIveyt1yihFRq3oXZjueMXS0AE-Hk6q9g1WEuY4scxY1o0I5ybrtTmkT9MvdRJHoRbJltRM-yyTNHJxB7_ibkl32kTTLhC64Nr-SfEBg6rK5M4RRr6Hz9rSA6H2TNdsnd7gRlrRO6RXpwCz9qrrYkZ6Yp6caD_yLoSSLqwUVsqMI?width=480&height=660&cropmode=none" width="288" height="396" />
<img src="https://bn1301files.storage.live.com/y4mTaHgXcMwM4idhy8du0LRxomOy0CJtUXuKujyUnYUoRS7dZ2E7TzN19-4axzyBv3KCai3dDHqJ3GY3TBkVXpgmS3MMvUkNXv8Ho_41v9_-05QBMmLedWPzsPopvpVD66joZD8PTb4RTWC2uSeIDrH9TB6K_prCgdG3UPqHEMexrBwSck41B3yTZ3WP16h8nUf?width=466&height=660&cropmode=none" width="280" height="396" />
<img src="https://bn1301files.storage.live.com/y4m5v_Ik6nCNB2Gs1FI-JeO70w22-JsAxX_MSUCk796J1jFv9puEH40ZnYEsofKKcywewjSHwlxX0Cr9EkmeO6WJThJ_EcihWL9qHKHKIO8KJi730SuGwIiLte9kf_fMDHh4jA4PAOLBj6TJbVmC5bOlF5Kdt95Br19nA1gM0T_XCd9PH-SKaXr35i-nOfw5nFy?width=660&height=582&cropmode=none" width="396" height="350" /></p>

<p align= "justify" > The design files can be found under the Tag_V2 and Anchor_V2 folders respectively. The anchor design contains an additional ESP8266 placed in the bottom. </p>

### Enclosure

<p align="center"><img src="https://bn1301files.storage.live.com/y4mXaiqNfTPrzJZCW3n-j3w9RZTCWGclgQKi2E6bs49YAvc2BhcUmuL9DHDqY_pnehp4Qnu68GxKcWlz0EGUZrQgR3lS-WjH4PQGmZwLtyGn7qmgeDQXs2furDOcxoZV8QPyRqt9-cqAYevh8PeAge80r-qefo1bWMeYoWlIQoWmPMejF5Xkr2wy7CeNWFG_ynL?width=256&height=144&cropmode=none" width="396" height="225" />
<img src="https://bn1301files.storage.live.com/y4mQTe4pf7Ty-wr2i01G1SgZUVNPhnlAUSrptMi5hayvdFC47v0R4g3GmVEdwPyHZOCH0aSS_xD5uVLvP_jAtP3g3Yn5i_rpe0p8L9II-9NMmkrPcq0pPuPXBU5B0mwiNV3rXHbSG8qqEUN8mmNkf_nCv4ME528FXktNEQckvwvwKrLfnop_Q7W8yw7PBPEmu55?width=256&height=144&cropmode=none" width="396" height="255" />
<img src="https://bn1301files.storage.live.com/y4mKoTAoKRMvcLewgw1QbcPN8ybqymxi4Y2bi4RU8QIIakEKz04iaz1WyctDZcn6o59t2adbLEh6M2AZVmFTfY53GI3LSvCF2Eq6HIGGTc5b6ysRKnCh9iuCUj2D3diOcw8M4sRip1R3b-1Pzsim4utyrLcOSc726FT9tDPcHjyucv9MRd3Zuar5rUTuKe1bgFf?width=256&height=144&cropmode=none" width="396" height="255" /></p>

<p align= "justify" > An enclosure was designed to house the device in Autodesk Fusion 360. The base was intended to be 3d printed on a PLA base which the lid will be a transparent laser cut acrylic. The PCB will be screwed on to the enclosure. The design file can be found under the hardware section</p>

## Software

<p align= "justify" > The firmware for the project was completely written in Arduino IDE with <a href="https://github.com/thotro/arduino-dw1000" target="_blank" rel="noopener noreferrer">arduino-dw1000 library</a> developed by Thomas Trojer. The programs could be found under the software section of this repository. </p>

## Working

<p align= "justify" > After uploading the program, the tag should be set in calibration mode to perform TWR and correct the calibration constant. After this, open a browser and navigate to the IP addess mentioned in the serial monitor of the master-anchor. The position of the tag will be updated every 10s in real-time with an accuracy < 30cm.</p>

<p align="center"><img src="https://bn1301files.storage.live.com/y4m8sz-SMFQ0lQiQuwE97hnNfLlVVMNMKa6mr0pmFl6-ONzQiAkjwwsHReiSBMPh96H3Arf2rZ29A2bcZI6jIu0JkJ_w8_z-p0r8P0r7eW9d9TNiTJMPBPAZLBf-UB8MXps0rTKNlF1mvJdFy8zmf1hRJHMHV3UQxT7dkhYyj9RCRJFemfO4vHxpM0zwLHURDin?width=462&height=660&cropmode=none" width="462" height="660" /></p>

## Outcome

<p align= "justify" >This capstone project was undertaken as part of my UG curriculum. Version 2 of the hardware did not progress beyond the design stage due to my graduation in May 2020, during the middle of the pandemic here. Fortunately, I was able to demonstate the working of the system using the first version of the hardware to earn my degree. However, as a hobby project, I am working on a TDoA implementation of the system to be deployed at Beeclust MRSL for tracking robots. It will be replacement for the april tags currently used in the projects. There are certain aspects of the system that could still be improved. Feel free to contact me if you would like to improve this project.</p>
