import serial
import time
import requests

# Replace 'COM8' with your Arduino's COM port
arduino = serial.Serial('COM8', 9600)

# Firebase database URL and API key
FIREBASE_URL = "https://gas-leak--iot-default-rtdb.firebaseio.com/"
API_KEY = "AIzaSyB0MruOVRIEFYYw0PneG_Ai2T2mgLtOc5I"

def send_to_firebase(data):
   
    try:
        # Firebase endpoint for the data (e.g., "arduino_data")
        url = f"{FIREBASE_URL}/arduino_data.json?auth={API_KEY}"

        # Payload to send
        payload = {"timestamp": int(time.time()),
                    "Actuel Leaking Time": time.strftime('%Y-%m-%d %H:%M:%S', time.localtime()),
                    "Sensor State": data}

        # Send POST request to Firebase
        response = requests.post(url, json=payload)
        
        if response.status_code == 200:
            print("Data successfully sent to Firebase:", response.json())
        else:
            print("Failed to send data to Firebase:", response.text)
    except Exception as e:
        print("Error sending data to Firebase:", str(e))

while True:
    try:
        # Read and decode the data from Arduino
        data = arduino.readline().decode().strip()
        print("Read from Arduino:", data)

      

        # Send the data to Firebase
        send_to_firebase(data)

    except KeyboardInterrupt:
        print("Exiting...")
        arduino.close()
        break
