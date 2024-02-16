# Arduino Heat Seeker

## Introduction
Welcome to Arduino Heat Seeker! Ever wondered how heat seeking missiles might work? Same here. So I took an MLX90640 IR camera and developed a solution, implemented with Arduino, which detects and tracks a heat source. As you will see, the implementation is pretty straightforward, but nonetheless pretty fun, and definitely educational. Enjoy!


![Seeker tracking the sun](images/sun_seeker.gif "Seeker tracking the sun")

As you may be able to see, if this is setup in view of the sun it will quickly lock-on. You could use any other heat source too (**_just be careful!_**), but if you don't, it's interesting to see how atmospheric and climatic conditions differ and induce noise in the image which the seeker will begin to follow erratically. 


## Background
Unlike older heat seeking missiles, the 'seeker' we will be using in this project is what is referred to as 'Imaging Infrared' (IIR). The big difference between this and older infrared sensors is that the IIR 'sees' an IR image. In this case, a 24 row by 32 column array of temperatures captured by the 768 sensor elements in the MLX90640. This is, in many ways, a conceptually simpler albeit far more powerful implementation than the old single element conical scan seekers of the Cold War.

Why am I telling you this? Fundamentally, it changes the types of algorithms we use, and frankly offers a different, arguably lower, barrier-to-entry. You don't need to have a strong grasp of signals processing to run operations on an array, for example. Moreover, it opens up a whole range of interesting possibilities for experimenting with a range of detection, tracking, and clutter rejection algorithms. In fact, if you've ever had much interest in Man Portable Air Defence Systems (MANPADS), playing with this sensor will help you understand why the newest generation are so hard to jam, and why the older ones were comparatively easier. 

## Hardware Requirements
The specific setup I used largely reflected what I had laying around, so I'll describe what I used, and also offer a more generic alternative. For my project, I used the following:

- An Adafruit PyGamer, for compute and visual output.
- A MLX90640 IR camera.
- A two-axis servo mount, with servos.
- A small bread board.
- Some jumper wires.

A more generic setup could see the PyGamer removed, and replaced by separate compute and visualisation components. This will entail changing the source code a little, but not considerably. Principally, it means that instead of the `Adafruit_Arcada` library you will probably need to use something like the `TFTLCD_Library` or `Adafruit-GFX-Library`. Check out the GitHub [repos](https://github.com/adafruit/TFTLCD-Library/tree/master/examples) for some [examples](https://github.com/adafruit/Adafruit-GFX-Library/tree/master/examples) - you will see they are pretty similar.

A generic setup might look like:

- An Adafruit Metro M4.
- An Adafruit TFT screen.
- A MLX90640 IR camera.
- A two-axis servo mount, with servos.
- A small bread board.
- Some jumper wires.

## Wiring Up
Wiring up should be pretty simple. You will need to connect the MLX90640 the PyGamer over I2C. The easiest way is by using a 4-pin JST/STEMMA connector, which plugs straight in to the PyGamer along the bottom. You could also do it via the pins. 

Next we need to power and direct the servos. This is also relatively easy. In my case, I took power from the PyGamer to a breadboard for both servos. This sorts two of the three wires. The third wire - the control wire - can be directly plugged in to the PyGamer. In this code, ports 14 and 15 are used. 

Now you just need to power the PyGamer - that's up to you, whatever you prefer!

## Running the Code 
To run the code, clone this directory, and open the Arduino IDE on the main file `heat_seeker.ino`. Before you upload the code to your chosen device, make sure you have installed all the necessary libraries. Principally those for the [PyGamer](https://learn.adafruit.com/adafruit-pygamer/using-with-arduino-ide) itself, and for driving the screen (as above). Now all you need to do is flash the device and grab a heat source! 

## To-do
- [x] Implement a basic detection algorithm.
- [x] Implement a basic tracking algorithm.
- [ ] Implement a basic clutter rejection algorithm. 
