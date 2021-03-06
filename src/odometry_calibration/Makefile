include ../Makefile.conf

MODULE_NAME = ODOMETRY_CALIBRATION
MODULE_COMMENT = Module to calibrate the bias of the Odometry

LINK = g++

IFLAGS += -I$(CARMEN_HOME)/sharedlib/libtf/src -I/usr/local/include/bullet/ 
LFLAGS += -lglobal -lipc -llocalize_ackerman_interface -lfused_odometry_interface -lvelodyne_interface -lparam_interface -lGL -lglut -lGLU \
	 	-L$(CARMEN_HOME)/sharedlib/libtf/src -ltf -lBulletCollision -lBulletDynamics -lBulletSoftBody -lLinearMath -lboost_thread-mt -lrt -lboost_signals -lboost_system    
LFLAGS += -lrobot_ackerman_interface -lobstacle_avoider_interface \
	-lmap_io -lmap_util -llaser_interface -lfused_odometry_interface -lvelodyne_interface \
	-lGLEW -lGL -lGLU -lglut -lX11 -lmap_interface -lbase_ackerman_interface \
	-lstereo_velodyne -lstereo_velodyne_interface -lstereo_interface -llocalize_ackerman_core -llocalize_ackerman_interface \
	-llocalize_ackerman_motion -lmap_server_interface -lgps_xyz_interface -lvisual_odometry_interface -lxsens_mtig_interface -lxsens_interface
IFLAGS += -I/usr/include/eigen3 
LFLAGS += -L /usr/local/lib -lcholmod -lg2o_core -lg2o_stuff -lg2o_types_slam2d -lg2o_cli
IFLAGS += -I /usr/include/suitesparse -I/usr/include/eigen3 -I /usr/local/include/EXTERNAL/csparse/ -I /usr/local/include/g2o/
LFLAGS += -lvtkCommon -lvtkFiltering -lpcl_common -lpcl_surface -lpcl_io -lpcl_registration -lpcl_kdtree -lpcl_features -lpcl_search -lpcl_octree -lpcl_sample_consensus -lpcl_filters -lpcl_visualization  -lboost_system -lboost_thread-mt -lrt -lboost_signals -lboost_system
IFLAGS += -I/usr/include/eigen3 -I/usr/local/include/pcl-1.7/  -I/usr/include/vtk-5.8/
IFLAGS += -I$(CARMEN_HOME)/sharedlib/prob_models -I$(CARMEN_HOME)/sharedlib/gl_plotter 
LFLAGS += -L$(CARMEN_HOME)/sharedlib/prob_models -L$(CARMEN_HOME)/sharedlib/gl_plotter -lprob_models -lrotation_geometry
IFLAGS += `pkg-config --cflags opencv`
IFLAGS += -I$(CARMEN_HOME)/sharedlib/pso 
LFLAGS += -L$(CARMEN_HOME)/sharedlib/pso -lpso++ -fopenmp
LFLAGS += `pkg-config --libs opencv`	  
LFLAGS += -lmapper_interface -lgrid_mapping -lmap_io -lmap_interface

SOURCES = grab_data_for_calibration.cpp calibrate_bias.cpp

PUBLIC_INCLUDES = 
PUBLIC_LIBRARIES = 
PUBLIC_BINARIES = grab_data_for_calibration calibrate_bias
TARGETS = libpso++.a grab_data_for_calibration calibrate_bias 

libpso++.a:
	$(MAKE) -C $(CARMEN_HOME)/sharedlib/pso/

clean: clean_pso
clean_pso:
	$(MAKE) clean -C $(CARMEN_HOME)/sharedlib/pso/	

grab_data_for_calibration: grab_data_for_calibration.o
calibrate_bias: calibrate_bias.o

include ../Makefile.rules
