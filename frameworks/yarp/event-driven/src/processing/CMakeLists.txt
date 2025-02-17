cmake_minimum_required(VERSION 2.6)

option(ENABLE_vFramer "Build visualisation module" ON)
option(ENABLE_vPreProcess "Build simple pre-processing module" ON)
option(ENABLE_vCircle "Build circle detector" OFF)
option(ENABLE_vCluster "Build cluster tracker" OFF)
option(ENABLE_vFlow "Build optical flow module" OFF)
option(ENABLE_vDelayControl "Build real-time circle tracker" OFF)
option(ENABLE_vSkinInterface "Build basic skin pre-processing" OFF)
option(ENABLE_vCorner "Build corner detection module" OFF)
option(ENABLE_DualCamTransform "Build Frame->ATIS geometric transform" OFF)

find_package(OpenCV)
if(OpenCV_FOUND)

    if(ENABLE_vFramer)
        add_subdirectory(vFramer)
    endif()

    if(ENABLE_vPreProcess)
        add_subdirectory(vPreProcess)
    endif()

else(OpenCV_FOUND)
    message("Warning: OpenCV not found. Skipping vFramer, vUndistortCam")
endif(OpenCV_FOUND)

if(ENABLE_vCircle)
    if(VLIB_DEPRECATED)
        add_subdirectory(vCircle)
    else()
        message("vCircle requries VLIB_DEPRECATED")
    endif()
endif()

if(ENABLE_vCluster)
    add_subdirectory(vCluster)
endif()

if(ENABLE_vFlow)
    if(VLIB_DEPRECATED)
        add_subdirectory(vFlow)
    else()
        message("vFlow requries VLIB_DEPRECATED")
    endif()
endif()

if(ENABLE_vDelayControl)
    add_subdirectory(vDelayControl)
endif()

if(ENABLE_vSkinInterface)
    add_subdirectory(vSkinInterface)
endif()

if(ENABLE_vCorner)
    if(VLIB_DEPRECATED)
        add_subdirectory(vCorner)
    else()
        message("vCorner requries VLIB_DEPRECATED")
    endif()
endif()

if(ENABLE_DualCamTransform)
    add_subdirectory(DualCamTransform)
endif()


