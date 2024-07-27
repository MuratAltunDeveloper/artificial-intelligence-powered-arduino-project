#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Wire.h>
#include <SPI.h>
#include <DHT.h>
#include <Fonts/FreeSerif9pt7b.h>
#include <Arduino.h>
//Yapaya Zeka ve Wifi için gerekli eklemeler ve açiklamalar
//********----------*****************---------------***********-----------**********---------
//Esp32 ile internet ve gemini apiye bağlan oradan yapay zeka ile veriyi işle ve ardunioyaya gönder
// Blynk  diye bir şey var bunla esp32 kontrol edebilirsin

//EKRANIN GENİSLİK VE YUKSEKLİK
#define ekrangenislik 128
#define ekranyukseklik 64
//sabitler
const int asagibuton=2;
const int yukaributon=4;
const int onaybuton=7;
byte menu=0;
byte menu2=0;
int giris=0;
//üRÜN KATEGORİSİNİN TANIMLANMASI
//char* products[] = {"hidrofor sistemi", "elektrik pano", "yangın", "pompa", "converter", "dataloger"};
char* products[] = {"1","pano sistem", "dataloger", "pompa sistem","geri"};
int productscounter[]={-1,-1,-1};//üretilen ürün sayısı dizisi
//Bir
int  whichMonths[]={0,0,0};
//şeçilen ürün kategorisi
int choseProduct=0;
//ürün sayfasına ğeçiş için
int bottombuton=0;
int upbuton=0;
int pagecroos=0;
// üretime harcanan zaman
int prdtime=0;//==>ÜRETİME HARCANAN ZAMAN aylik olarak
int cnttime=0;
//ekran tanımlama
Adafruit_SSD1306 ekran(ekrangenislik,ekranyukseklik, &Wire, -1);
//anaSayfaya çıkmak için flag tanımı
bool rtnMainPage=true;
bool rtnMainPage2=true;
int control=0;
bool state=true;
bool control_cikis=true;
//Oluşturacağım dizi ilk sutunu  bir ay veya yıl olması ile ilgili,ikinci sütun ürün sayısı
// 8x2 boyutlarında bir iki boyutlu dizi tanımlama

int matrix [8][2] = {
   {1,9},
   {12,11}, 
   {1,3},
   {12,7},
   {12,23},
   { 12,190},
   { 1,29},
   {12,2}
   

};














void setup() {
  
  // put your setup code here, to run once:
if(!ekran.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { 
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }


ekran.clearDisplay();
//ekran ozellikleri


pinMode(asagibuton,INPUT);
pinMode(yukaributon,INPUT);
pinMode(onaybuton,INPUT);

Serial.begin(9600);




}

void loop() {


  // put your main code here, to run repeatedly:
giris++;

if(giris==1)
{



while(1)
{
//ekran özelliklerini belirle

//ekran.setFont(&FreeSerif9pt7b);//font ayarı
ekran.clearDisplay();//ekranı temizle
ekran.setTextSize(1);//yazı tipi boyutu1
ekran.setTextColor(WHITE);//renk beyaz 
ekran.setCursor(0,0);



ekran.println("is ");
ekran.println("  Sistemi");





//butonları okuma
int yukaributonbas=digitalRead(yukaributon);
int asagibutonbas=digitalRead(asagibuton);
int onaybutonbas=digitalRead(onaybuton);




if(yukaributonbas==1)//sagbutona basma durumu
{
menu++;
if(menu>=1)
{menu=1;}

}

if(asagibutonbas==1)//sol butona basma durumu
{
menu--;
if(menu>=2)
{
  menu=0;
}


}

if(onaybutonbas==1)
{
  if(menu==1)
  {
   Predictionfunc();//tahmin yapma
  }
  if(menu==0)
  {
     

Asamasec();

//Serial.println("ana ekran SEVIYESINDEN CIKTI");










  }
}





if(menu==0)
{
ekran.println("tahminler");
ekran.println(">urunler");
}
else if(menu==1)
{
ekran.println(">tahminler");
ekran.println("urunler");
}


 
ekran.display();

}

}



















}

void Asamasec()
{



// zorluk seviyesini secmewhile(true)
//Serial.println("asama SEViYESiNE GIRDI");

int yukaributonbas;
int asagibutonbas;
int onaybutonbas;
int art=0;
int mantik=1;
//ekranlar arası geçiş kısmı için
int screen_switch=0;
//Serial.println(("go go go go go"));
while(mantik)
{
art++;

yukaributonbas=digitalRead(yukaributon);
asagibutonbas=digitalRead(asagibuton);
onaybutonbas=digitalRead(onaybuton);
if(art==1)
{
  onaybutonbas=0;

  delay(500);
}

/*
Serial.println("-------------------------------------------");
Serial.println("yukaributon2:");
Serial.println(yukaributonbas);
Serial.println("asagibuton2:");
Serial.println(asagibutonbas);
Serial.println("onaybuton2:");
Serial.println(onaybutonbas);
Serial.print("-------->");
*/

ekran.clearDisplay();//ekranı temizle
ekran.setTextSize(1);//yazı tipi boyutu1
ekran.setTextColor(WHITE);//renk beyaz 
ekran.setCursor(0,20);






if(yukaributonbas==1)//sagbutona basma durumu
{
menu2++;
if(menu2>=1)
{menu2=1;}

}

if(asagibutonbas==1)//sol butona basma durumu
{
menu2--;
if(menu2>=2)
{
  menu2=0;
}


}

if(menu2==0)
{
ekran.println("urun");
ekran.println(">geri");


delay(1);
}
else if(menu2==1)
{
ekran.println(">urun");
ekran.println("geri");



delay(1);
}

if(onaybutonbas==1)//onay butonuna basma
{
  if(menu2==1)
  { 
    
 
 int numProducts=sizeof(products) / sizeof(products[0]);
screen_switch = 1;
  int currentPos = 0;
  int lineHeight = 16; // Her ürün arasındaki dikey boşluk

  while (state) {

    ekran.clearDisplay(); // Ekranı temizle
    ekran.setTextSize(1); // Yazı tipi boyutu 1
    ekran.setTextColor(WHITE); // Beyaz renk
    ekran.setCursor(0, 0); // Başlangıç konumu

    // Font ayarı
    ekran.setFont(&FreeSerif9pt7b);
    if(control>=2)
    {control--;
      rtnMainPage=true;
     
      Serial.println("RTNMAİNPAGE  TRUE TRUE TRUE");
    }


    // Yukarı butonu basıldığında
    if (digitalRead(yukaributon) == 1) {
      upbuton++;
      currentPos -= 17; // Metni 2 piksel yukarı kaydır
      if (currentPos < 0) {
        currentPos = 0;
      }
      delay(20); // Giriş yanlış okumalarını önlemek için kısa bir gecikme
    }

    // Aşağı butonu basıldığında
    if (digitalRead(asagibuton) == 1) {
      bottombuton++;
      currentPos += 17; // Metni 2 piksel aşağı kaydır
      int maxPos = (numProducts - 1) * lineHeight; // Maksimum kaydırma limiti
      if (currentPos > maxPos) {
        currentPos = maxPos;
      }
      delay(20); // Giriş yanlış okumalarını önlemek için kısa bir gecikme
    }

    // Ürünleri ekrana yazdırma
    for (int i = 0; i < numProducts; i++) {
       ekran.setCursor(0,16);
       ekran.print("                     <-");
       
      
      int yPos = i * lineHeight - currentPos;
      if (yPos >= 0 && yPos < 64) {
        ekran.setCursor(0, yPos);
        //Serial.print("currentPos2=>");Serial.println(currentPos);
        ekran.println(products[i]);
      
 



      }
  
    if(digitalRead(onaybuton)==1)
    {Serial.println("onaylama  ürün listesi");
   Serial.println(String(pagecroos)+"-"+String(bottombuton)+"-"+String(upbuton)+"-"+String(rtnMainPage));

pagecroos++;
    if(pagecroos>1&&(bottombuton>=1||upbuton>=1))
    { 
      
    
      //onay butonuna bastı çıkmak için geri ve 130 fazla aşağı derinlikte
       if( (currentPos>45))
       {
           //Serial.println("artık bu adam tahmin Ekranına tekrar gelip tahmin yapmalı");
            //ekran.clearDisplay(); // Ekranı temizle
           state=false;
    ekran.clearDisplay(); // Ekranı temizle
    ekran.setTextSize(1); // Yazı tipi boyutu 1
    ekran.setTextColor(WHITE); // Beyaz renk
    ekran.setCursor(0, 20); // Başlangıç konumu

        break;
    
       }
     
      
      
      
      
      
      
      
      
      
      pagecroos=0;
      bottombuton=0;
      upbuton=0;
      choseProduct=(currentPos)/16;//0 olursa 2 ürün,1 olursa 3 ürün
      Serial.print("choseProduct:");Serial.println(choseProduct);
                      //Bu ürÜn sayfası ile alakalı
            int productpage=0;              
while(true&&rtnMainPage)
{
          Serial.println("uretim ve zaman secim");
   
            ekran.clearDisplay(); // Ekranı temizle
            ekran.setTextSize(1); // Yazı tipi boyutu 1
            ekran.setTextColor(WHITE); // Beyaz renk
            ekran.setCursor(0, 0); // Başlangıç konumu

            // Font ayarı
            ekran.setFont(&FreeSerif9pt7b);

                      
            if(digitalRead(yukaributon)==1)//sagbutona basma durumu
            {
            productpage++;
            if(productpage>=1)
            {productpage=1;}

            }

            if(digitalRead(asagibuton)==1)//sol butona basma durumu
            {
            productpage--;
            if(productpage>=2)
            {
              productpage=0;
            }


            }

            if(productpage==0)
            {ekran.println("   ");
            ekran.println("uretim");
            ekran.println(">zaman secim");
            delay(1);
       
            }
            else if(productpage==1)
            {
              ekran.println("       ");
            ekran.println(">uretim");
            ekran.println("zaman secim");
            delay(1);
            
            }
//onay butonuna basılana kadar
        if(digitalRead(onaybuton)==1)
              {
//uretim aşamasımı zaman aşamasımı
if(productpage==1)
  {control_cikis=true;
  ProductManager(choseProduct);
  }
  if(productpage==0 )
  {control++;
    TimeManager(choseProduct);
    //TimeMANAGER DEN SONRA ANA SAYFAYA DÖNÜYOR
     
  }










              }


  delay(100);
  ekran.display();

          
    }









        












      







    }
      



    }
    }
  
   







   Serial.print("currentPos:");
    Serial.println(currentPos);
    ekran.display();

    delay(100);
  }

   //Serial.println("£££££££££££££££££££££££££££££££££££££££££££££££££");














  }
  if(menu2==0)
  {screen_switch=1;
   // Serial.println("!!!!!!!!!!!!!!!!!!!!!!!!2 asama");
    delay(500);

//break;
  }
}
Serial.println("SORUN YOK");
//ekran değişti bir şeçim oldu

if(screen_switch==1)
{
//baslangic degerlerini ayarlama
screen_switch=0;
menu=0;
giris=0;
menu2=0;
state=true;



//burada ana sayfa dönme işlemleri kısmı
//ekran.setFont(&FreeSerif9pt7b);//font ayarı

while(1)
{
ekran.clearDisplay();//ekranı temizle
ekran.setTextColor(WHITE);//renk beyaz 
ekran.setTextSize(1);//yazı tipi boyutu1
ekran.setCursor(0,0);

//ekran özelliklerini belirle






ekran.println("is   Sistemi");





//butonları okuma
int yukaributonbas=digitalRead(yukaributon);
int asagibutonbas=digitalRead(asagibuton);
int onaybutonbas=digitalRead(onaybuton);




if(yukaributonbas==1)//sagbutona basma durumu
{
menu++;
if(menu>=1)
{menu=1;}
delay(200);
}

if(asagibutonbas==1)//sol butona basma durumu
{
menu--;
if(menu>=2)
{
  menu=0;
}
delay(200);

}

if(onaybutonbas==1)
{
  if(menu==1)
  {

delay(30);
Predictionfunc();
  }
  if(menu==0)
  {
   
ekran.clearDisplay();//ekranı temizle
ekran.setTextSize(1);//yazı tipi boyutu1
ekran.setTextColor(WHITE);//renk beyaz 
ekran.setCursor(0,15);
Asamasec();

//Serial.println("ana ekran SEVIYESINDEN CIKTI");










  }
  delay(100);
}





if(menu==0)
{
ekran.println("tahminler");
ekran.println(">urunler");
delay(20);
}
else if(menu==1)
{
ekran.println(">tahminler");
ekran.println("urunler");
delay(20);
}


 
ekran.display();

}






































}





ekran.display();
//Serial.println("menu2=");Serial.print(menu2);







}


}





void ProductManager(int whichproduct) {
  
  Serial.println("Product Manager");
  int uretilenproduct=productscounter[whichproduct];

  
  int cntrmanage = 0;

  while (control_cikis) {
    ekran.clearDisplay(); // Ekranı temizle
    ekran.setTextSize(1); // Yazı tipi boyutu 1
    
      if(productscounter[whichproduct]<0)
       {
        productscounter[whichproduct]=0;
       }



    if (cntrmanage == 0) {
    ekran.setCursor(0, 16); // Başlangıç konumu

    // Ürün sayaçlarını ekrana yazdırma
    char buffer[20];
    sprintf(buffer, ">artir %d     ", productscounter[whichproduct]);
    ekran.println(buffer);
    //Serial.print("ürün sayısı:");
    //Serial.print(productscounter[whichproduct]);
    //Serial.print("hangi ürün:");Serial.println(whichproduct);
    ekran.setCursor(0, 32);
    ekran.println("azalt");
    ekran.setCursor(0, 48);
    ekran.println("cikis");
    delay(20);
    }


    if (cntrmanage == 1) {
       ekran.setCursor(0, 16);
       ekran.println("artir");
      ekran.setCursor(0, 32);
        // Ürün sayaçlarını ekrana yazdırma
    char buffer[20];
   
       sprintf(buffer, ">azalt %d     ", productscounter[whichproduct]);
       ekran.println(buffer);
       //Serial.print("ürün sayısı:");
       //Serial.print(productscounter[whichproduct]);
       //Serial.print("hangi ürün:");Serial.println(whichproduct);
    
      ekran.setCursor(0, 48);
      ekran.println("cikis");
      delay(20);
    } else if (cntrmanage == 2) {
      ekran.setCursor(0, 16);
      ekran.println("artir");
      ekran.setCursor(0, 32);
      ekran.println("azalt");
      ekran.setCursor(0, 48);
      ekran.println(">cikis");
      delay(20);
    }

    ekran.display(); // Ekranı güncelleyin

    //Serial.print("cntrmanage: ");
    //Serial.println(cntrmanage);

    if (digitalRead(yukaributon) == HIGH) { // yukaributon basma durumu
      cntrmanage--;
      delay(200); // Debounce için kısa bir gecikme
    }

    if (digitalRead(asagibuton) == HIGH) { // asagibuton basma durumu
      cntrmanage++;
      delay(200); // Debounce için kısa bir gecikme
    }

    if (cntrmanage < 0) cntrmanage = 0;
    if (cntrmanage > 2) cntrmanage = 2;

    if (digitalRead(onaybuton) == HIGH) {
          if (cntrmanage == 0) {
        productscounter[whichproduct]++;
      } else if (cntrmanage == 1) {
        productscounter[whichproduct]--;
      }else if (cntrmanage == 2) {
         control_cikis=false;
      
      }

Serial.print("products counter:");Serial.println(productscounter[whichproduct]);Serial.print("hangi ürün:");Serial.println(whichproduct);

    }

    delay(10); // Döngü gecikmesi
  }












}

void TimeManager(int whichPrd){

Serial.println(("time manager       time manager"));
int twoCntOnayBtn=0;
int cnt=0;
cnttime++;
while(cnttime>1)
{
//ekran özelliklerini belirle

ekran.setFont(&FreeSerif9pt7b);//font ayarı
ekran.clearDisplay();//ekranı temizle
ekran.setTextSize(1);//yazı tipi boyutu1
ekran.setTextColor(WHITE);//renk beyaz 
ekran.setCursor(0,40);





if(digitalRead(yukaributon)==1)//sagbutona basma durumu
{
cnt++;
if(cnt==1)
{
  cnt=1;
}else if(cnt==2)
{
  cnt=2;
}else if(cnt==3)
{
  cnt=3;
}else if(cnt==4)
{
  cnt=4;
}else if(cnt==5)
{
  cnt=5;
}else if(cnt==6)
{
  cnt=6;
}else if(cnt==7)
{
  cnt=7;
}else if(cnt==8)
{
  cnt=8;
}else if(cnt>=9)
{
  cnt=9;
}

}

if(digitalRead(asagibuton)==1)//sol butona basma durumu
{
cnt--;
if(cnt<=0)
{
  cnt=1;
}else if(cnt==1)
{
  cnt=2;
}else if(cnt==2)
{
  cnt=3;
}else if(cnt==3)
{
  cnt=4;
}else if(cnt==4)
{
  cnt=5;
}else if(cnt==5)
{
  cnt=6;
}else if(cnt==6)
{
  cnt=7;
}else if(cnt==7)
{
  cnt=8;
}else if(cnt==8)
{
  cnt=9;
}

}

if(digitalRead(onaybuton)==1)
{//Serial.println("onay time");
twoCntOnayBtn++;
if(twoCntOnayBtn>1)
{
 if(cnt==1)
{
  cnt=1;
cnttime=0; 
rtnMainPage=false;

    
break;
}else if(cnt==2)
{
  cnt=2;
cnttime=0; 
rtnMainPage=false;

    
break;
}else if(cnt==3)
{
  cnt=3;
cnttime=0; 
rtnMainPage=false;

    
break;
}else if(cnt==4)
{
  cnt=4;
cnttime=0; 
rtnMainPage=false;

    
break;


}else if(cnt==5)
{
  cnt=5;
cnttime=0; 
rtnMainPage=false;

    
break;
}else if(cnt==6)
{
  cnt=6;
cnttime=0; 
rtnMainPage=false;

    
break;


}else if(cnt==7)
{
  
  cnt=7;
cnttime=0; 
rtnMainPage=false;

    
break;


}else if(cnt==8)
{
  cnt=8;
cnttime=0; 
rtnMainPage=false;

    
break;


}else if(cnt==9)
{
  cnt=9;
  
cnttime=0; 
rtnMainPage=false;

    
break;


}

}

}







if(cnt==1)
{
  whichMonths[whichPrd]=1;
 ekran.println("ocak");
 delay(20);
}else if(cnt==2)
{  whichMonths[whichPrd]=2;
  ekran.println("subat");
 delay(20);
}else if(cnt==3)
{  whichMonths[whichPrd]=3;
  ekran.println("mart");
 delay(20);
}else if(cnt==4)
{  whichMonths[whichPrd]=4;
 ekran.println("nisan");
 delay(20);
}else if(cnt==5)
{  whichMonths[whichPrd]=5;
  ekran.println("mayis");
 delay(20);
}else if(cnt==6)
{  whichMonths[whichPrd]=6;
  ekran.println("haziran");
 delay(20);
}else if(cnt==7)
{  whichMonths[whichPrd]=7;
  ekran.println("temmuz");
 delay(20);
}else if(cnt==8)
{  whichMonths[whichPrd]=8;
  ekran.println("agustos");
 delay(20);
}else if(cnt==9)
{  whichMonths[whichPrd]=9;
  ekran.println("eylul");
 delay(20);
}

ekran.display();

delay(200);
}




}
void Predictionfunc()
{
int yukaributonbas=digitalRead(yukaributon);
int asagibutonbas=digitalRead(asagibuton);
int onaybutonbas=digitalRead(onaybuton);



  //ekrana basılacak dizi
String ekranArray[4];
  //ekran ayarlamaları
  
  ekran.clearDisplay();//ekranı temizle
  ekran.setTextSize(1);//yazı tipi boyutu1
  ekran.setTextColor(WHITE);//renk beyaz 
  ekran.setCursor(0,10);




  
   int productguess[3];
  String datagemini="bos";
    String elements[3];
    int count = 0;




//whichmonths ve product counter gönder
//esp32 ye soruyu gönderme
String ai_data="+";

//Serial.println("productscounter:");
for(int x=0;x<3;x++)
{
  ai_data+=productscounter[x];
  ai_data+=",";
}ai_data+="*";
//Serial.println("whichMonths:");
for(int y=0;y<3;y++)
{
ai_data+=whichMonths[y];
ai_data+=",";
}
ai_data+="+";

Serial.println(ai_data);  // Seri1 portu üzerinden ESP32'ye veri gönder


//***************************ESP32 DEN GELEN VERİYİ ALMA KISMI
  while (true) {
    if(Serial.available() > 0)
    {
        String receivedData = Serial.readStringUntil('\n');  // ESP32'den gelen veriyi oku
    Serial.println("ESP32'den gelen veri: " + receivedData);  // Veriyi USB üzerinden seri monitöre yazdır
  //  ekran.println(receivedData);
   
    if(receivedData.indexOf("finish") != -1)
{ datagemini=receivedData;
  break;
}
    } 
    delay(1000);  // 1 sn bekle
  
  }
Serial.println("esp32 data data data data !!!!!!!!!!!!!!!!!!!!!!!!!!1 geldi data işleme");
//butonları okuma

//geminiden gelen veriyi al bos değilse
if(datagemini.indexOf("bos") == -1)
                                {
                          int startIndex = 0;
                          int endIndex = 0;

                          while (endIndex >= 0) {
                            endIndex = datagemini.indexOf(',', startIndex);
                            if (endIndex == -1) {
                              elements[count] = datagemini.substring(startIndex);
                            } else {
                              elements[count] = datagemini.substring(startIndex, endIndex);
                            }
                            startIndex = endIndex + 1;
                            count++;
                          }

                          int intCount = 0;
                          for (int i = 0; i < (count-1); i++) {
                            if (elements[i] != "finish") {
                              Serial.println("üretim ile tahmin kıyaslaması "+String(i)+" . ürün idsinde:"+String(elements[i]));
                                    if(elements[i]!="yok")
                                    {
                                                    if(elements[i].toInt()>=0)//+ ise eksik üretilmiş
                                            {
                                              ekranArray[i]=String(i)+".id "+String(elements[i])+" eksik";
                                              ekran.println(String(i)+".id "+String(elements[i])+" eksik");
                                            }else //- ise fazla üretilmis
                                            {elements[i]=String(elements[i].toInt()*-1);
                                              ekranArray[i]=String(i)+".id "+String(elements[i])+" fazla";
                                              ekran.println(String(i)+".id "+String(elements[i])+" fazla");
                                            }
                                    }else
                                    {ekranArray[i]="uretim yok";
                                     ekran.println(String(i)+".id "+"uretim yok");  
                                    }
                              
                                          ekranArray[i]="geri";
                             
                              
                              delay(200);
                              intCount++;
                            }
                          }

                          

                                }

ekran.display();
delay(20000);



}











































