#include "materials/TBMaterial.h"
#include "paramset.h"
#include "reflection.h"
#include "interaction.h"
#include "texture.h"
#include "interaction.h"

namespace pbrt {

TBMaterial::TBMaterial(int a)
{
}

TBMaterial::~TBMaterial()
{
}

void TBMaterial::ComputeScatteringFunctions(SurfaceInteraction *si, MemoryArena &arena,
                                    TransportMode mode,
                                    bool allowMultipleLobes) const {
    si->bsdf = ARENA_ALLOC(arena, BSDF)(*si);
    float alpha = BeckmannDistribution::RoughnessToAlpha(0.01f);
    MicrofacetDistribution *md = ARENA_ALLOC(arena, BeckmannDistribution)(0, .5f);
    Fresnel *f = ARENA_ALLOC(arena, FresnelDielectric)(0.1f, 1.f);
    si->bsdf->Add(ARENA_ALLOC(arena, MicrofacetReflection)(1.f, md, f));
}

TBMaterial *CreateTBMaterial(const TextureParams &mp)
{    
    return new TBMaterial(0);
}



} //namespace pbrt
