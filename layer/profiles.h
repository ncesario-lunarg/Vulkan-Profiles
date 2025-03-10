/*
 * Copyright (C) 2015-2022 Valve Corporation
 * Copyright (C) 2015-2022 LunarG, Inc.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 * Author: Mark Lobodzinski <mark@lunarg.com>
 */

#pragma once
#include "../layer-utils/vk_layer_settings.h"

enum SimulateCapabilityFlag {
    SIMULATE_API_VERSION_BIT = 1 << 0,
    SIMULATE_FEATURES_BIT = 1 << 1,
    SIMULATE_PROPERTIES_BIT = 1 << 2,
    SIMULATE_EXTENSIONS_BIT = 1 << 3,
    SIMULATE_FORMATS_BIT = 1 << 4,
    SIMULATE_QUEUE_FAMILY_PROPERTIES_BIT = 1 << 5,
    SIMULATE_MAX_ENUM = 0x7FFFFFFF
};
typedef int SimulateCapabilityFlags;

enum DebugAction {
    DEBUG_ACTION_FILE_BIT = (1 << 0),
    DEBUG_ACTION_STDOUT_BIT = (1 << 1),
    DEBUG_ACTION_OUTPUT_BIT = (1 << 2),
    DEBUG_ACTION_BREAKPOINT_BIT = (1 << 3),
    DEBUG_ACTION_MAX_ENUM = 0x7FFFFFFF
};
typedef int DebugActionFlags;

enum DebugReport {
    DEBUG_REPORT_NOTIFICATION_BIT = (1 << 0),
    DEBUG_REPORT_WARNING_BIT = (1 << 1),
    DEBUG_REPORT_ERROR_BIT = (1 << 2),
    DEBUG_REPORT_DEBUG_BIT = (1 << 3),
    DEBUG_REPORT_MAX_ENUM = 0x7FFFFFFF
};
typedef int DebugReportFlags;

static const VkStructureType VK_STRUCTURE_TYPE_PROFILES_LAYER_SETTINGS_EXT = static_cast<VkStructureType>(3000300005);

typedef struct VkProfileLayerSettingsEXT {
    VkProfileLayerSettingsEXT()
    : sType(VK_STRUCTURE_TYPE_PROFILES_LAYER_SETTINGS_EXT) {}

    VkStructureType sType;
    void* pNext{};
    std::string profile_file{};
    std::string profile_name{"${VP_DEFAULT}"};
    bool profile_validation{false};
    bool emulate_portability{true};
    bool constantAlphaColorBlendFactors{false};
    bool events{false};
    bool imageViewFormatReinterpretation{false};
    bool imageViewFormatSwizzle{false};
    bool imageView2DOn3DImage{false};
    bool multisampleArrayImage{false};
    bool mutableComparisonSamplers{false};
    bool pointPolygons{false};
    bool samplerMipLodBias{false};
    bool separateStencilMaskRef{false};
    bool shaderSampleRateInterpolationFunctions{false};
    bool tessellationIsolines{false};
    bool tessellationPointMode{false};
    bool triangleFans{false};
    bool vertexAttributeAccessBeyondStride{false};
    uint32_t minVertexInputBindingStrideAlignment{4};
    SimulateCapabilityFlags simulate_capabilities{SIMULATE_API_VERSION_BIT | SIMULATE_FEATURES_BIT | SIMULATE_PROPERTIES_BIT};
    DebugActionFlags debug_actions{DEBUG_ACTION_STDOUT_BIT};
    std::string debug_filename{"profiles_layer_log.txt"};
    bool debug_file_discard{true};
    DebugReportFlags debug_reports{DEBUG_REPORT_WARNING_BIT | DEBUG_REPORT_ERROR_BIT};
    bool debug_fail_on_error{false};
    vku::Strings exclude_device_extensions;
    vku::Strings exclude_formats;
} VkProfileLayerSettingsEXT;
