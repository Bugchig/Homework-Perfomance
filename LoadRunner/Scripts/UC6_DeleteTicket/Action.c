Action()
{
	int MAX;
	int i;
	
	
	lr_start_transaction("UC6_Delete_Ticket");

	
	
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


	lr_start_transaction("login");

	web_add_header("Origin", 
		"http://localhost:1080");

	web_add_auto_header("Sec-Fetch-User", 
		"?1");

	lr_think_time(33);
	
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

	// web_concurrent_start(NULL);

	web_custom_request("nav.pl_3", 
		"URL=http://localhost:1080/cgi-bin/nav.pl?page=menu&in=itinerary", 
		"Method=GET", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer=http://localhost:1080/cgi-bin/welcome.pl?page=itinerary", 
		"Snapshot=t7.inf", 
		"Mode=HTTP", 
		LAST);

	

	// web_concurrent_end(NULL);
	
	web_reg_save_param("flightID",
		"LB=flightID\" value=\"",
		"RB=\"",
		"Ord=all",
		LAST);
	

	
	// lr_eval_string("{flightID_count}");
	
	web_reg_save_param("cgifields",
		"LB=name=\".cgifields\" value=\"",
		"RB=\"",
		"Ord=ALL",
		LAST);

	
	web_custom_request("itinerary.pl", 
		"URL=http://localhost:1080/cgi-bin/itinerary.pl", 
		"Method=GET", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer=http://localhost:1080/cgi-bin/welcome.pl?page=itinerary", 
		"Snapshot=t8.inf", 
		"Mode=HTTP", 
		LAST);
	
	
	lr_output_message(lr_eval_string("{flightID_count}"));
	lr_output_message(lr_eval_string("{cgifields_count}"));
	
	MAX = atoi(lr_eval_string("{flightID_count}"));

	

	

	
	lr_save_string("","flightID_buffer");
	lr_param_sprintf("flightID_buffer", "%s=on&", "1");
	lr_save_string("","cgifields_buffer");
	for (i = 1; i <= MAX; i++){
		
		lr_param_sprintf("flightID_buffer", "%sflightID=%s&", lr_eval_string("{flightID_buffer}"), lr_paramarr_idx("flightID", i));
		
	    
	    lr_param_sprintf("cgifields_buffer", "%s&cgifields=%s", lr_eval_string("{cgifields_buffer}"), lr_paramarr_idx("cgifields", i));
	    
	};
	lr_output_message(lr_eval_string("{flightID_buffer}"));
	lr_output_message(lr_eval_string("{cgifields_buffer}"));
	
	lr_save_string(lr_eval_string("{flightID_buffer}removeFlights.x=36&removeFlights.y=4{cgifields_buffer}"),"result_string");
	
	lr_output_message(lr_eval_string("{result_string}"));
	
	
	lr_end_transaction("itinerary",LR_AUTO);

	lr_start_transaction("delete");

	web_add_header("Origin", 
		"http://localhost:1080");

	lr_think_time(55);
	
	
	web_reg_find("Fail=Found",
		"Text={flightID_1}",
		LAST);
	
	


	web_custom_request("itinerary.pl_2", 
		"URL=http://localhost:1080/cgi-bin/itinerary.pl", 
		"Method=POST", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer=http://localhost:1080/cgi-bin/itinerary.pl", 
		"Snapshot=t9.inf", 
		"Mode=HTTP", 
		"Body={result_string}",
		LAST);
	
	lr_output_message(lr_eval_string("{flightID_count}"));
	

	lr_end_transaction("delete",LR_AUTO);

	lr_think_time(15);

	lr_start_transaction("logout");

	web_revert_auto_header("Origin");

	lr_think_time(9);
	
	web_reg_find("Text=A Session ID has been created and loaded into a cookie called MSO",
		LAST);

	

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

	lr_end_transaction("logout",LR_AUTO);
	
	lr_end_transaction("UC6_Delete_Ticket", LR_AUTO);

	

	return 0;
}