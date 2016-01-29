# Pi should aready have the basics of python setup... since its the offical language and all. Here are some packages that need
# to be installed before this will work. Just run these in a terminal before you run the script
###################################
# sudo pip install feedparser
# sudo pip install beautifulsoup
# sudo pip install pyserial
# sudo pip install requests==1.1.0
# sudo pip install python-firebase
###################################

import time
import serial
import json
import requests
#import urllib2
from BeautifulSoup import BeautifulSoup
import feedparser
from firebase import firebase

interval = 1

firebase = firebase.FirebaseApplication('https://cesign.firebaseio.com/', None)


#ser = serial.Serial('/dev/ttyACM0')
#ser.baudrate = 9600
 
#facebooklikes
def facebook():
	# This access token MIGHT change. You have to go to graphs.facebook.com and generate a new token for the CE page if you
	# run into issues later. It should return an object that looks like this
	# 	{
   	#		"likes": 58,
   	#		"id": "1402950449978112"
	#	}

	# so it did change... had to go with the api from facebook vs the graph.facebook
	# graph.facebook requires to get an authentication key that you can programically get... it seemed like more work than it was wort
	# for just getting the like count.

	getUrl = requests.get('https://api.facebook.com/method/fql.query?query=select%20like_count%20from%20link_stat%20where%20url=%27https://www.facebook.com/ceclubsbcc%27&format=json')
	facebookJson = json.loads(getUrl.text)
	facebookLikes = int(facebookJson[0]['like_count'])
	# print facebookLikes
	return facebookLikes

##### This doesnt work with wordpres after wordpress 3.0....
# stats are now handled by jetpack
# Jetpack has an API thing, someone can look into it

#pageCount
# def checkWeb():
# 	page = urllib2.urlopen("http://stats.wordpress.com/csv.php?api_key=2f9d4bf59323&amp;blog_uri=computerengineering.club&amp;days=-1&amp;summarize")
# 	soup = BeautifulSoup(page)
# 	count = str(soup)
# 	count = count.replace("views","")
# 	count = count.replace('"',"")
# 	count = count.replace('\n',"")
# 	countNum = int(count)	
# 	#print countNum
# 	return countNum
 
#new user check
def userAdd():
	gmailURL = "https://cesbccclubdaemon:cedaemon@mail.google.com/gmail/feed/atom"
	#print gmailURL
	emailParsed = feedparser.parse(gmailURL)
	#print emailParsed
	numEmail = int(feedparser.parse(gmailURL)["feed"]["fullcount"])
	#print numEmail
	#print "\nNow Email\n"
	numFound = 0
	for x in range(0, numEmail-1):
		title = str(emailParsed['entries'][x]['title'])
		#print title
		if "[CE.CLUB] New User Registration" == title:
			emailId = str(emailParsed['entries'][x]['id'])
			# print emailId
			numFound = numFound + 1
			# print "ITS FOUND!"
			# print numFound
	return emailId
	

# Get the current set of data to compare against.
# like a boss.
origEmailId = userAdd()
origFacebook = facebook()
# origWeb = checkWeb()

# Get original colors
rgbC = firebase.get('/c', None)
rCorig = rgbC['r']
gCorig = rgbC['g']
bCorig = rgbC['b']

rgbE = firebase.get('/e', None)
rEorig = rgbE['r']
gEorig = rgbE['g']
bEorig = rgbE['b']

print origEmailId
print origFacebook
#print origWeb


# This will run until the book of revelations is complete
# or if the program is killed. Whatever comes first.
while True:
 
#####New CE.CLUB User#####
	newUserEmailId = userAdd()
	if origEmailId != newUserEmailId:
		#SEND FLASH COMMAND
		#ser.write("user")
		origEmailId = newUserEmailId
		print "New User"
	#end if
	
#####Facebook Like#####
	newFacebook = facebook()
	if newFacebook > origFacebook:
		#SEND FLASH COMMAND
		#ser.write("facebook")
		origFacebook = newFacebook
		print "Facebook Like"
	#end if
	# I guess if we were somehow to loose likes... but psh... lets get real
	if newFacebook < origFacebook:
		origFacebook = newFacebook
 
#####Web Site Visit#####
# currently doesn't work. someone needs to check out the jetpack api
	# newWeb = checkWeb()
	# if newWeb > origWeb:
	# 	#SEND FLASH COMMAND
	# 	ser.write("web")
	# 	origWeb = newWeb
	# 	print "Web Visit"
	# #end if
	# if newWeb < origWeb:
	# 	origWeb = newWeb

#####Update RGB colors#####
	rgbC = firebase.get('/c', None)
	rC = rgbC['r']
	gC = rgbC['g']
	bC = rgbC['b']

	if rC != rCorig:
		serString = "rC:" + str(rC)
		# ser.write(serString)
		print serString
		rCorig = rC

	if gC != gCorig:
		serString = "gC:" + str(gC)
		# ser.write(serString)
		print serString
		gCorig = gC

	if bC != bCorig:
		serString = "bC:" + str(bC)
		# ser.write(serString)
		print serString
		bCorig = bC

	rgbE = firebase.get('/e', None)
	rE = rgbE['r']
	gE = rgbE['g']
	bE = rgbE['b']

	if rE != rEorig:
		serString = "rE:" + str(rE)
		# ser.write(serString)
		print serString
		rEorig = rE

	if gE != gEorig:
		serString = "gE:" + str(gE)
		# ser.write(serString)
		print serString
		gEorig = gE

	if bE != bEorig:
		serString = "bE:" + str(bE)
		# ser.write(serString)
		print serString
		bEorig = bE


#####Sleep timer#####
	# time.sleep(interval)

