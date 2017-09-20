#ifndef _RAPID_PBD_CONDITION_CHECKER_H_
#define _RAPID_PBD_CONDITION_CHECKER_H_

#include <set>
#include <string>
#include <vector>

#include "geometry_msgs/Pose.h"
#include "geometry_msgs/Vector3.h"
#include "moveit_msgs/MoveGroupAction.h"
#include "moveit_msgs/MoveItErrorCodes.h"
#include "rapid_pbd_msgs/Landmark.h"
#include "rapid_pbd_msgs/Condition.h"
#include "ros/ros.h"
#include "tf/transform_listener.h"

#include "rapid_pbd/world.h"

namespace rapid {
namespace pbd {
class ConditionChecker {
 public:
  ConditionChecker(World* world);
  // Returns an error message, or empty string if no error.
  // Set seed_joint_names and seed_joint_positions to empty vectors if you do
  // not want to specify an IK seed.
  bool CheckConditions(const rapid_pbd_msgs::Condition& condition);
    // const std::string& actuator_group,
    //                       const geometry_msgs::Pose& pose,
    //                       const rapid_pbd_msgs::Landmark& landmark,
    //                       const std::vector<std::string>& seed_joint_names,
    //                       const std::vector<double>& seed_joint_positions);
  int num_goals() const;
  bool CheckPropertyConditions(const rapid_pbd_msgs::Condition& conditions,
                              const rapid_pbd_msgs::Landmark& match);
  bool CheckRelativeConditions(const rapid_pbd_msgs::Condition& conditions);
  bool PointDissimilarity(const float& value, const float& match,
                       const float& variance);

  bool VectorDissimilarity(const geometry_msgs::Vector3& actual,
                                          const geometry_msgs::Vector3& match,
                                          const geometry_msgs::Vector3& variance);
 private:
  World* world_;
  int num_goals_;
};

std::string ErrorCodeToString(const moveit_msgs::MoveItErrorCodes& code);
}  // namespace pbd
}  // namespace rapid

#endif  // _RAPID_PBD_CONDITION_CHECKER_H_