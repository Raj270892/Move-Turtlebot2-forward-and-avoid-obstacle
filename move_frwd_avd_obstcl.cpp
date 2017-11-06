//**************************************************************************
//Filename	:move_frwd_avd_obstcl.cpp.
//Objective	:Move turtlebot2 forward and avoid obstacle.
//Author	:Raj Gupta.
//Description: 	This node using a map already build to move Robot forward 
//		by a certain distance.
//		To Do this move_base node is used. When a goal is set using 
//		move base it automatically map the turtlebot2 and
//		create a paath plan to move it to the desired goal. 
//References	:
//**************************************************************************


#include<ros/ros.h>
#include<move_base_msgs/MoveBaseAction.h>
#include<actionlib/client/simple_action_client.h>

typedef actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> MoveBaseClient;

int main(int argc, char** argv)
{
   ros::init(argc,argv,"move_frwd_avd_obstcl");

   MoveBaseClient mbc("move_base",true);       // Tells to communicate with actionlib in move_base namespace and spin a thread by default
   while(!mbc.waitForServer(ros::Duration(5.0)))		//Wait for 5 seconds for to connect to actionlib server 
   {
      ROS_INFO("Waiting for actionlib server to come up");
   }

   move_base_msgs::MoveBaseGoal goal;   //Create an object goal of type MoveBaseGoal.
					// Used to define the goal of robot.
   goal.target_pose.header.frame_id = "base_link";
   goal.target_pose.header.stamp = ros::Time::now(); // set time as current time.
   
   goal.target_pose.pose.position.x= 5.0; // Tell bot to move 10 meter ahead.
   goal.target_pose.pose.orientation.w= 1.0; // give orientataion of turtlebot2 when it reaches the destination.

   ROS_INFO("Sending Goal to Robot");
   mbc.sendGoal(goal);	//Send the goal to actionlib server.

   mbc.waitForResult();  // Blocks until this goal finishes

   if(mbc.getState() ==actionlib::SimpleClientGoalState::SUCCEEDED)  //get the status set by actionlib depending on weather goal is achieved or not
      ROS_INFO("Robot Reached Destination");
   else
      ROS_INFO("FAILED");

   return 0;
}
   

