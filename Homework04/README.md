Use 'make' to build the program.

Once built, you can run ./hw4 without an arguments to start the program.

Part 1
-------
First, the Beaglebone will wait until the button connected to the designated GPIO pin is pressed. The stepper motor
will then begin to spin.

Part 2
-------
As the motor spins, it will average the voltage created by the phototransistors on the two designated analog in pins.
After it is finished spinning, it will report the lowest voltage detected (in mV) and the 'index' around its spin
it was detected.

Part 3
-------
After the first spin, the IR source should have been detected. The motor will then reverse direction until the sensor
is again facing the IR source (i.e. the 'index' found in Part 2).

Part 4
-------
Now, the motor and sensors will track the IR source. Should the source be detected by the right sensor, the motor
will begin spinning anticlockwise. should it be detected by the left sensor, the motor will spin clockwise.
