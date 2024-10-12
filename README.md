<!DOCTYPE html>
<html lang="en">

<h1>Advanced Self-Sustaining Agriculture Automation</h1>

<p>
    <strong>Author:</strong> Varad Chaskar<br>
    <strong>Date:</strong> 5 Mar 2023<br>
    <strong>Version:</strong> 14
</p>

<h2>Project Overview</h2>

<p>
    This project aims to automate various agricultural processes to create a self-sustaining environment.
    It controls devices like UV lights, water pumps, air pumps, and fans based on real-time environmental
    conditions and predefined time schedules. The system uses sensors to monitor temperature, humidity,
    water levels, light intensity, and vibrations to make informed decisions.
</p>

<h2>Key Features</h2>

<ul>
    <li><strong>Automatic Control:</strong> Automatically manages actuators based on sensor data and time.</li>
    <li><strong>Manual Override:</strong> Allows manual control of devices via serial commands.</li>
    <li><strong>Real-Time Monitoring:</strong> Displays current time, temperature, humidity, and water levels on an OLED screen.</li>
    <li><strong>Modular Design:</strong> Organized into separate modules for better maintainability and scalability.</li>
</ul>

<h2>Hardware Components</h2>

<ul>
    <li>Arduino Board</li>
    <li>DHT11 Temperature and Humidity Sensor</li>
    <li>LDR Sensor (Light-Dependent Resistor)</li>
    <li>Vibration Sensor</li>
    <li>Water Level Sensor</li>
    <li>UV Light</li>
    <li>Air Pump</li>
    <li>Fan</li>
    <li>Water Pump</li>
    <li>RTC Module (DS3231)</li>
    <li>OLED Display (SSD1306)</li>
</ul>

<h2>Software Libraries</h2>

<ul>
    <li><code>Arduino.h</code></li>
    <li><code>Wire.h</code></li>
    <li><code>SPI.h</code></li>
    <li><code>Adafruit_GFX.h</code></li>
    <li><code>Adafruit_SSD1306.h</code></li>
    <li><code>RTClib.h</code></li>
    <li><code>dht.h</code></li>
</ul>

<h2>File Structure</h2>

<ul>
    <li><code>main.cpp</code>: Main program that initializes hardware and runs the control loop.</li>
    <li><code>hardware.h</code> / <code>hardware.cpp</code>: Manages hardware initialization and actuator control.</li>
    <li><code>sensors.h</code> / <code>sensors.cpp</code>: Handles sensor data acquisition.</li>
    <li><code>constants.h</code>: Contains configuration constants and pin definitions.</li>
</ul>

<h2>Getting Started</h2>

<h3>Prerequisites</h3>

<ul>
    <li>Arduino IDE installed on your computer.</li>
    <li>Required Arduino libraries installed:
        <ul>
            <li>Adafruit GFX Library</li>
            <li>Adafruit SSD1306 Library</li>
            <li>RTClib</li>
            <li>DHT Sensor Library</li>
        </ul>
    </li>
</ul>

<h3>Installation</h3>

<ol>
    <li>Clone or download the repository to your local machine.</li>
    <li>Open the project in the Arduino IDE.</li>
    <li>Ensure all the hardware components are connected to the correct pins as defined in <code>constants.h</code>.</li>
    <li>Compile and upload the code to your Arduino board.</li>
</ol>

<h2>Usage</h2>

<h3>Automatic Control</h3>

<p>
    By default, the system operates in automatic mode, controlling all devices based on sensor readings and time schedules.
</p>

<h3>Manual Control</h3>

<p>
    You can manually control the devices using serial commands sent via the Arduino IDE's Serial Monitor or any serial terminal.
</p>

<h4>Serial Commands</h4>

<ul>
    <li><code>A</code> or <code>a</code>: Toggle automatic control mode.</li>
    <li><code>B</code> or <code>b</code>: Toggle UV light.</li>
    <li><code>C</code> or <code>c</code>: Toggle air pump.</li>
    <li><code>D</code> or <code>d</code>: Toggle fan.</li>
    <li><code>E</code> or <code>e</code>: Toggle water motor.</li>
</ul>

<h2>Code Explanation</h2>

<h3>1. constants.h</h3>

<p>
    Defines all the pin configurations and constant values used throughout the project. This makes it easy to change hardware connections or configuration settings from a single file.
</p>

<h3>2. hardware.h and hardware.cpp</h3>

<p>
    Contains functions responsible for initializing hardware components and controlling actuators like the UV light, air pump, fan, and water motor based on sensor readings and time schedules.
</p>

<h3>3. sensors.h and sensors.cpp</h3>

<p>
    Manages all sensor readings, including temperature, humidity, water level, LDR value, and vibration value. Provides getter functions to access these readings from other modules.
</p>

<h3>4. main.cpp</h3>

<p>
    The entry point of the program. It initializes the system and contains the main control loop. The loop reads sensor data, updates actuator statuses, handles serial input for manual control, and updates the OLED display.
</p>

</body>
</html>
