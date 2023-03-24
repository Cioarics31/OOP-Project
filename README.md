# OOP-Project
A console-type application in C++, which allows the management of user profiles of an application.
Each user is identified by a unique id.

The user profile is determined based on certain characteristics measured for each user. The measured data for each user is read from the text file: **sesiuni.txt**. 
The data in the file are organized according to a standard structure decided by each individual student.

**It is assumed that the data about each user is measured and exists in that file.**

The application must create a profile of the user based on the data in the file representing the previous interactions with the application based on several indicators created by the student. After establishing the user's profile, at his future logins it is checked whether the profile corresponds to the mode of interaction in the current login. If it corresponds, it means that the user is the right one and has permission to interact with the application. If the profile does not correspond or corresponds to a low percentage, it is considered that the user logged in the application is not the right one and must be logged out of the application.

For the proposed requirement I chose to create three classes:
1.ProfilBaza, in which we will retain the proposed data for comparison (number of left/right clicks and number of keys pressed);
2.ProfilAdv, in which we will store more details about the corresponding base profile (email, email verification status, number of Shift key presses, a user ID and a username for the corresponding profile);
3.DateExtra, in which the operating system from which the profile is used, the age of the profile (in seconds) and the profile ration (a ratio between the download and upload quantities, but a value for the ration will be entered directly) are stored.

Profile comparison is done by comparing the following attributes:
• Number of left clicks, looking for a difference of at least 6 clicks between profiles;
• Number of right clicks, looking for a difference of at least 6 clicks between profiles;
• Number of keys pressed, looking for a difference of at least 15 keys between profiles;

The objects of the three classes are held in an array, typical of each class. The already existing ones are correlated by a figure after the declaration of the object. For newly introduced ones, I use an index.
Whenever a new object is inserted, all three arrays are updated.
