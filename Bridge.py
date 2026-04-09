import paho.mqtt.client as mqtt
from influxdb_client import InfluxDBClient, Point
import json

# 1. Load your pre-trained model (from your NASA script)
# model = load_my_nasa_model('model.pkl')

def on_message(client, userdata, msg):
    # Decode the JSON coming from the ESP32
    data = json.loads(msg.payload)
    
    # Run the NASA-based AI logic
    # prediction = model.predict(data['metrics']['rms'])
    
    # 2. Format for InfluxDB
    point = Point("vibration_health") \
        .tag("device", data['device_id']) \
        .field("rms", data['metrics']['rms']) \
        .field("kurtosis", data['metrics']['kurtosis']) \
        .field("rul_estimate", 42.5) # Example RUL from AI
    
    # 3. Write to Database
    # write_api.write(bucket="deathdream_data", record=point)
    print(f"Data Processed: {data['metrics']['rms']} RMS")

# Setup MQTT Listener
client = mqtt.Client()
client.on_message = on_message
client.connect("localhost", 1883)
client.subscribe("factory/motor1/telemetry")
client.loop_forever()
