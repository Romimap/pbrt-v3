#ifndef PBRT_TBMATERIAL_H
#define PBRT_TBMATERIAL_H

#include "pbrt.h"
#include "material.h"

namespace pbrt {

class TBMaterial : public Material {
public:
    TBMaterial(int a);
    ~TBMaterial();
    void ComputeScatteringFunctions(SurfaceInteraction *si, MemoryArena &arena,
                                    TransportMode mode,
                                    bool allowMultipleLobes) const;
private:
    std::shared_ptr<Texture<Spectrum>> B;
    std::shared_ptr<Texture<Spectrum>> M;
};

TBMaterial *CreateTBMaterial(const TextureParams &mp);

} // namespace pbrt

#endif // PBRT_TBMATERIAL_H
