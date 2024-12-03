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

message("Fetching pico_headers...")
FetchContent_Declare(
  picoheaders
  GIT_REPOSITORY https://github.com/empyreanx/pico_headers.git
  GIT_TAG 080269a444fc4e4577ac40d929d1134a475f0f0e
)
FetchContent_MakeAvailable(picoheaders)

message("Fetching rres...")
FetchContent_Declare(
  rres
  GIT_REPOSITORY https://github.com/raysan5/rres.git
  GIT_TAG 536eb301e05e2fafd631e766baeb92d76e6c8f81
)
FetchContent_MakeAvailable(rres)

message("Fetching pico-ecs-cpp...")
FetchContent_Declare(
  picoecscpp
  GIT_REPOSITORY https://github.com/anupyldd/pico-ecs-cpp.git
  GIT_TAG 2588b4a77147c443a7f7f3ba781e96ee633b7041
)
FetchContent_MakeAvailable(picoecscpp)

message("Fetching reflect-cpp...")
FetchContent_Declare(
  reflectcpp
  GIT_REPOSITORY https://github.com/getml/reflect-cpp.git
  GIT_TAG e51edb704e6e21d12319b9392c024b6060d37a51
)
FetchContent_MakeAvailable(reflectcpp)

#message("Fetching rapidjson...")
#FetchContent_Declare(
#	rapidjson
#	GIT_REPOSITORY https://github.com/Tencent/rapidjson.git
#	GIT_TAG f54b0e47a08782a6131cc3d60f94d038fa6e0a51
#)
#FetchContent_MakeAvailable(rapidjson)

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

message("Copying pico_headers")
file(MAKE_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/vendor/pico)
set(PICO_DIR ${CMAKE_CURRENT_SOURCE_DIR}/vendor/pico)
file(COPY ${picoheaders_SOURCE_DIR}/pico_ecs.h DESTINATION ${PICO_DIR})
file(COPY ${picoecscpp_SOURCE_DIR}/src/PicoEcsCpp.h DESTINATION ${PICO_DIR})

# for some reason there's no yyjson header in the sources
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
src/utility/RresImpl.c
src/utility/RresImpl.h

src/core/App.h
src/core/App.cpp
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
src/core/map/ComponentSerializer.h
src/core/map/ComponentSerializer.cpp
src/core/map/Systems.h
src/core/map/MapUtil.h
src/core/map/ResourcePack.h

src/gui/Gui.h
src/gui/Gui.cpp
src/gui/GuiObject.h
src/gui/GuiStates.h
src/gui/MainMenu.h
src/gui/MainMenu.cpp

####################################################

${reflectcpp_SOURCE_DIR}/src/reflectcpp.cpp
${reflectcpp_SOURCE_DIR}/src/reflectcpp_json.cpp
${reflectcpp_SOURCE_DIR}/src/yyjson.c

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
	${rres_SOURCE_DIR}/src
	${reflectcpp_SOURCE_DIR}/include
	${IMGUI_DIR}
	${PICO_DIR}
	${VENDOR_DIR}
)

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET mmt PROPERTY CXX_STANDARD 20)
endif()

add_compile_options(/utf-8)
add_compile_options(/permissive)