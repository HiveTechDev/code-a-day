//////////////////////////////////////////////////////////////
///// 		Move the coach cam --- Like a boss			//////
///// Author: 	Tyler Hall (tyler@hive.technology)		//////
///// 			www.hive.technology						//////
///// How to use? Just run 'node changeCam.js' 			//////
///// Be sure to have node installed 				  	//////
//////////////////////////////////////////////////////////////

// module to make http request
var spawnOfThatOneGuy = require("child_process").spawn;

// Valid locations to jump to
var locations = ['Home','Leadbetter', 'Campus Center', 'Physical Sciences', 'Humanities Building', 'Surf Conditions']
var count = 0;	// Start at "home"

// 2 seconds == change for another time
var delay = 3000;


// // Repeat this untill the break o dawn
while(true){
	sleep(delay, function() {
		setcamera(count);
	});
	if (count == locations.length-1){ count = 0}else{count++}
}

// Simple GET.... we ignore all data being returned back
// Since we dont need any data back (no error checking or anything) its not a big deal. If you'd want that data...
// you can save to the node temp file, read/parse back. (But why? In this case.... we're not getting anything back)
// Endedup doing this spawn because of async and i didnt want to use an external library for people to install.
// See https://github.com/driverdan/node-XMLHttpRequest/blob/master/lib/XMLHttpRequest.js
// Saw that guy did it... rolled with it
function setcamera(shmashiboooshwooshi){
	console.log("Location: ", locations[shmashiboooshwooshi]);
	var execute = 'var http = require("http");http.get("http://www.sbcc.edu/coachcam/move.php?preset=' + locations[shmashiboooshwooshi] + '", function(response){return true});'
	var syncronnnnneessss = spawnOfThatOneGuy(process.argv[0], ["-e", execute]);
};

// Again.. while is a blocking call... This isn't best practice (Ryan, i'm sure you'll comment. Teach me a better way)s
function sleep(time, callback) {
    var stop = new Date().getTime();
    while(new Date().getTime() < stop + time) {
        ;
    }
    callback();
}











