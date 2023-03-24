# OOP-Project
A console-type application in C++, which allows the management of user profiles of an application.
Each user is identified by a unique id.

The user profile is determined based on certain characteristics measured for each user. The measured data for each user is read from the text file: **sesiuni.txt**. 
The data in the file are organized according to a standard structure decided by each individual student.

**It is assumed that the data about each user is measured and exists in that file.**

The application must create a profile of the user based on the data in the file representing the previous interactions with the application based on several indicators created by the student. After establishing the user's profile, at his future logins it is checked whether the profile corresponds to the mode of interaction in the current login. If it corresponds, it means that the user is the right one and has permission to interact with the application. If the profile does not correspond or corresponds to a low percentage, it is considered that the user logged in the application is not the right one and must be logged out of the application.
