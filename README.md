# Udacity Robotics Software Engineer Nanodegree Program Project 5 - Home Service Robot
## Intro
The task of this project was to use create a robot in a virtual environment along with a virtual object. The task of the robot was to navigate to the initial goal position, pick up the object and drop it off at the next goal postion. It had to do that while navigating the enviroment on it own. The robot is able to perform Simulataneous Localisation and Mapping or SLAM.
![Screenshot of the robot performing path planning and SLAM](https://github.com/murthybalaji0725/udap5/blob/master/Extra%20file/path%20planning%201.png)

## The robot performed :
1. Localisation using AMCL
2. SLAM using Gmapping package with uses a Grid Based FastSLAM 
3. Navigation using Dijkstra's algorithm

## Running the project 
Assuming ROS Kinetic has already been installed
1. Create a workspace directory and clone the packages
```
catkin_ws/src
cd catkin_ws/src
catkin_init_workspace
git clone https://github.com/murthybalaji0725/udap5.git
cd ..
catkin_make
```
2. Under catkin_ws,
```
source devel/setup.bash
cd scripts
```
3.  To test the home_service.sh 
```
./home_service.sh
```
To test SLAM 
```
./test_slam.sh
``` 
Navigate to the xterm terminal running keyboar_teleop. Instruction on how to control the robot are provided there.
    
To test navigation 
```
./test_navigation.sh
```
Give a few seconds for all the terminals to open and applications to start.
    
## ROS Packages used
###### GMapping 
[Documentation available here](http://wiki.ros.org/gmapping)
The package provides laser-based SLAM. Using slam_gmapping, you can create a 2-D occupancy grid map. This is  
###### turtlebot_teleop
[Documentation available here](http://wiki.ros.org/turtlebot_teleop)
Allows user to control the robot using commands from joystick or keyboard.
###### turtlebot_rviz_launchers
[Documentation available here](http://wiki.ros.org/turtlebot_rviz_launchers)
It contains the `view_navigation.launch` file using which can we load a preconfigured RViz workspace. It automatically loads the RobotModel, Trajectory, Maps and other relevant things in thr RViz workspace and saves lots of time 
###### turtlebot_gazebo
[Documentation available here](http://wiki.ros.org/turtlebot_rviz_launchers)
One of the most important packages. We can deploy the turtlebot in gazebo with our own custom world file. 
