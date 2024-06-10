Action()
{
lr_start_transaction("registering");

	/*Possible OAUTH authorization was detected. It is recommended to correlate the authorization parameters.*/

	web_set_sockets_option("SSL_VERSION", "AUTO");

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

	web_reg_find("Text=A Session ID has been created and loaded into a cookie called MSO",
		LAST);

	
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

	lr_start_transaction("Sign_up");

	web_add_auto_header("Sec-Fetch-User", 
		"?1");

	lr_think_time(13);

	web_custom_request("login.pl", 
		"URL=http://localhost:1080/cgi-bin/login.pl?username=&password=&getInfo=true", 
		"Method=GET", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer=http://localhost:1080/WebTours/home.html", 
		"Snapshot=t3.inf", 
		"Mode=HTTP", 
		LAST);

	lr_end_transaction("Sign_up",LR_AUTO);

	lr_start_transaction("customer_Profile");

	web_add_header("Origin", 
		"http://localhost:1080");

	lr_think_time(59);
	web_reg_find("Text=Thank you, <b>{Login}</b>, for registering",
		LAST);
	

	web_custom_request("login.pl_2", 
		"URL=http://localhost:1080/cgi-bin/login.pl", 
		"Method=POST", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer=http://localhost:1080/cgi-bin/login.pl?username=&password=&getInfo=true", 
		"Snapshot=t4.inf", 
		"Mode=HTTP", 
		"Body=username={Login}&password={password}&passwordConfirm={password}&firstName={firstName}&lastName={lastName}&address1={address1}&address2={address2}&register.x=51&register.y=5", 
		LAST);

	lr_end_transaction("customer_Profile",LR_AUTO);
	lr_end_transaction("registering", LR_AUTO);


	return 0;
}