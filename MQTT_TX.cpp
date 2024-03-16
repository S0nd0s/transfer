
#include <mosquitto.h>
#include <iostream>

class MQTT_Transmitter {
public:
    MQTT_Transmitter() {
        mosquitto_lib_init();
    }

    ~MQTT_Transmitter() {
        mosquitto_lib_cleanup();
    }

    void publish(const char* topic, const char* message) {
        struct mosquitto* mosq = mosquitto_new(nullptr, true, nullptr);
        if (!mosq) {
            std::cerr << "Error: Unable to create Mosquitto client instance." << std::endl;
            return;
        }

        if (mosquitto_connect(mosq, "192.168.142.155", 1883, 0) != MOSQ_ERR_SUCCESS) {
            std::cerr << "Error: Unable to connect to the broker." << std::endl;
            mosquitto_destroy(mosq);
            return;
        }

        if (mosquitto_publish(mosq, nullptr, topic, strlen(message), message, 0, false) != MOSQ_ERR_SUCCESS) {
            std::cerr << "Error: Unable to publish message." << std::endl;
        }

        mosquitto_disconnect(mosq);
        mosquitto_destroy(mosq);
    }
};

int main() {
    MQTT_Transmitter transmitter;
    transmitter.publish("test/topic", "Hello, MQTT!");
    return 0;
}



