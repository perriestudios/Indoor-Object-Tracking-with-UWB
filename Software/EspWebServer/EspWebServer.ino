#include <ESP8266WiFi.h>
#include <Wire.h>

// Replace with your network credentials
const char* ssid     = "pranav";
const char* password = "pranav123";

// Set web server port number to 80
WiFiServer server(80);

// Variable to store the HTTP request
String header;

// Current time
unsigned long currentTime = millis();
// Previous time
unsigned long previousTime = 0; 
// Define timeout time in milliseconds (example: 2000ms = 2s)
const long timeoutTime = 2000;

float x = 0;
float y = 0;

void setup() {
  Serial.begin(115200);
  Wire.begin(5, 4);
  // Connect to Wi-Fi network with SSID and password
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  // Print local IP address and start web server
  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  server.begin();
}

void loop(){
  char d[9];
  int n = 0;
  Wire.requestFrom(8, 9); /* request & read data of size 13 from slave */
  while(Wire.available()){
  // char p = Wire.read();
   d[n] = 0;
   d[n] = Wire.read();
   n = n+1;
   if (n == 9){
    n = 0;
   }
   /*for (int j = 0; j <9; j++)
   {
    Serial.print(d[j]);
   } */
   //Serial.print(p);
  }
  Serial.println();
  delay(1000);

  /*int x_unit = c[0];
  int x_ten = c[2];
  int x_hund = c[3];
  int y_unit = c[5];
  int y_ten = c[7];
  int y_hund = c[8]; */
  float find_x = 0;
  find_x = d[0] + (0.1*d[2]) + (0.01*d[3]);
  find_x = find_x - 53.28;
  float find_y = 0;
  find_y = d[5] + (0.1*d[7]) + (0.01*d[8]);
  find_y = find_y - 53.28;
  //Serial.println(find_x);
  //Serial.println(find_y);
   
  WiFiClient client = server.available();   // Listen for incoming clients

  if (client) {                             // If a new client connects,
    Serial.println("New Client.");          // print a message out in the serial port
    String currentLine = "";                // make a String to hold incoming data from the client
    currentTime = millis();
    previousTime = currentTime;
    while (client.connected() && currentTime - previousTime <= timeoutTime) { // loop while the client's connected
      currentTime = millis();         
      if (client.available()) {             // if there's bytes to read from the client,
        char c = client.read();             // read a byte, then
        Serial.write(c);                    // print it out the serial monitor
        header += c;
        if (c == '\n') {                    // if the byte is a newline character
          // if the current line is blank, you got two newline characters in a row.
          // that's the end of the client HTTP request, so send a response:
          if (currentLine.length() == 0) {
            // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
            // and a content-type so the client knows what's coming, then a blank line:
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println("Connection: close");
            client.println();
            
            // Display the HTML web page
            client.println("<!DOCTYPE html><html>");
            client.println("<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
            client.println("<link rel=\"icon\" href=\"data:,\">");
            // CSS to style the on/off buttons 
            // Feel free to change the background-color and font-size attributes to fit your preferences
            client.println("<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}");
            client.println(".button { background-color: #195B6A; border: none; color: white; padding: 16px 40px;");
            client.println("text-decoration: none; font-size: 30px; margin: 2px; cursor: pointer;}");
            client.println(".button2 {background-color: #77878A;}</style></head>");
            
            // Web Page Heading
            client.println("<body><h1>Indoor Object Tracking using Ultra Wideband Localization</h1>");
            //x = x+5;
            //y = y+5;
            // Display current state, and ON/OFF buttons for GPIO 5  
            client.println(" X Co-ordinate:" + String(find_x) + "<br>");
            client.println(" Y Co-ordinate:" + String(find_y));
            client.println("<meta http-equiv=\"refresh\" content=\"1\">");
            client.println("</body></html>");
            
            // The HTTP response ends with another blank line
            client.println();
            // Break out of the while loop
            break;
          } else { // if you got a newline, then clear currentLine
            currentLine = "";
          }
        } else if (c != '\r') {  // if you got anything else but a carriage return character,
          currentLine += c;      // add it to the end of the currentLine
        }
      }
    }
    // Clear the header variable
    header = "";
    // Close the connection
    client.stop();
    Serial.println("Client disconnected.");
    Serial.println("");
  }
}
