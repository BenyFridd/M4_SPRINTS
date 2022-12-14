#include <Arduino.h>
#ifdef ESP32
  #include <WiFi.h>
  #include <AsyncTCP.h>
#else
  #include <ESP32WiFi.h>
  #include <ESPAsyncTCP.h>
#endif
#include <ESPAsyncWebServer.h>
#include <LiquidCrystal_I2C.h>

#define I2C_SDA 48
#define I2C_SCL 47


LiquidCrystal_I2C lcd(0x27, 16, 2);

AsyncWebServer server(80);


const char* ssid = "Inteli-COLLEGE";
const char* password =  "QazWsx@123";


const char* PARAM_INPUT_1 = "result";

const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Document</title>
</head>
<body>
    <div id="gameDiv">
        <h1 class="gameText" id="playerText">Player: </h1>
        <h1 class="gameText" id="ComputadorText">Computador: </h1>
        <h1 class="gameText" id="resultText">Resultado: </h1>

        <button class="Botoes">Pedra</button>
        <button class="Botoes">Papel</button>
        <button class="Botoes">Tesoura</button>


    </div>
    <script>const playerText = document.querySelector("#playerText");
        const ComputadorText = document.querySelector("#ComputadorText");
        const resultText = document.querySelector("#resultText");
        const Botoes = document.querySelectorAll(".Botoes");
        
        let player;
        let Computador;
        let result;
        
        Botoes.forEach(button => button.addEventListener("click", () => {
        
            player = button.textContent;
            ComputadorTurn();
        
            playerText.textContent = "Player: " + player;
            ComputadorText.textContent = "Computador: " + Computador;
            resultText.textContent = checkWinner();

            result = checkWinner();

              if result == "Perdeu!" {
              $.get("http://10.128.65.158:80/Perdeu", function(Perdeu){
            }

              if result == "Empate!" {
              $.get("http://10.128.65.158:80/Empate", function(Empate){
            }

              if result == "Ganhou!" {
              $.get("http://10.128.65.158:80/Ganhou", function(Ganhou){
            }


        }));
        
        
        function ComputadorTurn(){
        
            const Numaletorio = Math.floor(Math.random() * 3) + 1;
        
            switch(Numaletorio){
              case 1:
                Computador = "Pedra";
                break;
              case 2:
                Computador = "Papel";
                break;
              case 3:
                Computador = "Tesoura";
                break;
            }
        }
        function checkWinner(){
            if(player == Computador){
              return "Empate!";
            }
            else if(Computador == "Pedra" && player == "Tesoura"){
              return "Perdeu!"
            }
            else if(Computador == "Papel" && player == "Pedra"){
              return "Perdeu!"
            }
            else if(Computador == "Tesoura" && player == "Papel"){
              return  "Perdeu!"
            }  
            else if (player == "Pedra" && Computador == "Tesoura"){
              return "Ganhou!"
            }
            else if (player == "Papel" && Computador == "Pedra"){
              return "Ganhou!"
            }
            else if (player == "Tesoura" && Computador == "Papel"){
              return "Ganhou!"
            }
        }
        console.log(result)
        </script>
</body>
</html>)rawliteral";


void notFound(AsyncWebServerRequest *request) {
  request->send(404, "text/plain", "Not found");
}

void setup() {
 Wire.begin(I2C_SDA, I2C_SCL);
  lcd.init();
  lcd.backlight();

  Serial.begin(115200);

  Serial.println(WiFi.localIP());

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  if (WiFi.waitForConnectResult() != WL_CONNECTED) {
    Serial.println("WiFi Failed!");
    return;
  }
  Serial.println();
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());



  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/html", index_html);
  });


  server.on("/get", HTTP_GET, [] (AsyncWebServerRequest *request) {
    String inputMessage;
    String inputParam;

    if (request->hasParam(PARAM_INPUT_1)) {
      inputMessage = request->getParam(PARAM_INPUT_1)->value();
      inputParam = PARAM_INPUT_1;
    }
  
    else {
      inputMessage = "No message sent";
      inputParam = "none";
    }

    lcd.print(inputMessage);
    Serial.println(inputMessage);
    delay(2000);
    lcd.clear();


    request->send(200, "text/html", "HTTP GET request enviado(" 
                                     + inputParam + ") resultText: " + inputMessage 
                                     );
  });

  server.onNotFound(notFound);
  server.begin();


}

void loop() {

}