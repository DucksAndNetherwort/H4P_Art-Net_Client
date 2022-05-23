#define H4P_VERBOSE 1
#include<H4Plugins.h>
H4_USE_PLUGINS(115200,H4_Q_CAPACITY,false) // Serial baud rate, Q size, SerialCmd autostop
//H4P_WiFi wiffy("MakeItZone","26EBF7gv5tfV","Art-Net Client");
H4P_WiFi wiffy("SHAW-E72E30","251155066304","Art-Net Client");
//H4P_UPNPServer lexy("Sonoff Basic Switch");

int startChannel = 0;
int channelCount = 3;
int red = 14;
int green = 12;
int blue = 13;

void h4setup() {
	analogWriteRange(255);
	pinMode(red, OUTPUT);
	pinMode(green, OUTPUT);
	pinMode(blue, OUTPUT);
	/*h4p.gvSetInt("Start Channel", 0);
	h4p.gvSetInt("Channel Count", 3);*/
}

H4P_ArtNetServer ArtNet(startChannel + 1, 3);//"H4P ArtNet", "longer name for it");

void myHandler(std::string svc, H4PE_TYPE t, std::string msg){
	//if(svc.c_str() != artNetTag()) return;
	//Serial.println((*msg.data()), HEX);
	analogWrite(red, ArtNet.GetChannel(0));
	analogWrite(green, ArtNet.GetChannel(1));
	analogWrite(blue, ArtNet.GetChannel(2));
};

void onViewersConnect() {
	Serial.println("User connected");
	wiffy.uiAddText("Start Channel", startChannel);
	wiffy.uiAddText("Channel Count", channelCount);

	/*wiffy.uiSetValue("Start Channel", startChannel);
	wiffy.uiSetValue("Channel Count", channelCount);*/
}

void onViewersDisconnect() {
	Serial.println("User left");
}

H4P_EventListener bigBrother(H4PE_ARTDMX, myHandler);

H4P_EventListener allexceptmsg(H4PE_VIEWERS, [](const std::string& svc, H4PE_TYPE t, const std::string& msg){
	switch (t) {
	case H4PE_VIEWERS:
		H4P_SERVICE_ADAPTER(Viewers);
		break;
	
	default:
		break;
	}
});

/*void h4pGlobalEventHandler(const std::string& svc,H4PE_TYPE t,const std::string& msg){
  /*Serial.printf("Big Brother sees EVERYTHING %s %s %s\n",CSTR(svc),CSTR(h4pGetEventName(t)),CSTR(msg));
  switch(t){
	case H4PE_NOOP:
	  Serial.printf("Used for testing: you will never see this\n");
	  break;
	// None of the SYSx events can be turned off / compiled out
	case H4PE_SYSINFO:
	  Serial.printf("Important system information:\n");
	  break;
	case H4PE_SYSWARN:
	  Serial.printf("You need to check this out and fix it: App may not run correctly\n");
	  break;
	case H4PE_SYSFATAL:
	  Serial.printf("Impossible to continue: App enters flashing 'hangup loop'\n");
	  break;
	case H4PE_MSG:
	  Serial.printf("Probably the most common type you will see. Can be 'compiled out'\n");
	  break;
	case H4PE_ARTDMX:
	  Serial.printf("AAAAAAAAAARRRRRRRTTTTTTTNEETT\n");
	  break;
	case H4PE_BOOT:
	case H4PE_STAGE2:
	  Serial.printf("Used internally to start services - don't mess with it!\n");
	  break;
	case H4PE_SERVICE:
	  Serial.printf("A service has started (msg==\"1\") or stopped (msg==\"0\")\n");
	  break;
	case H4PE_REBOOT:
	  Serial.printf("App is about to reboot: save config (if any) etc\n");
	  break;
	case H4PE_FACTORY:
	  Serial.printf("App is about to 'Factory Reset': clear any saved config data etc\n");
	  break;
	case H4PE_CMD:
	  Serial.printf("A command came into the app via 'svc'\n");
	  break;
	case H4PE_HEAP:
	  Serial.printf("H4 publishes current heap value (usually for diagnostics)\n");
	  break;
	case H4PE_Q:
	  Serial.printf("H4 publishes current Queue size (usually for diagnostics)\n");
	  break;
	case H4PE_LOOPS:
	  Serial.printf("H4 publishes current NLoops/sec (usually for diagnostics / performance tuning)\n");
	  break;
	case H4PE_PRESENCE:
	  Serial.printf("A device has %s the network\n",STOI(msg) ? "joined":"left");
	  break;
	case H4PE_GVCHANGE:
	  Serial.printf("A persistent storage variable %s has changed its value to %s\n",CSTR(svc),CSTR(msg));
	  break;
	case H4PE_GPIO:
	  Serial.printf("A hardware event hs occured on pin 'svc': its current value is in msg\n");
	  break;
	case H4PE_SIGNAL:
	  Serial.printf("Send flashing pattern to default signalling device, usually LED_BUILTIN\n");
	  break;
	case H4PE_VIEWERS:
	  Serial.printf("Web UI has 'msg' number of viewers. When 1, set up any resources, when 0 clear / reset them\n");
	  break;
	case H4PE_UISYNC:
	  Serial.printf("Keep UI in sync - user should call h4puiSync\n");
	  break;
	case H4PE_UIADD:
	  Serial.printf("Add an element to the UI user should call the appropriate function\n");
	  break;
	case H4PE_UIMSG:
	  Serial.printf("Send message to UI scrolling infor area\n");
	  break;
	case H4PE_RTC:
	  Serial.printf("NTP 'clock' time is now valid\n");
	  break;
	case H4PE_ALARM:
	  Serial.printf("clock time alarm has fired msg=1/0 on/off\n");
	  break;
	case H4PE_GRID:
	  Serial.printf("Used internally by presence detection: another h4 device joined the network\n");
	  break;
	case H4PE_UPNP:
	  Serial.printf("Used internally by presence detection\n");
	  break;
	case H4PE_HEARTBEAT:
	  Serial.printf("H4 has sent a synchronous 1-second, on-the-second 'ping'\n");
	  break;
	default:
	  Serial.printf("Something terrible has gone wrong: no such type '%u'!\n",t);
  }*/
