/* /* /**
 * @ Author: Mariam Raouf, Mark Nagy
 * @ Create Time: 2023-12-6 
 * @ Modified by: George Bahaa
 * @ Modified time: 2024-01-28 06:02:09
 * @ Description: handling transmission of mqtt 
 */
/*
#include "../inc/MQTT_TX.h"
#include <mosquitto.h>
#include <iostream>


namespace ara
{
    namespace v2x
    {
        namespace mqtt
        {
            uint32_t MQTT_TX::trans = 0;

            MQTT_TX::MQTT_TX()
            {
                auto res = mosquitto_lib_init();
                if (res)
                    throw std::runtime_error("mosquitto lib init problem");
            }

            MQTT_TX::~MQTT_TX() = default;

            void MQTT_TX::mosq_publisher(uint8_t *packet, uint16_t length,const char* topic)
            {
                auto mosquitto = mosquitto_new(SERVER_ID, true, nullptr);
                try
                {
                    int res = mosquitto_connect(mosquitto, BROKER_ADDRESS, MQTT_PORT, 0);
                    if (res)
                        throw std::runtime_error("mosquitto connect problem = " + std::to_string(res));
                    res = mosquitto_publish(mosquitto, nullptr, topic, length, packet, 0, false);
                    std::cout << "Publisher Transaction Id: " << trans << std::endl;
                    trans++;
                    if (res)
                        throw std::runtime_error("mosquitto publish problem = " + std::to_string(res)); 
                }
                catch (std::exception &e)
                {
                    std::cout << e.what();
                }
                mosquitto_disconnect(mosquitto);
                mosquitto_destroy(mosquitto);
            }
        }
    }
}  */


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



