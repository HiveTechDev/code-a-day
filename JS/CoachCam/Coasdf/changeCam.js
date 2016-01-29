//////////////////////////////////////////////////////////////
///// Author: 	Tyler Hall (tyler@hive.technology)		//////
///// 			www.hive.technology						//////
///// How to use? Just run with 'node changeCam.js' 	//////
///// Be sure to install  xhr2 with 'npm install xhr2'  //////
//////////////////////////////////////////////////////////////


var sys = require('util');
var XMLHttpRequest = require("./xmlhttprequest.js").XMLHttpRequest;


var locations = ['Home','Leadbetter', 'Campus Center', 'Physical Sciences', 'Humanities Building', 'Surf Conditions']

var delay=1000; //1 seconds
var counter = 0; // start at 'Home'

setTimeout(function(){
	setcamera();
}, delay);

setcamera(locations[0]);
setcamera(locations[1]);
setcamera(locations[2]);
setcamera(locations[3]);
setcamera(locations[4]);


function setcamera(Home){
	var xmlhttp = new XMLHttpRequest();
	console.log("Moving to location: ", Home)
	xmlhttp.open("GET","http://www.sbcc.edu/coachcam/move.php?preset=" + Home, true);
	xmlhttp.send();
	if(counter == locations.length) {counter = 0};
}