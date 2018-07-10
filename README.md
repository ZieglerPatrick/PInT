<h1>How to install and use the tool</h1>
<h2>1. Prerequisites</h2>
1) Install clang 5 with libTooling support<br>
2) Install cmake (3.4.1)<br>
3) Clone the git repository to your machine

<h2>2. Installing the tool</h2>
1) Change into the source directory<br>
2) Create a new directory ('mkdir build')<br>
3) Change into the new directory ('cd build')<br>
4) Create the build system ('ccmake ..')<br>
5) Compile the tool ('make')

<h2>3. Using the tool</h2>
<h3>3.1 Instrumentation of your code</h3>
1) Include pattern instrumentation headers (Mind the C and CPP versions) in your source file<br>
2) Add instrumenation commands at the beginning and end of code regions that belong to a pattern

<h3>3.2 <b>Optional:</b> Create compile_commands.json</h3>
1) Create a cmake project for your source files, or use an existing project<br>
2) Set the variable "EXPORT_COMPILE_COMMANDS" to true<br>
3) Create/update your build system ('mkdir build && cd build && ccmake ..')<br>
4) Copy compile_commands.json to the directory with the sources<br>
<b>OR</b><br>
Write your compile_commands.json manually. But I would advise against doing that.

<h3>3.3 Running the tool</h3>
1) If you created no compilation database: think of the parameters you would want to pass to the clang compiler<br>
2) Call the tool ('./HPC-pattern-tool /path/to/your/code.cpp [path/to/your/codeN.cpp] -- -extra-args=Your-Args-Go-Here')<br>
3) Check output on screen and in csv files if statistics with csv export are used