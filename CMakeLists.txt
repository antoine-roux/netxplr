cmake_minimum_required(VERSION 2.8)
project (netxplr)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(CMAKE_MODULE_PATH cmake)
set(EXECUTABLE_OUTPUT_PATH bin)
set(LIBRARY_OUTPUT_PATH lib)

# Debug
set(CMAKE_BUILD_TYPE Debug)

find_package(NetSNMP REQUIRED)
find_package(DL REQUIRED)
find_package(Threads REQUIRED)

include_directories(
	${NETSNMP_INCLUDE_DIR}
	${DL_INCLUDE_DIR}
)

# Commons
file(GLOB PRIMITIVES_CPP "src/primitives/*.cpp")

##
# Executables
#
file(GLOB MODEL_CPP "src/model/*.cpp")
file(GLOB TRANSLATORS_CPP "src/translators/*.cpp")
file(GLOB REQUEST_CPP "src/requests/*.cpp")
add_executable(netxplr
	${PRIMITIVES_CPP}
	${MODEL_CPP}
	${TRANSLATORS_CPP}
	${REQUEST_CPP}
	src/main.cpp
)

target_link_libraries(netxplr
	${DL_LIBRARIES}
	${CMAKE_THREAD_LIBS_INIT}
)

##
# Modules
#
file(GLOB MODULE_COMMON_CPP "src/modules/common/*.cpp")

add_library(ip-mac_snmp SHARED
	${PRIMITIVES_CPP}
	${MODULE_COMMON_CPP}
	src/modules/ip-mac_snmp/main.cpp
)
target_link_libraries(ip-mac_snmp
	${NETSNMP_LIBRARIES}
)

add_library(mac-port_snmp SHARED
	${PRIMITIVES_CPP}
	${MODULE_COMMON_CPP}
	src/modules/mac-port_snmp/main.cpp
)
target_link_libraries(mac-port_snmp
	${NETSNMP_LIBRARIES}
)
