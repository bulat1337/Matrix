cmake_minimum_required(VERSION 3.14)

project(Main)

enable_testing()

option(ENABLE_LOGGING "Enable logging" OFF)
set(ENABLE_LOGGING ${ENABLE_LOGGING} CACHE BOOL "Enable logging" FORCE)

option(DUMP_MATRIX "Enables matrix dump" OFF)
set(DUMP_MATRIX ${DUMP_MATRIX} CACHE BOOL "Enables matrix dump" FORCE)

option(ENABLE_BD_TESTS "Enables big data tests" ON)
set(ENABLE_BD_TESTS ${ENABLE_BD_TESTS} CACHE BOOL "Enables big data tests" FORCE)

set(CMAKE_BUILD_TYPE ${CMAKE_BUILD_TYPE} CACHE STRING "Build type")
add_subdirectory(unit_tests/)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(RELEASE_COMPILE_OPTIONS
	-O2
	-fstack-protector
	-fPIE
	-fstrict-overflow
	-Wformat-security
	-Wformat=2
	-Wall
	-Wextra
	-Wnon-virtual-dtor
	-Woverloaded-virtual
	-Wcast-align
	-Wpointer-arith
	-Wunreachable-code
	-Wno-pre-c++17-compat
)

set(DEBUG_COMPILE_OPTIONS
	-D_DEBUG
	-ggdb3
	-O0
	-Wall
	-Wextra
	-Wc++14-compat
	-Wmissing-declarations
	-Wcast-align
	-Wcast-qual
	-Wchar-subscripts
	-Wconversion
	-Wctor-dtor-privacy
	-Wempty-body
	-Wfloat-equal
	-Wformat-security
	-Winline
	-Wnon-virtual-dtor
	-Woverloaded-virtual
	-Wpacked
	-Wpointer-arith
	-Winit-self
	-Wredundant-decls
	-Wshadow
	-Wsign-conversion
	-Wsign-promo
	-Wstrict-overflow=2
	-Wsuggest-override
	-Wswitch-default
	-Wswitch-enum
	-Wundef
	-Wunreachable-code
	-Wunused
	-Wvariadic-macros
	-Wno-missing-field-initializers
	-Wno-narrowing
	-Wno-old-style-cast
	-Wno-varargs
	-Wstack-protector
	-fcheck-new
	-fsized-deallocation
	-fstack-protector
	-fstrict-overflow
	-fno-omit-frame-pointer
	-Wlarger-than=8192
	-fPIE
	-Werror=vla
	-Wno-pre-c++17-compat
	-Wno-pre-c++20-compat
	-fsanitize=address,alignment,bool,bounds,enum,float-cast-overflow,float-divide-by-zero,integer-divide-by-zero,nonnull-attribute,null,return,returns-nonnull-attribute,shift,signed-integer-overflow,undefined,unreachable,vla-bound,vptr
)

# ----- executable -----

add_executable(matrix.x ./main.cpp)
target_include_directories(matrix.x PRIVATE
	${CMAKE_SOURCE_DIR}/include
	${CMAKE_SOURCE_DIR}/include/detail
	${CMAKE_SOURCE_DIR}/utils/include
	${CMAKE_SOURCE_DIR}/RB_Tree/include)

if(ENABLE_LOGGING)
	target_compile_definitions(matrix.x PRIVATE ENABLE_LOGGING)
endif()

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
	target_compile_definitions(matrix.x PRIVATE DEBUG)
	target_compile_options(matrix.x PRIVATE ${DEBUG_COMPILE_OPTIONS})

	target_link_options(matrix.x PRIVATE
		-fsanitize=address,alignment,bool,bounds,enum,float-cast-overflow,float-divide-by-zero,nonnull-attribute,null,return,returns-nonnull-attribute,shift,signed-integer-overflow,undefined,unreachable,vla-bound,vptr
	)
else()
	target_compile_options(matrix.x PRIVATE ${RELEASE_COMPILE_OPTIONS})
endif()

# test generator

add_executable(test_gen.x ./test_gen.cpp)
target_include_directories(test_gen.x PRIVATE
	${CMAKE_SOURCE_DIR}/include
	${CMAKE_SOURCE_DIR}/include/detail
	${CMAKE_SOURCE_DIR}/utils/include)

if(ENABLE_LOGGING)
	target_compile_definitions(test_gen.x PRIVATE ENABLE_LOGGING)
	if(DUMP_MATRIX)
		target_compile_definitions(test_gen.x PRIVATE DUMP_MATRIX)
	endif()
endif()


if(CMAKE_BUILD_TYPE STREQUAL "Debug")
	target_compile_definitions(test_gen.x PRIVATE DEBUG)
	target_compile_options(test_gen.x PRIVATE ${DEBUG_COMPILE_OPTIONS})

	target_link_options(test_gen.x PRIVATE
		-fsanitize=address,alignment,bool,bounds,enum,float-cast-overflow,float-divide-by-zero,nonnull-attribute,null,return,returns-nonnull-attribute,shift,signed-integer-overflow,undefined,unreachable,vla-bound,vptr
	)
else()
	target_compile_options(test_gen.x PRIVATE ${RELEASE_COMPILE_OPTIONS})
endif()

