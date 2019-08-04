String GetGaragePic(byte DoorState) {
  String imgString = F("<svg version='1.0' xmlns='http://www.w3.org/2000/svg' width='112pt' height='64pt' viewBox='0 0 225 135' preserveAspectRatio='xMidYMid meet'>");

  if (DoorState == DOOR_OPENED) {
    imgString += F("<g transform='translate(0.000000,135.000000) scale(0.100000,-0.100000)' fill='#000000' stroke='none'>");
    imgString += F("<path d='M216 1324 c-11 -10 -16 -34 -16 -68 0 -94 -90 -86 963 -86 l927 0 0 -79 c0 -98 10 -111 84 -111 28 0 57 5 64 12 19 19 16 297 -4 326 l-15 22 -994 0 c-890 0 -995 -2 -1009 -16z'/>");
    imgString += F("</g>");
    imgString += F("<g transform='translate(0.000000,135.000000) scale(0.100000,-0.100000)' fill='#E2E2E2' stroke='none'>");
    imgString += F("<path d='M310 1144 c-19 -8 -44 -24 -55 -34 -11 -10 -58 -97 -105 -192 -47 -95 -91 -179 -98 -186 -6 -7 -12 -22 -12 -33 0 -10 -4 -19 -9 -19 -22 0 -31 -73 -31 -246 0 -218 -2 -214 116 -214 l72 0 6 -35 c6 -33 75 -115 96 -115 5 0 10 -5 12 -11 5 -15 86 -23 141 -15 32 5 55 17 85 47 23 22 42 44 42 49 0 6 4 10 10 10 5 0 12 16 16 35 l6 35 338 0 338 0 6 -35 c4 -19 11 -35 16 -35 6 0 10 -4 10 -9 0 -17 59 -72 94 -86 59 -25 196 -13 196 16 0 5 7 9 15 9 19 0 75 86 75 116 0 22 3 22 131 26 178 4 171 -5 167 223 l-3 172 -31 31 c-34 34 -51 39 -306 93 -102 22 -158 38 -158 47 0 6 -4 12 -10 12 -5 0 -10 5 -10 12 0 13 -100 172 -112 176 -4 2 -8 8 -8 14 0 5 -16 34 -36 63 -64 97 -52 95 -545 95 -356 -1 -430 -3 -459 -16z m380 -249 l0 -125 -210 0 c-116 0 -210 3 -210 8 1 4 24 54 53 112 35 71 60 109 77 117 16 8 73 13 158 13 l132 0 0 -125z m473 90 c19 -16 36 -34 36 -39 1 -14 92 -160 105 -168 6 -4 -94 -8 -221 -8 l-233 0 0 126 0 126 138 -4 c137 -3 139 -3 175 -33z m-730 -660 c46 -19 60 -70 32 -121 -47 -88 -170 -30 -151 70 5 28 14 40 39 50 41 18 39 18 80 1z m1116 -14 c62 -62 4 -162 -84 -145 -25 4 -39 14 -50 37 -22 45 -19 65 20 104 30 30 39 34 66 28 17 -4 39 -15 48 -24z'/>");
    imgString += F("</g>");

  } else if (DoorState == DOOR_CLOSEDWITHCAR) {
    imgString += F("<g transform='translate(0.000000,128.000000) scale(0.100000,-0.100000)' fill='#000000' stroke='none'>");
    imgString += F("<path d='M1486 1254 c-11 -10 -16 -34 -16 -69 0 -88 -12 -85 321 -85 l289 0 0 -484 c0 -552 -6 -516 84 -516 92 0 86 -42 86 581 0 477 -2 547 -16 567 l-15 22 -359 0 c-313 0 -361 -2 -374 -16z'/>");
    imgString += F("<path d='M305 1178 c-48 -26 -74 -66 -183 -283 l-117 -230 -3 -165 c-4 -207 -4 -208 110 -217 l77 -6 12 -36 c18 -55 38 -79 87 -109 93 -54 215 -21 260 70 11 24 23 51 26 61 5 16 31 17 356 17 325 0 351 -1 356 -18 36 -122 137 -181 251 -147 60 18 106 64 124 125 l12 40 101 1 c56 0 117 5 136 12 54 19 61 43 57 202 -3 152 -13 187 -57 210 -14 7 -118 34 -230 59 -113 26 -206 50 -208 54 -1 4 -49 79 -105 167 -65 101 -115 168 -136 182 l-34 23 -436 0 c-299 -1 -442 -4 -456 -12z m395 -233 l0 -135 -235 0 -234 0 55 118 c30 64 64 125 75 135 18 15 43 17 180 17 l159 0 0 -135z m458 110 c16 -13 59 -74 95 -135 l66 -110 -249 0 -250 0 0 135 0 135 154 0 c149 0 155 -1 184 -25z m-725 -666 c29 -13 57 -58 57 -91 0 -38 -35 -85 -73 -97 -85 -28 -166 64 -126 142 27 52 87 71 142 46z m1118 -18 c22 -23 29 -39 29 -70 0 -112 -147 -145 -195 -44 -21 43 -13 76 25 114 40 41 100 41 141 0z'/>");
    imgString += F("</g>");
    
  } else if (DoorState == DOOR_CLOSEDNOCAR){
    imgString += F("<g transform='translate(0.000000,128.000000) scale(0.100000,-0.100000)' fill='#000000' stroke='none'>");
    imgString += F("<path d='M1486 1254 c-11 -10 -16 -34 -16 -69 0 -88 -12 -85 321 -85 l289 0 0 -484 c0 -552 -6 -516 84 -516 92 0 86 -42 86 581 0 477 -2 547 -16 567 l-15 22 -359 0 c-313 0 -361 -2 -374 -16z'/>");
    imgString += F("</g>");
   
  }
  
  imgString += F("</svg>");
  return imgString;
}


void ServeWebClients() 
{
  String inString = F("<head><title>");
  inString += WIFI_HOSTNAME;
  inString += F("</title>");
  inString += F("<meta name='viewport' content='width=device-width, initial-scale=1'>");
  inString += F("<meta http-equiv='refresh' content='15'>");
  inString += F("<link rel='stylesheet' href='http://code.jquery.com/mobile/1.3.1/jquery.mobile-1.3.1.min.css' type='text/css'>");
  inString += F("<script src='http://code.jquery.com/jquery-1.9.1.min.js' type='text/javascript'></script>");
  inString += F("<script src='http://code.jquery.com/mobile/1.3.1/jquery.mobile-1.3.1.min.js' type='text/javascript'></script>");
  inString += F("</head>");
  inString += F("<body>");

  inString += F("<div data-role='page' id='page_opts'>");
  inString += F("<div data-role='header'><h3>");
  inString += WIFI_HOSTNAME;
  inString += F("</h3></div>");
  inString += F("<div data-role='content'>");

  inString += F("<fieldset data-role='controlgroup' data-type='horizontal'>");
  inString += F("<input type='radio' name='opt_group' id='basic' onclick='toggle_opt()' checked><label for='basic'>Info</label>");
  inString += F("<input type='radio' name='opt_group' id='other' onclick='toggle_opt()'><label for='other'>Settings</label>");
  inString += F("</fieldset>");
  
  
  inString += F("<div id='div_basic'>");

  // DOOR 1
  byte dst = getState(door1_lastDistanceValue);
  inString += F("<h3 class='ui-bar ui-bar-a ui-corner-all'>Door 1</h3>");
  inString += F("<table><tr><td><b>Door&nbsp;State:<br></td><td><label id='lbl_status' ");
  if (dst == DOOR_OPENED) {
    inString += F("style='color:red;'>OPEN");
  } else if ((dst == DOOR_CLOSEDNOCAR) || (dst == DOOR_CLOSEDWITHCAR)) {
    inString += F("style='color:green;'>CLOSED");
  } else {
    inString += F(">UNKNOWN");
  }
  inString += F("</label></td>");
  inString += F("<td rowspan='3'>");
  inString += GetGaragePic(dst);
  inString += F("</td>");
  inString += F("</tr><tr><td><b><label id='lbl_vstatus1'>Vehicle&nbsp;State:&nbsp</label></b></td>");
  inString += F("<td><label id='lbl_vstatus'>");
  if (dst == DOOR_CLOSEDNOCAR) {
    inString += F("Empty");
  } else if (dst == DOOR_CLOSEDWITHCAR) {
    inString += F("Present");
  } else {
    inString += F("UNKNOWN");
  }
  inString += F("</label></td></tr>");
  inString += F("<tr><td><b>Distance:</b></td><td><label id='lbl_dist'>");
  inString += String(door1_lastDistanceValue);
  inString += F(" (cm)</label></td></tr>");
  inString += F("<tr><td><b>Previous Reads:</b></td><td><label id='lbl_reads'>");
  for (int y=0; y<door_numValues; y++) {
    inString += String(door1_lastDistanceValues[y]);
    inString += F(",");
  }
  inString += F("</label></td><td></td></tr>");
  
  #if DHT_ENABLED == true
  byte tmp = dht.readTemperature();
  byte hum = dht.readHumidity();
  inString += F("<tr><td><b>");
  inString += DHT_TEMPERATURE_ALIAS;
  inString += F(": </b></td><td><label id='lbl_temp'>");
  if (DHT_TEMPERATURE_CELSIUS) {
      inString += String(tmp);
      inString += F(" &#176;C</label></td><td></td></tr>");
  } else {
      inString += String(tmp* 1.8 + 32);
      inString += F(" &#176;F</label></td><td></td></tr>");
  }
  inString += F("<tr><td><b>");
  inString += DHT_HUMIDITY_ALIAS;
  inString += F(": </b></td><td><label id='lbl_hum'>");
  inString += String(hum);
  inString += F(" %</label></td><td></td></tr>");
  #endif
  
  inString += F("</table><br />");
  
  #if DOOR2_ENABLED == true
    // DOOR 2
    dst = getState(door2_lastDistanceValue);
    inString += F("<h3 class='ui-bar ui-bar-a ui-corner-all'>Door 2</h3>");
    inString += F("<table><tr><td><b>Door&nbsp;State:<br></td><td><label id='lbl_status' ");
    if (dst == DOOR_OPENED) {
      inString += F("style='color:red;'>OPEN");
    } else if ((dst == DOOR_CLOSEDNOCAR) || (dst == DOOR_CLOSEDWITHCAR)) {
      inString += F("style='color:green;'>CLOSED");
    } else {
      inString += F(">UNKNOWN");
    }
    inString += F("</label></td>");
    inString += F("<td rowspan='3'>");
    inString += GetGaragePic(dst);
    inString += F("</td>");
    inString += F("</tr><tr><td><b><label id='lbl_vstatus1'>Vehicle&nbsp;State:&nbsp</label></b></td>");
    inString += F("<td><label id='lbl_vstatus'>");
    if (dst == DOOR_CLOSEDNOCAR) {
      inString += F("Empty");
    } else if (dst == DOOR_CLOSEDWITHCAR) {
      inString += F("Present");
    } else {
      inString += F("UNKNOWN");
    }
    inString += F("</label></td></tr>");
    inString += F("<tr><td><b>Distance:</b></td><td><label id='lbl_dist'>");
    inString += String(door2_lastDistanceValue);
    inString += F(" (cm)</label></td></tr>");
    inString += F("<tr><td><b>Previous Reads:</b></td><td><label id='lbl_reads'>");
    for (int y=0; y<door_numValues; y++) {
      inString += String(door2_lastDistanceValues[y]);
      inString += F(",");
    }
    inString += F("</label></td><td></td></tr>");
    inString += F("</table><br />");
  #endif


  #if DOOR3_ENABLED == true
    // DOOR 3
    dst = getState(door3_lastDistanceValue);
    inString += F("<h3 class='ui-bar ui-bar-a ui-corner-all'>Door 3</h3>");
    inString += F("<table><tr><td><b>Door&nbsp;State:<br></td><td><label id='lbl_status' ");
    if (dst == DOOR_OPENED) {
      inString += F("style='color:red;'>OPEN");
    } else if ((dst == DOOR_CLOSEDNOCAR) || (dst == DOOR_CLOSEDWITHCAR)) {
      inString += F("style='color:green;'>CLOSED");
    } else {
      inString += F(">UNKNOWN");
    }
    inString += F("</label></td>");
    inString += F("<td rowspan='3'>");
    inString += GetGaragePic(dst);
    inString += F("</td>");
    inString += F("</tr><tr><td><b><label id='lbl_vstatus1'>Vehicle&nbsp;State:&nbsp</label></b></td>");
    inString += F("<td><label id='lbl_vstatus'>");
    if (dst == DOOR_CLOSEDNOCAR) {
      inString += F("Empty");
    } else if (dst == DOOR_CLOSEDWITHCAR) {
      inString += F("Present");
    } else {
      inString += F("UNKNOWN");
    }
    inString += F("</label></td></tr>");
    inString += F("<tr><td><b>Distance:</b></td><td><label id='lbl_dist'>");
    inString += String(door3_lastDistanceValue);
    inString += F(" (cm)</label></td></tr>");
    inString += F("<tr><td><b>Previous Reads:</b></td><td><label id='lbl_reads'>");
    for (int y=0; y<door_numValues; y++) {
      inString += String(door3_lastDistanceValues[y]);
      inString += F(",");
    }
    inString += F("</label></td><td></td></tr>");
    inString += F("</table><br />");
  #endif

  inString += F("</div>");

  
  inString += F("<div id='div_other' style='display:none;'>");
  inString += F("<table cellpadding='2'>");
  inString += F("<tr><td colspan='2'>&nbsp;</td></tr>");
  
  inString += F("<tr><td><b>WIFI SSID:</b></td><td><label id='lbl_rssi'>");
  inString += WIFI_SSID;
  inString += F("</label></td></tr>");

  inString += F("<tr><td><b>WiFi&nbsp;Signal:</b></td><td><label id='lbl_rssi'>");
  long rssi = WiFi.RSSI();
  if (rssi > -71) {
    inString += F("Good");
  } else if (rssi > -81) {
    inString += F("Weak");    
  } else {
    inString += F("Poor");    
  }
  inString += F(" (");
  inString += rssi;
  inString += F(" dbBm)");
  inString += F("</label></td></tr>");
  
  inString += F("<tr><td colspan='2'>&nbsp;</td></tr>");

  inString += F("<tr><td><b>MQTT Server:</b></td><td><label id='lbl_rssi'>");
  inString += MQTT_SERVER;
  inString += F("</label></td></tr>");
  
  inString += F("<tr><td colspan='2'>&nbsp;</td></tr>");

  inString += F("<tr><td><b>Relay Active Timeout:</b></td><td><label id='lbl_rssi'>");
  inString += RELAY_ACTIVE_TIMEOUT;
  inString += F(" ms</label></td></tr>");

  inString += F("<tr><td><b>Ultrasonic Distance Max Open:</b></td><td><label id='lbl_rssi'>");
  inString += ULTRASONIC_DIST_MAX_OPEN;
  inString += F(" cm</label></td></tr>");

  inString += F("<tr><td><b>Ultrasonic Distance Max Car:</b></td><td><label id='lbl_rssi'>");
  inString += ULTRASONIC_DIST_MAX_CAR;
  inString += F(" cm</label></td></tr>");
  
  inString += F("<tr><td colspan='2'>&nbsp;</td></tr>");
  inString += F("<tr><td colspan='2'><input type='checkbox' id='cb1' ");
  inString += F("checked");
  inString += F(" disabled><label for='cb1'>");
  inString += DOOR1_ALIAS;
  inString += F("</label></td></tr>");
  
  inString += F("<tr><td colspan='2'><input type='checkbox' id='cb2' ");
  #if DOOR2_ENABLED == true
    inString += F("checked");
  #endif
  inString += F(" disabled><label for='cb2'>");
  inString += DOOR2_ALIAS;
  inString += F("</label></td></tr>");
  
  inString += F("<tr><td colspan='2'><input type='checkbox' id='cb3' ");
  #if DOOR3_ENABLED == true
    inString += F("checked");
  #endif
  inString += F(" disabled><label for='cb3'>");
  inString += DOOR3_ALIAS;
  inString += F("</label></td></tr>");

  inString += F("<tr><td colspan='2'><input type='checkbox' id='cb4' ");
  #if DHT_ENABLED == true
    inString += F("checked");
  #endif
  inString += F(" disabled><label for='cb4'>");
  inString += DHT_TEMPERATURE_ALIAS;
  inString += F(" & ");
  inString += DHT_HUMIDITY_ALIAS;
  inString += F("</label></td></tr>"); 
  
  inString += F("</table>");
  inString += F("</div>");

  
  inString += F("<div data-role='footer' data-theme='c'><h5>");
  inString += VERSION;
  inString += F("</h5></div>");
  inString += F("</div>");

  inString += F("<script>");
  inString += F("function eval_cb(n)  {return $(n).is(':checked')?1:0;}");
  inString += F("function toggle_opt() {");
  inString += F("$('#div_basic').hide();");
  inString += F("$('#div_other').hide();");
  inString += F("if(eval_cb('#basic')) $('#div_basic').show();");
  inString += F("if(eval_cb('#other')) $('#div_other').show();");
  inString += F("};");
  inString += F("</script>");
  inString += F("</body>");

  server.send(200, "text/html", inString);
}
