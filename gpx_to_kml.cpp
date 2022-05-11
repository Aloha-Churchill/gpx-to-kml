#include <iostream>
#include <stdio.h>
#include <fstream>
#include <vector>
#include <sstream>
#include <iomanip>
#include <stack>
#include <string>
#include <cstring>
#include "pugi/pugixml.hpp"

using namespace std;
using namespace pugi;

#define PRECISION 13
#define FILENAME_BUF 256

void error(const char* message){
    perror(message);
    exit(1);
}

void write_kml_header(ofstream& file){
    file << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n";
    file << "<kml xmlns=\"http://www.opengis.net/kml/2.2\">\n";
    file << "<Document>\n";
}

void write_kml_footer(ofstream& file){
    file << "</Document>\n";
    file << "</kml>";   
}


void write_kml_placemark(ofstream& file, const char* lat, const char* lon, const char* ele){
    file << lon << "," << lat << "," << ele;     
}
void write_to_kml(ofstream& file, const char* text){
    file << text;
}

void parse_gpx_file(const char* filename, ofstream& kml_file){
    xml_document doc;

    xml_parse_result result = doc.load_file(filename);
    if(!result){
        error("Could not load file\n");
    }

    xml_node root = doc.child("gpx");
    if(root == NULL){
        printf("Root is null\n");
    }

    stack<xml_node> s;
    s.push(root);

    // traverse through DOM tree structure
    while(!s.empty()){
        xml_node top = s.top();
        s.pop();
        for(xml_node child = top.first_child(); child; child = child.next_sibling()){
            s.push(child);
        }
        // if node type is waypoint
        if(strcmp(top.name(),"wpt") == 0){

            write_to_kml(kml_file, "<Placemark>\n\t<Point>\n\t\t<coordinates>");
            write_kml_placemark(kml_file, top.attribute("lat").value(), top.attribute("lon").value(), top.child("ele").text().get());
            write_to_kml(kml_file, "</coordinates>\n\t</Point>\n</Placemark>\n");
        }
        else if(strcmp(top.name(), "trk") == 0){
            xml_node trkseg = top.child("trkseg");
            // iterate through trkpt of trkseg
            write_to_kml(kml_file, "<Placemark>\n<LineString>\n<coordinates>\n");
            for(xml_node trkpt = trkseg.child("trkpt"); trkpt; trkpt = trkpt.next_sibling("trkpt")){

                write_kml_placemark(kml_file, trkpt.attribute("lat").value(), trkpt.attribute("lon").value(), trkpt.child("ele").text().get());
                write_to_kml(kml_file, "\n");
            }
            write_to_kml(kml_file, "</coordinates>\n</LineString>\n</Placemark>\n");
        }  
    }
}

int main(int argc, char* argv[]){
    if(argc < 2){
        error("Needs to take in at least one filename\n");
    }

    for(int i=1; i<argc; i++){
        ofstream kml_file;

        char kml_filename[FILENAME_BUF];
        bzero(kml_filename, FILENAME_BUF);

        strcpy(kml_filename,"output-");
        strcat(kml_filename, to_string(i).c_str());
        strcat(kml_filename, ".kml");
        
        kml_file.open(kml_filename);
        if(!kml_file.is_open()){
            error("Could not open kml file\n");
        }

        write_kml_header(kml_file);
        parse_gpx_file(argv[i], kml_file);

        write_kml_footer(kml_file);

        kml_file.close();
    }
    

    return 0;
}