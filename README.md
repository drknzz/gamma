# IPP2020
Project from IPP2020 - GAMMA

::::::BUILD::::::

mkdir release

cd release

cmake ..

make

::::::TARGET::::::

./gamma

::::::PLAY::::::

I (width) (height) (players) (areas)

::::::DEBUG::::::

mkdir debug

cd debug

cmake -D CMAKE_BUILD_TYPE=Debug ..

make

::::::DOCUMENTATION::::::

make doc
