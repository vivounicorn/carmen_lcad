include ../Makefile.conf

MODULE_NAME = Road Mapper
MODULE_COMMENT = Create, view, learn and predict *road maps*

LINK = g++
CFLAGS += -Wall

#CXXFLAGS += -std=c++11
CXXFLAGS += -Wno-ignored-qualifiers

IFLAGS += \
	`pkg-config --cflags opencv` \
	-I /usr/local/cuda/include \
	-I$(CAFFE_ENET_HOME)/include \
	-I$(CAFFE_ENET_HOME)/build/include 

LFLAGS += \
	-L$(CAFFE_ENET_HOME)/build/lib \
	`pkg-config --libs opencv` \
	-lparam_interface \
	-lipc \
	-lglobal \
	-llocalize_ackerman_interface \
	-lmap_server_interface \
	-lgrid_mapping \
	-lmap_io \
	-lmap_interface \
	-lpng \
	-lreadlog \
	-lkinect_interface \
	-lglog \
	-lprotobuf \
	-lboost_signals \
	-lboost_system \
	-lcaffe 

SOURCES = \
	road_mapper_main.cpp \
	road_mapper_interface.c \
	road_mapper_utils.cpp \
	road_mapper_save_remission_map_images.cpp \
	road_mapper_image_splitter.cpp \
	road_mapper_display_map2.cpp \
	road_mapper_display_map3.cpp \
	road_mapper_sampling.cpp \
	road_mapper_road_inference_main.cpp \
	road_mapper_log_tracker.cpp

PUBLIC_INCLUDES = \
	road_mapper_messages.h \
	road_mapper_interface.h \
	road_mapper.h

PUBLIC_LIBRARIES = \
	libroad_mapper_interface.a \
	libroad_mapper.a

PUBLIC_BINARIES = \
	road_mapper \
	road_mapper_save_remission_map_images \
	road_mapper_sampling \
	road_mapper_road_inference_main

TARGETS = \
	libroad_mapper_interface.a \
	libroad_mapper.a \
	road_mapper \
	road_mapper_save_remission_map_images \
	road_mapper_sampling \
	road_mapper_road_inference_main \
	road_mapper_image_splitter \
	road_mapper_display_map2 \
	road_mapper_display_map3 \
	road_mapper_log_tracker

# If you set graphics support in configure.
ifndef NO_GRAPHICS
#Carmen Global Graphic Library and Gtk+2 Graphics Libraries
IFLAGS += \
	`pkg-config --cflags gtk+-2.0 gmodule-export-2.0` \
	`pkg-config --cflags gtkglext-1.0`
LFLAGS += \
	-lglobal_graphics \
	`pkg-config --libs gtk+-2.0 gmodule-export-2.0` \
	`pkg-config --libs gtkglext-1.0`
endif

libroad_mapper_interface.a: road_mapper_interface.o
libroad_mapper.a: road_mapper.o
road_mapper: road_mapper_main.o road_mapper_interface.o
road_mapper_save_remission_map_images: road_mapper_save_remission_map_images.o road_mapper.o road_mapper_utils.o
road_mapper_sampling: road_mapper_sampling.o road_mapper.o road_mapper_utils.o
road_mapper_road_inference_main: road_mapper_road_inference_main.o road_mapper.o road_mapper_utils.o
road_mapper_image_splitter: road_mapper_image_splitter.o
road_mapper_display_map2: road_mapper_display_map2.o
road_mapper_display_map3: road_mapper_display_map3.o road_mapper.o road_mapper_utils.o
road_mapper_log_tracker: road_mapper_log_tracker.o

include ../Makefile.rules
