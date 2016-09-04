# TSOC_GROVEY_I2CHUB Theory of Operation

***TSOC_GROVEY_I2CHUB** is a self contained, Embedded Wi-Fi Module, with integated Li-Po battery control and charging.

**TSOC_GROVEY_I2CHUB** includes an ESP8266 Wi-Fi module, 
along with an [PCA8575 I/O Expander](http://www.nxp.com/documents/data_sheet/PCA8575.pdf) 
to provide an additional 16 Input/Output pins for the thingSoC Standard Socket,
and a Color RGB LED for USER status, with additonal, individual LEDS for Battery Charger Status and USB Status.

[![thingSoC TSOC_GROVEY_I2CHUB](http://patternagents.github.io/img/projects/TSOC_GROVEY_I2CHUB/TSOC_GROVEY_I2CHUB_top.png)  
*TSOC_GROVEY_I2CHUB*](https://github.com/PatternAgents/TSOC_GROVEY_I2CHUB/)

* [Supported by the Arduino IDE](https://www.arduino.cc/) 
* [thingSoC Compliant Module](http://www.thingsoc.com)
* [Mikrobus Compatible Module](http://www.mikroe.com/mikrobus/) 

---------------------------------------

## Theory of Operation <a name="theory_index"/>

The **TSOC_GROVEY_I2CHUB** supports a single "thingSoC" socket with 3.3 Volt Level signaling.

### Page A : USB Connector, Battery Connector and Power Supply<a name="PAGEA"/>


![Schematic Page A](https://raw.githubusercontent.com/PatternAgents/TSOC_GROVEY_I2CHUB/master/TSOC_GROVEY_I2CHUB/docs/images/sch_page_1.png "Schematic Page A")

Limitations: 

   
   
### Page B : USB to UART Bridge Controller <a name="PAGEB"/>


![Schematic Page B](https://raw.githubusercontent.com/PatternAgents/TSOC_GROVEY_I2CHUB/master/TSOC_GROVEY_I2CHUB/docs/images/sch_page_2.png "Schematic Page B")

### Page C <a name="PAGEC"/>

![Schematic Page C](https://raw.githubusercontent.com/PatternAgents/TSOC_GROVEY_I2CHUB/master/TSOC_GROVEY_I2CHUB/docs/images/sch_page_3.png "Schematic Page C")

### Page D <a name="PAGED"/>

![Schematic Page D](https://raw.githubusercontent.com/PatternAgents/TSOC_GROVEY_I2CHUB/master/TSOC_GROVEY_I2CHUB/docs/images/sch_page_4.png "Schematic Page D")

---------------------------------------

## Documentation Index <a name="documentation_index"/>

[TSOC_GROVEY_I2CHUB Quick Start Guide](https://github.com/PatternAgents/TSOC_GROVEY_I2CHUB/blob/master/TSOC_GROVEY_I2CHUB/docs/qsg.md)

[TSOC_GROVEY_I2CHUB User Guide](https://github.com/PatternAgents/TSOC_GROVEY_I2CHUB/blob/master/TSOC_GROVEY_I2CHUB/docs/ug.md)

[TSOC_GROVEY_I2CHUB Theory of Operation](https://github.com/PatternAgents/TSOC_GROVEY_I2CHUB/blob/master/TSOC_GROVEY_I2CHUB/docs/theory.md)

[thingSoC Organization Website](http://thingSoC.github.io)

[thingSoC FAQ - Frequently Asked Questions](http://thingsoc.github.io/support/faq.html)

[ESP8266 Community](https://github.com/esp8266/Arduino)

---------------------------------------

[![Image](http://thingsoc.github.io/img/projects/thingSoC/thingSoC_thumb.png?raw=true)  
*thingSoC*](http://thingsoc.github.io) 
 
