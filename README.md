<!--
MARKDOWN CHEATSHEAT:	https://github.com/adam-p/markdown-here/wiki/Markdown-Cheatsheet
MARKDOWN RENDERER:		http://johnmacfarlane.net/babelmark2/
-->

Arduino/Moteino MailboxNotifier, tuned for Uffa
----------------
By @uffal

###Overview:
Based on existing [mailbox notifier project](https://github.com/LowPowerLab/MailboxNotifier) code from LowPowerLab.com.


###Hardware:
* 2 x Moteino USB [Available at lowpowerlab.com](https://lowpowerlab.com/shop/moteinousb)
	* RFM69HW 915Mhz
	* 4Mbit Flash Addon
	* Side Header Addon



* Magnetic contact switch (door sensor) [Available at adafruit.com] (https://www.adafruit.com/products/375)
	* Normally open reed switch
	* ABS enclosure
	* Rated current: 100 mA max
	* Rated voltage: 200 VDC max
	* Distance: 15mm max



###Features:
This is the source code used to make a [MailboxNotifier](http://lowpowerlab.com/?p=519), which consists of a Moteino
based sensor that detects when your mail is delivered. It uses a Magnetic contact switch, feeding from a 9V battery.
The receiver is another Moteino that runs the receiver sketch, passing the info to... TBD.

### Also Available on CodeBender
* [UMoteinoHouse](https://codebender.cc/sketch:329450)
* [UMoteinoMailbox](https://codebender.cc/sketch:329447)