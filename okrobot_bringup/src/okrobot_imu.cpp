// Microinfinity Cia. Ltd.
// This program demonstrates how to communicate with the CruizCore R1050 gyroscope
// This program assumes that the port 'COMM_PORT' has been properly initialized. 
// In linux this can be done is Linux using the following command line:
// 			stty -F /dev/ttyUSB0 115200 raw
// This program can be compiled using:
// 			g++ -o ccr1050 ccr1050.cpp

#include <stdio.h>      
#include <stdlib.h>     
#include <unistd.h>     
#include <sys/stat.h>   
#include <iostream>
#include <fcntl.h>
#include <string.h>
#include <math.h>
#include <ros/ros.h>
#include <sensor_msgs/Imu.h>

#define pi 3.1415926

using namespace std;

//Define constants

const char COMM_PORT[] = "/dev/ttyUSB1";
const int PACKET_SIZE = 8;

float rate_float;
float angle_float;

int packet_size = 8;
//Define global variables
int file_descriptor;

// Get a data packet and parse it
bool ccr1050_getvalue()
{
    short header;
    short rate_int;
    short angle_int;

    short check_sum;
    unsigned char data_packet[PACKET_SIZE];

    if(PACKET_SIZE != read(file_descriptor,data_packet,PACKET_SIZE))
        return false;

    // Verify data packet header
    memcpy(&header,data_packet,sizeof(short));
    if(header != (short)0xFFFF)
    {
        cout << "Header error !!!\n";
        return false;
    }

    // Copy values from data string
    memcpy(&rate_int,data_packet+2,sizeof(short));
    memcpy(&angle_int,data_packet+4,sizeof(short));
    memcpy(&check_sum,data_packet+6,sizeof(short));

    // Verify checksum
    if(check_sum != (short)(0xFFFF + rate_int + angle_int))
    {
        cout<< "Checksum error!!\n";
        return false;
    }

    // Apply scale factors
    rate_float = rate_int/100.0;
    angle_float = angle_int/100.0;

   // cout << "rate_float:" << rate_float << " [deg/sec]\t angle_float:" << angle_float << " [deg]\n";
    return true;
}


int main(int argc, char** argv)
{
    ros::init(argc, argv, "okrobot_imu");
	
    std::string serial_port; // = "/dev/ttyUSB1";
    int serial_baudrate = 115200;
    std::string frame_id;

    sensor_msgs::Imu imu_msg;

    ros::NodeHandle nh;
    ros::Publisher imu_pub = nh.advertise<sensor_msgs::Imu>("imu/data", 1000);
    ros::NodeHandle nh_private("~");
    nh_private.param<std::string>("serial_port", serial_port, "/dev/ttyUSB1");
    nh_private.param<int>("serial_baudrate", serial_baudrate, 115200);
    nh_private.param<std::string>("frame_id", frame_id, "base_link");
   // nh_private.param<int>("packet_size", packet_size, 8);



    if(-1 == (file_descriptor = open(serial_port.c_str(),O_RDONLY)))
	{
		cout << "Error opening port \n";
		cout << "Set port parameters using the following Linux command:\n stty -F /dev/ttyUSB0 115200 raw\n";
		cout << "You may need to have ROOT access";
		return false;
	}
     cout << "CruizCoreR1050 communication port is ready\n";

  while(ros::ok()){

     ccr1050_getvalue();

     cout << "rate_float:" << rate_float << " [deg/sec]\t angle_float:" << angle_float << " [deg]\n";



     imu_msg.header.stamp = ros::Time::now();
     imu_msg.header.frame_id = frame_id;


     imu_msg.orientation.x = 0.0;
     imu_msg.orientation.y = 0.0;
     imu_msg.orientation.z = sin(angle_float*pi / 360);
     imu_msg.orientation.w = cos(angle_float*pi / 360);

     imu_pub.publish(imu_msg);
        
     ros::spinOnce();

    }
	return 0;
}
