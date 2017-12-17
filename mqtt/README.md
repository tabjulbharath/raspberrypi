## Using MQTT with Raspberry Pi

MQTT is a message communication protocol that is designed to be lightweight and
to work well with small micro-controllers to send data back and forth. There are
two parts to MQTT, the broker which is a kind of message server, and the client,
which is the application that sends and receives messages.

MQTT uses a publish and subscribe model. The broker is a central point which clients
can contact in order to subscribe to a data source. Clients send messages to the broker
which then repeats the message to all other clients which have subscribed to that
message channel.

MQTT is one of several types of publish/subscribe messaging protocols. Some messaging
protocols are heavier than MQTT offering more services. The following article provides
an overview of three of the most commonly used protocols: AMQP, MQTT, and STOMP.

Choosing your messaging protocoll: AMQP, MQTT, or STOMP
https://blogs.vmware.com/vfabric/2013/02/choosing-your-messaging-protocol-amqp-mqtt-or-stomp.html

See as well the following:

All About Messaging Protocols: What Are the Differences? http://www.eejournal.com/article/20150420-protocols/

IoT Standards and Protocols https://www.postscapes.com/internet-of-things-protocols/

MQTT and CoAP, IoT Protocols https://www.eclipse.org/community/eclipse_newsletter/2014/february/article2.php

### Available packages for MQTT

There are a number of different open source MQTT product offerings available. Mosquitto seems to be most
commonly used. It appears that most recently Mosquitto is a standard Raspbian install and is available
by using apt-get as in:

sudo apt-get install mosquitto mosquitto-clients

To get the development packages for Mosquitto C development (header and library files) use:

sudo apt-get install libmosquitto-dev

To get the development packages for Mosquitto plug-in development use:

sudo apt-get install mosquitto-dev

Setting up a local MQTT broker on the Raspberry Pi https://arduinodiy.wordpress.com/2017/02/04/setting-up-a-local-mqtt-broker-on-the-raspberry-pi/

Raspberry Pi as a MQTT server https://lowvoltage.github.io/2017/07/13/Raspberry-Pi-MQTT-Server

### JSON text messages

As MQTT sends and receives text, using JSON with MQTT seems a natural fit.

The FastJSON development library can be installed using apt-get. See https://github.com/rsyslog/libfastjson

sudo apt-get install libfastjson-dev

There is also GLIB JSON https://wiki.gnome.org/Projects/JsonGlib