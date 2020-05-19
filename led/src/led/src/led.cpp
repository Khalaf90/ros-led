#include "ros/ros.h"
#include "std_msgs/Bool.h"
#include "std_msgs/String.h"

#include "wiringPi.h"

//Wiring PI 1
#define LED 6 // ==> GPIO 25

bool is_recording=false;
ros::Subscriber sub1;
 
void recording_callback(const std_msgs::String::ConstPtr& msg)
{

    //  is_recording=true;
}

void blink_callback(const std_msgs::Bool::ConstPtr& msg)
{
 
        if (sub1.getNumPublishers() > 0)  
         {
             is_recording=true;
             //ROS_INFO("/begin_write being published");
         }

else if  (sub1.getNumPublishers() == 0) // shutting down the recording node
    {
            is_recording=false;
             //ROS_INFO("/begin_write stop being published");
    }


  if(( msg->data == 1) && ( is_recording==true)) 
    {
     	 digitalWrite (LED, HIGH) ;
    	  //ROS_INFO("LED ON");
    } 
 

  else if(( msg->data == 1) && ( is_recording==false))
    {
     	  digitalWrite (LED, HIGH) ;
    	  ros::Duration(1.0).sleep(); //delay(1000);
     	  digitalWrite (LED, LOW) ;
      	  ros::Duration(1.0).sleep(); //delay(1000);

    	  //ROS_INFO("LED Blink");
    }

 
else if ( msg->data == 0) 
    {
     	 digitalWrite (LED, LOW) ;
      	 //ROS_INFO("LED OFF");
    }
 
else 
 {
    // Do nothing
 }


int main(int argc, char** argv)
{
    ros::init(argc, argv,"blink_led1");
    ROS_INFO("Started Cam_1 Blink Node");
    wiringPiSetup();
    pinMode(LED, OUTPUT);
    ros::NodeHandle n;

    // Subscriber to isrecord Message.
    sub1 = n.subscribe("/begin_write",10,recording_callback);

    // Subscriber to isalive Message.
    ros::Subscriber sub2 = n.subscribe("/ir/flir_tau2/isalive",10,blink_callback);

    ros::spin();
}




