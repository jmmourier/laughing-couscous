# build boost with arm architecture

mkdir -p ./software/external/boost/stage

cd ./software/external/boost

./bootstrap.sh --prefix=./software/external/boost/stage
rm -rf project-config.jam
./b2 toolset=gcc-arm --project-config=project-config.jam install