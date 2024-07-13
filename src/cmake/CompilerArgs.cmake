if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
    message(STATUS "Setting build type to 'Debug' as none was specified.")
    set(CMAKE_BUILD_TYPE Debug CACHE STRING "Choose the type of build.")
    set_property(
        CACHE CMAKE_BUILD_TYPE
        PROPERTY STRINGS
                 "Debug"
                 "Release"
                 "MinSizeRel"
                 "RelWithDebInfo"
    )
endif()

if(CMAKE_CXX_COMPILER_ID MATCHES ".*Clang|GNU")
    if(CMAKE_BUILD_TYPE STREQUAL Debug)
        add_compile_options(-Og)
        add_compile_options(-ggdb)
        add_compile_options(-fno-omit-frame-pointer)
    else()
        target_compile_options(${PROJECT_NAME} PUBLIC -Ofast)
    endif()
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    if(CMAKE_BUILD_TYPE STREQUAL Debug)
        add_compile_options(/Od)
        add_compile_options(/Zi)
        add_compile_options(/MTd)
        add_compile_options(/MDd)
        add_compile_options(-UNDEBUG)
    else()
        add_compile_options(/O2)
    endif()
endif()

if(CMAKE_CXX_COMPILER_ID MATCHES ".*Clang")
    if(WIN32)
        add_compile_options(
            $<$<COMPILE_LANGUAGE:C>:-fcolor-diagnostics>
            $<$<COMPILE_LANGUAGE:CXX>:-fcolor-diagnostics>
        )
    else()
        add_compile_options(-fcolor-diagnostics)
    endif()
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    if(WIN32)
        add_compile_options(
            $<$<COMPILE_LANGUAGE:C>:-fdiagnostics-color=always>
            $<$<COMPILE_LANGUAGE:CXX>:-fdiagnostics-color=always>
        )
    else()
        add_compile_options(-fdiagnostics-color=always)
    endif()
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC" AND MSVC_VERSION GREATER 1900)
    add_compile_options(/diagnostics:column)
endif()

include(Utilities)
# MSVC but VSCMD_VER is not set, which means vcvarsall has not run
if(MSVC AND "$ENV{VSCMD_VER}" STREQUAL "")

    # find vcvarsall.bat
    get_filename_component(MSVC_DIR ${CMAKE_CXX_COMPILER} DIRECTORY)
    find_file(
        VCVARSALL_FILE
        NAMES vcvarsall.bat
        PATHS "${MSVC_DIR}"
              "${MSVC_DIR}/.."
              "${MSVC_DIR}/../.."
              "${MSVC_DIR}/../../../../../../../.."
              "${MSVC_DIR}/../../../../../../.."
        PATH_SUFFIXES "VC/Auxiliary/Build" "Common7/Tools" "Tools"
    )

    if(EXISTS ${VCVARSALL_FILE})
        # detect the architecture
        string(TOLOWER "${CMAKE_SYSTEM_PROCESSOR}" CMAKE_SYSTEM_PROCESSOR_LOWER)
        if(CMAKE_SYSTEM_PROCESSOR_LOWER STREQUAL x86
           OR CMAKE_SYSTEM_PROCESSOR_LOWER MATCHES "^i[3456]86$"
        )
            set(VCVARSALL_ARCH x86)
        elseif(CMAKE_SYSTEM_PROCESSOR_LOWER STREQUAL x64
               OR CMAKE_SYSTEM_PROCESSOR_LOWER STREQUAL x86_64
               OR CMAKE_SYSTEM_PROCESSOR_LOWER STREQUAL amd64
        )
            set(VCVARSALL_ARCH x64)
        elseif(CMAKE_SYSTEM_PROCESSOR_LOWER STREQUAL arm)
            set(VCVARSALL_ARCH arm)
        elseif(CMAKE_SYSTEM_PROCESSOR_LOWER STREQUAL arm64
               OR CMAKE_SYSTEM_PROCESSOR_LOWER STREQUAL aarch64
        )
            set(VCVARSALL_ARCH arm64)
        else()
            if(CMAKE_HOST_SYSTEM_PROCESSOR)
                set(VCVARSALL_ARCH ${CMAKE_HOST_SYSTEM_PROCESSOR})
            else()
                set(VCVARSALL_ARCH x64)
                message(STATUS "Unknown architecture - using x64")
            endif()
        endif()

        # run vcvarsall and print the environment variables
        message(STATUS "Running `${VCVARSALL_FILE} ${VCVARSALL_ARCH}`")
        execute_process(
            COMMAND
                "cmd" "/c" ${VCVARSALL_FILE} ${VCVARSALL_ARCH} #
                "&&" "call" "echo" "VCVARSALL_ENV_START" #
                "&" "set" #
            OUTPUT_VARIABLE VCVARSALL_OUTPUT
            OUTPUT_STRIP_TRAILING_WHITESPACE
        )

        # parse the output and get the environment variables string
        find_substring_by_prefix(
            VCVARSALL_ENV "VCVARSALL_ENV_START" "${VCVARSALL_OUTPUT}"
        )

        # set the environment variables
        set_env_from_string("${VCVARSALL_ENV}")

    else()
        message(
            WARNING
                "Could not find `vcvarsall.bat` for automatic MSVC environment preparation. Please manually open the MSVC command prompt and rebuild the project.
      "
        )
    endif()
endif()
