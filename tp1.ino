#include <WiFi.h>
#define PORT 80    
WiFiServer server(PORT);

const char* ssid     = "Frujter";
const char* password = "FrujterFrujter";

String header; 
int contconexion=0;

// variables
int preMillis = 0,num = 0,rest = 0;
bool verda = false;

void setup() {

Serial.begin(115200);
Serial.println("");

//declarar puerto y los PinMode

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED and contconexion <50) {
  ++contconexion;
  delay(500);
  Serial.print(".");
  }
  if (contconexion <50) {
    Serial.println("");
    Serial.println("WiFi conectado");
    Serial.println(WiFi.localIP());
    server.begin(); // iniciamos el servidor
  }
  else {
    Serial.println("");
    Serial.println("Error de conexion");
  }
}

void loop(){
  WiFiClient client = server.available();  
  if (client) {                           
  Serial.println("New Client.");        
  String currentLine = "";              
  while (client.connected()) {          
    if (client.available()) {           
      char c = client.read();           
      Serial.write(c);                  
      header += c;
      if (c == '\n') {                  
            if (currentLine.length() == 0) {
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println("Connection: close");
            client.println();
          


  if (header.indexOf("GET /diez") >= 0) {  
    num = 10; 
    verda = true;
  }
    else if (header.indexOf("GET /treinta") >= 0) {  
    num = 30; 
    verda = true;
  }
    else if (header.indexOf("GET /unminuto") >= 0) {  
    num = 60; 
    verda = true;
  }    
  int Millis1 = millis();  //esta sección reduce a la variable "num" cada segundo, el valor de num va a depender del boton oprimido
  if (Millis1 - preMillis >= 1000) {
    preMillis = Millis1;

    rest--;
    if (verda == true){
    rest = num;
    Serial.println(num);
    
    if(num <= 0){
      verda = false;
      num = 0;
    }
   }
  }
 
  
 String pagina = "<!DOCTYPE html>"
 "<html>"
"<head>"
    "<title>tpJoaco</title>"
"</head>"
"<body>"
    "<center>"
    "<titulo>CONTROLADOR TEMPORIZADOR</titulo>"
    "<table>"
        "<td><p><a href='/diez'> <button div class='diez'> 10s </button> </a></p></td>"
        "<td><p><a href='/treinta'> <button div class='treinta'> 30s </button> </a></p></td>"
        "<td><p><a href='/unminuto'> <button div class='unminuto'> 1min </button> </a></p></td>"
    "</table>"
    "<p> Tiempo Restante: "+String(num)+"s </p>"
"</center>"
"</body>"

"<style>"

"titulo {"
    "font-size: 36px;"
    "font-family: Impact;"
    "font-weight: bold;"
"}"
"body {"
    "background-color: #86969c;"  
"}"
"button {"
    "height: 40px;"
    "width: 80px;"
    "border-width: 2px;"
    "border-color: black;"
    "border-radius: 10px;"
    "font-weight: bold;"
"}"
".diez {"
    "background-color: yellow;"
"}"
".treinta {"
    "background-color: orange;"
"}"
".unminuto{"
    "background-color: green;"
"}"
"</style>"
"</html>"
 "";
 
    client.println(pagina);     
            client.println();
          break;
          } else currentLine = "";
        } else if (c != '\r') { 
            currentLine += c;   
        }
      }
  }
  header = "";
  client.stop();
  Serial.println("Client disconnected.");
  Serial.println("");
  }
}
