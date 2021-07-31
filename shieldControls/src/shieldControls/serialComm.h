
#include "common.h"

const byte COMM_MSGSIZE = 16;
String commMessage = "";      // a String to hold incoming serial data/messages
char msgTerminator1 = '\n';   // signifies the end of a message
char msgTerminator2 = '\r';   // signifies the end of a message

void loop_comms() {
    while (Serial.available() > 0) {
        char inChar = (char)Serial.read();
        if (inChar == msgTerminator1 || inChar == msgTerminator2) {
            // We have a full message. Handle the message

            // Check for static messages
            if (commMessage == "reset") {
              resetMcu();
            }
            

            // Check for dynamic messages
            switch (commMessage[0]) {
                
                // Identifier request
                case '@': {
                    // Someone has asked us to identify ourselves.
                    // Turn off all reporting so that the requesting computer sees our message
                    buttonMessagesEnabled = false;
                    Serial.println("AmongUs-ShieldControls");
                    break;
                }
                
                // Button Operations
                case 'B': {
                    switch (commMessage[1]) {
                        // Change verbosity
                        case 'V': {
                            switch (commMessage[2]) {
                                case '0': {
                                  // Turn OFF BTN messages
                                  buttonMessagesEnabled = false;
                                  Serial.println("Button Messages - OFF");
                                  break;
                                }
                                case '1': {
                                  // Turn ON BTN messages
                                  buttonMessagesEnabled = true;
                                  Serial.println("Button Messages - ON");
                                  break;
                                }
                                default: {
                                  // Bad message
                                  Serial.println("[Button Messages] bad message");
                                  break;
                                }
                            }
                            break;
                        }

                        // Write to EEPROM
                        case 'E': {

//                            switch(commMessage[2]) {
//
//                                // Update the Circumference of the Wheel
//                                case 'C' : {
//                                    String sValue = commMessage.substring(3);
//                                    float value = sValue.toFloat();
//                                    // If value is good, store it to EEPROM
//                                    // If no valid conversion could be performed because the String doesn’t start with a digit, a zero is returned. Data type:
//                                    if (value > 0) {
//                                        storeWheelCircumference(value);
//                                    } else {
//                                        Serial.println("[COMM] Setting Wheel Circumference failed: sValue=\"" + sValue + "\", value=" + String(value));
//                                    }
//                                    break;
//                                }
//                                
//                                // Update the TicksPerRevolution in EEPROM
//                                case 'T': {
//                                    String sValue = commMessage.substring(3);
//                                    int value = sValue.toInt();
//                                    // If value is good, store it to EEPROM
//                                    // If no valid conversion could be performed because the String doesn’t start with a digit, a zero is returned. Data type:
//                                    if (value > 0) {
//                                        storeTicksPerRev(value);
//                                    } else {
//                                        Serial.println("[COMM] Setting TicksPerRevolution failed: sValue=\"" + sValue + "\", value=" + String(value));
//                                    }
//                                    break;                                    
//                                }                    
//                            }                            
                            break;
                        }
                    }
                    break;
                }

//                // Commit all data to EEPROM
//                case 'C': {
//                    // All interrupts must be stopped before accessing flash
//                    EEPROM.commit();
//                    
//                    // Re-enable interrupts                    
//                    break;
//                }
                
                case '~': {
                    // Reset the MCU
                    resetMcu();
                    break;
                }
                
                default: {
                    Serial.println("\"" + commMessage + "\" is not a valid message");
                    break;
                }
            }

            // Message has been processed. Clear it
            commMessage = "";
        } else {
            // Not the end of the message. Append the character and move on
            commMessage += inChar;
        }
    }
}
