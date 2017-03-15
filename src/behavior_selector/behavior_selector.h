/*
 * behavior_selector.h
 *
 *  Created on: 28/09/2012
 *      Author: romulo
 */

#ifndef BEHAVIOR_SELECTOR_H_
#define BEHAVIOR_SELECTOR_H_

#include <carmen/carmen.h>
#include <carmen/rddf_messages.h>
#include "SampleFilter.h"

// struct _moving_object
// {
// 	bool valid;
// 	int index;
// 	carmen_ackerman_traj_point_t pose;
// 	carmen_ackerman_traj_point_t car_pose;
// 	double timestamp;
// };
//
// typedef struct _moving_object MOVING_OBJECT;
//
// #define MOVING_OBJECT_HISTORY_SIZE 40


void change_distance_between_waypoints_and_goals(double dist_between_waypoints, double change_goal_dist);

void behavior_selector_initialize(carmen_robot_ackerman_config_t config, double dist_between_waypoints,
		double change_goal_dist, carmen_behavior_selector_algorithm_t f_planner, carmen_behavior_selector_algorithm_t p_planner);

void behavior_selector_update_robot_pose(carmen_ackerman_traj_point_t robot_pose);

void behavior_selector_update_rddf(carmen_rddf_road_profile_message *rddf_msg, int rddf_num_poses_by_velocity, double timestamp);

void behavior_selector_update_map(carmen_obstacle_distance_mapper_message *map);

void behavior_selector_publish_periodic_messages();

void behavior_selector_set_algorithm(carmen_behavior_selector_algorithm_t algorithm, carmen_behavior_selector_state_t state);

int behavior_selector_set_state(carmen_behavior_selector_state_t state);

int behavior_selector_set_goal_source(carmen_behavior_selector_goal_source_t goal_source);

void behavior_selector_add_goal(carmen_point_t goal);

void behavior_selector_clear_goal_list();

void behavior_selector_remove_goal();

void behavior_selector_update_annotations(carmen_rddf_annotation_message *message);

carmen_behavior_selector_algorithm_t get_current_algorithm();

void behavior_selector_get_state(carmen_behavior_selector_state_t *current_state_out, carmen_behavior_selector_algorithm_t *following_lane_planner_out,
		carmen_behavior_selector_algorithm_t *parking_planner_out, carmen_behavior_selector_goal_source_t *current_goal_source_out);

carmen_ackerman_traj_point_t *behavior_selector_get_goal_list(int *goal_list_size_out);

carmen_ackerman_traj_point_t get_robot_pose();
double get_max_v();
carmen_robot_ackerman_config_t *get_robot_config();

carmen_rddf_road_profile_message *get_last_rddf_message();

int behaviour_selector_fill_goal_list(carmen_rddf_road_profile_message *rddf, bool *goal_in_front_is_a_moving_obstacle, double timestamp);
// double get_moving_object_in_front_v();
// int moving_object_in_front();
double distance_between_waypoints_and_goals();
bool red_traffic_light_ahead();

void publish_dynamic_annotation(carmen_vector_3D_t annotation_point, double orientation, char *annotation_description,
		int annotation_type, int annotation_code, double timestamp);

#endif /* BEHAVIOR_SELECTOR_H_ */
