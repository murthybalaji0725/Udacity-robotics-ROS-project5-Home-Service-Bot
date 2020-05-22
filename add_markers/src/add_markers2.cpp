#include <ros/ros.h>
#include <visualization_msgs/Marker.h>
#include <math.h>
#include <nav_msgs/Odometry.h> 
#include <geometry_msgs/PoseWithCovarianceStamped.h>

double x_coordinate_pickup = 3.0;
double y_coordinate_pickup = 3.0;
double x_coordinate_droppoint = -3.0;
double y_coordinate_droppoint = 3.0;
double threshold = 0.2;
double marker_size = 0.3;
bool item_pick_state = false;
bool item_drop_state = false;

void amclCallback(const geometry_msgs::PoseWithCovarianceStamped::ConstPtr& msg) {
	//checking if robot near its goals using amcl pose 
  double bot_pose_x = msg->pose.pose.position.x;
  double bot_pose_y = msg->pose.pose.position.y;
  ROS_INFO("Received nav_msgs");

    //checking if bot is within threshold range of 1 m of pickup point and and declare that it is 
  double current_pickup_distance = sqrt(pow(bot_pose_x - x_coordinate_pickup, 2) + pow(bot_pose_y - y_coordinate_pickup, 2));  
  if (current_pickup_distance < threshold) {
    item_pick_state = true;
    ROS_INFO("Hey I'm at the pickup point");
  }

   ////checking if bot is within threshold range of 1 m of droppoint point and and declare that it is 
  double current_droppoint_distance = sqrt(pow(bot_pose_x - x_coordinate_droppoint, 2) + pow(bot_pose_y - y_coordinate_droppoint, 2));
  if (current_droppoint_distance < threshold) {
    item_drop_state = true;
    ROS_INFO("Hey I'm at the drop off point");
  }
}


int main( int argc, char** argv )
{
  ros::init(argc, argv, "add_markers2");
  ros::NodeHandle n;
  ros::Rate r(1);
  ros::Publisher marker_pub = n.advertise<visualization_msgs::Marker>("visualization_marker", 1);
  ros::Subscriber amcl_sub = n.subscribe("amcl_pose", 10, amclCallback);

  visualization_msgs::Marker marker;

  // Set our initial shape type to be a cube
  uint32_t shape = visualization_msgs::Marker::CUBE;

  // Set the frame ID and timestamp.  See the TF tutorials for information on these.
  marker.header.frame_id = "map";
  marker.header.stamp = ros::Time::now();

  // Set the namespace and id for this marker.  This serves to create a unique ID
  // Any marker sent with the same namespace and id will overwrite the old one
  marker.ns = "cube";
  marker.id = 0;

  // Set the marker type.  Initially this is CUBE, and cycles between that and SPHERE, ARROW, and CYLINDER
  marker.type = shape;

  // Set the pose of the marker.  This is a full 6DOF pose relative to the frame/time specified in the header
  marker.pose.position.x = x_coordinate_pickup;
  marker.pose.position.y = y_coordinate_pickup;
  marker.pose.position.z = 0;
  marker.pose.orientation.x = 0.0;
  marker.pose.orientation.y = 0.0;
  marker.pose.orientation.z = 0.0;
  marker.pose.orientation.w = 1.0;

  // Set the scale of the marker -- 1x1x1 here means 1m on a side
  marker.scale.x = marker_size;
  marker.scale.y = marker_size;
  marker.scale.z = marker_size;

  // Set the color -- be sure to set alpha to something non-zero!
  marker.color.r = 0.0f;
  marker.color.g = 1.0f;
  marker.color.b = 0.0f;
  marker.color.a = 1.0;

  marker.lifetime = ros::Duration();
  while (ros::ok())
  {
		// Publish the marker
		while (marker_pub.getNumSubscribers() < 1)
		{
				if (!ros::ok())
				{
				return 0;
				}
				ROS_WARN_ONCE("Please create a subscriber to the marker");
				sleep(1);
		}

		if (!item_pick_state)
		{		
			//show the marker at pickup point till the item is not picked up
			marker.action = visualization_msgs::Marker::ADD;
			marker_pub.publish(marker);
			ROS_INFO("waiting for package to be picked up");
		}

		else if (!item_drop_state)
		{	//delete the marker and wait for 5 seconds to simulate pickup
			marker.action = visualization_msgs::Marker::DELETE;
			marker_pub.publish(marker);
			ROS_INFO("Wait here for picking up!");
			ros::Duration(5.0).sleep();
		}
		else
		{		
			//show marker at drop point 
			marker.pose.position.x = x_coordinate_droppoint;
			marker.pose.position.y = y_coordinate_droppoint;
			marker.action = visualization_msgs::Marker::ADD;
			marker_pub.publish(marker);
		}

		ros::spinOnce();
  }
}
