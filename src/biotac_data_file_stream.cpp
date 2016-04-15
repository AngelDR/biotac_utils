#include "ros/ros.h"
#include "std_msgs/String.h"
#include "sr_robot_msgs/BiotacAll.h"

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
using namespace std;

// File_index
int id = 0;
// Positions of the electrodes(19)
/**double position_x_list[19] = {0.0, 0.0, -0.05, 0.3, 0.3, 0.3, -0.05, 0.3, 0.3, 0.3, -0.05, 0.3, 0.3, 0.3, 0.0, 0.0, 0.0, 0.0, 0.0};
double position_y_list[19] = {0.0, 0.0, -0.05, 0.3, 0.3, 0.3, -0.05, 0.3, 0.3, 0.3, -0.05, 0.3, 0.3, 0.3, 0.0, 0.0, 0.0, 0.0, 0.0};
double position_z_list[19] = {0.0, 0.0, -0.05, 0.3, 0.3, 0.3, -0.05, 0.3, 0.3, 0.3, -0.05, 0.3, 0.3, 0.3, 0.0, 0.0, 0.0, 0.0, 0.0}; */

void dataCallback(const sr_robot_msgs::BiotacAll& msg)
{
  //ROS_INFO("I heard");
  id++;
  ofstream tactile_file;
  std::string file_name;
  std::ostringstream oss;
  oss << "/home/anxo/Documentos/DOC/I.Pascal/probas/tactile_files/tactile_data_" << id << ".txt";
  file_name = oss.str();
  tactile_file.open (file_name.c_str());
  if(tactile_file.is_open()){
    ROS_INFO("Archivo tactil_data abierto");
    // Each line of the file corresponds to a sensor (5 sensors)
    for(int finger = 0; finger<5 ; finger++){
      for(int i=0; i<19; i++){
         tactile_file << msg.tactiles[finger].electrodes[i] << " ";
      }
      tactile_file << "\n";
    }
  }

}

int main(int argc, char **argv)
{
  ros::init(argc, argv, "biotac_data_file_stream_node");
  ros::NodeHandle n;
  ros::Subscriber sub = n.subscribe("/tactile", 1000, dataCallback);
  ros::spin();
  return 0;
}