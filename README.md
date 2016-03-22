# Field-Cuts-Encounter-6

This program (built using openFrameworks) was used in performance of Field Cuts: Encounter 6 at EMPAC Studio 2 on 03.10.2016

Footage of this performance can be found here: https://vimeo.com/159868244 

This program consists of three parts necessary for this performance:

##Devices
###fc_device
This object manages the sending of messages to each device, including the wrist packs and the torso packs (which include relay). If the device includes a relay, this class manages the duration and recovery limiting times by blocking new messages from being forwarded to the device if it is in one of these periods. 

###fc_deviceManager
This object manages all of the instances of the fc_device class.

###fc_deviceAccelParser
This object receives all the accelerometer data from all objects and sorts it int other correct fc_device object based on matching the prefix on the received data to the IP address of the device. This object is contained within the fc_deviceManager class.

##Conditions
###fc_condition
This object contains a set of parameters and variables which define a condition which creates virtual connections between input and output -- accelerometer data and relay/electrical stimulation.

###fc_conditionStream


###fc_conditionManager

##Score
###fc_scoreManager

###fc_performer
