#include <ESP8266WiFi.h>

const char* ssid = "<ssid name>";
const char* password = "<internet password>";
 
//set pins
int red = D6;
int yellow = D5;
int green = D0;

//set count
int count = 0;

//set cycling boolean
bool isCycling = false;

//set millis variables
unsigned long previousMillis = 0;
int interval = 2000;

//set up server
WiFiServer server(80);

//SETUP
void setup() {
  Serial.begin(115200);  //115200 baud
  delay(10);
 
  //set all pin modes to output
  pinMode(red, OUTPUT);
  pinMode(yellow, OUTPUT);
  pinMode(green, OUTPUT);
  
  //set all leds to low
  digitalWrite(red, LOW);
  digitalWrite(yellow, LOW);
  digitalWrite(green, LOW);
 
  // Connect to WiFi network
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);
 
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
 
  // Start the server
  server.begin();
  Serial.println("Server started");
 
  // Print the IP address
  Serial.print("Use this URL : ");
  Serial.print("http://");
  Serial.print(WiFi.localIP());
  Serial.println("/");
 
}

//MAIN LOOP
void loop() {
  //Check if the cycling bool is true
  //If so, use millis() (non-blocking code) to cycle lights
  if(isCycling == true){
    unsigned long currentMillis = millis();
      if ((unsigned long)(currentMillis - previousMillis) >= interval) {
        if(count % 3 == 0){
          digitalWrite(red, HIGH);
          digitalWrite(yellow, LOW);
          digitalWrite(green, LOW);
        }
        if(count % 3 == 1){
          digitalWrite(red, LOW);
          digitalWrite(yellow, HIGH);
          digitalWrite(green, LOW);
        }
        if(count % 3 == 2){
          digitalWrite(red, LOW);
          digitalWrite(yellow, LOW);
          digitalWrite(green, HIGH);
        }
        ++count;
        previousMillis = currentMillis;
     }
  }
  
  // Check if a client has connected
  WiFiClient client = server.available();
  if (!client) {
    return;
  }
 
  // Wait until the client sends some data
  Serial.println("new client");
  while(!client.available()){
    delay(1);
  }
 
  // Read the first line of the request
  String request = client.readStringUntil('\r');
  Serial.println(request);
  client.flush();

  // Match the request
  if (request.indexOf("/RED") != -1) {
    digitalWrite(red, HIGH);
    digitalWrite(yellow, LOW);
    digitalWrite(green, LOW);
    isCycling = false;
  } 
  if (request.indexOf("/YELLOW") != -1){
    digitalWrite(red, LOW);
    digitalWrite(yellow, HIGH);
    digitalWrite(green, LOW);
    isCycling = false;
  }
  if (request.indexOf("/GREEN") != -1){
    digitalWrite(red, LOW);
    digitalWrite(yellow, LOW);
    digitalWrite(green, HIGH);
    isCycling = false;
  }
  if (request.indexOf("/OFF") != -1){
    digitalWrite(red, LOW);
    digitalWrite(yellow, LOW);
    digitalWrite(green, LOW);
    isCycling = false;
  }
  if (request.indexOf("/CYCLE") != -1){
    count = 0;
    isCycling = true;
  }
 
  // Return the response: html
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println(""); //  do not forget this one
  client.println("<!DOCTYPE HTML>");
  client.println("<html>");
  client.println("<head>");
  client.println("<style>");
  client.println("html {text-align: center;background: #8fa5b2}");
  client.println(".redBtn {height: 100px; width: 100px; background: #DE4B4E; border-radius: 50%}");
  client.println(".yellowBtn {height: 100px; width: 100px; background: #FBFFAB; border-radius: 50%}");
  client.println(".greenBtn {height: 100px; width: 100px; background: #99FFA7; border-radius: 50%}");
  client.println("#holder {height: 340px; width: 100px; background: #BACBDE; border-radius: 30px; padding: 25px;}");
  client.println(".offBtn {font-size: 25px; height: 25px; width: 75px; background: #ffffff; border-radius: 10px; padding: 25px; color: #8fa5b2;}");
  client.println("a {text-decoration: none;}");
  client.println("</style>");
  client.println("</head>");
  client.println("<body>");
  
  client.println("<div id=\"holder\">");
  client.println("<a href=\"/RED\"><div class=\"redBtn\"></div></a>");
  client.println("<br>");
  client.println("<a href=\"/YELLOW\"><div class=\"yellowBtn\"></div></a>");
  client.println("<br>");
  client.println("<a href=\"/GREEN\"><div class=\"greenBtn\"></div></a>");
  client.println("</div>");
  
  client.println("<br>");
  client.println("<a href=\"/OFF\"><div class=\"offBtn\"> OFF </div></a>");
  
  client.println("<br>");
  client.println("<a href=\"/CYCLE\"><div class=\"offBtn\"> CYCLE </div></a>");
  
  client.println("</body>");
  client.println("</html>");
 
  delay(1);
  Serial.println("Client disconnected");
  Serial.println("");
 
}
