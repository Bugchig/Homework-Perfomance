Action()
{

	web_add_auto_header("sec-ch-ua", 
		"\"Chromium\";v=\"124\", \"Google Chrome\";v=\"124\", \"Not-A.Brand\";v=\"99\"");

	web_add_auto_header("sec-ch-ua-mobile", 
		"?0");

	web_add_auto_header("sec-ch-ua-platform", 
		"\"Windows\"");

	web_add_auto_header("Upgrade-Insecure-Requests", 
		"1");

	web_add_auto_header("Sec-Fetch-Site", 
		"same-origin");

	web_add_auto_header("Sec-Fetch-Mode", 
		"navigate");

	web_add_auto_header("Sec-Fetch-Dest", 
		"frame");

	web_custom_request("welcome.pl", 
		"URL=http://localhost:1080/cgi-bin/welcome.pl?signOff=true", 
		"Method=GET", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer=http://localhost:1080/WebTours/", 
		"Snapshot=t1.inf", 
		"Mode=HTTP", 
		LAST);

	web_custom_request("nav.pl", 
		"URL=http://localhost:1080/cgi-bin/nav.pl?in=home", 
		"Method=GET", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer=http://localhost:1080/cgi-bin/welcome.pl?signOff=true", 
		"Snapshot=t2.inf", 
		"Mode=HTTP", 
		LAST);

	web_set_sockets_option("SSL_VERSION", "AUTO");

	lr_start_transaction("Login");

	web_add_header("Origin", 
		"http://localhost:1080");

	web_add_auto_header("Sec-Fetch-User", 
		"?1");

	lr_think_time(33);

	web_custom_request("login.pl", 
		"URL=http://localhost:1080/cgi-bin/login.pl", 
		"Method=POST", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer=http://localhost:1080/cgi-bin/nav.pl?in=home", 
		"Snapshot=t3.inf", 
		"Mode=HTTP", 
		"Body=userSession=138922.76127987HVtfiDQpfDDDDDDDtciHfpADHc&username=jojo&password=bean&login.x=51&login.y=18&JSFormSubmit=off", 
		LAST);

	web_concurrent_start(NULL);

	web_custom_request("login.pl_2", 
		"URL=http://localhost:1080/cgi-bin/login.pl?intro=true", 
		"Method=GET", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer=http://localhost:1080/cgi-bin/login.pl", 
		"Snapshot=t4.inf", 
		"Mode=HTTP", 
		LAST);

	web_custom_request("nav.pl_2", 
		"URL=http://localhost:1080/cgi-bin/nav.pl?page=menu&in=home", 
		"Method=GET", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer=http://localhost:1080/cgi-bin/login.pl", 
		"Snapshot=t5.inf", 
		"Mode=HTTP", 
		LAST);

	web_concurrent_end(NULL);

	lr_end_transaction("Login",LR_AUTO);

	lr_think_time(30);

	lr_start_transaction("Flights");

	web_custom_request("Search Flights Button", 
		"URL=http://localhost:1080/cgi-bin/welcome.pl?page=search", 
		"Method=GET", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer=http://localhost:1080/cgi-bin/nav.pl?page=menu&in=home", 
		"Snapshot=t6.inf", 
		"Mode=HTTP", 
		LAST);

	web_concurrent_start(NULL);

	web_custom_request("reservations.pl", 
		"URL=http://localhost:1080/cgi-bin/reservations.pl?page=welcome", 
		"Method=GET", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer=http://localhost:1080/cgi-bin/welcome.pl?page=search", 
		"Snapshot=t7.inf", 
		"Mode=HTTP", 
		LAST);

	web_custom_request("nav.pl_3", 
		"URL=http://localhost:1080/cgi-bin/nav.pl?page=menu&in=flights", 
		"Method=GET", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer=http://localhost:1080/cgi-bin/welcome.pl?page=search", 
		"Snapshot=t8.inf", 
		"Mode=HTTP", 
		LAST);

	web_concurrent_end(NULL);

	lr_end_transaction("Flights",LR_AUTO);

	lr_start_transaction("Find_Flight");

	web_add_auto_header("Origin", 
		"http://localhost:1080");

	lr_think_time(42);

	web_custom_request("reservations.pl_2", 
		"URL=http://localhost:1080/cgi-bin/reservations.pl", 
		"Method=POST", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer=http://localhost:1080/cgi-bin/reservations.pl?page=welcome", 
		"Snapshot=t9.inf", 
		"Mode=HTTP", 
		"Body=advanceDiscount=0&depart=Los+Angeles&departDate=05%2F07%2F2024&arrive=Paris&returnDate=05%2F08%2F2024&numPassengers=1&seatPref=None&seatType=Coach&findFlights.x=24&findFlights.y=7&.cgifields=roundtrip&.cgifields=seatType&.cgifields=seatPref", 
		LAST);

	lr_end_transaction("Find_Flight",LR_AUTO);

	lr_think_time(18);

	lr_start_transaction("Choice_Flight");

	web_custom_request("reservations.pl_3", 
		"URL=http://localhost:1080/cgi-bin/reservations.pl", 
		"Method=POST", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer=http://localhost:1080/cgi-bin/reservations.pl", 
		"Snapshot=t10.inf", 
		"Mode=HTTP", 
		"Body=outboundFlight=340%3B438%3B05%2F07%2F2024&numPassengers=1&advanceDiscount=0&seatType=Coach&seatPref=None&reserveFlights.x=45&reserveFlights.y=10", 
		LAST);

	lr_end_transaction("Choice_Flight",LR_AUTO);

	lr_think_time(42);

	lr_start_transaction("Payment");

	web_custom_request("reservations.pl_4", 
		"URL=http://localhost:1080/cgi-bin/reservations.pl", 
		"Method=POST", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer=http://localhost:1080/cgi-bin/reservations.pl", 
		"Snapshot=t11.inf", 
		"Mode=HTTP", 
		"Body=firstName=Jojo&lastName=Bean&address1=12345&address2=Moscow&pass1=Jojo+Bean&creditCard=12345&expDate=11%2F26&oldCCOption=&numPassengers=1&seatType=Coach&seatPref=None&outboundFlight=340%3B438%3B05%2F07%2F2024&advanceDiscount=0&returnFlight=&JSFormSubmit=off&buyFlights.x=18&buyFlights.y=8&.cgifields=saveCC", 
		LAST);

	lr_end_transaction("Payment",LR_AUTO);

	lr_start_transaction("Logout");

	web_revert_auto_header("Origin");

	lr_think_time(9);

	web_custom_request("SignOff Button", 
		"URL=http://localhost:1080/cgi-bin/welcome.pl?signOff=1", 
		"Method=GET", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer=http://localhost:1080/cgi-bin/nav.pl?page=menu&in=flights", 
		"Snapshot=t12.inf", 
		"Mode=HTTP", 
		LAST);

	web_custom_request("nav.pl_4", 
		"URL=http://localhost:1080/cgi-bin/nav.pl?in=home", 
		"Method=GET", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer=http://localhost:1080/cgi-bin/welcome.pl?signOff=1", 
		"Snapshot=t13.inf", 
		"Mode=HTTP", 
		LAST);

	lr_end_transaction("Logout",LR_AUTO);

	return 0;
}