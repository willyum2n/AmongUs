# AmongUs
Realizing some of the "Among Us" tasks in hardware for some non-virtual fun

I'd like our kids (and adults alike) to be able to physically interact with some of the Among Us tasks. This project will realize as many of them as possible. Each task will have its own microcontroller (ESP32 using Arduino IDE) and will communicate with a main controller via TCP (Probably rPi as the main controller) The Common project will contain all of the standard communications stuff that can be shared around each microcontroller.

# Shield Task
The Shield Task is a simple UI with 7 Hexagons arranged in a hexagon. Each hexagon will be a capacitive touch button. Each button represents a section of the ship's shield in the game. During game play, when this objective is activated, different sections of the shield will be turned off or on randomly. There will be an "Active" and "Inactive" color for each button so the user can figure out what to do.

# Wiring Task
A box that can be "wired". There will be 4 cables that can be pull upwards to get connected to a port. Each port will have LEDs around it so we can randomly assign which cable should be "wired" to each port. We will use electromagnets so the cable can be connected to the port. Once the task is done, the objective will self-reset by releasing the electro-magnets and the cables will fall back into their place ready for the next player.

# Simon Task
This task has 9 buttons arranged in a square. A randomly generated 5 part sequence is displayed and the user must click them in the correct order. This will be capacitive sense as well

# Card Swipe
We have been talking about passing out cards that can track your scores and unlock more objectives/competitions

# Number Pad
We will add a number pad that has a LCD above it. The LCD display will show a random sequence that needs to be punched into the keypad. Might even do some math or puzzles that have to be keyed in

# Communications Array
We can add knobs and a OLED display for showing waveforms that have to be added/subtracted to get the communications back online
