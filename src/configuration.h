/***************************************************************************
                          configuration.h  -  description
                             -------------------
    begin                : Fri Feb 27 2004
    copyright            : (C) 2003 by Lynn Hazan
    email                :
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#ifndef CONFIGURATION_H
#define CONFIGURATION_H

// include files for QT
#include <QString>
#include <qfont.h>
#include <QColor>

//General C++ include files
#include <iostream>
using namespace std;

/**
  * This is the one and only configuration object.
  * The member functions read() and write() can be used to load and save
  * the properties to the application configuration file.
  *@author Lynn Hazan
*/

class Configuration {
public:
    /** Reads the configuration data from the application config file.
    * If a property does not already exist in the config file it will be
    * set to a default value.*/
    void read();
    /** Writes the configuration data to the application config file.*/
    void write() const;

    /**Sets the screen gain in milivolts by centimeters used to display the field potentiels.
    */
    inline void setScreenGain(float gain){
        screenGain = gain;
    }

    /**Sets the voltage range of the acquisition system in milivolts.
    */
    inline void setVoltageRange(int value){
        voltageRange = value;
    }

    /**Sets the amplification of the acquisition system.
    */
    inline void setAmplification(int value){
        amplification = value;
    }

    /**Sets the background color.*/
    inline void setBackgroundColor(QColor color) {backgroundColor = color;}

    /**Sets the display of the palette headers.*/
    inline void setPaletteHeaders(bool show){displayPaletteHeaders = show;}
    
    /**Sets the number of channels.*/
    inline void setNbChannels(int nb){nbChannels = nb;}

    /**Sets the sampling rate for the dat file.*/
    inline void setDatSamplingRate(double rate){datSamplingRate = rate;}

    /**Sets the sampling rate for the eeg file.*/
    inline void setEegSamplingRate(double rate){eegSamplingRate = rate;}

    /**Sets the initial offset for all the field potentials.*/
    inline void setOffset(int offset){this->offset = offset;}

    /**Sets the resolution of the acquisition system.*/
    inline void setResolutionIndex(int index){resolutionIndex = index;}

    /**Sets the event position, in percentage from the begining of the window, where the events are display when browsing.*/
    inline void setEventPosition(int position){eventPosition = position;}

    /**Sets the cluster position, in percentage from the begining of the window, where the clusters are display when browsing.*/
    inline void setClusterPosition(int position){clusterPosition = position;}

    /**Sets the number of samples per spike waveform.*/
    inline void setNbSamples(int nb){nbSamples = nb;}

    /**Sets the index of the peak sample in the spike waveform.*/
    inline void setPeakIndex(int index){peakIndex = index;}

    /**Sets the video acquisition sampling rate.*/
    inline void setSamplingRate(double rate){videoSamplingRate = rate;}

    /**Sets the video image width.*/
    inline void setWidth(int width){this->width = width;}

    /**Sets the video image height.*/
    inline void setHeight(int height){this->height = height;}

    /**Sets the background image for the position view.*/
    inline void setBackgroundImage(QString image){backgroundImage = image;}

    /**Sets the video image rotation angle.*/
    inline void setRotation(int angle){rotation = angle;}

    /**Sets the  video image flip orientation.*/
    inline void setFlip(int index){flip = index;}
    
    /**All the positions contained in a position file can be used to create a background image for the PositionView.
    * This function sets if such background has to be created.
    */
    inline void setPositionsBackground(int drawPositions){drawPositionsOnBackground = drawPositions;}
    
    /**Sets the background image for the trace view.*/
    inline void setTraceBackgroundImage(QString image){traceBackgroundImage = image;}
    
    /**Returns the screen gain in milivolts by centimeters used to display the field potentiels.
    */
    inline float getScreenGain() const{
        return screenGainDefault;
    }

    /**Returns the voltage range of the acquisition system in volts.
    */
    inline int getVoltageRange() const{
        return voltageRange;
    }

    /**Returns the amplification of the acquisition system.
    */
    inline int getAmplification() const{
        return amplificationDefault;
    }


    /**Returns the background color.*/
    inline QColor getBackgroundColor() const{return backgroundColor;}

    /**Returns true if the palette headers are displayed, false othewise.*/
    inline bool isPaletteHeadersDisplayed() const{return displayPaletteHeaders;}
    
    /**Returns the number of channels.*/
    inline int getNbChannels() const{return nbChannels;}

    /**Returns sampling rate for the dat file.*/
    inline double getDatSamplingRate() const{return datSamplingRate;}

    /**Returns sampling rate for the eeg file.*/
    inline double getEegSamplingRate() const{return eegSamplingRate;}

    /**Returns the initial offset for all the field potentials.*/
    inline int getOffset() const{return offset;}

    /**Returns the resolution of the acquisition system.*/
    inline int getResolution()const{
        switch(resolutionIndex){
        case 0:
            return 12;
        case 1:
            return 14;
        case 2:
            return 16;
        case 3:
            return 32;
        default:
            return 16;
        }
    }

    /**Returns the index corresponding to there solution of the acquisition system.*/
    inline int getResolutionIndex() const{return resolutionIndex;}

    /**Returns the background image for the TraceView.*/
    inline QString getTraceBackgroundImage()const{return traceBackgroundImage;}

    /**Returns the event position, in percentage from the begining of the window, where the events are display when browsing.*/
    inline int getEventPosition()const{return eventPosition;}
    
    /**Returns the cluster position, in percentage from the begining of the window, where the clusters are display when browsing.*/
    inline int getClusterPosition()const{return clusterPosition;}

    /**Returns the number of samples per spike waveform.*/
    inline int getNbSamples()const{return nbSamples;}

    /**Returns the index of the peak sample in the spike waveform.*/
    inline int getPeakIndex()const{return peakIndex;}

    /**Returns the video acquisition sampling rate.*/
    inline double getVideoSamplingRate()const{return videoSamplingRate;}

    /**Returns the video image width.*/
    inline int getWidth()const{return width;}

    /**Returns the video image height.*/
    inline int getHeight()const{return height;}

    /**Returns the background image.*/
    inline QString getBackgroundImage()const{return backgroundImage;}

    /**Returns the video image rotation angle.*/
    inline int getRotation()const{return rotation;}

    /**Returns the video image flip orientation.
    * 0 stands for none, 1 for vertical and 2 for horizontal.
    */
    inline int getFlip()const{return flip;}
    
    /**All the positions contained in a position file can be used to create a background image for the PositionView.
    * The value return by this function tells if such background has to be created.
    * @return true if the all the positions contain in the position file have to be drawn on the background, false otherwise.
    */
    inline bool getPositionsBackground()const{return drawPositionsOnBackground;}
    
    /**Returns the default screen gain in milivolts by centimeters used to display the field potentiels.
    */
    inline float getScreenGainDefault() const{
        return screenGainDefault;
    }

    /**Returns the default voltage range of the acquisition system in volts.
    */
    inline int getVoltageRangeDefault() const{
        return voltageRangeDefault;
    }

    /**Returns the default amplification of the acquisition system.
    */
    inline int getAmplificationDefault() const{
        return amplificationDefault;
    }

    /**Returns the default background color.*/
    inline QColor getBackgroundColorDefault() const{return backgroundColorDefault;}

    /**Returns the default value for the display of the palette headers,
    * true if the palette headers are displayed, false othewise.*/
    inline bool isPaletteHeadersDisplayedDefault() const{return displayPaletteHeadersDefault;}
    
    /**Returns the default number of channels.*/
    inline int getNbChannelsDefault() const{return nbChannelsDefault;}

    /**Returns the default sampling rate for the dat file.*/
    inline double getDatSamplingRateDefault() const{return datSamplingRateDefault;}

    /**Returns the default sampling rate for the eeg file.*/
    inline double getEegSamplingRateDefault() const{return eegSamplingRateDefault;}

    /**Returns the default initial offset for all the field potentials.*/
    inline int getOffsetDefault() const{return offsetDefault;}

    /**Returns the index corresponding to the default resolution of the acquisition system.*/
    inline int getResolutionIndexDefault()const{return resolutionIndexDefault;}

    /**Returns the default event position, in percentage from the begining of the window, where the events are display when browsing.*/
    inline int getEventPositionDefault()const{return eventPositionDefault;}

    /**Returns the default cluster position, in percentage from the begining of the window, where the clusters are display when browsing.*/
    inline int getClusterPositionDefault()const{return clusterPositionDefault;}

    /**Returns the default number of samples per spike waveform.*/
    inline int getNbSamplesDefault()const{return nbSamplesDefault;}

    /**Returns the default index of the peak sample in the spike waveform.*/
    inline int getPeakIndexDefault()const{return peakIndexDefault;}

    /**Returns the default video acquisition sampling rate.*/
    inline double getVideoSamplingRateDefault()const{return videoSamplingRateDefault;}

    /**Returns the default video image width.*/
    inline int getWidthDefault()const{return widthDefault;}

    /**Returns the default video image height.*/
    inline int getHeightDefault()const{return heightDefault;}

    /**Returns the default background image.*/
    inline QString getBackgroundImageDefault()const{return backgroundImageDefault;}

    /**Returns the default video image rotation angle.*/
    inline int getRotationDefault()const{return rotationDefault;}

    /**Returns the default video image flip orientation.
    * 0 stands for none, 1 for vertical and 2 for horizontal.
    */
    inline int getFlipDefault()const{return flipDefault;}

    /**All the positions contained in a position file can be used to create a background image for the PositionView.
    * The value return by this function tells if the default is to create such background.
    * @return true if the all the positions contain in the position file have to be drawn on the background, false otherwise.
    */
    inline bool getPositionsBackgroundDefault()const{return drawPositionsOnBackgroundDefault;}

private:
    /**Screen gain in milivolts by centimeters used to display the field potentiels.*/
    float screenGain;
    /**Voltage range of the acquisition system in volts.*/
    int voltageRange;
    /**Amplification of the acquisition system.*/
    int amplification;
    /**Number of channels.*/
    int nbChannels;
    /**Background color of the views.*/
    QColor backgroundColor;
    /**Sampling rate for the dat file.*/
    double datSamplingRate;
    /**Sampling rate for the eeg file.*/
    double eegSamplingRate;
    /**Initial offset for all the field potentials.*/
    int offset;
    /**Resolution of the acquisition system (in bits).*/
    int resolutionIndex;
    /**Boolean indicating if the headers of the palettes have to be diplayed.*/
    bool displayPaletteHeaders;
    /**Represents event position, in percentage from the begining of the window, where the events are display when browsing.*/
    int eventPosition;
    /**Represents cluster position, in percentage from the begining of the window, where the clusters are display when browsing.*/
    int clusterPosition;
    /**Number of samples per spike waveform.*/
    int nbSamples;
    /**Index of the peak sample in the spike waveform.*/
    int peakIndex;
    /**Video acquisition sampling rate.*/
    double videoSamplingRate;
    /**Video image width.*/
    int width;
    /**Video image height.*/
    int height;
    /**Background image for the position view.*/
    QString backgroundImage;
    /**Angle of rotation of the video records.*/
    int rotation;
    /**Flip horientation of the video records.*/
    int flip;
    /**Boolean indicating if the all the positions contain in the position file have to be drawn on the background.*/
    bool drawPositionsOnBackground;
    /**Background image for the trace view*/
    QString traceBackgroundImage;

    static const float  screenGainDefault;
    static const int  voltageRangeDefault;
    static const int  amplificationDefault;
    static const int  nbChannelsDefault;
    static const double  datSamplingRateDefault;
    static const double  eegSamplingRateDefault;
    static const QColor backgroundColorDefault;
    static const int  offsetDefault;
    static const int  resolutionIndexDefault;
    static const bool displayPaletteHeadersDefault;
    static const int  eventPositionDefault;
    static const int  clusterPositionDefault;
    static const int  nbSamplesDefault;
    static const int  peakIndexDefault;
    static const double  videoSamplingRateDefault;
    static const int  widthDefault;
    static const int  heightDefault;
    static const QString backgroundImageDefault;
    static const int  rotationDefault;
    static const int  flipDefault;
    static const bool drawPositionsOnBackgroundDefault;
    static const QString traceBackgroundImageDefault;

    Configuration();
    inline ~Configuration(){}
    Configuration(const Configuration&);

    friend Configuration& configuration();

};

/// Returns a reference to the application configuration object.
Configuration& configuration();

#endif  // CONFIGURATION_H
