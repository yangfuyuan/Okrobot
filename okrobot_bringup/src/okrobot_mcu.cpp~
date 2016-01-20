#include <stdio.h>      
#include <stdlib.h>     
#include <unistd.h>     
#include <sys/stat.h>   
#include <iostream>
#include <fcntl.h>
#include <string.h>
#include <math.h>
#include <ros/ros.h>
#include <sensor_msgs/Float32.h>
#include <sensor_msgs/Int64.h>

using namespace std;

//Define constants

const char COMM_PORT[] = "/dev/ttyUSB1";
const int PACKET_SIZE = 13;

int left_int;
int right_int;

// Get a data packet and parse it
bool serial_getvalue()
{
    short header;
    short address;
    short operation;
    short left;
    short right;

    short check_sum;
    unsigned char data_packet[PACKET_SIZE];

    if(PACKET_SIZE != read(file_descriptor,data_packet,PACKET_SIZE))
        return false;

    // Verify data packet header
    memcpy(&header,data_packet,sizeof(short));
    if(header != (short)0xFC0D)
    {
        cout << "Header error !!!\n";
        return false;
    }

    // Copy values from data string
    memcpy(&address,data_packet+2,sizeof(short));
    if(address != (short)0x0001)
    {
	cout << "Address error !!!\n";
	return false;
    }
    memcpy(&operation,data_packet+4,sizeof(short));
    if(operation != (short)0x0080)
    {
	cout << "Operation error !!!\n";
	return false;
    }
    memcpy(&left,data_packet+6,sizeof(short));
    memcpy(&right,data_packet+8,sizeof(short));
    memcpy(&check_sum,data_packet+10,sizeof(short));

    // Verify checksum
    if(check_sum != (short)(0xFC0D + address + operation + left + right))
    {
        cout<< "Checksum error!!\n";
        return false;
    }

    // Apply scale factors
    left_int = left;
    left_int = right;
    //cout << "left_int:" << left_int << " [Number]\t right_int:" << right_int << " [Number]\n";
   
    return true;
}



//Define global variables
int file_descriptor;
void Leftscallback(const std_msgs::Float32::ConstPtr& left_speed)
{
    
}

void Leftscallback(const std_msgs::Float32::ConstPtr& right_speed)
{
}

int main(int argc, char** argv)
{
    ros::init(argc, argv, "okrobot_mcu");
	
    std::string serial_port; // = "/dev/ttyUSB1";
    int serial_baudrate = 115200;
    std::string frame_id;

    sensor_msgs::Imu imu_msg;

    ros::NodeHandle nh;
    ros::Publisher _Left_Encoder_pub = nh.advertise<sensor_msgs::Int64>("lwheel", 1000, queue_size = 10);
    ros::Publisher _Right_Encoder_pub = nh.advertise<sensor_msgs::Int64>("rwheel", 1000, queue_size = 10);
    
    ros::Subscriber _Left_speed_sub = n.subscribe("left_wheel_speed", 10, &Leftscanback, this);
    ros::Subscriber _Left_speed_sub = n.subscribe("right_wheel_speed", 10, &Rightscanback, this);

    ros::NodeHandle nh_private("~");
    nh_private.param<std::string>("serial_port", serial_port, "/dev/ttyUSB1");
    nh_private.param<int>("serial_baudrate", serial_baudrate, 115200);
    nh_private.param<std::string>("frame_id", frame_id, "base_link");
   // nh_private.param<int>("packet_size", packet_size, 13);


   if(-1 == (file_descriptor = open(serial_port.c_str(),O_RDWR)))
	{
		cout << "Error opening port \n";
		return false;
	}

   while(ros::ok()){
	serial_getvalue();
	cout << "left_int:" << left_int << " [Number]\t right_int:" << right_int << " [Number]\n";

   }
    
}
