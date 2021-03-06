/*****************************************************************************
 *  Copyright (c) 2009, OpenJAUS.com.
 *  All rights reserved.
 *
 *  This file is part of OpenJAUS.  OpenJAUS is distributed under the BSD
 *  license.  See the LICENSE file for details.
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions
 *  are met:
 *
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above
 *       copyright notice, this list of conditions and the following
 *       disclaimer in the documentation and/or other materials provided
 *       with the distribution.
 *     * Neither the name of the University of Florida nor the names of its
 *       contributors may be used to endorse or promote products depdrived from
 *       this software without specific prior written permission.
 *
 *   THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 *   "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 *   LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 *   A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 *   OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 *   SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 *   LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 *   DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 *   THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 *   (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 *   OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 ****************************************************************************/
// File:		wd.h
//
// Version:		3.3.0b
//
// Written by:	Danny Kent (jaus AT dannykent DOT com)
//
// Date:		09/08/09
//
// Description:	This file contains the skeleton C header file code for implementing the wd.c file

#ifndef WD_H
#define WD_H

#include <jaus.h>
#include "vehicle.h"

#ifndef FALSE
#define FALSE 0
#endif
#ifndef TRUE
#define TRUE 1
#endif

#define WD_THREAD_DESIRED_RATE_HZ			50.0	// USER: Modify this rate as needed

OjCmpt wdCreate(void);
void wdDestroy(OjCmpt wd);
// USER: Insert prototypes for added public function here
ReportWrenchEffortMessage wdGetReportedWrench(OjCmpt wd);
SetWrenchEffortMessage wdGetCommandedWrench(OjCmpt wd);
ReportVelocityStateMessage wdGetVss(OjCmpt wd);
ReportGlobalPoseMessage wdGetGpos(OjCmpt wd);
SetTravelSpeedMessage wdGetTravelSpeed(OjCmpt wd);
SetGlobalWaypointMessage wdGetGlobalWaypoint(OjCmpt wd);

JausState wdGetPdState(OjCmpt wd);
JausBoolean wdGetPdWrenchScStatus(OjCmpt wd);
JausBoolean wdGetPdStatusScStatus(OjCmpt wd);
JausBoolean wdGetVssScStatus(OjCmpt wd);
JausBoolean wdGetGposScStatus(OjCmpt wd);
JausBoolean wdGetInControlStatus(OjCmpt wd);
VehicleState wdGetDesiredVehicleState(OjCmpt wd);
double wdGetWaypointDistanceM(OjCmpt wd);
int wdGetActiveWaypoint(OjCmpt wd);
int wdGetWaypointCount(OjCmpt wd);
void wdToggleRequestControl(OjCmpt wd);
JausBoolean wdGetRequestControl(OjCmpt wd);
void wdCreateWaypoint(OjCmpt wd);
void wdSetSpeed(OjCmpt wd);

#endif // WD_H
