#!/bin/bash
cityname="SIN"
cd build
echo `date`
echo "start osrm-extract"
./osrm-extract -p car.lua ${cityname}.osm.pbf
echo `date`

echo "start osrm-partition"
./osrm-partition ${cityname}.osrm
echo `date`

echo "start osrm-customize"
./osrm-customize ${cityname}.osrm

echo `date`
echo "pb files"
ls *.pb
