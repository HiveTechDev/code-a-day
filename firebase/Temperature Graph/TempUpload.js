///////////////////////////////////////////////////////////////////////////////
/////// Temperature Upload 												///////
/////// Exploring Node JS - Uploads random temp (under 100) to firebase ///////
///////////////////////////////////////////////////////////////////////////////

// Get firebase dependency
var Firebase = require("firebase");

// Wait time interval to "push" up dats
var timeWait = 1000;


// Shows program start
console.log("**** Begin temp logging ****")

// Link to firebase database
var ref = new Firebase("https://opness.firebaseio.com/");
var tempFrontRoom = ref.child("devices").child("front room");

// Define function to push data to firebase
var upperLimit = 100
var lowerLimit = 80
var temper = lowerLimit
var adder = 1
var multiplier = 2
var degree = 0

var pushTemp = function(){
	// Was random temp at fist.... to crazy, chart looked bad because all
	// over the place
	//var temper = Math.floor(Math.random()*100);

	temper = temper + (adder * multiplier)
	if (temper >= upperLimit || temper <= lowerLimit){multiplier = multiplier * -1}

	if (degree >= 360){degree = 0}
	var degreeRad = degree * (180 / Math.PI)

	// NOTE: Local timestamp value
	console.log("Temp1: ", temper, " || Timestamp: ", Date.now());
	console.log("Temp2: ", (Math.cos(degreeRad) *3) + 90, " || Timestamp: ", Date.now(), "\n")
	degree ++;


	//Sends the "data" to firebase w/firebase's timestamp value
	tempFrontRoom.child("A942").push({"temp" : temper, time: Firebase.ServerValue.TIMESTAMP} );
	tempFrontRoom.child("B435").push({"temp" : (Math.cos(degreeRad) *5) + 90, time: Firebase.ServerValue.TIMESTAMP} );


}

// Repeat every specified time interval
setInterval(pushTemp, timeWait);