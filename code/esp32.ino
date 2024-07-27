#include <Arduino.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>

// WiFi bilgileri
const char* ssid = "Taytech Fabrika";
const char* password = "T@y2020tech**";

// API bilgileri
const char* Gemini_Token = "AIzaSyDLXyM1gycKjJ-JyxxuihB7sK_zmkVtjGc";
const char* Gemini_Max_Tokens = "425";

String res = "";
unsigned long lastRequestTime = 0;
unsigned long requestInterval = 5000;

String extractBetweenTripleBackticks(String input) {
      String tripleBacktick = "```";
      int firstTripleBacktickIndex = input.indexOf(tripleBacktick);
      int secondTripleBacktickIndex = input.lastIndexOf(tripleBacktick);

      if (firstTripleBacktickIndex ==0 && secondTripleBacktickIndex != -1 && input.indexOf("```json")!=-1 && (input.indexOf("9.ay")!=-1 || input.indexOf("9. Ay")!=-1 || input.indexOf("9. ay")!=-1) && input.indexOf("}\n}")!=-1)  {
        return input.substring(firstTripleBacktickIndex+7, secondTripleBacktickIndex);
      } else {
        return "x"; // Üçlü backtickler bulunamazsa boş string döner
      }
}







void connectToWiFi() {
  Serial.print("Bağlanılıyor: ");
  Serial.println(ssid);
  
  WiFi.begin(ssid, password);

  // WiFi bağlantısı bekleniyor
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println("Bağlandı!");
  Serial.print("IP adresi: ");
  Serial.println(WiFi.localIP());
}

void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  Serial2.begin(9600, SERIAL_8N1, 16, 17);
  connectToWiFi();
}

void loop() {
  // WiFi bağlantı durumunu kontrol et ve gerekirse yeniden bağlan
  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("WiFi bağlantısı kesildi, yeniden bağlanılıyor...");
    connectToWiFi();
  }

  // UART üzerinden gelen veriyi alma
  if (Serial2.available() > 0) {
    String receivedData = Serial2.readString();
    Serial.println("Arduino Mega'dan Gelen Veri: " + receivedData);

    if (receivedData.indexOf("+") != -1 && receivedData.indexOf("*") != -1 && receivedData.charAt(0) == '+') {
      Serial.println("Tahmin verisi geldi: " + receivedData);
      String inputString = receivedData;
      String extractedString = "";
      int startIndex = inputString.indexOf('+') + 1;
      int endIndex = inputString.indexOf('*') - 1;

      Serial.println(startIndex);
      Serial.println(endIndex);
      Serial.println("-----------------------------------------product count total");

      String numberStringArray[10];
      if (startIndex != -1 && endIndex != -1) {
        extractedString = inputString.substring(startIndex, endIndex);
      }
      int arrayIndex = 0;
      int commaIndex = 0;
      while ((commaIndex = extractedString.indexOf(',')) != -1) {
        numberStringArray[arrayIndex++] = extractedString.substring(0, commaIndex);
        extractedString = extractedString.substring(commaIndex + 1);
      }
      numberStringArray[arrayIndex] = extractedString;

      int productnumberArray[arrayIndex + 1];
      for (int i = 0; i <= arrayIndex; i++) {
        productnumberArray[i] = numberStringArray[i].toInt();
      }

      for (int x = 0; x <= arrayIndex; x++) {
        Serial.print(productnumberArray[x]);//bu ürün üretim sayı dizisi
        Serial.print(" ");
      }

      Serial.println("-------------------------months");
      String extractedString2 = "";
      int startIndex2 = inputString.indexOf('*') + 1;
      int endIndex2 = inputString.lastIndexOf('+');
      String months[12];
      if (startIndex2 != -1 && endIndex2 != -1) {
        extractedString2 = inputString.substring(startIndex2, endIndex2);
      }

      int arrayIndex2 = 0;
      int commaIndex2 = 0;
      while ((commaIndex2 = extractedString2.indexOf(',')) != -1) {
        months[arrayIndex2++] = extractedString2.substring(0, commaIndex2);
        extractedString2 = extractedString2.substring(commaIndex2 + 1);
      }
   //Serial.println("arrayIndex2:"+arrayIndex2);
      int monthsInt[arrayIndex2];
      for (int i = 0; i <arrayIndex2; i++) {
        monthsInt[i] = months[i].toInt();
      }

      for (int i = 0; i <arrayIndex2; i++) {
        Serial.print(monthsInt[i]);//bu hangi ay olduğunu söyler 
        Serial.print(" ");
      }
Serial.print("gemini kısnmı");
      // Verileri işleme
        // Verileri işleme
       res = R"raw(      1.yıl:
[[1, 1, 1], [2, 22, 1], [3, 31, 1], [4, 3, 1], [5, 45, 1], [6, 12, 1], [7, 12, 1], [8, 22, 1], [9, 12, 1], [10, 12, 1], [11, 22, 1], [12, 232, 1],
 [1, 21, 2], [2, 31, 2], [3, 4, 2], [4, 41, 2], [5, 52, 2], [6, 4, 2], [7, 66, 2], [8, 8, 2], [9, 35, 2], [10, 45, 2], [11, 126, 2], [12, 178, 2],
 [1, 64, 3], [2, 516, 3], [3, 718, 3], [4, 24, 3], [5, 567, 3], [6, 24, 3], [7, 23, 3], [8, 23, 3], [9, 34, 3], [10, 1213, 3], [11, 113, 3], [12, 234, 3],

2.yıl:
[[1, 53, 1], [2, 50, 1], [3, 160, 1], [4, 210, 1], [5, 26, 1], [6, 43, 1], [7, 35, 1], [8, 214, 1], [9, 204, 1], [10, 39, 1], [11, 87, 1], [12, 44, 1],
 [1, 171, 2], [2, 205, 2], [3, 24, 2], [4, 24, 2], [5, 223, 2], [6, 111, 2], [7, 7, 2], [8, 227, 2], [9, 123, 2], [10, 184, 2], [11, 63, 2], [12, 26, 2],
 [1, 123, 3], [2, 121, 3], [3, 145, 3], [4, 122, 3], [5, 182, 3], [6, 143, 3], [7, 160, 3], [8, 145, 3], [9, 193, 3], [10, 118, 3], [11, 171, 3], [12, 167, 3],



	===>bu veri kümesi sırası ile son üç yıla dayanır,iki boyutlu dizinin içindeki dizilerdeki ilk eleman yılın kaçıncı ayı olduğunu,ikinci eleman ürün sayısını,üçüncü eleman ise ürün idsini verir buna göre bir dahaki yıl benzer şartlar altında  1,2,3 ürün idli ürünlerden yılın  dokuz ayına göre  kaç tane üretilir ,her ay için  json formatı halinde sadece üçüncü yılın tahminini döndür?
	

)raw"; //bunu farklı raw string tanımlarsak   iç kısma girmiyor( if (Serial2.available() > 0) {)




 // Belirli bir süre bekleyin, ardından isteği gönderin
  unsigned long currentMillis = millis();
  if (currentMillis - lastRequestTime >= requestInterval && res.length() > 0) {
  Serial.println("\niç kısımdayız...");
    lastRequestTime = currentMillis;
String geminiresult ="x";//gemini cevap
int guessNumber[9][3];// Bu matrix, 9 satır ve 3 sütuna sahip bir urunSayilari adında bir 3 boyutlu dizi tanımlar.bu matrix ürün tahmin aylık sayılarını tutacak
/*
int urunSayilari[9][3] = {
  {134, 124, 114}, // 1. ay
  {126, 124, 147}, // 2. ay
  {185, 180, 210}, // 3. ay
  {145, 142, 167}, // 4. ay
  {164, 160, 187}, // 5. ay
  {148, 145, 170}, // 6. ay
  {197, 191, 222}, // 7. ay
  {178, 174, 198}, // 8. ay
  {169, 165, 189}  // 9. ay
};
*/


do{ 
    // HTTPS isteği başlatın
    HTTPClient https;
   if (https.begin("https://generativelanguage.googleapis.com/v1beta/models/gemini-1.5-flash:generateContent?key=" + String(Gemini_Token))) {

    https.setTimeout(15000); //isteğe zamanlama koydum
  https.addHeader("Content-Type", "application/json");
  //String payload = R"raw({"contents": [{"parts":[{"text": ")" + res + R"raw("}]}],"generationConfig": {"maxOutputTokens": )raw" + String(Gemini_Max_Tokens) + R"raw(}})raw";
String payload = "{\"contents\": [{\"parts\":[{\"text\": \"" + res + "\"}]}],\"generationConfig\": {\"maxOutputTokens\": " + String(Gemini_Max_Tokens) + "}}";

  int httpCode = https.POST(payload);
  Serial.println(https.errorToString(httpCode).c_str());
  if (httpCode == HTTP_CODE_OK || httpCode == HTTP_CODE_MOVED_PERMANENTLY) {


String payload = https.getString();

    // JSON verisini işleyin
    DynamicJsonDocument doc(2048); // Bellek boyutunu artırın
    DeserializationError error = deserializeJson(doc, payload);
    if (error) {
      Serial.print("JSON ayrıştırma hatası: ");
      Serial.println(error.c_str());
      return;
    }
    String Answer = doc["candidates"][0]["content"]["parts"][0]["text"];
// gemini cevap işleme
   geminiresult = extractBetweenTripleBackticks(Answer);
  
    // Yanıtı seri monitöre yazdırın
    Serial.println("Yanıtınız: ");
    Serial.println(Answer);
    Serial.print("*********************************************************gemini cevap işleme:");
    Serial.println(geminiresult);
            if(geminiresult!="x")
            { 
//gemini iştediğim json formatındfa alınmıştır?

 // JSON verisini ayrıştırma
  DynamicJsonDocument jsongemini(2048);
  deserializeJson(jsongemini, geminiresult);


  // JSON verilerini diziye dönüştürme
  for (int i = 0; i < 9; ++i) {
    String monthKey;
    if(geminiresult.indexOf("1.ay")!=-1)
    {
 monthKey = String(i + 1) + ".ay";
    }else if(geminiresult.indexOf("1. Ay")!=-1)
    {
 monthKey = String(i + 1) + ". Ay";
    }else if(geminiresult.indexOf("1. ay")!=-1)
    {
 monthKey = String(i + 1) + ". ay";
    }
   
    JsonObject month = jsongemini[monthKey];
    
    for (int j = 0; j < 3; ++j) {
      guessNumber[i][j] = month[String(j + 1)];
    }
  }

  // Diziyi seri porta yazdırma
  for (int i = 0; i < 9; ++i) {
    Serial.print("Ay ");
    Serial.print(i + 1);
    Serial.print(": ");
    for (int j = 0; j < 3; ++j) {
      Serial.print(guessNumber[i][j]);
      Serial.print(" ");
    }
    Serial.println();
  }
Serial.println("-----------------------------------------------------------");
String guessaccuracy[3]={"yok","yok","yok"};
String esp32response="";
  // GUESS NUMBER BENİM  SONUÇLARIMI BULUP ÇIKARMA
  for(int i=1;i<=9;i++)
  { for(int j=0;j<3;j++)
          {
            //bu dongude ise monthsInt ve productnumberArray kullanacağım
            for(int x=0;x<3;x++)
            {   
                      if(monthsInt[x]==i&&(x==j))//x==j 1ürün==1ürün 
                          {
                             Serial.println(String(monthsInt[x])+". ayda ürün idsi"+String(x)+"'in*********** tahmini üretim :"+String(guessNumber[i-1][x]));
                             guessaccuracy[x]=String(guessNumber[i-1][x]-productnumberArray[x]);
                          }
                      
                    


            }
          }

  }
   Serial.println("**********----------------****************------------***************-----------************");
for(int q=0;q<sizeof(guessaccuracy)/sizeof(guessaccuracy[0]);q++)
 {
esp32response+=(guessaccuracy[q]);
Serial.println(guessaccuracy[q]);
esp32response+=",";
 }
esp32response+="finish";
Serial.print("esp32 response:");
Serial.println(esp32response);
 Serial2.println(esp32response); // Veriyi Serial2 üzerinden gönderme


            }





  } else {
    Serial.printf("[HTTPS] İstek başarısız, hata: %s\n", https.errorToString(httpCode).c_str());
  }
  https.end();
} else {
  Serial.printf("[HTTPS] Sunucuya bağlanılamıyor\n");
}


//yanıttaki ``` arasındaki ifadeleri işleme
}while(geminiresult=="x");




    res = "";
  }







  
    }
  }

  delay(1000); // CPU yükünü azaltmak için bekleme süresi
}


