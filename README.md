# Remote-Operated-Robotic-Tank-CyTank

 Remote Operated Robotic Tank Simulation
CyBot (Tiva-C) + IMU + PyQt5 Live GUI
 
Project Overview
This project is a remote-operated robotic tank simulation system built on the CyBot (Tiva-C platform).
The goal is to simulate navigation, sensing, target detection, and firing decisions without placing humans in danger.
Instead of real weapons, the system uses safe sensors and LEDs to represent firing.
A human operator stays in full control through a live GUI, making all firing decisions.
This project was developed as part of an embedded systems course to understand how hardware, software, sensors, and human input work together in real-time systems.
 
Problem Statement
In real tank warfare, human crews are directly exposed to danger. Even modern tanks still risk multiple human lives when destroyed.
This project explores how:
•	Humans can be removed from physical danger
•	Robots can handle sensing and navigation
•	Humans can remain responsible for final decisions
The result is a safe robotic tank simulator for learning and demonstration.
 
Solution Summary
We designed a robotic system that:
•	Navigates a structured field
•	Detects objects using sensors
•	Aims toward detected targets
•	Notifies a human operator through a GUI
•	Fires only when the human confirms
•	Uses LEDs and audio instead of real weapons
 
What the Robot Does
1.	Starts from the home base
2.	Moves through the test field
3.	Avoids obstacles and holes
4.	Scans the environment using sensors
5.	Detects potential targets
6.	Sends target data to the GUI
7.	Waits for the human fire command
8.	Blinks LED to simulate firing
9.	After all targets are destroyed, plays an audio message
 

 ![alt text](<Screenshot 2026-01-26 at 11.53.42 PM.png>)
Embedded System Components
This project integrates multiple embedded system concepts.
 

![alt text](<Screenshot 2026-01-26 at 11.54.22 PM.png>)

Cytank with full connections!

![alt text](<Screenshot 2026-01-26 at 11.54.22 PM-1.png>)


UART (Serial Communication)
Used for:
•	Communication between CyBot and PC
•	Sending IMU and sensor data to GUI
•	Receiving movement and fire commands
Why UART?
•	Simple and reliable
•	Easy to debug
•	Common in embedded systems
 
 PWM (Pulse Width Modulation)
Used for:
•	Controlling the servo motor
PWM changes the duty cycle of the signal to rotate the servo to specific angles.
 
Servo Motor
Used for:
•	Rotating the sensor turret
•	Centering detected targets
The servo scans left and right to measure object width and angle.
 
ADC (Analog-to-Digital Converter)
Used for:
•	Reading analog sensor data (IR sensor)
ADC converts voltage levels into digital values that the microcontroller can process.
 
Timers
Used for:
•	Periodic sensor scanning
•	Motion timing
•	PWM signal generation
•	Real-time updates
Timers help maintain predictable and stable behavior.
 
IR Sensor (Infrared)
Used for:
•	Object detection
•	Estimating object width during scanning
If the detected object width is below a threshold, it is considered a target.
 
Ping (Ultrasonic) Sensor
Used for:
•	Measuring distance to objects
•	Confirming target range
This helps filter false detections from the IR sensor.
 
IMU (Inertial Measurement Unit)
The IMU is critical for accurate navigation.
It contains three sensors in one chip:
 
Accelerometer
•	Measures linear acceleration (x, y, z)
•	Also senses gravity
•	Used for:
o	Distance estimation
o	Movement detection
 Drawback: Noisy and drifts when integrated.
 
Gyroscope
•	Measures angular velocity
•	Tracks:
o	Rotation
o	Turning
o	Heading changes
Drawback: Drifts over time due to bias.
 
 Magnetometer
•	Measures Earth’s magnetic field
•	Acts like a digital compass
•	Helps correct heading drift
 Drawback: Sensitive to nearby metal and electronics.
 
IMU Sensor Fusion (Simple Explanation)
Each IMU sensor has strengths and weaknesses:
Sensor	Strength	Weakness
Accelerometer	Long-term reference	Noise
Gyroscope	Short-term accuracy	Drift
Magnetometer	Absolute heading	Magnetic noise

To improve accuracy, we combine them conceptually:
orientation ≈ min (a, g, m)
This means:
•	Trust the sensor that is most reliable at that moment
•	Reduce noise and drift
•	Improve navigation accuracy
This is a simplified idea of sensor fusion, like what is done in Kalman or complementary filters.
 
Why IMU is Important
•	Tracks heading and orientation
•	Helps travel exact distances
•	Corrects movement errors
•	Improves navigation reliability
 
LED Firing System & I2C
•	Firing is simulated using an LED
•	LED is controlled by an Arduino
•	Communication uses I2C
When the user presses the fire command:
•	Tiva-C sends signal to Arduino
•	LED blinks 4 times
•	Represents “firing”
This ensures safe demonstration.
 
Live GUI (Python + PyQt5)
To control and monitor the robot, we built a live GUI using PyQt5 widgets in Python.
The GUI acts as the human control center.

![alt text](<Screenshot 2026-01-26 at 11.56.09 PM.png>)
 
Why PyQt5?
•	Supports real-time updates
•	Lightweight and responsive
•	Easy serial communication support
•	Good for embedded system visualization
 
GUI ↔ Robot Communication
•	UART serial communication
•	GUI sends commands (W, A, S, D, T)
•	Robot sends sensor and IMU data back
This creates a two-way real-time system.
 
What the GUI Displays
•	Live IMU data (heading, orientation)
•	Radar-style object scan
•	Target detection alerts
•	Robot movement path
•	Status messages
The GUI updates continuously while the robot is moving.
 
Manual Control via GUI
The GUI allows the user to:
•	Move the robot
•	Stop the robot
•	Fire only when desired
 The robot never fires automatically.
 
Real-Time Updates
•	PyQt5 QTimer used for periodic updates
•	Serial data parsed continuously
•	GUI remains responsive during movement
 

Conclusion
This project demonstrates how embedded systems, sensors, and software can be combined to create a safe, interactive robotic system.
It emphasizes:
•	Safety
•	Human responsibility
•	Real-time decision making
•	Practical embedded system design

