cmake_minimum_required(VERSION 2.6)

set(MODULENAME autosaccade)
project(${MODULENAME})

file(GLOB source src/*.cpp)
file(GLOB header include/*.h)

include_directories(${PROJECT_SOURCE_DIR}/include
                    ${EVENTDRIVENLIBS_INCLUDE_DIRS})

add_executable(${MODULENAME} ${source} ${header})

target_link_libraries(${MODULENAME} ${YARP_LIBRARIES} ${EVENTDRIVEN_LIBRARIES})

install(TARGETS ${MODULENAME} DESTINATION bin)

yarp_install(FILES ${MODULENAME}.ini DESTINATION ${ICUBCONTRIB_CONTEXTS_INSTALL_DIR}/${CONTEXT_DIR})
yarp_install(FILES app_${MODULENAME}.xml.template DESTINATION ${ICUBCONTRIB_APPLICATIONS_TEMPLATES_INSTALL_DIR})
if(ADD_DOCS_TO_IDE)
    add_custom_target(${MODULENAME}_docs SOURCES ${MODULENAME}.ini ${MODULENAME}.xml app_${MODULENAME}.xml.template)
endif(ADD_DOCS_TO_IDE)
