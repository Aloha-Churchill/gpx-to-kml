COMPILER = g++
FLAGS = -Wall -g
OBJ = gpx_to_kml.cpp pugi/pugixml.cpp
EXE = gpx_to_kml

run: $(EXE)
	./$(EXE) gpx_samples/germany.gpx gpx_samples/gpx_simple.gpx gpx_samples/strava_run.gpx
	mv *.kml kml_output/

all: $(OBJ)
	$(COMPILER) $(FLAGS) $(OBJ) -o $(EXE)
	
clean:
	rm $(EXE)