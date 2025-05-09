cmake_minimum_required(VERSION 3.15)
project(SloteProject LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
option(BUILD_SHARED_LIBS "Build shared libraries" OFF)

include(FetchContent)

FetchContent_Declare(SFML
        GIT_REPOSITORY https://github.com/SFML/SFML.git
        GIT_TAG 2.6.x
        GIT_SHALLOW ON
        EXCLUDE_FROM_ALL
        SYSTEM)
FetchContent_MakeAvailable(SFML)

add_executable(${PROJECT_NAME} WIN32
src/main.cpp
src/Variables.cpp
src/Colors.cpp
src/Triangle.cpp
src/Star.cpp
src/SloteDraw.cpp 
src/SloteLogic.cpp
src/MyShape.cpp
src/Rectangle.cpp
src/Circle.cpp
src/TextButton.cpp
src/ResourceManager.cpp
src/Combination.cpp
src/Statistic.cpp
src/SloteMachineLogic.cpp
src/SloteMachineDraw.cpp
src/StateLogic.cpp
src/WaitingStateLogic.cpp
src/SpinningStateLogic.cpp
src/ShowWinStateLogic.cpp
src/GameScene.cpp
src/DrawScene.cpp
src/Button.cpp
src/ButtonRender.cpp)

target_link_libraries(${PROJECT_NAME} PRIVATE sfml-graphics sfml-network sfml-audio)
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_17)

file(COPY res/ DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
if(WIN32)
    add_custom_command(
        TARGET ${PROJECT_NAME}
        COMMENT "Copy OpenAL DLL"
        PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy 
        ${SFML_SOURCE_DIR}/extlibs/bin/$<IF:$<EQUAL:${CMAKE_SIZEOF_VOID_P},8>,x64,x86>/openal32.dll
        $<TARGET_FILE_DIR:${PROJECT_NAME}>
        VERBATIM
    )

    file(GLOB SFML_DLLS "${SFML_BINARY_DIR}/bin/*.dll")
    foreach(dll ${SFML_DLLS})
        add_custom_command(
            TARGET ${PROJECT_NAME}
            POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different 
            ${dll} 
            $<TARGET_FILE_DIR:${PROJECT_NAME}>
            COMMENT "Copying ${dll} to the output directory"
        )
    endforeach()
endif()