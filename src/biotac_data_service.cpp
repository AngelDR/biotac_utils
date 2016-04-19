#include "ros/ros.h"
#include "std_msgs/String.h"
#include "sr_robot_msgs/BiotacAll.h"

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
using namespace std;



class NodeClass {

private:

public:
  ros::NodeHandle n;
  ros::Subscriber sub;


    //Constructor
  NodeClass()
  {
    ;
  }


  void dataCallback(const sr_robot_msgs::BiotacAll& msg)
  {

    std::string name_param;
    ROS_INFO("Callback iniciado");

    for(int finger = 0; finger<5 ; finger++){
        switch (finger){
          case 0: name_param = "/biotac_electrodes_ff";break;
          case 1: name_param = "/biotac_electrodes_mf";break;
          case 2: name_param = "/biotac_electrodes_rf";break;
          case 3: name_param = "/biotac_electrodes_lf";break;
          case 4: name_param = "/biotac_electrodes_th";break;
        }
        std::vector<double> vector_values;
        // valor electrodos -> vector
        for(int i=0; i<19; i++){
           vector_values.push_back(msg.tactiles[finger].electrodes[i]);
           ROS_INFO("Anhadido valor al vector tactil");
        }  
         
        // set param <- vector
        n.setParam(name_param,vector_values);
        ROS_INFO("Param set");
    }
  }

};


int main(int argc, char **argv)
{
  ros::init(argc, argv, "biotac_data_service");
  NodeClass* a = new NodeClass();
  a->sub = a->n.subscribe("/rh/tactile", 1000, &NodeClass::dataCallback,a);
  ros::spin();
  return 0;
}
