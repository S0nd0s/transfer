/**

 * @ Author: Mariam Raouf, Mark Nagy

 * @ Create Time: 2023-12-6 

 * @ Modified by: George Bahaa

 * @ Modified time: 2024-01-28 06:02:09

 * @ Description: handling transmission of mqtt 

 */



#include <mosquitto.h>

#include <iostream>







#define MQTT_TLS_PORT 1883

#define MQTT_PORT 1883

#define SERVER_ID "SERVER_ID"

#define MQTT_TOPIC "V2X"

#define BROKER_ADDRESS "192.168.1.11"


#include <cstring>
#include <mosquitto.h>
#include <iostream>




  



    void publish(const char* topic, const char* message) {

        struct mosquitto* mosq = mosquitto_new(nullptr, true, nullptr);

        if (!mosq) {

            std::cerr << "Error: Unable to create Mosquitto client instance." << std::endl;

            return;

        }



        if (mosquitto_connect(mosq, BROKER_ADDRESS, MQTT_PORT, 0) != MOSQ_ERR_SUCCESS) {

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





int main() {

    mosquitto_lib_init();

    publish(MQTT_TOPIC, "Hello, MQTT!");
    mosquitto_lib_cleanup();
    return 0;

}

