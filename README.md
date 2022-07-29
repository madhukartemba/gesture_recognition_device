# gesture_recognition_device

<br><br>
Video Link: https://youtu.be/z1BC8VKuFR8
<br><br>


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

 ![datapic](https://user-images.githubusercontent.com/97425422/177105462-cc709fec-1d59-440a-b5b7-686f8605cf52.PNG)


Then copy the data to excel with each file containing one gesture information.

![datacollectionpic](https://user-images.githubusercontent.com/97425422/177105494-1db035b7-417e-4107-aa39-b371b10c5e7c.PNG)

 
 
Then arrange the data using text to columns in excel:
![dataarrange](https://user-images.githubusercontent.com/97425422/177105515-37b16767-c283-4ab8-8bc1-9f12bdd677bc.PNG)

![dataarrange2](https://user-images.githubusercontent.com/97425422/177105519-3b661bca-4a60-49f4-a6bd-89279fd7e012.PNG)

After arranging:


![dataarrange3](https://user-images.githubusercontent.com/97425422/177105528-c2f17d1e-fec2-4839-aa78-538898059630.PNG)

Now move all the gesture files into one folder and run the converter code in python:
 
Specify the classifier (using Random Forest) here:
 
The micromlgen converter will output the C code as text:
 

Now we copy and paste it in the Arduino IDE in a file named model.h:
 

After that in the main file we include the model:
 
![include model](https://user-images.githubusercontent.com/97425422/177107599-b1ba464a-946e-4f9c-b23c-327b42c41f55.PNG)

![include model classifier](https://user-images.githubusercontent.com/97425422/177107607-a75f2eeb-0434-42af-b7cc-d541368e655a.PNG)

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
1.	First we record all the part dimensions.

 ![dimension pic 1](https://user-images.githubusercontent.com/97425422/177107676-dabdd6c9-b1d7-47e7-b41b-8bb10e1fdae9.PNG)

2.	Then we make the pinout table.

 ![pinout](https://user-images.githubusercontent.com/97425422/177107659-b486f856-e37d-4c33-8be9-a2773246939a.PNG)

3.	After recording all the data.

 ![dataarrange3](https://user-images.githubusercontent.com/97425422/177107710-5dc9865c-0ff7-4e8a-87ed-d483446073b9.PNG)

4.	Let us make the 3D model in Fusion 360.

 ![Screenshot (33)](https://user-images.githubusercontent.com/97425422/177105103-11d6c8e4-4712-4f40-bca4-d05aa5d3262e.png)


 


Now let’s start the assembly and testing:

1.	Attaching the IMU to the microcontroller to save space:

![20210325_211555](https://user-images.githubusercontent.com/97425422/177103886-692eca23-a50a-43c7-a3aa-13fbca75da96.jpg)

 
Testing the OLED display.


 
2.	3D printing the parts.
 
  ![Screenshot (30)](https://user-images.githubusercontent.com/97425422/177103727-ee78d4ec-d6fe-4caf-8cca-94b74daef98b.png)
 

3.	Joining the buttons.
 
 
 ![20210327_110243](https://user-images.githubusercontent.com/97425422/177103918-1a66db74-7150-4383-80d6-928968482b04.jpg)

 ![20210327_111027](https://user-images.githubusercontent.com/97425422/177103935-2e764f32-ce13-4d5b-a575-92f8566dc49a.jpg)


4.	Testing the IR led.

 ![LED Test](https://user-images.githubusercontent.com/97425422/177104133-2b585124-7ddd-4392-ad64-ad144be1f5cd.PNG)

 

Making the circuit small.
 
![20210327_120047](https://user-images.githubusercontent.com/97425422/177104166-a9971fdf-cf72-46d9-acd7-762fd2af065d.jpg)

 

5.	Making the test enclosures for the OLED display and 3D printing the front cover.

![20210328_104503](https://user-images.githubusercontent.com/97425422/177104516-ed3872cb-a2b8-4e55-8b66-8c352158e185.jpg)

![20210327_234927](https://user-images.githubusercontent.com/97425422/177104216-ed97f249-b33a-4b63-858d-8a0f10caab1b.jpg)
 
![20210328_013757](https://user-images.githubusercontent.com/97425422/177104234-67867e3d-79ae-4972-b746-becb746260ca.jpg)


6. Assmebling all the parts together.

 ![20210327_135714](https://user-images.githubusercontent.com/97425422/177104175-b535ca78-ed9c-45cc-86c9-d90feabf9846.jpg)

 

7.	Final Result.

![20210328_122717](https://user-images.githubusercontent.com/97425422/177104605-e9b8dc5b-66a3-4baf-9b8e-936c1c613eb3.jpg)

 ![20210328_122723](https://user-images.githubusercontent.com/97425422/177104612-d0778f0a-be19-4bed-8315-2272fb0c2887.jpg)
 
![20210328_123549](https://user-images.githubusercontent.com/97425422/177104622-43499782-c5ed-4588-9a3b-d5d441d5935e.jpg)

![Screenshot (35)](https://user-images.githubusercontent.com/97425422/177104669-05b68f40-a340-4ccd-a291-41a6dbe2e21c.png)

Features:
1.	Has 4 buttons, one for power and the rest for controlling the device:
 
 ![20210412_185006](https://user-images.githubusercontent.com/97425422/177105156-1a9b4b68-04c5-4271-bd91-bcb8ad5ee5e2.jpg)

2.	Two ports: One for charging and the other one for data transfer.

 ![20210412_185054](https://user-images.githubusercontent.com/97425422/177105179-e47b6840-b56a-4de2-82c2-b8bd6364c3e5.jpg)

3.	Front mounted IR led to control televisions.

 ![20210412_185023](https://user-images.githubusercontent.com/97425422/177105163-632fc592-b5c7-4a12-828a-3bae04da5c88.jpg)


4.	Has a 128X64 pixel OLED display.
 ![20210412_185035](https://user-images.githubusercontent.com/97425422/177105190-b7ac9aef-238d-4c5d-a611-a0a5df659fe3.jpg)


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

Kernel	C	Gamma	Degree	Vectors	Flash size	RAM (b)	Avg accuracy <br>
RBF	10	0.001	-	37	53 Kb	1228	99%<br>
Poly	100	0.001	2	12	25 Kb	1228	99%<br>
Poly	100	0.001	3	25	40 Kb	1228	97%<br>
Linear	50	-	1	40	55 Kb	1228	95%<br>
RBF	100	0.01	-	61	80 Kb	1228	95%<br>


 
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

