# gesture_recognition_device
This is a handheld gesture recongnition device which uses an 6 axis MPU to capture the motion and classifies it into different gestures. It uses the Random forest classifier.
Methodology

•	For training the model:
We use the Adafruit MPU6050 library to get the output data from the IMU.
•	Then we truncate it to make it not exceed specified value.
•	After that we repeatedly check if the board is in motion using the IMU data.
•	If the board is in motion then we record the data from the IMU and we store it in an array.
•	After 3 second delay we print the array on to the serial monitor where each value is separated by a comma.
•	After that we calibrate the IMU recording the data and setting a new baseline so that we can detect motion again.
•	We continue this process until we collect the required amount of data samples.
•	After that we copy the data to excel and arrange it in a dataset.
•	Now we create and store separate excel files for each gesture and store it in a folder.
•	Then we open python, select the classifier and generate the C code for the machine learning program using micromlgen.


First, we make the required gesture 15-20 times and record it.
The output on the serial monitor looks like this:

 

Then copy the data to excel with each file containing one gesture information.
 
Then arrange the data using text to columns in excel:
 
After arranging:
 
Now move all the gesture files into one folder and run the converter code in python:
 
Specify the classifier (using Random Forest) here:
 
The micromlgen converter will output the C code as text:
 

Now we copy and paste it in the Arduino IDE in a file named model.h:
 

After that in the main file we include the model:
 


•	What the code does:
The code first calibrates the IMU data.
•	Then it checks for motion by the IMU.
•	If motion is detected that is if the acceleration is greater than the set threshold then it will start recording the IMU data to an array.
•	It take around 300 samples of the 3 accelerometer axis and 3 gyroscope rotations/sec values.
•	After that it uses support vector machine classifier to determine the gesture.
•	The accuracy of the classifier is 97% according to the maker.

Now we upload the code to the microcontroller and we will get the output in the serial monitor when we perform the gesture: 	 

Output on the serial monitor:
 
The detected gesture is also printed in the screen:
 

For a wireless serial monitor we can use Telnet Stream:
 
 

THE BUILD PROCESS
1.	First we record all the part dimensions:
 
2.	Then we make the pinout table:
 
3.	After recording all the data:
 
4.	Let us make the 3D model in Fusion 360:

 

 


Now let’s start the assembly and testing:

1.	Attaching the IMU to the microcontroller to save space:
 
 
Testing the OLED display.

 
2.	3D printing the parts.
 
 

3.	Joining the buttons.
 
 
 
 

4.	Testing the IR led.
 

Making the circuit small.
 


 

5.	Making the test enclosures for the OLED display.
 


6.	3D printing the front cover.
 
 

 

7.	Final Result.
 

Features:
1.	Has 4 buttons, one for power and the rest for controlling the device:
 

2.	Two ports: One for charging and the other one for data transfer.
 
3.	Front mounted IR led to control televisions:

 

4.	Has a 128X64 pixel OLED display:
 

•	Has a 2000mAh battery.
•	Up to 24 hours of continuous usage.
•	It has Wi-Fi for communicating with computers.
•	It has deep sleep capability to save power.
•	Buzzer for audio feedback.
•	IR led for communicating with televisions.
•	Has a 6 axis IMU.
•	It has over the air (OTA) update capability.


Running the ML code on the device:
 

 


Experiments


I trained many gestures like left swipe, right swipe etc. I also trained the alphabets ‘A’ and ‘B’ to see will it recognise these too or not.


•	The device detects the correct gesture about 70 percent of the time.
•	It has problems with very similar data such as drawing different letters.
•	The user has to perform a very similar gesture as made while recording the data to make the device detect the correct one.
•	A change in the start time of the recording leads to incorrect classification. So, it is configured to start recording as soon as it detects motion.



Comparative study

The creator of the ML program Eloquent had more model accuracy than my model.

Kernel	C	Gamma	Degree	Vectors	Flash size	RAM (b)	Avg accuracy
RBF	10	0.001	-	37	53 Kb	1228	99%
Poly	100	0.001	2	12	25 Kb	1228	99%
Poly	100	0.001	3	25	40 Kb	1228	97%
Linear	50	-	1	40	55 Kb	1228	95%
RBF	100	0.01	-	61	80 Kb	1228	95%


 
Decision boundaries of 2 PCA components of Gestures features, RBF kernel, 0.001 gamma
 

Decision boundaries of 2 PCA components of Gestures features, RBF kernel, 0.01 gamma




My Results


11 gestures are in the dataset which are labelled 0 to 10 from top to bottom:

 

The test data was recorded separately and stored in the folder ‘testdata’
 
The classifiers tested are:
•	Random Forest
•	Multi-layer perceptron
•	Decision Tree
•	Linear Regression
•	Logistic Regression
•	Gaussian Naïve Bayes
•	Support Vector Classifier
•	Gaussian Process Classifier

Testing and Visualisation Method

•	Each classifier is trained using the dataset and then tested using the test data recorded separately.
•	The accuracy, MAE,MSE, RMSE and R2 scores are compared.
•	Scatter plot and histogram is also plotted between the actual and predicted values.
•	For visualising the classifier the data was converted into 2D data using principal component analysis.
•	Please check the .ipynb file named ‘Model Tester and Visualiser’. This file contains the code for testing and visualisation.

1.	Random Forest 

 
 
The histogram has plotted the difference between ytest and predictedvalues.

Conclusion

We have successfully implemented machine learning on a microcontroller and used it to recognise the gestures made by the user. We have also seen that Random Forest classifier gave the highest accuracy among all classifiers of 97%.
We have made a handheld device which can recognise the gestures and send it to a computer as an input device. We can also control televisions using the IR sender built in to the device.


For the project files and videos, please go to this link:

https://drive.google.com/drive/folders/1BVnznAhVSvPpDGUZEza924hyiwaR41iG?usp=sharing




References

1.	Machine learning on Arduino by Eloquent:
https://eloquentarduino.github.io/2019/12/how-to-do-gesture-identification-on-arduino/#tocrun-the-inference
2.	Video tutorial by Neutrino:
https://www.youtube.com/watch?v=NuA1YfmMS0w&list=PLnE78kV3yoOCpjkf3mPX4Q4f3bYR4GM-v&index=4
3.	Tensorflow for microcontrollers:
https://blog.tensorflow.org/2019/11/how-to-get-started-with-machine.html
4.	ESP8266 and computer communication by Instructables:
https://www.instructables.com/ESP8266-and-Python-Communication-ForNoobs/

