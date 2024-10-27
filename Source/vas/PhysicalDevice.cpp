#include "PhysicalDevice.hpp"

namespace vas {
    PhysicalDevice::PhysicalDevice()
    : m_physicalDeviceProperties({ }), m_physicalDeviceFeatures({ }) { }

    PhysicalDevice::PhysicalDevice(VkInstance instance, const PhysicalDeviceCriteria& physicalDeviceCriteria)
    : m_physicalDeviceProperties({ }), m_physicalDeviceFeatures({ }) {
        unsigned int physicalDevicesCount = 0;
        vkEnumeratePhysicalDevices(instance, &physicalDevicesCount, nullptr);
        std::vector<VkPhysicalDevice> physicalDevices(physicalDevicesCount);
        vkEnumeratePhysicalDevices(instance, &physicalDevicesCount, physicalDevices.data());

        std::vector<VkPhysicalDeviceProperties> physicalDevicesProperties(physicalDevicesCount);
        std::vector<VkPhysicalDeviceFeatures> physicalDevicesFeatures(physicalDevicesCount);
        std::vector<uint8_t> physicalDevicesScores(physicalDevicesCount);

        bool found = false;
        for(auto i = 0; i < physicalDevices.size(); ++i) {
            vkGetPhysicalDeviceProperties(physicalDevices[i], &physicalDevicesProperties[i]);
            vkGetPhysicalDeviceFeatures(physicalDevices[i], &physicalDevicesFeatures[i]);

            if(physicalDeviceCriteria.check) {
                if(physicalDevicesProperties[i].apiVersion >= physicalDeviceCriteria.physicalDeviceProperties.apiVersion) { ++physicalDevicesScores[i]; }
                if(physicalDevicesProperties[i].driverVersion >= physicalDeviceCriteria.physicalDeviceProperties.driverVersion) { ++physicalDevicesScores[i]; }
                if(physicalDevicesProperties[i].vendorID == physicalDeviceCriteria.physicalDeviceProperties.vendorID) { ++physicalDevicesScores[i]; }
                if(physicalDevicesProperties[i].deviceID == physicalDeviceCriteria.physicalDeviceProperties.deviceID) { ++physicalDevicesScores[i]; }
                if(physicalDevicesProperties[i].deviceType == physicalDeviceCriteria.physicalDeviceProperties.deviceType) { ++physicalDevicesScores[i]; }
                if(std::strcmp(physicalDevicesProperties[i].deviceName, physicalDeviceCriteria.physicalDeviceProperties.deviceName) == 0) { ++physicalDevicesScores[i]; }
                if(std::equal(std::begin(physicalDevicesProperties[i].pipelineCacheUUID), std::end(physicalDevicesProperties[i].pipelineCacheUUID), std::begin(physicalDeviceCriteria.physicalDeviceProperties.pipelineCacheUUID))) { ++physicalDevicesScores[i]; }
                
                if(physicalDevicesProperties[i].limits.maxImageDimension1D >= physicalDeviceCriteria.physicalDeviceProperties.limits.maxImageDimension1D) { ++physicalDevicesScores[i]; }
                if(physicalDevicesProperties[i].limits.maxImageDimension2D >= physicalDeviceCriteria.physicalDeviceProperties.limits.maxImageDimension2D) { ++physicalDevicesScores[i]; }
                if(physicalDevicesProperties[i].limits.maxImageDimension3D >= physicalDeviceCriteria.physicalDeviceProperties.limits.maxImageDimension3D) { ++physicalDevicesScores[i]; }
                if(physicalDevicesProperties[i].limits.maxImageDimensionCube >= physicalDeviceCriteria.physicalDeviceProperties.limits.maxImageDimensionCube) { ++physicalDevicesScores[i]; }
                if(physicalDevicesProperties[i].limits.maxImageArrayLayers >= physicalDeviceCriteria.physicalDeviceProperties.limits.maxImageArrayLayers) { ++physicalDevicesScores[i]; }
                if(physicalDevicesProperties[i].limits.maxTexelBufferElements >= physicalDeviceCriteria.physicalDeviceProperties.limits.maxTexelBufferElements) { ++physicalDevicesScores[i]; }
                if(physicalDevicesProperties[i].limits.maxUniformBufferRange >= physicalDeviceCriteria.physicalDeviceProperties.limits.maxUniformBufferRange) { ++physicalDevicesScores[i]; }
                if(physicalDevicesProperties[i].limits.maxStorageBufferRange >= physicalDeviceCriteria.physicalDeviceProperties.limits.maxStorageBufferRange) { ++physicalDevicesScores[i]; }
                if(physicalDevicesProperties[i].limits.maxPushConstantsSize >= physicalDeviceCriteria.physicalDeviceProperties.limits.maxPushConstantsSize) { ++physicalDevicesScores[i]; }
                if(physicalDevicesProperties[i].limits.maxMemoryAllocationCount >= physicalDeviceCriteria.physicalDeviceProperties.limits.maxMemoryAllocationCount) { ++physicalDevicesScores[i]; }
                if(physicalDevicesProperties[i].limits.maxSamplerAllocationCount >= physicalDeviceCriteria.physicalDeviceProperties.limits.maxSamplerAllocationCount) { ++physicalDevicesScores[i]; }
                if(physicalDevicesProperties[i].limits.bufferImageGranularity >= physicalDeviceCriteria.physicalDeviceProperties.limits.bufferImageGranularity) { ++physicalDevicesScores[i]; }
                if(physicalDevicesProperties[i].limits.sparseAddressSpaceSize >= physicalDeviceCriteria.physicalDeviceProperties.limits.sparseAddressSpaceSize) { ++physicalDevicesScores[i]; }
                if(physicalDevicesProperties[i].limits.maxBoundDescriptorSets >= physicalDeviceCriteria.physicalDeviceProperties.limits.maxBoundDescriptorSets) { ++physicalDevicesScores[i]; }
                if(physicalDevicesProperties[i].limits.maxPerStageDescriptorSamplers >= physicalDeviceCriteria.physicalDeviceProperties.limits.maxPerStageDescriptorSamplers) { ++physicalDevicesScores[i]; }
                if(physicalDevicesProperties[i].limits.maxPerStageDescriptorUniformBuffers >= physicalDeviceCriteria.physicalDeviceProperties.limits.maxPerStageDescriptorUniformBuffers) { ++physicalDevicesScores[i]; }
                if(physicalDevicesProperties[i].limits.maxPerStageDescriptorStorageBuffers >= physicalDeviceCriteria.physicalDeviceProperties.limits.maxPerStageDescriptorStorageBuffers) { ++physicalDevicesScores[i]; }
                if(physicalDevicesProperties[i].limits.maxPerStageDescriptorSampledImages >= physicalDeviceCriteria.physicalDeviceProperties.limits.maxPerStageDescriptorSampledImages) { ++physicalDevicesScores[i]; }
                if(physicalDevicesProperties[i].limits.maxPerStageDescriptorStorageImages >= physicalDeviceCriteria.physicalDeviceProperties.limits.maxPerStageDescriptorStorageImages) { ++physicalDevicesScores[i]; }
                if(physicalDevicesProperties[i].limits.maxPerStageDescriptorInputAttachments >= physicalDeviceCriteria.physicalDeviceProperties.limits.maxPerStageDescriptorInputAttachments) { ++physicalDevicesScores[i]; }
                if(physicalDevicesProperties[i].limits.maxPerStageResources >= physicalDeviceCriteria.physicalDeviceProperties.limits.maxPerStageResources) { ++physicalDevicesScores[i]; }
                if(physicalDevicesProperties[i].limits.maxDescriptorSetSamplers >= physicalDeviceCriteria.physicalDeviceProperties.limits.maxDescriptorSetSamplers) { ++physicalDevicesScores[i]; }
                if(physicalDevicesProperties[i].limits.maxDescriptorSetUniformBuffers >= physicalDeviceCriteria.physicalDeviceProperties.limits.maxDescriptorSetUniformBuffers) { ++physicalDevicesScores[i]; }
                if(physicalDevicesProperties[i].limits.maxDescriptorSetUniformBuffersDynamic >= physicalDeviceCriteria.physicalDeviceProperties.limits.maxDescriptorSetUniformBuffersDynamic) { ++physicalDevicesScores[i]; }
                if(physicalDevicesProperties[i].limits.maxDescriptorSetStorageBuffers >= physicalDeviceCriteria.physicalDeviceProperties.limits.maxDescriptorSetStorageBuffers) { ++physicalDevicesScores[i]; }
                if(physicalDevicesProperties[i].limits.maxDescriptorSetStorageBuffersDynamic >= physicalDeviceCriteria.physicalDeviceProperties.limits.maxDescriptorSetStorageBuffersDynamic) { ++physicalDevicesScores[i]; }
                if(physicalDevicesProperties[i].limits.maxDescriptorSetSampledImages >= physicalDeviceCriteria.physicalDeviceProperties.limits.maxDescriptorSetSampledImages) { ++physicalDevicesScores[i]; }
                if(physicalDevicesProperties[i].limits.maxDescriptorSetStorageImages >= physicalDeviceCriteria.physicalDeviceProperties.limits.maxDescriptorSetStorageImages) { ++physicalDevicesScores[i]; }
                if(physicalDevicesProperties[i].limits.maxDescriptorSetInputAttachments >= physicalDeviceCriteria.physicalDeviceProperties.limits.maxDescriptorSetInputAttachments) { ++physicalDevicesScores[i]; }
                if(physicalDevicesProperties[i].limits.maxVertexInputAttributes >= physicalDeviceCriteria.physicalDeviceProperties.limits.maxVertexInputAttributes) { ++physicalDevicesScores[i]; }
                if(physicalDevicesProperties[i].limits.maxVertexInputBindings >= physicalDeviceCriteria.physicalDeviceProperties.limits.maxVertexInputBindings) { ++physicalDevicesScores[i]; }
                if(physicalDevicesProperties[i].limits.maxVertexInputAttributeOffset >= physicalDeviceCriteria.physicalDeviceProperties.limits.maxVertexInputAttributeOffset) { ++physicalDevicesScores[i]; }
                if(physicalDevicesProperties[i].limits.maxVertexInputBindingStride >= physicalDeviceCriteria.physicalDeviceProperties.limits.maxVertexInputBindingStride) { ++physicalDevicesScores[i]; }
                if(physicalDevicesProperties[i].limits.maxVertexOutputComponents >= physicalDeviceCriteria.physicalDeviceProperties.limits.maxVertexOutputComponents) { ++physicalDevicesScores[i]; }
                if(physicalDevicesProperties[i].limits.maxTessellationGenerationLevel >= physicalDeviceCriteria.physicalDeviceProperties.limits.maxTessellationGenerationLevel) { ++physicalDevicesScores[i]; }
                if(physicalDevicesProperties[i].limits.maxTessellationPatchSize >= physicalDeviceCriteria.physicalDeviceProperties.limits.maxTessellationPatchSize) { ++physicalDevicesScores[i]; }
                if(physicalDevicesProperties[i].limits.maxTessellationControlPerVertexInputComponents >= physicalDeviceCriteria.physicalDeviceProperties.limits.maxTessellationControlPerVertexInputComponents) { ++physicalDevicesScores[i]; }
                if(physicalDevicesProperties[i].limits.maxTessellationControlPerVertexOutputComponents >= physicalDeviceCriteria.physicalDeviceProperties.limits.maxTessellationControlPerVertexOutputComponents) { ++physicalDevicesScores[i]; }
                if(physicalDevicesProperties[i].limits.maxTessellationControlPerPatchOutputComponents >= physicalDeviceCriteria.physicalDeviceProperties.limits.maxTessellationControlPerPatchOutputComponents) { ++physicalDevicesScores[i]; }
                if(physicalDevicesProperties[i].limits.maxTessellationControlTotalOutputComponents >= physicalDeviceCriteria.physicalDeviceProperties.limits.maxTessellationControlTotalOutputComponents) { ++physicalDevicesScores[i]; }
                if(physicalDevicesProperties[i].limits.maxTessellationEvaluationInputComponents >= physicalDeviceCriteria.physicalDeviceProperties.limits.maxTessellationEvaluationInputComponents) { ++physicalDevicesScores[i]; }
                if(physicalDevicesProperties[i].limits.maxTessellationEvaluationOutputComponents >= physicalDeviceCriteria.physicalDeviceProperties.limits.maxTessellationEvaluationOutputComponents) { ++physicalDevicesScores[i]; }
                if(physicalDevicesProperties[i].limits.maxGeometryShaderInvocations >= physicalDeviceCriteria.physicalDeviceProperties.limits.maxGeometryShaderInvocations) { ++physicalDevicesScores[i]; }
                if(physicalDevicesProperties[i].limits.maxGeometryInputComponents >= physicalDeviceCriteria.physicalDeviceProperties.limits.maxGeometryInputComponents) { ++physicalDevicesScores[i]; }
                if(physicalDevicesProperties[i].limits.maxGeometryOutputComponents >= physicalDeviceCriteria.physicalDeviceProperties.limits.maxGeometryOutputComponents) { ++physicalDevicesScores[i]; }
                if(physicalDevicesProperties[i].limits.maxGeometryOutputVertices >= physicalDeviceCriteria.physicalDeviceProperties.limits.maxGeometryOutputVertices) { ++physicalDevicesScores[i]; }
                if(physicalDevicesProperties[i].limits.maxGeometryTotalOutputComponents >= physicalDeviceCriteria.physicalDeviceProperties.limits.maxGeometryTotalOutputComponents) { ++physicalDevicesScores[i]; }
                if(physicalDevicesProperties[i].limits.maxFragmentInputComponents >= physicalDeviceCriteria.physicalDeviceProperties.limits.maxFragmentInputComponents) { ++physicalDevicesScores[i]; }
                if(physicalDevicesProperties[i].limits.maxFragmentOutputAttachments >= physicalDeviceCriteria.physicalDeviceProperties.limits.maxFragmentOutputAttachments) { ++physicalDevicesScores[i]; }
                if(physicalDevicesProperties[i].limits.maxFragmentDualSrcAttachments >= physicalDeviceCriteria.physicalDeviceProperties.limits.maxFragmentDualSrcAttachments) { ++physicalDevicesScores[i]; }
                if(physicalDevicesProperties[i].limits.maxFragmentCombinedOutputResources >= physicalDeviceCriteria.physicalDeviceProperties.limits.maxFragmentCombinedOutputResources) { ++physicalDevicesScores[i]; }
                if(physicalDevicesProperties[i].limits.maxComputeSharedMemorySize >= physicalDeviceCriteria.physicalDeviceProperties.limits.maxComputeSharedMemorySize) { ++physicalDevicesScores[i]; }
                if(physicalDevicesProperties[i].limits.maxComputeWorkGroupCount[0] >= physicalDeviceCriteria.physicalDeviceProperties.limits.maxComputeWorkGroupCount[0]) { ++physicalDevicesScores[i]; }
                if(physicalDevicesProperties[i].limits.maxComputeWorkGroupCount[1] >= physicalDeviceCriteria.physicalDeviceProperties.limits.maxComputeWorkGroupCount[1]) { ++physicalDevicesScores[i]; }
                if(physicalDevicesProperties[i].limits.maxComputeWorkGroupCount[2] >= physicalDeviceCriteria.physicalDeviceProperties.limits.maxComputeWorkGroupCount[2]) { ++physicalDevicesScores[i]; }
                if(physicalDevicesProperties[i].limits.maxComputeWorkGroupInvocations >= physicalDeviceCriteria.physicalDeviceProperties.limits.maxComputeWorkGroupInvocations) { ++physicalDevicesScores[i]; }
                if(physicalDevicesProperties[i].limits.maxComputeWorkGroupSize[0] >= physicalDeviceCriteria.physicalDeviceProperties.limits.maxComputeWorkGroupSize[0]) { ++physicalDevicesScores[i]; }
                if(physicalDevicesProperties[i].limits.maxComputeWorkGroupSize[1] >= physicalDeviceCriteria.physicalDeviceProperties.limits.maxComputeWorkGroupSize[1]) { ++physicalDevicesScores[i]; }
                if(physicalDevicesProperties[i].limits.maxComputeWorkGroupSize[2] >= physicalDeviceCriteria.physicalDeviceProperties.limits.maxComputeWorkGroupSize[2]) { ++physicalDevicesScores[i]; }
                if(physicalDevicesProperties[i].limits.subPixelPrecisionBits >= physicalDeviceCriteria.physicalDeviceProperties.limits.subPixelPrecisionBits) { ++physicalDevicesScores[i]; }
                if(physicalDevicesProperties[i].limits.subTexelPrecisionBits >= physicalDeviceCriteria.physicalDeviceProperties.limits.subTexelPrecisionBits) { ++physicalDevicesScores[i]; }
                if(physicalDevicesProperties[i].limits.mipmapPrecisionBits >= physicalDeviceCriteria.physicalDeviceProperties.limits.mipmapPrecisionBits) { ++physicalDevicesScores[i]; }
                if(physicalDevicesProperties[i].limits.maxDrawIndexedIndexValue >= physicalDeviceCriteria.physicalDeviceProperties.limits.maxDrawIndexedIndexValue) { ++physicalDevicesScores[i]; }
                if(physicalDevicesProperties[i].limits.maxDrawIndirectCount >= physicalDeviceCriteria.physicalDeviceProperties.limits.maxDrawIndirectCount) { ++physicalDevicesScores[i]; }
                if(physicalDevicesProperties[i].limits.maxSamplerLodBias >= physicalDeviceCriteria.physicalDeviceProperties.limits.maxSamplerLodBias) { ++physicalDevicesScores[i]; }
                if(physicalDevicesProperties[i].limits.maxSamplerAnisotropy >= physicalDeviceCriteria.physicalDeviceProperties.limits.maxSamplerAnisotropy) { ++physicalDevicesScores[i]; }
                if(physicalDevicesProperties[i].limits.maxViewports >= physicalDeviceCriteria.physicalDeviceProperties.limits.maxViewports) { ++physicalDevicesScores[i]; }
                if(physicalDevicesProperties[i].limits.maxViewportDimensions[0] >= physicalDeviceCriteria.physicalDeviceProperties.limits.maxViewportDimensions[0]) { ++physicalDevicesScores[i]; }
                if(physicalDevicesProperties[i].limits.maxViewportDimensions[1] >= physicalDeviceCriteria.physicalDeviceProperties.limits.maxViewportDimensions[1]) { ++physicalDevicesScores[i]; }
                if(physicalDevicesProperties[i].limits.viewportBoundsRange[0] >= physicalDeviceCriteria.physicalDeviceProperties.limits.viewportBoundsRange[0]) { ++physicalDevicesScores[i]; }
                if(physicalDevicesProperties[i].limits.viewportBoundsRange[1] >= physicalDeviceCriteria.physicalDeviceProperties.limits.viewportBoundsRange[1]) { ++physicalDevicesScores[i]; }
                if(physicalDevicesProperties[i].limits.viewportSubPixelBits >= physicalDeviceCriteria.physicalDeviceProperties.limits.viewportSubPixelBits) { ++physicalDevicesScores[i]; }
                if(physicalDevicesProperties[i].limits.minMemoryMapAlignment <= physicalDeviceCriteria.physicalDeviceProperties.limits.minMemoryMapAlignment) { ++physicalDevicesScores[i]; }
                if(physicalDevicesProperties[i].limits.minTexelBufferOffsetAlignment <= physicalDeviceCriteria.physicalDeviceProperties.limits.minTexelBufferOffsetAlignment) { ++physicalDevicesScores[i]; }
                if(physicalDevicesProperties[i].limits.minUniformBufferOffsetAlignment <= physicalDeviceCriteria.physicalDeviceProperties.limits.minUniformBufferOffsetAlignment) { ++physicalDevicesScores[i]; }
                if(physicalDevicesProperties[i].limits.minStorageBufferOffsetAlignment <= physicalDeviceCriteria.physicalDeviceProperties.limits.minStorageBufferOffsetAlignment) { ++physicalDevicesScores[i]; }
                if(physicalDevicesProperties[i].limits.minTexelOffset <= physicalDeviceCriteria.physicalDeviceProperties.limits.minTexelOffset) { ++physicalDevicesScores[i]; }
                if(physicalDevicesProperties[i].limits.maxTexelOffset >= physicalDeviceCriteria.physicalDeviceProperties.limits.maxTexelOffset) { ++physicalDevicesScores[i]; }
                if(physicalDevicesProperties[i].limits.minTexelGatherOffset <= physicalDeviceCriteria.physicalDeviceProperties.limits.minTexelGatherOffset) { ++physicalDevicesScores[i]; }
                if(physicalDevicesProperties[i].limits.maxTexelGatherOffset >= physicalDeviceCriteria.physicalDeviceProperties.limits.maxTexelGatherOffset) { ++physicalDevicesScores[i]; }
                if(physicalDevicesProperties[i].limits.minInterpolationOffset <= physicalDeviceCriteria.physicalDeviceProperties.limits.minInterpolationOffset) { ++physicalDevicesScores[i]; }
                if(physicalDevicesProperties[i].limits.maxInterpolationOffset >= physicalDeviceCriteria.physicalDeviceProperties.limits.maxInterpolationOffset) { ++physicalDevicesScores[i]; }
                if(physicalDevicesProperties[i].limits.subPixelInterpolationOffsetBits >= physicalDeviceCriteria.physicalDeviceProperties.limits.subPixelInterpolationOffsetBits) { ++physicalDevicesScores[i]; }
                if(physicalDevicesProperties[i].limits.maxFramebufferWidth >= physicalDeviceCriteria.physicalDeviceProperties.limits.maxFramebufferWidth) { ++physicalDevicesScores[i]; }
                if(physicalDevicesProperties[i].limits.maxFramebufferHeight >= physicalDeviceCriteria.physicalDeviceProperties.limits.maxFramebufferHeight) { ++physicalDevicesScores[i]; }
                if(physicalDevicesProperties[i].limits.maxFramebufferLayers >= physicalDeviceCriteria.physicalDeviceProperties.limits.maxFramebufferLayers) { ++physicalDevicesScores[i]; }
                if(physicalDevicesProperties[i].limits.framebufferColorSampleCounts >= physicalDeviceCriteria.physicalDeviceProperties.limits.framebufferColorSampleCounts) { ++physicalDevicesScores[i]; }
                if(physicalDevicesProperties[i].limits.framebufferDepthSampleCounts >= physicalDeviceCriteria.physicalDeviceProperties.limits.framebufferDepthSampleCounts) { ++physicalDevicesScores[i]; }
                if(physicalDevicesProperties[i].limits.framebufferStencilSampleCounts >= physicalDeviceCriteria.physicalDeviceProperties.limits.framebufferStencilSampleCounts) { ++physicalDevicesScores[i]; }
                if(physicalDevicesProperties[i].limits.framebufferNoAttachmentsSampleCounts >= physicalDeviceCriteria.physicalDeviceProperties.limits.framebufferNoAttachmentsSampleCounts) { ++physicalDevicesScores[i]; }
                if(physicalDevicesProperties[i].limits.maxColorAttachments >= physicalDeviceCriteria.physicalDeviceProperties.limits.maxColorAttachments) { ++physicalDevicesScores[i]; }
                if(physicalDevicesProperties[i].limits.sampledImageColorSampleCounts >= physicalDeviceCriteria.physicalDeviceProperties.limits.sampledImageColorSampleCounts) { ++physicalDevicesScores[i]; }
                if(physicalDevicesProperties[i].limits.sampledImageIntegerSampleCounts >= physicalDeviceCriteria.physicalDeviceProperties.limits.sampledImageIntegerSampleCounts) { ++physicalDevicesScores[i]; }
                if(physicalDevicesProperties[i].limits.sampledImageDepthSampleCounts >= physicalDeviceCriteria.physicalDeviceProperties.limits.sampledImageDepthSampleCounts) { ++physicalDevicesScores[i]; }
                if(physicalDevicesProperties[i].limits.sampledImageStencilSampleCounts >= physicalDeviceCriteria.physicalDeviceProperties.limits.sampledImageStencilSampleCounts) { ++physicalDevicesScores[i]; }
                if(physicalDevicesProperties[i].limits.storageImageSampleCounts >= physicalDeviceCriteria.physicalDeviceProperties.limits.storageImageSampleCounts) { ++physicalDevicesScores[i]; }
                if(physicalDevicesProperties[i].limits.maxSampleMaskWords >= physicalDeviceCriteria.physicalDeviceProperties.limits.maxSampleMaskWords) { ++physicalDevicesScores[i]; }
                if(physicalDevicesProperties[i].limits.timestampComputeAndGraphics >= physicalDeviceCriteria.physicalDeviceProperties.limits.timestampComputeAndGraphics) { ++physicalDevicesScores[i]; }
                if(physicalDevicesProperties[i].limits.timestampPeriod >= physicalDeviceCriteria.physicalDeviceProperties.limits.timestampPeriod) { ++physicalDevicesScores[i]; }
                if(physicalDevicesProperties[i].limits.maxClipDistances >= physicalDeviceCriteria.physicalDeviceProperties.limits.maxClipDistances) { ++physicalDevicesScores[i]; }
                if(physicalDevicesProperties[i].limits.maxCullDistances >= physicalDeviceCriteria.physicalDeviceProperties.limits.maxCullDistances) { ++physicalDevicesScores[i]; }
                if(physicalDevicesProperties[i].limits.maxCombinedClipAndCullDistances >= physicalDeviceCriteria.physicalDeviceProperties.limits.maxCombinedClipAndCullDistances) { ++physicalDevicesScores[i]; }
                if(physicalDevicesProperties[i].limits.discreteQueuePriorities >= physicalDeviceCriteria.physicalDeviceProperties.limits.discreteQueuePriorities) { ++physicalDevicesScores[i]; }
                if(physicalDevicesProperties[i].limits.pointSizeRange[0] <= physicalDeviceCriteria.physicalDeviceProperties.limits.pointSizeRange[0]) { ++physicalDevicesScores[i]; }
                if(physicalDevicesProperties[i].limits.pointSizeRange[1] >= physicalDeviceCriteria.physicalDeviceProperties.limits.pointSizeRange[1]) { ++physicalDevicesScores[i]; }
                if(physicalDevicesProperties[i].limits.lineWidthRange[0] <= physicalDeviceCriteria.physicalDeviceProperties.limits.lineWidthRange[0]) { ++physicalDevicesScores[i]; }
                if(physicalDevicesProperties[i].limits.lineWidthRange[1] >= physicalDeviceCriteria.physicalDeviceProperties.limits.lineWidthRange[1]) { ++physicalDevicesScores[i]; }
                if(physicalDevicesProperties[i].limits.pointSizeGranularity >= physicalDeviceCriteria.physicalDeviceProperties.limits.pointSizeGranularity) { ++physicalDevicesScores[i]; }
                if(physicalDevicesProperties[i].limits.lineWidthGranularity >= physicalDeviceCriteria.physicalDeviceProperties.limits.lineWidthGranularity) { ++physicalDevicesScores[i]; }
                if(physicalDevicesProperties[i].limits.strictLines >= physicalDeviceCriteria.physicalDeviceProperties.limits.strictLines) { ++physicalDevicesScores[i]; }
                if(physicalDevicesProperties[i].limits.standardSampleLocations >= physicalDeviceCriteria.physicalDeviceProperties.limits.standardSampleLocations) { ++physicalDevicesScores[i]; }
                if(physicalDevicesProperties[i].limits.optimalBufferCopyOffsetAlignment >= physicalDeviceCriteria.physicalDeviceProperties.limits.optimalBufferCopyOffsetAlignment) { ++physicalDevicesScores[i]; }
                if(physicalDevicesProperties[i].limits.optimalBufferCopyRowPitchAlignment >= physicalDeviceCriteria.physicalDeviceProperties.limits.optimalBufferCopyRowPitchAlignment) { ++physicalDevicesScores[i]; }
                if(physicalDevicesProperties[i].limits.nonCoherentAtomSize >= physicalDeviceCriteria.physicalDeviceProperties.limits.nonCoherentAtomSize) { ++physicalDevicesScores[i]; }
                
                if(physicalDevicesProperties[i].sparseProperties.residencyStandard2DBlockShape >= physicalDeviceCriteria.physicalDeviceProperties.sparseProperties.residencyStandard2DBlockShape) { ++physicalDevicesScores[i]; }
                if(physicalDevicesProperties[i].sparseProperties.residencyStandard2DMultisampleBlockShape >= physicalDeviceCriteria.physicalDeviceProperties.sparseProperties.residencyStandard2DMultisampleBlockShape) { ++physicalDevicesScores[i]; }
                if(physicalDevicesProperties[i].sparseProperties.residencyStandard3DBlockShape >= physicalDeviceCriteria.physicalDeviceProperties.sparseProperties.residencyStandard3DBlockShape) { ++physicalDevicesScores[i]; }
                if(physicalDevicesProperties[i].sparseProperties.residencyAlignedMipSize >= physicalDeviceCriteria.physicalDeviceProperties.sparseProperties.residencyAlignedMipSize) { ++physicalDevicesScores[i]; }
                if(physicalDevicesProperties[i].sparseProperties.residencyNonResidentStrict >= physicalDeviceCriteria.physicalDeviceProperties.sparseProperties.residencyNonResidentStrict) { ++physicalDevicesScores[i]; }

                if((physicalDevicesFeatures[i].robustBufferAccess == VK_TRUE) && (physicalDevicesFeatures[i].robustBufferAccess == physicalDeviceCriteria.physicalDeviceFeatures.robustBufferAccess)) { ++physicalDevicesScores[i]; }
                if((physicalDevicesFeatures[i].fullDrawIndexUint32 == VK_TRUE) && (physicalDevicesFeatures[i].fullDrawIndexUint32 == physicalDeviceCriteria.physicalDeviceFeatures.fullDrawIndexUint32)) { ++physicalDevicesScores[i]; }
                if((physicalDevicesFeatures[i].imageCubeArray == VK_TRUE) && (physicalDevicesFeatures[i].imageCubeArray == physicalDeviceCriteria.physicalDeviceFeatures.imageCubeArray)) { ++physicalDevicesScores[i]; }
                if((physicalDevicesFeatures[i].independentBlend == VK_TRUE) && (physicalDevicesFeatures[i].independentBlend == physicalDeviceCriteria.physicalDeviceFeatures.independentBlend)) { ++physicalDevicesScores[i]; }
                if((physicalDevicesFeatures[i].geometryShader == VK_TRUE) && (physicalDevicesFeatures[i].geometryShader == physicalDeviceCriteria.physicalDeviceFeatures.geometryShader)) { ++physicalDevicesScores[i]; }
                if((physicalDevicesFeatures[i].tessellationShader == VK_TRUE) && (physicalDevicesFeatures[i].tessellationShader == physicalDeviceCriteria.physicalDeviceFeatures.tessellationShader)) { ++physicalDevicesScores[i]; }
                if((physicalDevicesFeatures[i].sampleRateShading == VK_TRUE) && (physicalDevicesFeatures[i].sampleRateShading == physicalDeviceCriteria.physicalDeviceFeatures.sampleRateShading)) { ++physicalDevicesScores[i]; }
                if((physicalDevicesFeatures[i].dualSrcBlend == VK_TRUE) && (physicalDevicesFeatures[i].dualSrcBlend == physicalDeviceCriteria.physicalDeviceFeatures.dualSrcBlend)) { ++physicalDevicesScores[i]; }
                if((physicalDevicesFeatures[i].logicOp == VK_TRUE) && (physicalDevicesFeatures[i].logicOp == physicalDeviceCriteria.physicalDeviceFeatures.logicOp)) { ++physicalDevicesScores[i]; }
                if((physicalDevicesFeatures[i].multiDrawIndirect == VK_TRUE) && (physicalDevicesFeatures[i].multiDrawIndirect == physicalDeviceCriteria.physicalDeviceFeatures.multiDrawIndirect)) { ++physicalDevicesScores[i]; }
                if((physicalDevicesFeatures[i].drawIndirectFirstInstance == VK_TRUE) && (physicalDevicesFeatures[i].drawIndirectFirstInstance == physicalDeviceCriteria.physicalDeviceFeatures.drawIndirectFirstInstance)) { ++physicalDevicesScores[i]; }
                if((physicalDevicesFeatures[i].depthClamp == VK_TRUE) && (physicalDevicesFeatures[i].depthClamp == physicalDeviceCriteria.physicalDeviceFeatures.depthClamp)) { ++physicalDevicesScores[i]; }
                if((physicalDevicesFeatures[i].depthBiasClamp == VK_TRUE) && (physicalDevicesFeatures[i].depthBiasClamp == physicalDeviceCriteria.physicalDeviceFeatures.depthBiasClamp)) { ++physicalDevicesScores[i]; }
                if((physicalDevicesFeatures[i].fillModeNonSolid == VK_TRUE) && (physicalDevicesFeatures[i].fillModeNonSolid == physicalDeviceCriteria.physicalDeviceFeatures.fillModeNonSolid)) { ++physicalDevicesScores[i]; }
                if((physicalDevicesFeatures[i].depthBounds == VK_TRUE) && (physicalDevicesFeatures[i].depthBounds == physicalDeviceCriteria.physicalDeviceFeatures.depthBounds)) { ++physicalDevicesScores[i]; }
                if((physicalDevicesFeatures[i].wideLines == VK_TRUE) && (physicalDevicesFeatures[i].wideLines == physicalDeviceCriteria.physicalDeviceFeatures.wideLines)) { ++physicalDevicesScores[i]; }
                if((physicalDevicesFeatures[i].largePoints == VK_TRUE) && (physicalDevicesFeatures[i].largePoints == physicalDeviceCriteria.physicalDeviceFeatures.largePoints)) { ++physicalDevicesScores[i]; }
                if((physicalDevicesFeatures[i].alphaToOne == VK_TRUE) && (physicalDevicesFeatures[i].alphaToOne == physicalDeviceCriteria.physicalDeviceFeatures.alphaToOne)) { ++physicalDevicesScores[i]; }
                if((physicalDevicesFeatures[i].multiViewport == VK_TRUE) && (physicalDevicesFeatures[i].multiViewport == physicalDeviceCriteria.physicalDeviceFeatures.multiViewport)) { ++physicalDevicesScores[i]; }
                if((physicalDevicesFeatures[i].samplerAnisotropy == VK_TRUE) && (physicalDevicesFeatures[i].samplerAnisotropy == physicalDeviceCriteria.physicalDeviceFeatures.samplerAnisotropy)) { ++physicalDevicesScores[i]; }
                if((physicalDevicesFeatures[i].textureCompressionETC2 == VK_TRUE) && (physicalDevicesFeatures[i].textureCompressionETC2 == physicalDeviceCriteria.physicalDeviceFeatures.textureCompressionETC2)) { ++physicalDevicesScores[i]; }
                if((physicalDevicesFeatures[i].textureCompressionASTC_LDR == VK_TRUE) && (physicalDevicesFeatures[i].textureCompressionASTC_LDR == physicalDeviceCriteria.physicalDeviceFeatures.textureCompressionASTC_LDR)) { ++physicalDevicesScores[i]; }
                if((physicalDevicesFeatures[i].textureCompressionBC == VK_TRUE) && (physicalDevicesFeatures[i].textureCompressionBC == physicalDeviceCriteria.physicalDeviceFeatures.textureCompressionBC)) { ++physicalDevicesScores[i]; }
                if((physicalDevicesFeatures[i].occlusionQueryPrecise == VK_TRUE) && (physicalDevicesFeatures[i].occlusionQueryPrecise == physicalDeviceCriteria.physicalDeviceFeatures.occlusionQueryPrecise)) { ++physicalDevicesScores[i]; }
                if((physicalDevicesFeatures[i].pipelineStatisticsQuery == VK_TRUE) && (physicalDevicesFeatures[i].pipelineStatisticsQuery == physicalDeviceCriteria.physicalDeviceFeatures.pipelineStatisticsQuery)) { ++physicalDevicesScores[i]; }
                if((physicalDevicesFeatures[i].vertexPipelineStoresAndAtomics == VK_TRUE) && (physicalDevicesFeatures[i].vertexPipelineStoresAndAtomics == physicalDeviceCriteria.physicalDeviceFeatures.vertexPipelineStoresAndAtomics)) { ++physicalDevicesScores[i]; }
                if((physicalDevicesFeatures[i].fragmentStoresAndAtomics == VK_TRUE) && (physicalDevicesFeatures[i].fragmentStoresAndAtomics == physicalDeviceCriteria.physicalDeviceFeatures.fragmentStoresAndAtomics)) { ++physicalDevicesScores[i]; }
                if((physicalDevicesFeatures[i].shaderTessellationAndGeometryPointSize == VK_TRUE) && (physicalDevicesFeatures[i].shaderTessellationAndGeometryPointSize == physicalDeviceCriteria.physicalDeviceFeatures.shaderTessellationAndGeometryPointSize)) { ++physicalDevicesScores[i]; }
                if((physicalDevicesFeatures[i].shaderImageGatherExtended == VK_TRUE) && (physicalDevicesFeatures[i].shaderImageGatherExtended == physicalDeviceCriteria.physicalDeviceFeatures.shaderImageGatherExtended)) { ++physicalDevicesScores[i]; }
                if((physicalDevicesFeatures[i].shaderStorageImageExtendedFormats == VK_TRUE) && (physicalDevicesFeatures[i].shaderStorageImageExtendedFormats == physicalDeviceCriteria.physicalDeviceFeatures.shaderStorageImageExtendedFormats)) { ++physicalDevicesScores[i]; }
                if((physicalDevicesFeatures[i].shaderStorageImageMultisample == VK_TRUE) && (physicalDevicesFeatures[i].shaderStorageImageMultisample == physicalDeviceCriteria.physicalDeviceFeatures.shaderStorageImageMultisample)) { ++physicalDevicesScores[i]; }
                if((physicalDevicesFeatures[i].shaderStorageImageReadWithoutFormat == VK_TRUE) && (physicalDevicesFeatures[i].shaderStorageImageReadWithoutFormat == physicalDeviceCriteria.physicalDeviceFeatures.shaderStorageImageReadWithoutFormat)) { ++physicalDevicesScores[i]; }
                if((physicalDevicesFeatures[i].shaderStorageImageWriteWithoutFormat == VK_TRUE) && (physicalDevicesFeatures[i].shaderStorageImageWriteWithoutFormat == physicalDeviceCriteria.physicalDeviceFeatures.shaderStorageImageWriteWithoutFormat)) { ++physicalDevicesScores[i]; }
                if((physicalDevicesFeatures[i].shaderUniformBufferArrayDynamicIndexing == VK_TRUE) && (physicalDevicesFeatures[i].shaderUniformBufferArrayDynamicIndexing == physicalDeviceCriteria.physicalDeviceFeatures.shaderUniformBufferArrayDynamicIndexing)) { ++physicalDevicesScores[i]; }
                if((physicalDevicesFeatures[i].shaderSampledImageArrayDynamicIndexing == VK_TRUE) && (physicalDevicesFeatures[i].shaderSampledImageArrayDynamicIndexing == physicalDeviceCriteria.physicalDeviceFeatures.shaderSampledImageArrayDynamicIndexing)) { ++physicalDevicesScores[i]; }
                if((physicalDevicesFeatures[i].shaderStorageBufferArrayDynamicIndexing == VK_TRUE) && (physicalDevicesFeatures[i].shaderStorageBufferArrayDynamicIndexing == physicalDeviceCriteria.physicalDeviceFeatures.shaderStorageBufferArrayDynamicIndexing)) { ++physicalDevicesScores[i]; }
                if((physicalDevicesFeatures[i].shaderStorageImageArrayDynamicIndexing == VK_TRUE) && (physicalDevicesFeatures[i].shaderStorageImageArrayDynamicIndexing == physicalDeviceCriteria.physicalDeviceFeatures.shaderStorageImageArrayDynamicIndexing)) { ++physicalDevicesScores[i]; }
                if((physicalDevicesFeatures[i].shaderClipDistance == VK_TRUE) && (physicalDevicesFeatures[i].shaderClipDistance == physicalDeviceCriteria.physicalDeviceFeatures.shaderClipDistance)) { ++physicalDevicesScores[i]; }
                if((physicalDevicesFeatures[i].shaderCullDistance == VK_TRUE) && (physicalDevicesFeatures[i].shaderCullDistance == physicalDeviceCriteria.physicalDeviceFeatures.shaderCullDistance)) { ++physicalDevicesScores[i]; }
                if((physicalDevicesFeatures[i].shaderFloat64 == VK_TRUE) && (physicalDevicesFeatures[i].shaderFloat64 == physicalDeviceCriteria.physicalDeviceFeatures.shaderFloat64)) { ++physicalDevicesScores[i]; }
                if((physicalDevicesFeatures[i].shaderInt64 == VK_TRUE) && (physicalDevicesFeatures[i].shaderInt64 == physicalDeviceCriteria.physicalDeviceFeatures.shaderInt64)) { ++physicalDevicesScores[i]; }
                if((physicalDevicesFeatures[i].shaderInt16 == VK_TRUE) && (physicalDevicesFeatures[i].shaderInt16 == physicalDeviceCriteria.physicalDeviceFeatures.shaderInt16)) { ++physicalDevicesScores[i]; }
                if((physicalDevicesFeatures[i].shaderResourceResidency == VK_TRUE) && (physicalDevicesFeatures[i].shaderResourceResidency == physicalDeviceCriteria.physicalDeviceFeatures.shaderResourceResidency)) { ++physicalDevicesScores[i]; }
                if((physicalDevicesFeatures[i].shaderResourceMinLod == VK_TRUE) && (physicalDevicesFeatures[i].shaderResourceMinLod == physicalDeviceCriteria.physicalDeviceFeatures.shaderResourceMinLod)) { ++physicalDevicesScores[i]; }
                if((physicalDevicesFeatures[i].sparseBinding == VK_TRUE) && (physicalDevicesFeatures[i].sparseBinding == physicalDeviceCriteria.physicalDeviceFeatures.sparseBinding)) { ++physicalDevicesScores[i]; }
                if((physicalDevicesFeatures[i].sparseResidencyBuffer == VK_TRUE) && (physicalDevicesFeatures[i].sparseResidencyBuffer == physicalDeviceCriteria.physicalDeviceFeatures.sparseResidencyBuffer)) { ++physicalDevicesScores[i]; }
                if((physicalDevicesFeatures[i].sparseResidencyImage2D == VK_TRUE) && (physicalDevicesFeatures[i].sparseResidencyImage2D == physicalDeviceCriteria.physicalDeviceFeatures.sparseResidencyImage2D)) { ++physicalDevicesScores[i]; }
                if((physicalDevicesFeatures[i].sparseResidencyImage3D == VK_TRUE) && (physicalDevicesFeatures[i].sparseResidencyImage3D == physicalDeviceCriteria.physicalDeviceFeatures.sparseResidencyImage3D)) { ++physicalDevicesScores[i]; }
                if((physicalDevicesFeatures[i].sparseResidency2Samples == VK_TRUE) && (physicalDevicesFeatures[i].sparseResidency2Samples == physicalDeviceCriteria.physicalDeviceFeatures.sparseResidency2Samples)) { ++physicalDevicesScores[i]; }
                if((physicalDevicesFeatures[i].sparseResidency4Samples == VK_TRUE) && (physicalDevicesFeatures[i].sparseResidency4Samples == physicalDeviceCriteria.physicalDeviceFeatures.sparseResidency4Samples)) { ++physicalDevicesScores[i]; }
                if((physicalDevicesFeatures[i].sparseResidency8Samples == VK_TRUE) && (physicalDevicesFeatures[i].sparseResidency8Samples == physicalDeviceCriteria.physicalDeviceFeatures.sparseResidency8Samples)) { ++physicalDevicesScores[i]; }
                if((physicalDevicesFeatures[i].sparseResidency16Samples == VK_TRUE) && (physicalDevicesFeatures[i].sparseResidency16Samples == physicalDeviceCriteria.physicalDeviceFeatures.sparseResidency16Samples)) { ++physicalDevicesScores[i]; }
                if((physicalDevicesFeatures[i].sparseResidencyAliased == VK_TRUE) && (physicalDevicesFeatures[i].sparseResidencyAliased == physicalDeviceCriteria.physicalDeviceFeatures.sparseResidencyAliased)) { ++physicalDevicesScores[i]; }
                if((physicalDevicesFeatures[i].variableMultisampleRate == VK_TRUE) && (physicalDevicesFeatures[i].variableMultisampleRate == physicalDeviceCriteria.physicalDeviceFeatures.variableMultisampleRate)) { ++physicalDevicesScores[i]; }
                if((physicalDevicesFeatures[i].inheritedQueries == VK_TRUE) && (physicalDevicesFeatures[i].inheritedQueries == physicalDeviceCriteria.physicalDeviceFeatures.inheritedQueries)) { ++physicalDevicesScores[i]; }
            }
        }

        if(physicalDeviceCriteria.check) {
            uint32_t index = std::distance(physicalDevicesScores.begin(), std::max_element(physicalDevicesScores.begin(), physicalDevicesScores.end()));
            VAS_LOG("gpu - " + std::string(physicalDevicesProperties[index].deviceName));

            m_physicalDeviceProperties = physicalDevicesProperties[index];
            m_physicalDeviceFeatures = physicalDevicesFeatures[index];
            m_physicalDevice = physicalDevices[index];

            found = true;
        } else {
            VAS_LOG("gpu - " + std::string(physicalDevicesProperties[0].deviceName));
        }

        if(!found) {
            m_physicalDeviceProperties = physicalDevicesProperties[0];
            m_physicalDeviceFeatures = physicalDevicesFeatures[0];
            m_physicalDevice = physicalDevices[0];
        }

        VAS_LOG("physical device is ready");
    }

    VkPhysicalDeviceProperties& PhysicalDevice::GetPhysicalDeviceProperties() {
        return m_physicalDeviceProperties;
    }
    
    VkPhysicalDeviceFeatures& PhysicalDevice::GetPhysicalDeviceFeatures() {
        return m_physicalDeviceFeatures;
    }
    
    VkPhysicalDevice PhysicalDevice::GetPhysicalDevice() {
        if(m_physicalDevice != VK_NULL_HANDLE) {
            return m_physicalDevice;
        } else {
            VAS_LOG("accessing physical device while being undefined");
            return nullptr;
        }
    }
};