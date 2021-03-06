#ifndef VIRTUAL_SCAN_POSTERIOR_H
#define VIRTUAL_SCAN_POSTERIOR_H

#include "readings.h"
#include "track.h"

#include <map>

namespace virtual_scan
{

/**
 * @brief Class used to manage exchanges between dynamic and static readings.
 */
class Collector
{
	/** @brief Whether to collect hitting or missing points. */
	bool hits;

	/** @brief Sequence of collected points. */
	std::vector<carmen_point_t> points;

public:
	/**
	 * Create a new collector of given mode.
	 */
	Collector(bool hits);

	/**
	 * @brief Collect the given point if its mode agrees with the object's.
	 */
	void operator() (bool mode, const carmen_point_t &point);

	/**
	 * @brief Move points from origin to destination reading.
	 */
	void move(Reading &Z_i, Reading &Z_j);
};

/**
 * @brief Algorithm class for computing the posterior probability of a sequence of Track objects.
 */
class Posterior
{
	/** @brief Map of track lengths. */
	std::map<Track::ID, int> lengths;

	/** @brief Sums of ray distances, indexed by generating obstacle. */
	std::map<const virtual_scan_graph_node_t*, double> distances;

	/** @brief Dynamic sensor readings, indexed by generatig obstacle. */
	std::map<const virtual_scan_graph_node_t*, Reading> Zd;

	/** @brief Static sensor readings. */
	Readings Zs;

	/** @brief Sum of the lengths of all tracks. */
	double S_len;

	/** @brief Sum of the covariances of all tracks. */
	double S_mot;

	/** @brief Sum of the distances between dynamic sensor readings and their generating obstacles. */
	double S_ms1;

	/** @brief Number of static sensor readings found behind obstacles. */
	double S_ms2;

	/** @brief Number of static sensor readings found in areas occupied by obstacles in some earlier or later time. */
	double S_ms3;

	/** @brief Number of dynamic sensor readings found behind presumed static objects. */
	double S_ms4;

	/**
	 * @brief Update the value of the `S_len` parameter with the given track's new length.
	 *
	 * @param i Position of the track in the sequence.
	 *
	 * @param tracks Sequence containing the updated track.
	 */
	void update_S_len(int i, const Track::S &tracks);

	/**
	 * @brief Update the value of the `S_mot` parameter with the given track's new covariance.
	 *
	 * @param i Position of the track in the sequence.
	 *
	 * @param tracks Sequence containing the updated track.
	 */
	void update_S_mot(int i, const Track::S &tracks);

	/**
	 * @brief Update the distances between dynamic sensor readings and a given obstacle pose.
	 *
	 * This method also updates the internal dynamic and static sensor reading
	 * collections used by other update methods.
	 *
	 * @param i Position of the given track in the sequence.
	 *
	 * @param j Position of the track pose to update.
	 *
	 * @param tracks Sequence containing the updated track.
	 */
	void update_S_ms1(int i, int j, const Track::S &tracks);

	/**
	 * @brief Update the distances between the given object and reading rays.
	 *
	 * Rays that do or don't hit the object at the given pose will be collected for
	 * reassignment according to the configuration of the given Collector object.
	 */
	void update_S_ms1(const ObstaclePose &pose, const Reading &Z_k, Collector &collect);

	/**
	 * @brief Update the counter for static objects observed behind obstacle poses.
	 *
	 * @param i Position of the given track in the sequence.
	 *
	 * @param j Position of the track pose to update.
	 *
	 * @param tracks Sequence containing the updated track.
	 */
	void update_S_ms2(int i, int j, const Track::S &tracks);

	/**
	 * @brief Update the counter for static objects observed in areas occupied by obstacle at some point in time.
	 *
	 * @param i Position of the given track in the sequence.
	 *
	 * @param j Position of the track pose to update.
	 *
	 * @param tracks Sequence containing the updated track.
	 */
	void update_S_ms3(int i, int j, const Track::S &tracks);

	/**
	 * @brief Update the counter for dynamic sensor readings found behind presumed static objects.
	 *
	 * @param i Position of the given track in the sequence.
	 *
	 * @param j Position of the track pose to update.
	 *
	 * @param tracks Sequence containing the updated track.
	 */
	void update_S_ms4(int i, int j, const Track::S &tracks);

public:
	/**
	 * @brief Default constructor.
	 */
	Posterior();

	/**
	 * @brief Return the current posterior value.
	 */
	double operator () () const;

	/**
	 * @brief Update the posterior in response to a diffusion operation performed on the given track.
	 *
	 * @param i Index of the track in its parent sequence.
	 *
	 * @param j Index of the updated pose in the track.
	 *
	 * @param tracks Sequence containing the updated track.
	 *
	 * @param readings Sequence of sensor readings over the time window.
	 */
	void diffuse(int i, int j, const Track::S &tracks);

	/**
	 * @brief Update the posterior in response to a swap operations performed on the given track pair.
	 *
	 * @param i Index to first swapped track.
	 *
	 * @param j Index to second swapped track.
	 *
	 * @param tracks Sequence containing the swapped tracks at the given indexes.
	 */
	void swap(int i, int j, const Track::S &tracks);

	/**
	 * @brief Update the readings over the time window and recompute respective posterior terms.
	 */
	void update(const Track::S &tracks, const Readings &readings);
};

} // namespace virtual_scan

#endif
