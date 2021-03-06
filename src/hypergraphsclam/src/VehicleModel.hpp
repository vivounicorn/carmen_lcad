#ifndef HYPERGRAPHSLAM_VEHICLE_MODEL_HPP
#define HYPERGRAPHSLAM_VEHICLE_MODEL_HPP

#include <string>

#include <g2o/types/slam2d/se2.h>

namespace hyper {

class VehicleModel {

    private:

        // a simple configuration
        static double max_steering_angle;
        static double axle_distance;
        static double understeer;

    public:

        // base constructor
        VehicleModel();

        // read the vehicle parameters from file
        static void SetParameters(double msa, double ald, double und);

        // get the next vehicle state
        static g2o::SE2 GetOdometryMeasure(double v, double phi, double dt);

        // get the next vehicle state
        static g2o::SE2 NextState(g2o::SE2 prev, double v, double phi, double dt);

};

}

#endif
