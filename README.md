The aim of my project is to design an artificial intelligence supported product production management platform using Arduino and ESP32 boards. In this platform, an interface is designed to enable the user to log in to the system and after the login process, an interface is designed that provides product production information and product time information according to the user's selection from the products in the current product production list. The product production information received temporally was transmitted via UART (Serial) communication over ESP32. Using the Gemini API key, a prediction result was generated with the temporal product production data from previous years and this result was shown to the user for production comparison.


![git_arduino2](https://github.com/user-attachments/assets/9fabd5a4-26d4-442a-b99e-c1265e5f9e77)
The connections on the arduino side of the project are as in the image below:
![image](https://github.com/user-attachments/assets/2df5df39-73fc-43a6-a4f8-ad4f9246481c)
On the esp32 side, connections are made with pins G17 and G16. 

