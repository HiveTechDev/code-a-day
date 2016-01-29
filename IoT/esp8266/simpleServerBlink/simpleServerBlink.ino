//////////////////////////////////////////////////////////////////////////////////
// Tyler Hall - www.Hive.technology												//
// Code A Day Challenge															//
//																				//
// This software is not intended for redistribution, as such it is not fully	//
// documented or gaurenteed.													//
//																				//
// This is pretty much not even important enough to put a licence on.			//
// Yeah, I went there. Contact me with questions.								//
//																				//
//////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////
// Objective: 	First time experimenting with esp8266							//
// 				Two LEDS on D0, and D3 with D1, and D4 acting as ground 		//
//				-- Messing around to get a feel for how this works				//
//////////////////////////////////////////////////////////////////////////////////

#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>

const char *ssid = "AP";
const char *password = "PW";

ESP8266WebServer server ( 80 );

const int led1 = D0;
const int led1g = D1;

const int led2 = D3;
const int led2g = D4;

int ledStatus = 0;


void ledOn(){

	digitalWrite ( led1, 1 );
	digitalWrite ( led2, 1 );

	char temp[400];
	int sec = millis() / 1000;
	int min = sec / 60;
	int hr = min / 60;

	snprintf ( temp, 400,
		"<html>\
		  <head>\
		    <title>Hive LED</title>\
		    <style>\
		      body { background-color: #cccccc; font-family: Arial, Helvetica, Sans-Serif; Color: #ffa200; }\
		    </style>\
		  </head>\
		  <body>\
		    <h1>Hive LED</h1>\
		    <button><a href=\"/on\">LED on</a></button>\
		    <button><a href=\"/off\">LED off</a></button>\
		    <p>Uptime: %02d:%02d:%02d</p>\
		  </body>\
		</html>",

		hr, min % 60, sec % 60
	);

	server.send ( 200, "text/html", temp );
	digitalWrite ( led1, 0 );
}

void ledOff(){
	digitalWrite ( led1, 1 );
	digitalWrite ( led2, 0 );

	char temp[400];
	int sec = millis() / 1000;
	int min = sec / 60;
	int hr = min / 60;

	snprintf ( temp, 400,
		"<html>\
		  <head>\
		    <title>Hive LED</title>\
		    <style>\
		      body { background-color: #cccccc; font-family: Arial, Helvetica, Sans-Serif; Color: #ffa200; }\
		    </style>\
		  </head>\
		  <body>\
		    <h1>Hive LED</h1>\
		    <button><a href=\"/on\">LED on</a></button>\
		    <button><a href=\"/off\">LED off</a></button>\
		    <p>Uptime: %02d:%02d:%02d</p>\
		  </body>\
		</html>",

		hr, min % 60, sec % 60
	);
	server.send ( 200, "text/html", temp );
	digitalWrite ( led1, 0 );
}




void handleNotFound() {
	digitalWrite ( led1, 1 );
	String message = "Invalid URL\n\n";
	message += "URI: ";
	message += server.uri();
	message += "\nMethod: ";
	message += ( server.method() == HTTP_GET ) ? "GET" : "POST";
	message += "\nArguments: ";
	message += server.args();
	message += "\n";

	for ( uint8_t i = 0; i < server.args(); i++ ) {
		message += " " + server.argName ( i ) + ": " + server.arg ( i ) + "\n";
	}

	server.send ( 404, "text/plain", message );
	digitalWrite ( led1, 0 );
}

void setup ( void ) {

	// Setup LED output
	pinMode ( led1, OUTPUT );
	pinMode ( led1g, OUTPUT );
	pinMode ( led2, OUTPUT );
	pinMode ( led2g, OUTPUT );
	digitalWrite ( led1, 0 );
	digitalWrite ( led1g, 0 );
	digitalWrite ( led2, 0 );
	digitalWrite ( led2g, 0 );

	// Set up serial and Wifi
	Serial.begin ( 115200 );
	WiFi.begin ( ssid, password );
	Serial.println ( "" );

	// Wait for connection
	while ( WiFi.status() != WL_CONNECTED ) {
		delay ( 500 );
		Serial.print ( "." );
	}

	Serial.println ( "" );
	Serial.print ( "Connected to " );
	Serial.println ( ssid );
	Serial.print ( "IP address: " );
	Serial.println ( WiFi.localIP() );

	// Gives us a http://hiveTech.local address
	if ( MDNS.begin ( "hiveTech" ) ) {
		Serial.println ( "MDNS responder started" );
	}

	server.on ( "/on", ledOn );
	server.on ( "/off", ledOff );
	server.onNotFound ( handleNotFound );
	server.begin();
	Serial.println ( "HTTP server started" );
}

void loop ( void ) {
	server.handleClient();
}

