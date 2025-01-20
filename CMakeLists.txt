cmake_minimum_required (VERSION 3.8)

# some default VS stuff
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project(mmt LANGUAGES CXX C)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

####################################################
####################################################
####################################################


include(FetchContent)

message("Fetching raylib...")
FetchContent_Declare(
  raylib
  GIT_REPOSITORY https://github.com/raysan5/raylib.git
  GIT_TAG c1ab645ca298a2801097931d1079b10ff7eb9df8
)
FetchContent_MakeAvailable(raylib)

message("Fetching rlImGui...")
FetchContent_Declare(
  rlImGui
  GIT_REPOSITORY https://github.com/raylib-extras/rlImGui.git
  GIT_TAG 89107354ea407970e24f6b9a5d6c54e2bebadf35
)
FetchContent_MakeAvailable(rlImGui)

message("Fetching Dear ImGui...")
FetchContent_Declare(
  imgui
  GIT_REPOSITORY https://github.com/ocornut/imgui.git
  GIT_TAG c71e4e8c7cb9b42b460bbaedfa4bc443f885b05b
)
FetchContent_MakeAvailable(imgui)

message("Fetching reflect-cpp...")
FetchContent_Declare(
  reflectcpp
  GIT_REPOSITORY https://github.com/getml/reflect-cpp.git
  GIT_TAG e51edb704e6e21d12319b9392c024b6060d37a51
)
FetchContent_MakeAvailable(reflectcpp)

#message("Fetching PhysicsFS...")
#FetchContent_Declare(
#	physfs
#	GIT_REPOSITORY https://github.com/icculus/physfs.git
#	GIT_TAG eb3383b532c5f74bfeb42ec306ba2cf80eed988c
#)
#FetchContent_MakeAvailable(physfs)

####################################################

# for some reason there's no yyjson header in the reflect-cpp sources
message("Copying yyjson.h")
file(
	COPY 
	${reflectcpp_SOURCE_DIR}/include/rfl/thirdparty/yyjson.h 
	DESTINATION 
	${reflectcpp_SOURCE_DIR}/src)

####################################################
####################################################
####################################################


set(SRCS

src/MMT.cpp

src/utility/Defines.h
src/utility/Log.h
src/utility/Log.cpp
src/utility/StateMachine.h
src/utility/StringUtil.h
src/utility/Observer.h
src/utility/Serialization.h
src/utility/Json.h
src/utility/Zip.h
src/utility/Zip.cpp

src/core/App.h
src/core/App.cpp
src/core/AppStates.h
src/core/AppStates.cpp
src/core/Config.h
src/core/Config.cpp
src/core/Localization.h
src/core/Localization.cpp
src/core/ResourceManager.h
src/core/ResourceManager.cpp

src/core/map/Atlas.h
src/core/map/Atlas.cpp
src/core/map/Map.h
src/core/map/Map.cpp
src/core/map/Components.h
src/core/map/ComponentRegistry.h
src/core/map/Systems.h
src/core/map/Systems.cpp
src/core/map/MapUtil.h
src/core/map/Resources.h
src/core/map/Resources.cpp
src/core/map/PackFolder.h
src/core/map/Pack.h
src/core/map/Pack.cpp
src/core/map/PackManager.h
src/core/map/PackManager.cpp

src/gui/Gui.h
src/gui/Gui.cpp
src/gui/GuiObject.h
src/gui/GuiStates.h
src/gui/MainMenu.h
src/gui/MainMenu.cpp
src/gui/ResourceView.h
src/gui/ResourceView.cpp

####################################################

${reflectcpp_SOURCE_DIR}/src/reflectcpp.cpp
${reflectcpp_SOURCE_DIR}/src/reflectcpp_json.cpp
${reflectcpp_SOURCE_DIR}/src/yyjson.c

${imgui_SOURCE_DIR}/imgui.cpp
${imgui_SOURCE_DIR}/imgui_demo.cpp
${imgui_SOURCE_DIR}/imgui_draw.cpp
${imgui_SOURCE_DIR}/imgui_tables.cpp
${imgui_SOURCE_DIR}/imgui_widgets.cpp
${rlimgui_SOURCE_DIR}/rlImGui.cpp

${CMAKE_CURRENT_SOURCE_DIR}/vendor/log/loguru.hpp
${CMAKE_CURRENT_SOURCE_DIR}/vendor/log/loguru.cpp

####################################################

)

####################################################
####################################################
####################################################

add_executable("${PROJECT_NAME}" ${SRCS})

message("Linking libraries...")
target_link_libraries(
	"${PROJECT_NAME}" 
	PRIVATE 
	raylib
)

message("Including directories...")
target_include_directories(
	"${PROJECT_NAME}" 
	PUBLIC 
	${raylib_SOURCE_DIR}/src 
	${raylib_SOURCE_DIR}/src/external 
	${raylib_SOURCE_DIR}/src/external/glfw/include 
	${imgui_SOURCE_DIR}
	${rlimgui_SOURCE_DIR}
	${reflectcpp_SOURCE_DIR}/include
	${spdlog_SOURCE_DIR}/include
	${physfs_SOURCE_DIR}/src
	${CMAKE_CURRENT_SOURCE_DIR}/vendor
)

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET mmt PROPERTY CXX_STANDARD 20)
endif()

add_compile_options(/utf-8)
add_compile_options(/permissive)

#add_custom_command(TARGET mmt POST_BUILD
#                   COMMAND ${CMAKE_COMMAND} -E copy_directory
#                       ${CMAKE_SOURCE_DIR}/data/ $<TARGET_FILE_DIR:mmt>/data)

#add_custom_command(TARGET mmt PRE_BUILD
#    COMMAND ${CMAKE_COMMAND} -E rm -rf $<TARGET_FILE_DIR:mmt>/data
#    COMMAND ${CMAKE_COMMAND} -E copy_directory
#        ${CMAKE_SOURCE_DIR}/data/ $<TARGET_FILE_DIR:mmt>/data)

set(DATA_OUTPUT_DIR ${CMAKE_BINARY_DIR}/data)

file(GLOB_RECURSE DATA_FILES ${CMAKE_SOURCE_DIR}/data/*)

add_custom_target(copy_data ALL
    COMMAND ${CMAKE_COMMAND} -E rm -rf ${DATA_OUTPUT_DIR}
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/data ${DATA_OUTPUT_DIR}
    DEPENDS ${DATA_FILES}
)

add_custom_command(
    TARGET mmt POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${DATA_OUTPUT_DIR} $<TARGET_FILE_DIR:mmt>/data
)