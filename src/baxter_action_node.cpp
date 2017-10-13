// Node that runs Baxter action servers using the control_msgs API.

#include "controller_manager_msgs/ListControllers.h"
#include "controller_manager_msgs/SwitchController.h"
#include "rapid_pbd/action_names.h"
#include "rapid_pbd/baxter_actions.h"
#include "rapid_pbd_msgs/ArmControllerState.h"
#include "rapid_pbd_msgs/FreezeArm.h"
#include "rapid_pbd_msgs/RelaxArm.h"
#include "ros/ros.h"

namespace pbd = rapid::pbd;
namespace msgs = rapid_pbd_msgs;

int main(int argc, char** argv) {
  ros::init(argc, argv, "baxter_actuator_server");
  ros::NodeHandle nh;

  pbd::baxter::GripperAction left_gripper(pbd::kLeftGripperActionName,
                                       pbd::baxter::kLeftGripperActionName);
  pbd::baxter::GripperAction right_gripper(pbd::kRightGripperActionName,
                                        pbd::baxter::kRightGripperActionName);

  pbd::baxter::HeadAction head_action(pbd::kHeadActionName,
                                      pbd::baxter::kHeadActionName);

  ros::Publisher arm_controller_state_pub =
      nh.advertise<msgs::ArmControllerState>(pbd::kArmControllerStateTopic, 5,
                                             true);
  ros::ServiceClient list_client =
      nh.serviceClient<controller_manager_msgs::ListControllers>(
          pbd::baxter::kListControllersService);
  ros::ServiceClient switch_client =
      nh.serviceClient<controller_manager_msgs::SwitchController>(
          pbd::baxter::kSwitchControllerService);
  pbd::baxter::ArmControllerManager arm_controller_manager(
      arm_controller_state_pub, list_client, switch_client);
  ros::ServiceServer freeze_srv = nh.advertiseService(
      pbd::kFreezeArmService, &pbd::baxter::ArmControllerManager::HandleFreeze,
      &arm_controller_manager);
  ros::ServiceServer relax_srv = nh.advertiseService(
      pbd::kRelaxArmService, &pbd::baxter::ArmControllerManager::HandleRelax,
      &arm_controller_manager);

  left_gripper.Start();
  right_gripper.Start();
  head_action.Start();
  arm_controller_manager.Start();
  ros::spin();
  return 0;
}