//este código solo tiene un boton, para ver si podia lograr un contador utilizado millis
#include <WiFi.h>
#define PORT 80    
WiFiServer server(PORT);

const char* ssid     = "Frujter";
const char* password = "FrujterFrujter";

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
          


  if (header.indexOf("GET /10s") >= 0) {  
    num = 10; 
    verda = true;
  }
  
  
   if(verda = true){
   int Millis1 = millis();  //esta sección reduce a la variable "num" cada segundo, el valor de num va a depender del boton oprimido
  if (Millis1 - preMillis >= 1000) {
    preMillis = Millis1;

    num--;
    
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
    "<title>Título de la página</title>"
"</head>"
"<body>"
    "<p><a href='10s'><button div class='10s'> 10 SEGUNDOS </button></a></p>" //codigo html rudimentario para probar el contador
    "<p>la leyenda es: '+num+' s</p>"
"</body>"
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
