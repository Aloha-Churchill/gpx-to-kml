# GPX to KML Parser

## Plan For Approach
* There are three major types of coordinates in gpx files
    * wpt = singular markers ==> Placemark (Point) in KML
    * trkpt = ordered points that are part of a path ==> Placemark (LineString) in KML
    * rtept = ordered list of waypoints

Traverse through the DOM structure and write any waypoints to Points in KML immediately. Wpt will be children of gpx doc root usually. 
If encounter trk, then find children trkseg, then traverse through trkpt children of trkseg and convert to coordinates of lineseg in KML file.

Helpful documents
- https://www.topografix.com/gpx.asp


# Run
```make all```
```make run```


