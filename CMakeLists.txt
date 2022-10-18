#放置在src目的是git版本管理，编译时放置在上一级目录：..
#cmake . -G "MinGW Makefiles"
#mingw32-make -f makefile
#需要安装OpenSSL：https://slproweb.com/products/Win32OpenSSL.html
cmake_minimum_required(VERSION 3.8)

project(JpegFile)
set(CMAKE_CXX_COMPILER "D:/dev/ide/codeblocks-20.03mingw-nosetup/MinGW/bin/g++.exe")
set(CMAKE_C_COMPILER "D:/dev/ide/codeblocks-20.03mingw-nosetup/MinGW/bin/gcc.exe")
set(CMAKE_CXX_STANDARD 17)
#set(CMAKE_MAKE_PROGRAM  "D:/dev/ide/CLion-2021.3.4.win/bin/ninja/win/ninja.exe")

#set compile options


SET(CMAKE_BUILD_TYPE "Release")
SET(BOOST_ROOT "D:/dev/cpp_lib/boost")
#SET(Boost_COMPILER "-clang31")
SET(SQLite3 "D:/dev/cpp_lib/sqlite3")
SET(Boost_INCLUDE_DIR "D:/dev/cpp_lib/boost/include")
set(SQLite3_LIBRARY "d:/dev/cpp_lib/sqlite3/libsqlite3.so")
set(SQLite3_INCLUDE_DIR "d:/dev/cpp_lib/sqlite3")
set(Boost_USE_STATIC_LIBS ON)
set(Boost_USE_STATIC_RUNTIME OFF)
set(DEP_LIBS
        OpenSSL::Crypto OpenSSL::SSL  # modern
        #${OPENSSL_SSL_LIBRARY} ${OPENSSL_CRYPTO_LIBRARY}  # old style
        )
set(WX_LIBS
        libwxmsw31u_core.a
        libwxbase31u.a
        libwxpng.a
        libwxzlib.a
        libwxmsw31u_aui.a
        )

find_package(OpenSSL REQUIRED)
find_package(Boost COMPONENTS filesystem thread REQUIRED)   # 最好是加上REQUIRED，否则找不到某些库也不会报错，链接会出问题
find_package (SQLite3)
add_compile_options("$<$<C_COMPILER_ID:GCC>:/utf-8>")
add_compile_options("$<$<CXX_COMPILER_ID:GCC>:/utf-8>")
aux_source_directory(src srcs)
include_directories(
        d:/dev/cpp_lib/sqlite3
        d:/dev/cpp_lib/wxWidgets/include
        d:/dev/cpp_lib/wxWidgets/lib/gcc810_x64_dll/mswud
        D:/projects/cpp/JpegFile
        ${Boost_INCLUDE_DIRS}
)
link_directories(d:/dev/cpp_lib/wxWidgets/lib/gcc810_x64_dll )


#set(SOURCE_FILES main.cpp)
#add_executable(gui WIN32 MACOSX_BUNDLE main.cpp Ai16.xpm Ai48.xpm Avi16.xpm Avi48.xpm Bmp16.xpm Bmp48.xpm)
add_executable(jpegFile WIN32 ${srcs})
#message(STATUS ${WX_LIBS} )
#message(STATUS ${DEP_LIBS} )
message(STATUS ${Boost_LIBRARIES} )
target_link_libraries(
        jpegFile
        ${WX_LIBS}
        ${DEP_LIBS}
        ${Boost_LIBRARIES}
        ${SQLite3_LIBRARY}
        -lcomctl32
)