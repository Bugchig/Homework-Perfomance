Action()
{
	lr_start_transaction("UC5_Search");

	
	
	lr_start_transaction("home_page");


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
	web_reg_save_param("userSession",
		"LB=userSession\" value=\"",
		"RB=\"/>",
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
	
	
    lr_end_transaction("home_page", LR_AUTO);
    
    lr_think_time(33);

	lr_start_transaction("login");

	web_add_header("Origin", 
		"http://localhost:1080");

	web_add_auto_header("Sec-Fetch-User", 
		"?1");

	
	web_reg_find("Text=User password was correct",LAST);

	web_custom_request("login.pl", 
		"URL=http://localhost:1080/cgi-bin/login.pl", 
		"Method=POST", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer=http://localhost:1080/cgi-bin/nav.pl?in=home", 
		"Snapshot=t3.inf", 
		"Mode=HTTP", 
		"Body=userSession={userSession}&username={login}&password={password}&login.x=51&login.y=18&JSFormSubmit=off", 
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

	lr_end_transaction("login",LR_AUTO);

	lr_think_time(30);

	lr_start_transaction("flights");
	
	web_reg_find("Text=User has returned to the search page",
		LAST);

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

	lr_end_transaction("flights",LR_AUTO);
	
	lr_think_time(42);

	lr_start_transaction("find_flight");

	web_add_auto_header("Origin", 
		"http://localhost:1080");

	web_reg_find("Text/IC= from <B>{depart}</B> to <B>{arrive}</B>",
		LAST);

/*Correlation comment - Do not change!  Original value='340;438;05/07/2024' Name ='outboundFlight' Type ='RecordReplay'*/
	web_reg_save_param_attrib(
		"ParamName=outboundFlight",
		"TagName=input",
		"Extract=value",
		"Name=outboundFlight",
		"Type=radio",
		LAST);

	web_custom_request("reservations.pl_2", 
		"URL=http://localhost:1080/cgi-bin/reservations.pl", 
		"Method=POST", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer=http://localhost:1080/cgi-bin/reservations.pl?page=welcome", 
		"Snapshot=t9.inf", 
		"Mode=HTTP", 
		"Body=advanceDiscount=0&depart={depart}&departDate={departDate}&arrive={arrive}&returnDate={returnDate}&numPassengers=1&seatPref={seatPref}&seatType={seatType}&findFlights.x=24&findFlights.y=7&.cgifields=roundtrip&.cgifields=seatType&.cgifields=seatPref", 
		LAST);

	web_convert_param("outboundFlight_URL2",
		"SourceString={outboundFlight}",
		"SourceEncoding=HTML",
		"TargetEncoding=URL",
		LAST);

	lr_end_transaction("find_flight",LR_AUTO);

	lr_think_time(18);

	lr_start_transaction("choice_flight");

	web_custom_request("reservations.pl_3",
		"URL=http://localhost:1080/cgi-bin/reservations.pl",
		"Method=POST",
		"Resource=0",
		"RecContentType=text/html",
		"Referer=http://localhost:1080/cgi-bin/reservations.pl",
		"Snapshot=t10.inf",
		"Mode=HTTP",
		"Body=outboundFlight={outboundFlight_URL2}&numPassengers=1&advanceDiscount=0&seatType={seatType}&seatPref={seatPref}&reserveFlights.x=45&reserveFlights.y=10",
		LAST);

	lr_end_transaction("choice_flight",LR_AUTO);

	lr_think_time(42);
	
	lr_start_transaction("itinerary");

	web_custom_request("Itinerary Button", 
		"URL=http://localhost:1080/cgi-bin/welcome.pl?page=itinerary", 
		"Method=GET", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer=http://localhost:1080/cgi-bin/nav.pl?page=menu&in=home", 
		"Snapshot=t6.inf", 
		"Mode=HTTP", 
		LAST);

	web_concurrent_start(NULL);

	web_custom_request("itinerary.pl", 
		"URL=http://localhost:1080/cgi-bin/itinerary.pl", 
		"Method=GET", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer=http://localhost:1080/cgi-bin/welcome.pl?page=itinerary", 
		"Snapshot=t7.inf", 
		"Mode=HTTP", 
		LAST);

	web_custom_request("nav.pl_3", 
		"URL=http://localhost:1080/cgi-bin/nav.pl?page=menu&in=itinerary", 
		"Method=GET", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer=http://localhost:1080/cgi-bin/welcome.pl?page=itinerary", 
		"Snapshot=t8.inf", 
		"Mode=HTTP", 
		LAST);

	web_concurrent_end(NULL);

	lr_end_transaction("itinerary",LR_AUTO);
		
	lr_end_transaction("UC5_Search", LR_AUTO);

	

	return 0;
}