# COVID-19_tracker_with-BLYNK
 COVID-19 Live tracker and display using BLYNK APP

 Using thingspeak on https//api.thingspeak.com COVID-19 data from worldofmeters.com is gotten
 
 
Requirements to get started
•	An account with Thingspeak
•	An account with Blynk and the Blynk App
•	NodeMcu module


 Create a Thinghttp under apps
  Under thingspeak create a ThingHTTP and under URL  add https://www.worldometers.info/coronavirus/
	Method: GET
	Parse String: 
		Go to https://www.worldometers.info/coronavirus/ 
		Choose your country and under each field e.g Cases right click and select Inspect
		Copy the XPath to Parse String and save.

	This will generate an API which is to be added to the url in the arduino code
	e.g const char* url3 = "/apps/thinghttp/send_request?api_key=6FAFZP7ZQ1XVY54Y";
	// add your unique api_key


On BLYNK add the three gauges  one for cases, recoveries and Deaths. Each is to be assigned a Virtual Pin according to the code.
Upload the code and RUN BLYNK App.
