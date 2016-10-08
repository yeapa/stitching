cmake_minimum_required(VERSION 3.6)
project(stitching)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

link_libraries(-lpthread)
set(SOURCE_FILES
    src/CAnonymSem.cpp
    src/CAnonymSem.h
    src/CConfig.cpp
    src/CConfig.h
    src/CEventObserver.cpp
    src/CEventObserver.h
    src/CException.cpp
    src/CException.h
    src/CLocalLog.cpp
    src/CLocalLog.h
    src/CLocalThreadLog.cpp
    src/CLocalThreadLog.h
    src/CLog.cpp
    src/CLog.h
    src/CMsgQueue.cpp
    src/CMsgQueue.h
    src/CMutex.cpp
    src/CMutex.h
    src/COutDataWkThread.cpp
    src/COutDataWkThread.h
    src/COutDataWkThreadPool.cpp
    src/COutDataWkThreadPool.h
    src/CReator.cpp
    src/CReator.h
    src/CSimpleConfig.cpp
    src/CSimpleConfig.h
    src/CThread.cpp
    src/CThread.h
    src/CThreadPool.cpp
    src/CThreadPool.h
    src/main.cpp
    src/Message.h
    src/CImageTrans.cpp
        src/CImageTrans.h)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "~/Desktop/ye/dataHandle/stitching/bin")
#ffmpeg
include_directories(/usr/local/ffmpeg/include /usr/include/vigra)
link_directories(/usr/local/ffmpeg/lib  /usr/lib)
link_libraries(avformat avcodec avutil avdevice swresample swscale vigraimpex)

add_executable(stitching ${SOURCE_FILES})