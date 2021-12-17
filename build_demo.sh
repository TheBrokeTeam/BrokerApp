#export PATH=$HOME/bin:/usr/local/bin:$PATH
DIR="DemoImplot"

if [ -d "$DIR" ]; then
   echo "$DIR directory already exists!"
else
  echo "Downloading depencies at: '$DIR'"
  git clone --branch docking git@github.com:TheBrokeTeam/imgui.git "$DIR/imgui"
  git clone git@github.com:TheBrokeTeam/implot.git "$DIR/implot"
  git clone --branch fix/build-mac-os git@github.com:TheBrokeTeam/implot_demos.git "$DIR/implot_demos"
fi

cd DemoImplot/implot_demos
mkdir build
cd build
cmake ..
cmake --build . --config Release
cd ..
cd ..

#if [ -d "$DIR" ]; then
#  echo "$DIR directory already exists!"
##    rm -rf "$DIR"
#else
#
#fi
#
