#ifndef PBRT_TBMATERIAL_H
#define PBRT_TBMATERIAL_H

#include "pbrt.h"
#include "material.h"

namespace pbrt {

class TBMaterial : public Material {
public:
    TBMaterial(std::shared_ptr<pbrt::Texture<pbrt::Spectrum>> B,
                std::shared_ptr<pbrt::Texture<pbrt::Spectrum>> M,
                std::shared_ptr<pbrt::Texture<pbrt::Float>> bump);
    ~TBMaterial();
    void ComputeScatteringFunctions(SurfaceInteraction *si, MemoryArena &arena,
                                    TransportMode mode,
                                    bool allowMultipleLobes) const;
private:
    std::shared_ptr<Texture<Spectrum>> B;
    std::shared_ptr<Texture<Spectrum>> M;
    std::shared_ptr<Texture<Float>> bumpMap;
};

TBMaterial *CreateTBMaterial(const TextureParams &mp);

} // namespace pbrt

#endif // PBRT_TBMATERIAL_H
