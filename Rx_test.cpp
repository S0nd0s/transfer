
#include <mutex>
#include <string>
#include <iostream>
#include <mosquitto.h>

#define MQTT_PORT 8883
#define RASPI2_ID "10"
#define MQTT_TOPIC "V2X"
#define BROKER_ADDRESS "xxx.xxx.xxx.xxx"


const char *MQTT_TOPIC1 = "mqttTest";
std::mutex mtx_rx;


void Rx_init()
{
	auto res = mosquitto_lib_init();
        if (res)
        throw std::runtime_error("mosquitto lib init problem");
}

void on_message(struct mosquitto *, void *, const struct mosquitto_message *message)
{
     // Handle incoming byte array data
                if (message->payloadlen)
                {
                    uint8_t *data = static_cast<uint8_t *>(message->payload);
                     std::cout << "\nReceived message with components: ";
                     for (size_t i = 0; i < message->payloadlen; ++i)
                     {
                        std::cout << static_cast<int>(data[i]) << " ";
                     }
                   // reception.V2X_RT_MQTT_GEO_receive(message->payloadlen, data);
                    std::cout << std::endl;
                }
}




void mosq_subscriber()
{
                char gnAddressString[20];
               // uint64_t gnAddress = this->geoManagement->V2X_GEOMANAGEMENT_getgnAddress();

                //snprintf(gnAddressString, sizeof(gnAddressString), "%llu", this->geoManagement->V2X_GEOMANAGEMENT_getgnAddress());

                auto mosquitto = mosquitto_new(RASPI2_ID, true, nullptr);
                try
                {
                    int res = mosquitto_connect(mosquitto, BROKER_ADDRESS, MQTT_PORT, 0);
                    if (res)
                        throw std::runtime_error("mosquitto connect problem = " + std::to_string(res));

                    // Subscribe to two topics
                    res = mosquitto_subscribe(mosquitto, nullptr, MQTT_TOPIC1, 0);
                    if (res)
                        throw std::runtime_error("mosquitto subscribe problem for topic1 = " + std::to_string(res));

//#ifdef REAL_TEST
  //                  res = mosquitto_subscribe(mosquitto, nullptr, gnAddressString, 0);
//#else
  //                  res = mosquitto_subscribe(mosquitto, nullptr, MQTT_TOPIC2, 0);
//#endif

//                    if (res)
  //                      throw std::runtime_error("mosquitto subscribe problem for topic2 = " + std::to_string(res));

                    mosquitto_message_callback_set(mosquitto, on_message);

                    res = mosquitto_loop_forever(mosquitto, -1, 1);

                    // This point will be reached only if an error occurs in the loop
                    throw std::runtime_error("mosquitto loop problem = " + std::to_string(res));
                }
                catch (std::exception &e)
                {
                    std::cout << e.what();
                }
                mosquitto_disconnect(mosquitto);
                mosquitto_destroy(mosquitto);
            }



int main()
{ 	
	Rx_init();
	mosq_subscriber();
	return 0;


}