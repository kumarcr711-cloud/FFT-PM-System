import socket
print("Testing InfluxDB Port...")
print(socket.create_connection(("127.0.0.1", 8086), timeout=5))
print("Testing MQTT Port...")
print(socket.create_connection(("127.0.0.1", 1883), timeout=5))