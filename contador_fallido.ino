#include <WiFi.h>
#define PORT 80    
WiFiServer server(PORT);

const char* ssid     = "Telecentro-34ba";
const char* password = "CVLZLWNKG4CH";

String header; 
int contconexion=0;

// variables
int preMillis = 0,num = 0;
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
          

  int Millis1 = millis();  
  if (Millis1 - preMillis >= 1000) {
      preMillis = Millis1;
      num++;
}
 
  
 String pagina = "<!DOCTYPE html>"
 "<html>"
"<head>"
    "<title>tpJoaco</title>"
"</head>"
"<body>"
    "<center>"
    "<titulo>CONTROLADOR TEMPORIZADOR</titulo>"
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
