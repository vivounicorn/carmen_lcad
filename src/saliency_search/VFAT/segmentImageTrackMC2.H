/*!@file VFAT/segmentImageTrackMC2.H Basic image segmenter blob finder using color */

// //////////////////////////////////////////////////////////////////// //
// The iLab Neuromorphic Vision C++ Toolkit - Copyright (C) 2001 by the //
// University of Southern California (USC) and the iLab at USC.         //
// See http://iLab.usc.edu for information about this project.          //
// //////////////////////////////////////////////////////////////////// //
// Major portions of the iLab Neuromorphic Vision Toolkit are protected //
// under the U.S. patent ``Computation of Intrinsic Perceptual Saliency //
// in Visual Environments, and Applications'' by Christof Koch and      //
// Laurent Itti, California Institute of Technology, 2001 (patent       //
// pending; application number 09/912,225 filed July 23, 2001; see      //
// http://pair.uspto.gov/cgi-bin/final/home.pl for current status).     //
// //////////////////////////////////////////////////////////////////// //
// This file is part of the iLab Neuromorphic Vision C++ Toolkit.       //
//                                                                      //
// The iLab Neuromorphic Vision C++ Toolkit is free software; you can   //
// redistribute it and/or modify it under the terms of the GNU General  //
// Public License as published by the Free Software Foundation; either  //
// version 2 of the License, or (at your option) any later version.     //
//                                                                      //
// The iLab Neuromorphic Vision C++ Toolkit is distributed in the hope  //
// that it will be useful, but WITHOUT ANY WARRANTY; without even the   //
// implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR      //
// PURPOSE.  See the GNU General Public License for more details.       //
//                                                                      //
// You should have received a copy of the GNU General Public License    //
// along with the iLab Neuromorphic Vision C++ Toolkit; if not, write   //
// to the Free Software Foundation, Inc., 59 Temple Place, Suite 330,   //
// Boston, MA 02111-1307 USA.                                           //
// //////////////////////////////////////////////////////////////////// //
//
// Primary maintainer for this file: T. Nathan Mundhenk <mundhenk@usc.edu>
// $HeadURL: svn://isvn.usc.edu/software/invt/trunk/saliency/src/VFAT/segmentImageTrackMC2.H $
// $Id: segmentImageTrackMC2.H 7188 2006-09-20 16:14:27Z rjpeters $
//

// ############################################################
// ############################################################
// ##### --- VFAT ---
// ##### Vision Feature Analysis Tool:
// ##### T. Nathan Mundhenk nathan@mundhenk.com
// ##### Laurent Itti itti@pollux.usc.edu
// #####
// ############################################################
// ############################################################

#ifndef SEGMENTIMAGETRACKMC2_H_DEFINED
#define SEGMENTIMAGETRACKMC2_H_DEFINED

#include "Image/Image.H"
#include "Util/Timer.H"
#include "Util/log.H"
#include "Util/readConfig.H"
#include "VFAT/blobProp.H"
#include "VFAT/segmentImageMC2.H"
#include "VFAT/segHolder.H"
#include "VFAT/covHolder.H"
#include <math.h>

//*******************************************
/* ABOUT THE USE OF TEMPLATES HERE

 the INT value is an integer number and should be an unsigned
 number (but isn't required to be). However, for images larger
 than 256x256 after decimation
 e.g. that contain more than 2^16 pixels, you should use a long instead
 this is because the number of blobs may be as large as the number
 of pixels.

 the FLOAT is for a floating point. A double may be used to obtain more
 accurate values at run time. This is at your discression

*/

//! decimation size reduction factor
#define SIT_GLOBAL_DEC      2

//! Define the template declaration for this class
#define SIT_TEMPLATE_CLASS <class FLOAT, class INT, unsigned int SIT_channels>
//! further define templates for this class
#define SIT_TEMPLATE       FLOAT,INT,SIT_channels
//! log file
#define SIT_LOG_FILE       "segmentTrack.log"
//! This is a class to track hyper spectal blobs
/*! This class will segment blobs and track them using adaptive
    thresholding and by calling segmentImageMC2. It can be used as a
    simple color tracker or can track anything else in real time so
    long as its features are contiuous
*/
template SIT_TEMPLATE_CLASS
class segmentImageTrackMC
{
private:
  blobProp SIT_blobProp;
  segmentImageMC2<SIT_TEMPLATE> SIT_segment;
  //! holds the histo gram color bar image
  Image<PixRGB<byte> >         SIT_auxHold;
  Image<PixRGB<byte> >        *SIT_imageHold;
  Image<PixRGB<FLOAT> >       *SIT_fimaHold;
  typename std::vector<INT>    SIT_blobList;
  //! holder for PixRGB to channel conversion
  typename std::vector<Image<FLOAT> > SIT_chans;
  //! holder for temporal image smoothing
  typename std::vector<Image<FLOAT> > SIT_fimaLast;
  readConfig configIn;
  readConfig polySet;
  readConfig blobConf;
  //! run color adaptation methods on all channels
  void SITcolorAdaptation();
  //! reset color values
  void SITresetColor();
  //! analyze blobs, remove those that are no good
  void SITanalyzeBlobs();
  //! merge all remaining blobs into a single motherblob
  void SITmergeBlobs();

  std::string    SIT_LOTtypeName;
  //! boundary for blobs to be considered at close to last blob
  unsigned char  SIT_boxRed;
  unsigned char  SIT_boxGreen;
  unsigned char  SIT_boxBlue;
  unsigned char  SIT_bigBoxRed;
  unsigned char  SIT_bigBoxGreen;
  unsigned char  SIT_bigBoxBlue;
  unsigned char  SIT_circleRed;
  unsigned char  SIT_circleGreen;
  unsigned char  SIT_circleBlue;
  unsigned char  SIT_LOTcount;
  unsigned char  SIT_LOTtype;

  short SIT_xBound;
  short SIT_yBound;
  short SIT_centerX;
  short SIT_centerY;
  short SIT_centerXmod;
  short SIT_centerYmod;
  unsigned short SIT_minX;
  unsigned short SIT_maxX;
  unsigned short SIT_minY;
  unsigned short SIT_maxY;
  unsigned short SIT_minXmod;
  unsigned short SIT_maxXmod;
  unsigned short SIT_minYmod;
  unsigned short SIT_maxYmod;
  unsigned short SIT_expectedX;
  unsigned short SIT_expectedY;
  unsigned short SIT_expectedXmax;
  unsigned short SIT_expectedYmax;
  unsigned short SIT_expectedXmin;
  unsigned short SIT_expectedYmin;
  unsigned short SIT_barSpace;
  unsigned short SIT_barWidth;
  unsigned int SIT_totalBlobs;
  unsigned int SIT_killedBlobs;

  //! what frame are we in?
  unsigned long SIT_frameNumber;
  unsigned long SIT_lifeSpan;
  unsigned long SIT_totalLifeSpan;

  FLOAT SIT_thresh;
  FLOAT SIT_mass;
  FLOAT SIT_histoHeight;
  FLOAT SIT_smoothingAlpha;
  //! if set, we edit blobs based on expected locations
  bool SIT_useExpectedLocation;
  bool SIT_LOT, SIT_didCircleColor, SIT_didBoxColor, SIT_didTrackColor;
  bool SIT_useSmoothing, SIT_didSmoothing, SIT_draw, SIT_resetColor;
  //! set to true if histogram bars have been drawn, false otherwise
  bool SIT_didColorBars;
  //! This toggles the loging to file
  bool SIT_useLog;
  //! This toggles drawing the target image
  bool SIT_drawTargetImage;
  //! This toggles drawing the color adaptation image
  bool SIT_drawColorAdaptImage;
  //! toggles color adaptation (defaults to true, on)
  bool SIT_useColorAdaptation;
  //! toggle whether to edit blobs in tracker
  bool SIT_editBlobs;
  //! This is true if we use hard bounds in the color adaptation
  bool SIT_useHardBounds;

  INT SIT_blobListSize;

  //! mean color value for this channel
  typename std::vector<FLOAT> SIT_chMean1;
  //! temp holder for the mean value on this channel
  typename std::vector<FLOAT> SIT_chMean2;
  //! old mean value on this channel
  typename std::vector<FLOAT> SIT_oldMean;
  //! standard deviation for the color on this channel
  typename std::vector<FLOAT> SIT_chStd1;
  //! temp holder for the standard deviation on this channel
  typename std::vector<FLOAT> SIT_chStd2;
  //! old standard deviation on this channel
  typename std::vector<FLOAT> SIT_oldStd;
  //! lower bound for this channel
  typename std::vector<FLOAT> SIT_chLB;
  //! upper bound for this channel
  typename std::vector<FLOAT> SIT_chUB;
  //! old lower bound for this channel
  typename std::vector<FLOAT> SIT_oldLB;
  //! old upper bound for this channel
  typename std::vector<FLOAT> SIT_oldUB;
  //! special holder for standard deviation in colot adaptation
  typename std::vector<FLOAT> SIT_chNSTD;
  //! adaptation bias per channel
  typename std::vector<FLOAT> SIT_chAdapt;
  //! normalizer over channels
  typename std::vector<FLOAT> SIT_chNorm;
  //! old normalizer over channels
  typename std::vector<FLOAT> SIT_oldNorm;
  //! holder for skew
  typename std::vector<FLOAT> SIT_chSkew;
  //! Initial mean color for tracking
  typename std::vector<FLOAT> SIT_initMean;
  //! Inital standard Deviation for tracking
  typename std::vector<FLOAT> SIT_initStd;

  std::vector<bool>           SIT_softCandidateBlob;
  std::vector<bool>           SIT_candidateBlob;
  std::vector<bool>           SIT_killedByTrack;
  //! why was this blob killed string version
  std::vector<std::string>    SIT_reasonForKill;
  //! why was this blob killed unsigned short int code
  std::vector<unsigned short> SIT_reasonForKillCode;

  // center of the frame
  int SIT_x_center, SIT_y_center;

public:

  //! default constructor, also sets up number of color channels
  segmentImageTrackMC(INT maxBlobCount);
  ~segmentImageTrackMC();

  //! set the tracking color for mass circle
  /*!
    @param r this is the red color for the output circle
    @param g this is the green color for the output circle
    @param b this is the blue color for the output circle
    @param instance this is the tracker to apply these settings to
  */
  void SITsetCircleColor(unsigned char r, unsigned char g, unsigned char b);

  //! set the tracking colot for the bounding box
  //! set the tracking color for mass circle
  /*!
    @param r this is the red color for the output bounding box
    @param g this is the green color for the output bounding box
    @param b this is the blue color for the output bounding box
    @param bigr this is the red color for the merged bounding box
    @param bigg this is the green color for the merged bounding box
    @param bigb this is the blue color for the merged bounding box
    @param instance this is the tracker to apply these settings to
  */
  void SITsetBoxColor(unsigned char r, unsigned char g, unsigned char b,
                      unsigned char bigr,
                      unsigned char bigg,
                      unsigned char bigb);
  //! set default tracking color values
  /*!
    In this method you place the properties for the colors you wish
    to track as a list from a std::vector. You upload the mean color
    on each channel which is the color you wish to initially track. You
    also upload the boundary for the color as the parameter std. This tells
    the inital range for considering a pixel as OK. The range is
    color +/- std. Norm is a normalizer to the color. For instance, if a
    channel ranges between 0 and 255 then this should be set to 255. The
    parameter adapt is for the color adaptation. This defines the range
    around which new colors can be found. This is a value that is multiplied
    by standard deviation of adapted color mean. Higher values mean less
    selective. The upper and lower bound determine the values above or
    below color adaptation can never go (ever). This keeps the adaptation
    in check.
    @param color This is the mean color to track on each channel
    @param std This is the threshold for color (color +/- std)
    @param norm This is the normalizer range for a color channel
    @param adapt This is the adaptation multiplier for color adaption
    @param upperBound This is the hard upper bound on channel values
    @param lowerBound This is the hard lower bound on channel values
  */
  void SITsetTrackColor(typename std::vector<FLOAT> color,
                        typename std::vector<FLOAT> std,
                        typename std::vector<FLOAT> norm,
                        typename std::vector<FLOAT> adapt,
                        typename std::vector<FLOAT> upperBound,
                        typename std::vector<FLOAT> lowerBound,
                        bool resetColor = true,
                        bool resetCandidates = false);
  //! set default tracking color values
  /*! Input a covHolder signature for tracking along with data from
     a segHolder.
     @param cov This is a covHolder object from covHolder.H
     @param seg This is a segHolder object from segHolder.H
  */
  void SITsetTrackSignature(const covHolder<double> *cov,
                            segHolder<FLOAT,INT,SIT_channels>  *seg);
  //! get back the segHolder with values that describe the target
  void SITgetTrackSignature(segHolder<FLOAT,INT,SIT_channels>  *seg);

  //! set frame size for color tracker
  /*! This allows the algorithm to inpect an area within each image
    rather than the whole image. Thus, images do not need to be resized in
    order to contrain the region processed.
  */
  void SITsetFrame(unsigned short *x, unsigned short *y);
  //! set this if you want to temporally smooth frames
  /*! this will use a Kalman like filter to preserve past images
    @param alpha This is the percentage of last iteration to keep 0-1
  */
  void SITsetUseSmoothing(bool smoothing, FLOAT alpha);

  //! OPTIONAL - set where you expect the target appear
  /*!
    @param posX This is the centroid in X where you expect the target
    @param posY This is the centroid in Y where you expect the target
    @param maxX This creates a boundary for expectations
    @param maxY This creates a boundary for expectations
    @param minX This creates a boundary for expectations
    @param minY This creates a boundary for expectations
   */
  void SITsetExpectedTargetPosition(const unsigned short posX,
                                    const unsigned short posY,
                                    const unsigned short maxX,
                                    const unsigned short maxY,
                                    const unsigned short minX,
                                    const unsigned short minY);
  //! return the expect target positions you set
  void SITgetExpectedTargetPosition(unsigned short *posX,
                                    unsigned short *posY,
                                    unsigned short *maxX,
                                    unsigned short *maxY,
                                    unsigned short *minX,
                                    unsigned short *minY,
                                    bool *isSet) const;
  //! unset the bool to use expected location
  void SITunsetExpectedTargetPosition();
  //! tell us if the new target overlaps with the current target
  bool SITintersection(const covHolder<double> *cov,
                       const int boundX,
                       const int boundY) const;
  //! find out how much another target overlaps with this
  void SITpercentOverlap(const segHolder<FLOAT,INT,SIT_channels>  *seg,
                         FLOAT *overlap,
                         FLOAT *thisArea,
                         FLOAT *otherArea) const;

  //! turn on or off candidate pixel band passing (on,true by default)
  void SITtoggleCandidateBandPass(bool toggle);
  //! turn on or off color adaptation
  void SITtoggleColorAdaptation(bool toggle);
  //! turn on or off hard bounds in color adaptations
  void SITtoggleHardBounds(bool toggle);
  //! OPTIONAL set the frame number
  void SITsetFrameNumber(unsigned long frame);
  //! turn on or off blob editing
  void SITeditBlobs(bool toggle);
  //! Put image one at a time into tracker and get back tracker image output
  /*!
    This is designed to run any pixel type images.
    If one wishes to use hyperspectral
    images use SITtrackImage with an input of vectorized images.
    @param input this is the raw input image
    @param output this is a pointer to the output image
  */

  void SITtrackImage(Image<PixH2SV2<FLOAT> > &input,
                     Image<PixRGB<byte> > *output);
  //! smooth the input image with a temporal Kalman filter
  void SITsmoothImage(typename std::vector<Image<FLOAT> > *input);
  //! OPTIONAL call this to turn on the logger
  void SITuseLog(bool useLog);
  //! OPTIONAL call this to turn off some drawing functions
  void SITtoggleDrawing(bool targetImage,
                        bool colorAdaptImage);
  //! run the tracker
  void SITrunTrack(Image<PixRGB<byte> > *image,
                   typename std::vector<Image<FLOAT> > *input);

  //! This tells if no good target can be found. It returns loss of track.
  bool SITreturnLOT();

  //! tells what kind of loss of track we have
  /*! Types of loss of track are
    1 - object is no longer inside tracking frame
    2 - object no longer has mass, this either means a total loss
        of track OR all blobs have been edited out
  */
  unsigned int SITreturnLOTtype();
  //! returns an explanation of LOT
  std::string SITreturnLOTtypeName();

  //! return the blob ID map from SI
  Image<long> SITreturnBlobMap();
  //! return the image of candidate pixels
  Image<byte> SITreturnCandidateImage();
  //! return gaussian P for X, Xbar and std
  FLOAT SITPgauss(FLOAT X, FLOAT Xbar, FLOAT std);
  //! draw a tracking circle around blob i
  void SITdrawBlobTrack(INT i);
  //! draw the merged blob track box
  void SITdrawBlobTrackMerged();
  //! draw a tracking blob around bad condidate blob
  void SITdrawBlobBox(INT i);
  //! draw histogram given the values provided
  void SITdrawHistoValues(typename std::vector<FLOAT> *mean,
                          typename std::vector<FLOAT> *std,
                          typename std::vector<FLOAT> *lb,
                          typename std::vector<FLOAT> *ub,
                          typename std::vector<FLOAT> *norm,
                          bool LOT);
  //! return the blob position (for tracking) as an x y coord
  void SITgetBlobPosition(unsigned short *x, unsigned short *y);
  //! return the bounding box to the blobs
  void SITgetMinMaxBoundry(unsigned short *minX, unsigned short *maxX,
                           unsigned short *minY, unsigned short *maxY);
  //! return the color adaptation bar image if used
  Image<PixRGB<byte> > SITgetColorBars();
  //! return the mass of the remaining blob
  FLOAT SITgetMass();
  //! how many potential blobs have been killed
  void SITgetBlobAttrition(INT *totalBlobs,
                           INT *killedBlobs);
  //! How long have we been tracking this object
  /*! totalLifeSpan is the total number of tracking iterations while
      lifeSpan does not include short intervals where we have lost track
      thus, we can see how strong our track is by comparing the total time
      vs. the time actually spent tracking
  */
  void SITgetLifeSpans(unsigned long *totalLifeSpan,
                       unsigned long *lifeSpan);
  //! get new adaptive values for color tracking
  void SITgetAdaptiveChannelVals(typename std::vector<FLOAT> *mean,
                                 typename std::vector<FLOAT> *std);
  //! get how many loss of tracks have been found since last reset of color
  unsigned int SITgetLOTcount();

  // Use these methods to keep track of simple blob attrition

  //! return the total number of blobs
  INT SITnumberBlobs();
  //! for each blob this tells why it was killed
  unsigned short SITgetBlobReasonForKillCode(INT blob);
  //! for each blob this tells why it was killed
  std::string SITgetBlobReasonForKill(INT blob);
  //! for each blob, return its mass
  INT SITgetBlobMass(INT blob);
  //! for each blob, return its X position
  INT SITgetBlobPosX(INT blob);
  //! for each blob, return its Y position
  INT SITgetBlobPosY(INT blob);

  //! this is set to true if after calling the tracker it reset colors
  /*! This indicates that the number of loss of tracks has exceded the
      the max number causing the color to be reset. This is only
      set once after colors are reset. Then it returns to having a
      value of false when the tracker is called again.
  */
  bool SIT_LOTandRESET;

};

#endif
