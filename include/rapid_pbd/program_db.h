#ifndef _RAPID_PBD_PROGRAM_DB_H_
#define _RAPID_PBD_PROGRAM_DB_H_

#include <map>
#include <string>

#include "mongodb_store/message_store.h"
#include "rapid_pbd_msgs/PDDLDomain.h"
#include "rapid_pbd_msgs/Program.h"
#include "ros/ros.h"
#include "sensor_msgs/PointCloud2.h"

#include "rapid_pbd/db_names.h"

namespace msgs = rapid_pbd_msgs;
namespace rapid {
namespace pbd {
static const char kProgramListTopic[] = "program_list";
static const char kPDDLDomainListTopic[] = "domain_list";

class SceneDb {
 public:
  explicit SceneDb(mongodb_store::MessageStoreProxy* db);

  std::string Insert(const sensor_msgs::PointCloud2& cloud);
  bool Get(const std::string& db_id, sensor_msgs::PointCloud2* cloud) const;
  bool Delete(const std::string& db_id);

 private:
  mongodb_store::MessageStoreProxy* db_;
};

class ProgramDb {
 public:
  ProgramDb(const ros::NodeHandle& nh, mongodb_store::MessageStoreProxy* db,
            ros::Publisher* list_pub);

  // Publishes the first message.
  void Start();

  std::string Insert(const msgs::Program& program);
  void Update(const std::string& db_id, const msgs::Program& program);
  void StartPublishingProgramById(const std::string& db_id);
  bool Get(const std::string& db_id, msgs::Program* program) const;
  bool GetByName(const std::string& name, msgs::Program* program) const;
  void Delete(const std::string& db_id);
  bool GetList(std::vector<std::string>* names);

 private:
  ros::NodeHandle nh_;
  mongodb_store::MessageStoreProxy* db_;
  ros::Publisher* list_pub_;
  std::map<std::string, ros::Publisher> program_pubs_;

  void PublishList();
  void PublishProgram(const std::string& db_id);
};

class PDDLDomainDb {
 public:
  PDDLDomainDb(const ros::NodeHandle& nh,
               mongodb_store::MessageStoreProxy* domain,
               ros::Publisher* list_pub);

  // Publishes the first message.
  void Start();

  std::string Insert(const msgs::PDDLDomain& domain);
  void Update(const std::string& domain_id, const msgs::PDDLDomain& domain);
  void StartPublishingPDDLDomainById(const std::string& domain_id);
  bool Get(const std::string& domain_id, msgs::PDDLDomain* domain) const;
  bool GetByName(const std::string& name, msgs::PDDLDomain* domain) const;
  void Delete(const std::string& domain_id);
  bool GetList(std::vector<std::string>* names);

 private:
  ros::NodeHandle nh_;
  mongodb_store::MessageStoreProxy* domain_;
  ros::Publisher* list_pub_;
  std::map<std::string, ros::Publisher> domain_pubs_;

  void PublishList();
  void PublishPDDLDomain(const std::string& domain_id);
};

}  // namespace pbd
}  // namespace rapid

#endif  // _RAPID_PBD_PROGRAM_DB_H_
