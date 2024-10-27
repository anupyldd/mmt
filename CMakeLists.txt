cmake_minimum_required (VERSION 3.8)

# some default VS stuff
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project(HillsAndDales LANGUAGES CXX)

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
  GIT_TAG ae50bfa2cc569c0f8d5bc4315d39db64005b1b08
)
FetchContent_MakeAvailable(raylib)

message("Fetching picojson...")
FetchContent_Declare(
  picojson
  GIT_REPOSITORY https://github.com/kazuho/picojson.git
  GIT_TAG 25fc213cca61ea22b3c2e4db8def9927562ba5f7
)
FetchContent_MakeAvailable(picojson)

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

####################################################

message("Working with third-party stuff...")
file(MAKE_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/vendor)
set(VENDOR_DIR ${CMAKE_CURRENT_SOURCE_DIR}/vendor)

message("Copying rlImGui files...")
file(MAKE_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/vendor/imgui)
set(IMGUI_DIR ${CMAKE_CURRENT_SOURCE_DIR}/vendor/imgui)

file(COPY ${rlimgui_SOURCE_DIR}/extras DESTINATION ${IMGUI_DIR})
file(COPY ${rlimgui_SOURCE_DIR}/imgui_impl_raylib.h DESTINATION ${IMGUI_DIR})
file(COPY ${rlimgui_SOURCE_DIR}/rlImGui.h DESTINATION ${IMGUI_DIR})
file(COPY ${rlimgui_SOURCE_DIR}/rlImGuiColors.h DESTINATION ${IMGUI_DIR})
file(COPY ${rlimgui_SOURCE_DIR}/rlImGui.cpp DESTINATION ${IMGUI_DIR})

message("Copying imgui files...")
file(COPY ${imgui_SOURCE_DIR}/backends DESTINATION ${IMGUI_DIR})
file(COPY ${imgui_SOURCE_DIR}/misc DESTINATION ${IMGUI_DIR})
file(COPY ${imgui_SOURCE_DIR}/imconfig.h DESTINATION ${IMGUI_DIR})
file(COPY ${imgui_SOURCE_DIR}/imgui.cpp DESTINATION ${IMGUI_DIR})
file(COPY ${imgui_SOURCE_DIR}/imgui.h DESTINATION ${IMGUI_DIR})
file(COPY ${imgui_SOURCE_DIR}/imgui_demo.cpp DESTINATION ${IMGUI_DIR})
file(COPY ${imgui_SOURCE_DIR}/imgui_draw.cpp DESTINATION ${IMGUI_DIR})
file(COPY ${imgui_SOURCE_DIR}/imgui_internal.h DESTINATION ${IMGUI_DIR})
file(COPY ${imgui_SOURCE_DIR}/imgui_tables.cpp DESTINATION ${IMGUI_DIR})
file(COPY ${imgui_SOURCE_DIR}/imgui_widgets.cpp DESTINATION ${IMGUI_DIR})
file(COPY ${imgui_SOURCE_DIR}/imstb_rectpack.h DESTINATION ${IMGUI_DIR})
file(COPY ${imgui_SOURCE_DIR}/imstb_textedit.h DESTINATION ${IMGUI_DIR})
file(COPY ${imgui_SOURCE_DIR}/imstb_truetype.h DESTINATION ${IMGUI_DIR})

####################################################
####################################################
####################################################

set(SRCS

src/HillsAndDales.cpp

src/utility/Defines.h
src/utility/Log.h
src/utility/Log.cpp 
src/utility/StateMachine.h
src/utility/StringHash.h
src/utility/Observer.h

src/core/App.h
src/core/App.cpp
src/core/Config.h
src/core/Config.cpp
src/core/ConfigStructs.h
src/core/Localization.h
src/core/Localization.cpp

src/core/atlas/Map.h
src/core/atlas/Map.cpp
src/core/atlas/Layer.h
src/core/atlas/Layer.cpp
src/core/atlas/MapObject.h
src/core/atlas/MapObject.cpp
src/core/atlas/MapObjectGroup.h
src/core/atlas/MapObjectGroup.cpp
src/core/atlas/Quadtree.h
src/core/atlas/Quadtree.cpp

src/gui/Gui.h
src/gui/Gui.cpp
src/gui/GuiObject.h
src/gui/GuiStates.h
src/gui/MainMenu.h
src/gui/MainMenu.cpp

####################################################

vendor/imgui/imgui.cpp
vendor/imgui/imgui_demo.cpp
vendor/imgui/imgui_draw.cpp
vendor/imgui/imgui_tables.cpp
vendor/imgui/imgui_widgets.cpp
vendor/imgui/rlImGui.cpp

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
	${picojson_SOURCE_DIR}
	${IMGUI_DIR}
	${VENDOR_DIR}
)

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET HillsAndDales PROPERTY CXX_STANDARD 20)
endif()

add_compile_options(/utf-8)