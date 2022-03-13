DIR="external"
if [ -d "$DIR" ]; then
   echo "$DIR directory already exists! Doing nothing."
else
    echo "Downloading depencies at: '$DIR'"

    git clone https://github.com/Dav1dde/glad.git "$DIR/glad"
    git clone https://github.com/glfw/glfw.git "$DIR/glfw"
    git clone https://github.com/fmtlib/fmt.git "$DIR/fmt"
    git clone https://github.com/gelldur/EventBus.git "$DIR/eventBus"
    git clone https://github.com/btzy/nativefiledialog-extended.git "$DIR/nativefiledialog-extended"
    git clone https://github.com/d99kris/rapidcsv.git "$DIR/rapidcsv"
    git clone https://github.com/Tencent/rapidjson.git "$DIR/rapidjson"
    git clone https://github.com/nothings/stb.git "$DIR/stb"
    git clone git@github.com:tatolevicz/binapi-no-deps.git "$DIR/binapi"

#    FORKS TEAM
    git clone --branch docking git@github.com:TheBrokeTeam/imgui.git "$DIR/imgui"
    git clone --branch brokerapp git@github.com:TheBrokeTeam/implot.git "$DIR/implot"
    git clone git@github.com:TheBrokeTeam/imnodes.git "$DIR/node_editor"
    git clone git@github.com:TheBrokeTeam/miniz-cpp.git "$DIR/miniz-cpp"

fi