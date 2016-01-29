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
// Objective: Sends a warning text at 12:00, 6:00, 9:00 if no code today		//
// Dependencies: cheerio, request												//																		//
//////////////////////////////////////////////////////////////////////////////////

// Github URL
var gitHubUrl ='https://github.com/users/koulwa/contributions'
var request = require("request");
var cheerio = require("cheerio");
var Firebase = require("firebase");
var nodemailer = require('nodemailer');

// Update db
var dashboard = new Firebase("dbURL");

// Email/Text notifier
var transporter = nodemailer.createTransport('smtps://user%40gmail.com:pw@smtp.gmail.com');

var setMailOptions = function(txt) {
	return {
	    from: 'Git Alarm <alarm@hive.technology>', // sender address
	    to: 'phone@phoneprovider.com,  email@email.com', // list of receivers
	    subject: 'Git Alarm', // Subject line
	    text: txt, // plaintext body
	};
};

var sendMail = function(mailOptions) {
	transporter.sendMail(mailOptions, function(error, info){
	    if(error){
		    dashboard.child("error").push({
						  "script": "gitWarning.js",
						  "timeStamp": Firebase.ServerValue.TIMESTAMP,
						  "error": error
						});
	        return console.log(error);
	    }
	    console.log('Message sent!');
	});	
};


request({
  uri: gitHubUrl,
}, function(error, response, body) {

	if(error){
		    dashboard.child("error").push({
						  "script": "gitWarning.js",
						  "timeStamp": Firebase.ServerValue.TIMESTAMP,
						  "error": error
						});
		console.log("Error: ", error);
	} else {
		var $ = cheerio.load(body);
		var year = [];
		var today = new Date();

		$('rect').each(function(i, elem) {
			var eachDateString = elem.attribs['data-date']
			var eachDateSplit = eachDateString.split("-");
			var eachDate = new Date(eachDateSplit[0], eachDateSplit[1] - 1, eachDateSplit[2]);

			if(today.toDateString() === eachDate.toDateString()){
				if(elem.attribs['data-count'] == 0){
					var msg = eachDateSplit[2] +'-'+ eachDateSplit[1] +'-'+ eachDateSplit[0] + ": Time to get to work! Get some code done!"
					sendMail(setMailOptions(msg));
					// Update dashboard
					dashboard.child(eachDate.getTime()).update({
					  "gitDone": false
					});
				} else {
					// Update dashboard
					dashboard.child(eachDate.getTime()).update({
					  "gitDone": true
					});
				}
			};
		});
 	};
});


// end the party