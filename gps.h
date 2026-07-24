#ifndef GPS_H
#define GPS_H

void initGPS();

void updateGPS();

void openGPS();

void drawGPS();


bool gpsHasFix();

float getLatitude();

float getLongitude();

float getAltitude();

float getSpeed();

float getHDOP();

int getHour();

int getMinute();

bool gpsTimeValid();

#endif