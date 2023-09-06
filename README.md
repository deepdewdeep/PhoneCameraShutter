# Remote Mobile Camera Shutter

## Overview

The **Remote Mobile Camera Shutter** is a groundbreaking project that leverages the power of the ESP32 microcontroller and Arduino IDE to create a Bluetooth Low Energy (BLE) Human Interface Device (HID). This innovative device transforms your smartphone into a versatile and remote-controlled camera, adding convenience and creativity to your mobile photography and videography experiences.

**Key Features:**

- **Extended Range:** Experience unprecedented wireless freedom with a range of up to 100 meters in open spaces and approximately 10 meters in closed environments. Say goodbye to limitations and capture moments from unique perspectives.

- **Vlogger and YouTuber Companion:** For content creators who rely on their smartphones, the Remote Mobile Camera Shutter is a game-changer. Start and stop video recording remotely, achieving professional-quality content effortlessly.

- **Custom Hardware:** Powered by the ESP32-WROOM-32D microcontroller, this device combines robust processing capabilities with energy efficiency. Its low power consumption ensures long-lasting performance.

- **Elegant Enclosure:** The 3D-printed enclosure not only protects the internal components but also adds a touch of style to your mobile photography and videography setup.

- **Long Battery Life:** Thanks to efficient power management and a high-capacity 3.7V 802540 600mAh Li-Po battery, you can enjoy extended usage on a single charge.

- **Open Source:** I believe in the spirit of collaboration, and this project is open source, inviting fellow makers and enthusiasts to contribute and customize.

**Technical Insights:**

The Remote Mobile Camera Shutter is built upon the principles of BLE HID (Bluetooth Low Energy Human Interface Device). It relies on a range of libraries to create a Bluetooth keyboard that sends keypress events when a button is pressed and released. Here are some technical highlights:

- **BLE Library Integration:** The project utilizes various libraries for seamless interaction with BLE and HID devices, ensuring a robust and reliable connection.

- **BLE Server Callbacks:** Callback functions are defined to handle device connections and disconnections. When a device connects, it enables notifications on the input report, enhancing communication efficiency.

- **Output Callbacks:** The project manages data written to the output report, logging special keys received during operation.

- **taskServer Function:** This function serves as the core of the project. It initializes the BLE server, configures the HID device, defines the report map for the keyboard, and initiates advertising of the HID service. Additional settings such as manufacturer information, PnP ID, HID info, and security parameters are also established here.

- **setup Function:** The setup function is the heart of the Arduino setup routine. It initializes serial communication, configures the button pin as an input, attaches an interrupt to the button pin, sets up the LED pin, and creates a task to execute the taskServer function.

- **loop Function:** The loop function represents the primary execution loop of the project. It continuously checks if the button is pressed (btnFlag is set) and whether a BLE device is connected (connected is true). When both conditions are met, it emulates keypress events by manipulating values in the input report, notifies the change, briefly waits, and then releases the key. Visual feedback is provided through LED toggling.

- **pushButton Function (Interrupt Handler):** The pushButton function serves as an interrupt handler, responsible for setting the btnFlag when the button is pressed. It also detaches the interrupt to prevent multiple triggers.

In summary, the Remote Mobile Camera Shutter empowers you to redefine your mobile photography and videography experiences. With an extended wireless range, effortless remote control, and an open-source foundation, this project invites you to explore new horizons in smartphone content creation.

![shutter](https://github.com/deepdewdeep/PhoneCameraShutter/assets/56537975/31b3923a-5b25-4e3f-a4ff-34998637e3c5)

*Capture moments from a distance and revolutionize your content creation with the Remote Mobile Camera Shutter.*


## Circuit Design and Component Selection

The circuit design of the Remote Mobile Camera Shutter combines efficiency, reliability, and low power consumption to deliver a compact and versatile solution for mobile photography enthusiasts. Here, I'll explore key components and design choices that make this project a reality.

### Power Supply with Li-Po Battery

The device is powered by a high-capacity 3.7V 802540 600mAh Li-Po battery, ensuring extended usage between charges. This lightweight and compact power source provides reliable energy for your photography and videography adventures. The power management circuitry efficiently utilizes the Li-Po battery's capacity while maintaining stable voltage levels.

### Power Regulation with TPS7A2033PDBVR

One of the critical components in the circuit is the **TPS7A2033PDBVR Low Dropout Regulator**. This regulator ensures stable and reliable power distribution throughout the system, regardless of the battery voltage. Key features of this regulator include:

- **Low Dropout Voltage:** The TPS7A2033PDBVR boasts a low dropout voltage, minimizing wasted energy and maximizing battery life, a crucial factor for extended usage without frequent recharging.

- **Efficiency:** The regulator's high efficiency contributes to overall power savings, making it an ideal choice for battery-powered applications.

- **Voltage Stability:** It maintains a stable output voltage, ensuring that the ESP32-WROOM-32D microcontroller and other components operate within their specified voltage range.

### ESP32-WROOM-32D Microcontroller

The heart of the Remote Mobile Camera Shutter is the **ESP32-WROOM-32D microcontroller**. This choice was made for several reasons:

- **Low Power Consumption:** The ESP32-WROOM-32D is known for its energy efficiency, making it suitable for battery-powered devices. It can operate in low-power modes, extending the device's runtime on a single charge.

- **Serial Programming:** Serial pins are used to program the microcontroller, allowing for easy firmware updates and customization.

## PCB Design

The PCB design of the Remote Mobile Camera Shutter is a testament to efficiency and compactness. I've carefully selected and integrated Surface Mount Device (SMD) components to optimize the device's size and performance. SMD components are renowned for their smaller form factor and reliability, making them ideal for projects where space is a premium.

**Key PCB Design Highlights:**

- **Compact Form Factor:** I've meticulously designed the PCB to minimize its footprint while maximizing functionality. The compact size ensures that the Remote Mobile Camera Shutter is easy to carry and integrate into your mobile photography setup.

- **Surface Mount Devices (SMD):** SMD components play a pivotal role in achieving the device's compactness. These components are soldered directly onto the surface of the PCB, eliminating the need for bulky through-hole components.

- **Strength Where It Matters:** While I've embraced SMD components for their space-saving advantages, I've strategically used Surface Mount Technology (SMT) components in areas where physical strength and reliability are crucial. This hybrid approach ensures that the device can withstand everyday use and potential wear and tear.

- **Two-Layer PCB:** The circuit design is implemented on a two-layer PCB. This design choice strikes a balance between complexity and simplicity, making the PCB layout more accessible for hobbyists and makers while maintaining high performance.

- **Designed with Altium Designer (Version 22.4.2):** The PCB layout and design were meticulously crafted using Altium Designer, version 22.4.2, a leading electronic design automation software. Altium Designer enabled me to create a PCB layout that optimized signal integrity and minimized interference.

![Screenshot 2023-09-06 180453](https://github.com/deepdewdeep/Remote-Mobile-Camera-Shutter/assets/56537975/c3b1d5b9-ae9e-4c21-85ec-3f60c6e39e69)

## Enclosure Design

The enclosure design of the Remote Mobile Camera Shutter serves both protective and aesthetic purposes. It not only shields the device's internal components but also offers design choices to cater to different preferences and functional requirements.

### Dual Design Approach

I've adopted a dual design approach, offering two distinct enclosure designs:

1. **Minimalist Design:** This design emphasizes simplicity and functionality. It provides a clean and unobtrusive look, ensuring that the Remote Mobile Camera Shutter integrates seamlessly with your setup. It prioritizes a sleek, understated appearance.

2. **User-Attractive Design:** In contrast, the user-attractive design focuses on aesthetics and visual appeal. It's ideal for users who want their device to stand out as a stylish accessory. This design adds an element of style while maintaining functionality.

### Solidworks Software

To create these enclosures, I rely on **Solidworks**, a professional 3D modeling and design software known for its precision and versatility. Key aspects of my enclosure design process using Solidworks include:

- **Precision Fit:** Every enclosure is designed to provide a precise fit for all internal components. This ensures that the device is securely housed within and well-protected.

- **Customization:** Solidworks allows me to tailor the enclosures to specific design requirements. I can accommodate different button layouts, LED placements, and access points, ensuring flexibility and functionality.

- **Durability:** The enclosures are engineered to withstand daily usage and potential impacts, safeguarding the internal electronics effectively.

<img src="https://github.com/deepdewdeep/Remote-Mobile-Camera-Shutter/assets/56537975/5f4b1448-929e-4229-b352-2047ba4f52f0" alt="image" width="200" />
<img src="https://github.com/deepdewdeep/Remote-Mobile-Camera-Shutter/assets/56537975/afdf3d44-b108-4a25-b837-8413cabb7d6d" alt="image" width="200" />




## Conclusion

The **Remote Mobile Camera Shutter** project represents the fusion of innovation, versatility, and open-source collaboration. Designed to amplify your mobile photography and videography experiences, this device redefines how you interact with your smartphone's camera. With an impressive extended range, seamless Bluetooth connectivity, and user-friendly features, it unlocks a world of possibilities for content creators, photographers, vloggers, and enthusiasts.

By choosing an open-source approach, I invite the maker community to join me in refining and customizing the Remote Mobile Camera Shutter. Whether you're a seasoned developer looking to contribute to the codebase or a hobbyist eager to build your own remote camera controller, this project provides a valuable platform for exploration and learning.

As technology continues to shape the way we capture and share moments, the Remote Mobile Camera Shutter stands as a testament to the endless possibilities of DIY electronics and the collaborative spirit of the maker community. Embrace the freedom to capture, create, and innovate with the Remote Mobile Camera Shutter.

I hope this project inspires you to embark on your own journey of exploration and creativity in the world of embedded systems and mobile content creation. Share your experiences, ideas, and improvements, and together, we can push the boundaries of what's possible with technology.

Thank you for joining me on this exciting venture. Now, it's your turn to capture the extraordinary, one remote click at a time.
