if (PROFILES_BUILD_TESTS AND NOT ANDROID)
    add_subdirectory(test)
endif()

set(MERGE_PYTHON_FILES ${PROJECT_SOURCE_DIR}/scripts/gen_profiles_file.py)
set(LAYER_PYTHON_FILES ${PROJECT_SOURCE_DIR}/scripts/gen_profiles_solution.py)

file(GLOB PROFILES_FILES ${CMAKE_CURRENT_LIST_DIR})
source_group("Python Files" FILES ${MERGE_PYTHON_FILES} ${LAYER_PYTHON_FILES})

set(PROFILE_DESKTOP_MAX_2022_LABEL "LunarG Vulkan Desktop Max 2022 profile")
set(PROFILE_DESKTOP_MAX_2022_DESC "A profile generated by the intersection of a collection of GPUInfo.org device reports to support the latest AMD, Intel and NVIDIA GPUs and drivers.")

add_custom_target(VpCreateDesktopMax2022 ALL
	COMMAND ${PYTHON_EXECUTABLE} ${MERGE_PYTHON_FILES}
		--registry ${VULKAN_HEADERS_REGISTRY_DIRECTORY}/vk.xml
		--input ${CMAKE_CURRENT_LIST_DIR}/VP_LUNARG_desktop_max_2022
		--output-path ${CMAKE_CURRENT_LIST_DIR}/test/data/VP_LUNARG_desktop_max_2022.json
		--output-profile VP_LUNARG_desktop_max_2022
		--profile-label ${PROFILE_DESKTOP_MAX_2022_LABEL}
		--profile-desc ${PROFILE_DESKTOP_MAX_2022_DESC}
		--profile-date 2022-09-06
		--profile-stage BETA
	VERBATIM
	SOURCES ${MERGE_PYTHON_FILES} ${PROFILES_FILES}
	DEPENDS ${MERGE_PYTHON_FILES} ${PROFILES_FILES})

set_target_properties(VpCreateDesktopMax2022 PROPERTIES FOLDER "Profiles generator")

set(PROFILE_DESKTOP_BASELINE_2023_LABEL "LunarG Vulkan Desktop Baseline 2023 profile")
set(PROFILE_DESKTOP_BASELINE_2023_DESC "A profile generated by the intersection of a collection of GPUInfo.org device reports to support a large number of actual systems in the Vulkan ecosystem. This profile is meant to be a usage example for Vulkan application developer.")
set(PROFILE_DESKTOP_BASELINE_2023_API_VERSION "1.2.148")

add_custom_target(VpCreateDesktopBaseline2023 ALL
	COMMAND ${PYTHON_EXECUTABLE} ${MERGE_PYTHON_FILES}
		--registry ${VULKAN_HEADERS_REGISTRY_DIRECTORY}/vk.xml
		--input ${CMAKE_CURRENT_LIST_DIR}/VP_LUNARG_desktop_baseline_2023
		--output-path ${CMAKE_CURRENT_LIST_DIR}/VP_LUNARG_desktop_baseline_2023.json
		--output-profile VP_LUNARG_desktop_baseline_2023
		--profile-label ${PROFILE_DESKTOP_BASELINE_2023_LABEL}
		--profile-desc ${PROFILE_DESKTOP_BASELINE_2023_DESC}
		--profile-date 2023-01-30
		--profile-api-version ${PROFILE_DESKTOP_BASELINE_2023_API_VERSION}
	VERBATIM
	SOURCES ${MERGE_PYTHON_FILES} ${PROFILES_FILES}
	DEPENDS ${MERGE_PYTHON_FILES} ${PROFILES_FILES})

set_target_properties(VpCreateDesktopBaseline2023 PROPERTIES FOLDER "Profiles generator")

set(PROFILE_DESKTOP_BASELINE_2022_LABEL "LunarG Vulkan Desktop Baseline 2022 profile")
set(PROFILE_DESKTOP_BASELINE_2022_DESC "A profile generated by the intersection of a collection of GPUInfo.org device reports to support a large number of actual systems in the Vulkan ecosystem. This profile is meant to be a usage example for Vulkan application developer.")
set(PROFILE_DESKTOP_BASELINE_2022_API_VERSION "1.1.139")

add_custom_target(VpCreateDesktopBaseline2022 ALL
	COMMAND ${PYTHON_EXECUTABLE} ${MERGE_PYTHON_FILES}
		--registry ${VULKAN_HEADERS_REGISTRY_DIRECTORY}/vk.xml
		--input ${CMAKE_CURRENT_LIST_DIR}/VP_LUNARG_desktop_baseline_2022
		--output-path ${CMAKE_CURRENT_LIST_DIR}/VP_LUNARG_desktop_baseline_2022.json
		--output-profile VP_LUNARG_desktop_baseline_2022
		--profile-label ${PROFILE_DESKTOP_BASELINE_2022_LABEL}
		--profile-desc ${PROFILE_DESKTOP_BASELINE_2022_DESC}
		--profile-date 2023-01-26
		--profile-api-version ${PROFILE_DESKTOP_BASELINE_2022_API_VERSION}
	VERBATIM
	SOURCES ${MERGE_PYTHON_FILES} ${PROFILES_FILES}
	DEPENDS ${MERGE_PYTHON_FILES} ${PROFILES_FILES})

set_target_properties(VpCreateDesktopBaseline2022 PROPERTIES FOLDER "Profiles generator")

set(PROFILE_DESKTOP_PORTABILITY_2022_LABEL "LunarG Vulkan Desktop Portability 2022 profile")
set(PROFILE_DESKTOP_PORTABILITY_2022_DESC "A variant of VP_LUNARG_desktop_baseline_2022 that includes portability extensions to work on macOS devices.")
set(PROFILE_DESKTOP_PORTABILITY_2022_API_VERSION "1.1.208")

add_custom_target(VpCreateDesktopPortability2022 ALL
	COMMAND ${PYTHON_EXECUTABLE} ${MERGE_PYTHON_FILES}
		--registry ${VULKAN_HEADERS_REGISTRY_DIRECTORY}/vk.xml
		--input ${CMAKE_CURRENT_LIST_DIR}/VP_LUNARG_desktop_portability_2022
		--output-path ${CMAKE_CURRENT_LIST_DIR}/VP_LUNARG_desktop_portability_2022.json
		--output-profile VP_LUNARG_desktop_portability_2022
		--profile-label ${PROFILE_DESKTOP_PORTABILITY_2022_LABEL}
		--profile-desc ${PROFILE_DESKTOP_PORTABILITY_2022_DESC}
		--profile-api-version ${PROFILE_DESKTOP_PORTABILITY_2022_API_VERSION}
		--profile-date 2022-08-26
		--profile-stage BETA
		--mode union
	VERBATIM
	SOURCES ${MERGE_PYTHON_FILES} ${PROFILES_FILES}
	DEPENDS ${MERGE_PYTHON_FILES} ${PROFILES_FILES})

add_custom_command(
	TARGET VpCreateDesktopPortability2022 PRE_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy
		${CMAKE_CURRENT_LIST_DIR}/VP_LUNARG_desktop_baseline_2022.json
		${CMAKE_CURRENT_LIST_DIR}/VP_LUNARG_desktop_portability_2022)

set_target_properties(VpCreateDesktopPortability2022 PROPERTIES FOLDER "Profiles generator")

add_dependencies(VpCreateDesktopPortability2022 VpCreateDesktopBaseline2022)

add_custom_target(VpGenerated
	COMMAND ${CMAKE_COMMAND} -E make_directory ${PROJECT_SOURCE_DIR}/schema
	COMMAND ${CMAKE_COMMAND} -E copy_directory ${VULKAN_HEADERS_REGISTRY_DIRECTORY}/profiles ${CMAKE_CURRENT_LIST_DIR}
	COMMAND ${PYTHON_EXECUTABLE} ${LAYER_PYTHON_FILES}
		--registry ${VULKAN_HEADERS_REGISTRY_DIRECTORY}/vk.xml
		--input ${CMAKE_CURRENT_LIST_DIR}
		--output-library-inc ${PROJECT_SOURCE_DIR}/library/include/vulkan
		--output-library-src ${PROJECT_SOURCE_DIR}/library/source
		--output-schema ${PROJECT_SOURCE_DIR}/schema/${PROFILES_SCHEMA_FILENAME}
		--output-doc ${PROJECT_SOURCE_DIR}/PROFILES.md
		--validate
		--debug
	VERBATIM
	SOURCES ${LAYER_PYTHON_FILES} ${PROFILES_FILES}
	DEPENDS ${LAYER_PYTHON_FILES} ${PROFILES_FILES})

set_target_properties(VpGenerated PROPERTIES FOLDER "Profiles generator")

add_dependencies(VpGenerated VpCreateDesktopBaseline2023 VpCreateDesktopBaseline2022 VpCreateDesktopPortability2022)

add_custom_target(VpTestIntersect ALL
	COMMAND ${PYTHON_EXECUTABLE} ${MERGE_PYTHON_FILES}
		--registry ${VULKAN_HEADERS_REGISTRY_DIRECTORY}/vk.xml
		--input ${CMAKE_CURRENT_LIST_DIR}/test/data/VP_LUNARG_test_combine_intersect
		--output-path ${CMAKE_CURRENT_LIST_DIR}/test/data/VP_LUNARG_test_combine_intersect.json
		--output-profile VP_LUNARG_test_combine_intersect
		--mode intersection
	VERBATIM
	SOURCES ${MERGE_PYTHON_FILES} ${PROFILES_FILES}
	DEPENDS ${MERGE_PYTHON_FILES} ${PROFILES_FILES})

set_target_properties(VpTestIntersect PROPERTIES FOLDER "Profiles generator/Tests")

add_dependencies(VpTestIntersect VpGenerated)

add_custom_target(VpTestUnion ALL
	COMMAND ${PYTHON_EXECUTABLE} ${MERGE_PYTHON_FILES}
		--registry ${VULKAN_HEADERS_REGISTRY_DIRECTORY}/vk.xml
		--input ${CMAKE_CURRENT_LIST_DIR}/test/data/VP_LUNARG_test_combine_union
		--output-path ${CMAKE_CURRENT_LIST_DIR}/test/data/VP_LUNARG_test_combine_union.json
		--output-profile VP_LUNARG_test_combine_union
		--mode union
	VERBATIM
	SOURCES ${MERGE_PYTHON_FILES} ${PROFILES_FILES}
	DEPENDS ${MERGE_PYTHON_FILES} ${PROFILES_FILES})

set_target_properties(VpTestUnion PROPERTIES FOLDER "Profiles generator/Tests")

add_dependencies(VpTestUnion VpGenerated)

add_custom_target(VpTestGeneratedName ALL
	COMMAND ${PYTHON_EXECUTABLE} ${MERGE_PYTHON_FILES}
		--registry ${VULKAN_HEADERS_REGISTRY_DIRECTORY}/vk.xml
		--input ${CMAKE_CURRENT_LIST_DIR}/test/data/VP_LUNARG_test_combine_intersect
		--output-path ${CMAKE_CURRENT_LIST_DIR}/test/data/VP_LUNARG_test_generated_name.json
	VERBATIM
	SOURCES ${MERGE_PYTHON_FILES} ${PROFILES_FILES}
	DEPENDS ${MERGE_PYTHON_FILES} ${PROFILES_FILES})

set_target_properties(VpTestGeneratedName PROPERTIES FOLDER "Profiles generator/Tests")

add_dependencies(VpTestGeneratedName VpGenerated)

install(
    FILES 
        VP_ANDROID_baseline_2021.json
        VP_ANDROID_baseline_2022.json
        VP_KHR_roadmap_2022.json
        VP_LUNARG_desktop_baseline_2022.json
        VP_LUNARG_desktop_baseline_2023.json
        VP_LUNARG_desktop_portability_2022.json
    DESTINATION
        "${CMAKE_INSTALL_DATADIR}/vulkan/config/VK_LAYER_KHRONOS_profiles"
)

install(
    FILES
        ${MERGE_PYTHON_FILES}
        ${LAYER_PYTHON_FILES}
        ${PROJECT_SOURCE_DIR}/schema/${PROFILES_SCHEMA_FILENAME}
    DESTINATION
        "${CMAKE_INSTALL_DATADIR}/vulkan/registry"
)
