cmake_minimum_required( VERSION 3.17 )
project( blockchain_tools )

include_directories( ${CMAKE_CURRENT_SOURCE_DIR} ${MAIN_LIB_DIRECTORY} )

add_library(${PROJECT_NAME} SHARED
        src/nginx_ordinary_parameter.cpp
        src/nginx_config_parameter.cpp
        src/nginx_parameter_writer.cpp
        src/nginx_config_constructor.cpp
        src/nginx_db_connector.cpp
        src/nginx_resource_configuration.cpp
        src/nginx_server_parameters.cpp
        src/nginx_configuration.cpp
        src/nginx_parameters_tools.cpp
        src/nginx_license_configuration.cpp
        nginx_ordinary_parameter.h
        nginx_config_parameter.h
        nginx_parameter_writer.h
        nginx_config_constructor.h
        nginx_db_connector.h
        nginx_resource_configuration.h
        nginx_server_parameters.h
        nginx_configuration.h
        nginx_license_configuration.h
        nginx_parameter_builder.h
        nginx_parameters_tools.h
        nginx_parameter_interface.h
        nginx_server.h src/nginx_server.cpp)

target_link_libraries( ${PROJECT_NAME}

        )

install( TARGETS ${PROJECT_NAME} DESTINATION opt/itcs/lib PERMISSIONS OWNER_READ OWNER_WRITE OWNER_EXECUTE GROUP_READ GROUP_EXECUTE WORLD_READ WORLD_EXECUTE)