Arduino/Moteino MailboxNotifier, tuned for Uffa
----------------
By @uffal

###Overview:
Based on existing [mailbox notifier project](https://github.com/LowPowerLab/MailboxNotifier) code from LowPowerLab.com.


###Hardware:
* 2 x [Moteino USB - RFM69HW 915Mhz, with 5Mbit Flash + Side Headers](https://lowpowerlab.com/shop/moteinousb)
* [Magnetic contact switch (door sensor)](https://www.adafruit.com/products/375)


###Features:
This is the source code used to make a [MailboxNotifier](http://lowpowerlab.com/?p=519), which consists of a Moteino
based sensor that detects when your mail is delivered. It uses a Magnetic contact switch, feeding from a 9V battery.
The receiver is another Moteino that runs the receiver sketch, passing the info to... TBD.