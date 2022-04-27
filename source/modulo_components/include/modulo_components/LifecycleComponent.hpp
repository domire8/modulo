#pragma once

#include <rclcpp_lifecycle/lifecycle_node.hpp>

#include "modulo_components/ComponentInterface.hpp"

#include "modulo_new_core/EncodedState.hpp"
#include <rclcpp_lifecycle/lifecycle_node.hpp>
#include <rclcpp_lifecycle/lifecycle_publisher.hpp>

namespace modulo_components {

class LifecycleComponent : public ComponentInterface<rclcpp_lifecycle::LifecycleNode> {
public:
  friend class LifecycleComponentPublicInterface;

  /**
   * @brief Constructor from node options
   * @param node_options node options as used in ROS2 Node
   */
  explicit LifecycleComponent(const rclcpp::NodeOptions& node_options);

protected:
  /**
   * @brief Add an output signal of the component.
   * @tparam DataT Type of the data pointer
   * @param signal_name Name of the output signal
   * @param data Data to transmit on the output signal
   * @param fixed_topic If true, the topic name of the output signal is fixed
   */
  template<typename DataT>
  void add_output(const std::string& signal_name, const std::shared_ptr<DataT>& data, bool fixed_topic = false);

private:
  /**
   * @brief Configure all outputs.
   * @return True configuration was successful
   */
  bool configure_outputs();

  /**
   * @brief Activate all outputs.
   * @return True activation was successful
   */
  bool activate_outputs();

  /**
   * @brief Deactivate all outputs.
   * @return True deactivation was successful
   */
  bool deactivate_outputs();

  using ComponentInterface<rclcpp_lifecycle::LifecycleNode>::create_output;
  using ComponentInterface<rclcpp_lifecycle::LifecycleNode>::qos_;
};

template<typename DataT>
void
LifecycleComponent::add_output(const std::string& signal_name, const std::shared_ptr<DataT>& data, bool fixed_topic) {
  try {
    std::string parsed_signal_name = utilities::parse_signal_name(signal_name);
    this->create_output(parsed_signal_name, data, fixed_topic);
  } catch (const std::exception& ex) {
    RCLCPP_ERROR_STREAM(this->get_logger(), "Failed to add output '" << signal_name << "': " << ex.what());
  }
}

}