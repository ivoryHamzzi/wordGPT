cmake_minimum_required(VERSION 3.0)

project(wordGPT)
SET ( CMAKE_VERBOSE_MAKEFILE true )

option(CURL_STATIC_LINKING "Set to ON to build libcurl with static linking."  OFF)

if(CURL_STATIC_LINKING)
    message("-DCURL_STATICLIB [added]")
    add_definitions(-DCURL_STATICLIB)
endif()

add_definitions(-DJSON_USE_IMPLICIT_CONVERSIONS=0)

# SET(CURL_MIN_VERSION "7.61.0")
find_package(CURL REQUIRED)

include_directories(${CURL_INCLUDE_DIRS})

message("Using compiler ${CMAKE_CXX_COMPILER_ID} ${CMAKE_CXX_COMPILER_VERSION}")

set (TARGETS_EXAMPLES
    main
    dict
    lang
    quiz
    record
    user
)

add_executable(word_gpt main.cc dict.cc lang.cc quiz.cc record.cc user.cc)
    set_property(TARGET word_gpt PROPERTY CXX_STANDARD 20)
    set_property(TARGET word_gpt PROPERTY CXX_STANDARD_REQUIRED ON)
    target_compile_options(word_gpt PRIVATE
        $<$<CXX_COMPILER_ID:MSVC>:/W4>
        $<$<NOT:$<CXX_COMPILER_ID:MSVC>>:-Wall -Wextra -pedantic>
    )
    target_link_libraries(word_gpt ${CURL_LIBRARIES})


