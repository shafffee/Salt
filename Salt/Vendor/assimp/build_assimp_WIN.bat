REM # creating folders
mkdir build\
mkdir include\
mkdir lib\

REM # build assimp
cd build
cmake ../assimp-master/CMakeLists.txt -DBUILD_SHARED_LIBS=OFF -DASSIMP_BUILD_ZLIB=ON -DASSIMP_INJECT_DEBUG_POSTFIX=OFF
cmake --build .


REM # copy includes
cd ../
xcopy assimp-master\include\ include\ /E /Y
xcopy build\include\ include\ /E /Y

REM # copy lib file
xcopy build\lib\Debug\ lib\ /E /Y
xcopy build\contrib\zlib\Debug lib\ /E /Y

pause