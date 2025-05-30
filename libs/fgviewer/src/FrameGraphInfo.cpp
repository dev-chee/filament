/*
 * Copyright (C) 2024 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <fgviewer/FrameGraphInfo.h>

#include <utils/CString.h>

#include <unordered_map>
#include <vector>

namespace filament::fgviewer {

FrameGraphInfo::FrameGraphInfo(utils::CString viewName):
    viewName(std::move(viewName)), passes({}), resources({}) {}

FrameGraphInfo::~FrameGraphInfo() = default;

FrameGraphInfo::FrameGraphInfo(FrameGraphInfo&& rhs) noexcept = default;

bool FrameGraphInfo::operator==(const FrameGraphInfo& rhs) const {
    // We skip checking graphviz here since checking passes and resources should be enough.
    return viewName == rhs.viewName
            && passes == rhs.passes
            && resources == rhs.resources;
}

FrameGraphInfo::Pass::Pass(utils::CString name, std::vector<ResourceId> reads,
    std::vector<ResourceId> writes): name(std::move(name)),
                                    reads(std::move(reads)),
                                    writes(std::move(writes)) {}

bool FrameGraphInfo::Pass::operator==(const Pass& rhs) const {
    return name == rhs.name && reads == rhs.reads && writes == rhs.writes;
}

FrameGraphInfo::Resource::Resource(ResourceId id, utils::CString name,
    std::vector<Property> properties): id(id),
    name(std::move(name)), properties(std::move(properties)) {}

bool FrameGraphInfo::Resource::operator==(const Resource& rhs) const {
    return id == rhs.id && name == rhs.name && properties == rhs.properties;
}

bool FrameGraphInfo::Resource::Property::operator==(const Property &rhs) const {
    return name == rhs.name && value == rhs.value;
}

void FrameGraphInfo::setResources(
    std::unordered_map<ResourceId, Resource> resources) {
    this->resources = std::move(resources);
}

void FrameGraphInfo::setPasses(std::vector<Pass> sortedPasses) {
    passes = std::move(sortedPasses);
}

void FrameGraphInfo::setGraphvizData(utils::CString data) {
    graphvizData = std::move(data);
}

const char* FrameGraphInfo::getViewName() const {
    return viewName.c_str_safe();
}

const std::vector<FrameGraphInfo::Pass>& FrameGraphInfo::getPasses() const {
    return passes;
}

const std::unordered_map<ResourceId, FrameGraphInfo::Resource>&
    FrameGraphInfo::getResources() const {
    return resources;
}

const char* FrameGraphInfo::getGraphvizData() const {
    return graphvizData.c_str_safe();
}

} // namespace filament::fgviewer
