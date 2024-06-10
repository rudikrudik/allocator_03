cmake_minimum_required(VERSION 3.22)
project(allocator)

project(allocator VERSION 0.0.$ENV{GITHUB_RUN_NUMBER})
#project(allocator VERSION 0.0.1)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(src)

if (MSVC)
    target_compile_options(allocator PRIVATE
            /W4
    )
else ()
    target_compile_options(allocator PRIVATE
            -Wall -Wextra -pedantic -Werror
    )
endif()

install(TARGETS allocator RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)
set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")
set(CPACK_PACKAGE_CONTACT rudik.login@gmail.com)
include(CPack)