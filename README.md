Plan for Approach
* There are two major types of coordinates in gpx files
    * wpt = singular markers ==> Placemark (Point) in KML
    * trkpt = ordered points that are part of a path ==> Placemark (LineString) in KML


Traverse through the DOM structure and write any waypoints to Points in KML immediately. Wpt will be children of gpx doc root usually. 
If encounter trk, then find children trkseg, then traverse through trkpt children of trkseg and convert to coordinates of lineseg in KML file.

We want level order? Actually probably Inorder traversal through tree. 
if encounter waypoint --> immediately write to kml
if encounter trk, then traverse down it and write to kml