# Udacity Robotics Software Engineer Nanodegree Program Project 5 - Home Service Robot
## Intro
The task of this project was to use create a robot in a virtual environment along with a virtual object. The task of the robot was to navigate to the initial goal position, pick up the object and drop it off at the next goal postion. It had to do that while navigating the enviroment on it own. The robot is able to perform Simulataneous Localisation and Mapping or SLAM.

## The robot performed :
1. Localisation using AMCL
2. SLAM using Gmapping package with uses a Grid Based FastSLAM 
3. Navigation using Dijkstra's algorithm

## Running the project 
Assuming ROS Kinetic has already been installed
1. Create a workspace directory 
```
catkin_ws/src
cd catkin_ws/src
catkin_init_workspace
git clone https://github.com/murthybalaji0725/udap5.git
cd ..
catkin_make
```

## ROS Packages used
###### GMapping
The package provides laser-based SLAM. Using slam_gmapping, you can create a 2-D occupancy grid map. This is  
###### GMapping
###### GMapping
###### GMapping
