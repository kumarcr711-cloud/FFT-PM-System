print("--- SCRIPT STARTING ---") // to confirm initialisation of the script
import paho.mqtt.client as mqtt
from influxdb_client import InfluxDBClient, Point
from influxdb_client.client.write_api import SYNCHRONOUS
import json

# --- CONFIG---
INFLUX_TOKEN = "some token id"
INFLUX_ORG = "some techy name"
INFLUX_BUCKET = "idk"
INFLUX_URL = "http:etc.."

client = InfluxDBClient(url=INFLUX_URL, token=INFLUX_TOKEN, org=INFLUX_ORG)
write_api = client.write_api(write_synchronous=SYNCHRONOUS)

print(">>> BRIDGE INITIALIZED. Waiting for MQTT...")

def on_message(client, userdata, msg):
    try:
        payload = json.loads(msg.payload)
        print(f"MQTT Data Caught: {payload}") # If you see this, MQTT is OK.
        
        # Build the point
        p = Point("vibration") \
            .tag("device", "ESP32-S3") \
            .field("x", float(payload['x'])) \
            .field("y", float(payload['y'])) \
            .field("z", float(payload['z']))
        
        # ATTEMPT WRITE
        print(f"Sending to InfluxDB bucket '{INFLUX_BUCKET}'...")
        write_api.write(bucket=INFLUX_BUCKET, org=INFLUX_ORG, record=p)
        print("✅ SUCCESS: Data is in the database!")

    except Exception as e:
        print(f"❌ DATABASE ERROR: {e}")

# MQTT Setup (Version 2)
mqtt_client = mqtt.Client(mqtt.CallbackAPIVersion.VERSION2)
mqtt_client.on_message = on_message
mqtt_client.connect("127.0.0.1", 1883, 60)
mqtt_client.subscribe("motor/vibration")

mqtt_client.loop_forever()
