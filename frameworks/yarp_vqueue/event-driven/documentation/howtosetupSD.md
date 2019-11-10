
# How to set-up an SD for a zynq board

## Set-up icub user

(as root)

> groups icub 

> visudo

* add line: "icub ALL=(ALL:ALL) ALL"

> mkdir /usr/local/src/robot

> chown icub /usr/local/src/robot

## Set up repositories

(as icub)

> mkdir /usr/local/src/robot/icub-contrib-install

> vim ~/.bashrc

add lines:

* export ROBOT_CODE=/usr/local/src/robot
* export YARP_DIR=$ROBOT_CODE/yarp/build
* export ICUBcontrib_DIR=$ROBOT_CODE/icub-contrib-install
* export YARP_DATA_DIRS=$YARP_DIR/share/yarp:$ICUBcontrib_DIR/share/ICUBcontrib
* export PATH=$YARP_DIR/bin:$ICUBcontrib_DIR/bin:$PATH
* export ED_ROOT=$ROBOT_CODE/event-driven
  
### Set up YARP

#### Important note:
The newest YARP requires CMake>3.5, which is not installable via apt on the Debian 8.10 (jessie) distribution we have installed on the zynq. To upgrade CMake you need to install it via backports (reference: https://backports.debian.org/Instructions). 
To do so:
 - add to /etc/apt/sources.list the line below:
      deb http://ftp.debian.org/debian jessie-backports main 
- sudo apt update
- sudo apt -t jessie-backports install cmake
 
At this point you should be able to recompile YARP 3.0 and event-driven master branch.
 
**We can consider updating the Debian distribution of the zynq boards since the Debian 8.10 is no longer supported by YARP**

> cd /usr/local/src/robot  

> git clone https://github.com/robotology/yarp

> cd yarp

> mkdir build

> cd build

> ccmake ../

* set CREATE_GUIS = OFF

> make (not install)

### Set up install directory as $ICUBcontrib_DIR
> cd /usr/local/src/robot  

> git clone https://github.com/robotology/icub-contrib-common

> cd icub-contrib-common

> mkdir build

> cd build

> ccmake ../

* set CMAKE_INSTALL_PREFIX=$ICUBcontrib_DIR

> make install


### Set up event-driven 
> cd /usr/local/src/robot  

> git clone https://github.com/robotology/event-driven

> cd event-driven

> mkdir build

> cd build

> ccmake ../

* (cmake should have found install directory as $ICUBcontrib_DIR automatically)
* BUILD_HARDWAREIO = ON

configure and then

* ENABLE_zynqgrabber = ON

> make install
    
## Set up device drivers

(as icub)

> sudo usermod -a -G i2c icub

> sudo vim /lib/udev/rules.d/77-iit-hpu.rules

add lines:

* SUBSYSTEM=="iit-hpu-class", GROUP="i2c"

> sudo vim /etc/rc.local

add lines:

* insmod $PATH_TO_HPU_DRIVER.ko ps=4096
* $PATH_TO_ZYNQGRABBER --biaswrite > /usr/local/src/robot/zynqGrabber.log
  
## Misc

check the device driver meta data

> udevadm info -q all -a /dev/iit-hpu0

check the device driver parameters

> cat /sys/module/iit_hpucore_dma/parameters/ps

