#include "materials/TBMaterial.h"
#include "paramset.h"
#include "reflection.h"
#include "interaction.h"
#include "texture.h"
#include "interaction.h"

namespace pbrt {

TBMaterial::TBMaterial(std::shared_ptr<Texture<Spectrum>> B, std::shared_ptr<Texture<Spectrum>> M, std::shared_ptr<Texture<Float>> bump) {
    this->B = B;
    this->M = M;
    this->bumpMap = bump;
}

TBMaterial::~TBMaterial()
{
}

void TBMaterial::ComputeScatteringFunctions(SurfaceInteraction *si, MemoryArena &arena,
                                    TransportMode mode,
                                    bool allowMultipleLobes) const {
    //if (bumpMap) Bump(bumpMap, si);                                    
    Spectrum bspectrum = B->Evaluate(*si);
    Spectrum mspectrum = M->Evaluate(*si);
    Float bump = bumpMap->Evaluate(*si);
//
    float bx = bspectrum[0] * 2.f - 1.f;
    float by = bspectrum[1] * 2.f - 1.f;
    float mx = mspectrum[0] * 2.f - 1.f;
    float my = mspectrum[1] * 2.f - 1.f;
    float mz = mspectrum[2] * 2.f - 1.f;
    //printf("bx:%.5f by:%.5f mx:%.5f my:%.5f mz:%.5f\n", bx, by, mx, my, mz);

    Vector3f sigma(mx - bx*bx, my - by*by, mz - bx*by);

    //printf("%.5f %.5f %.5f\n", sigma[0], sigma[1], sigma[2]);

    si->bsdf = ARENA_ALLOC(arena, BSDF)(*si);
    //MicrofacetDistribution *md = ARENA_ALLOC(arena, BeckmannDistribution)(0.1, 0.1);
    //Fresnel *f = ARENA_ALLOC(arena, FresnelDielectric)(1.6f, 1.f);
    //si->bsdf->Add(ARENA_ALLOC(arena, MicrofacetReflection)(1.f, md, f));
    si->bsdf->Add(ARENA_ALLOC(arena, LambertianReflection)(std::abs(bump)));
}

TBMaterial *CreateTBMaterial(const TextureParams &mp)
{    
    std::shared_ptr<Texture<Spectrum>> B = mp.GetSpectrumTexture("B", Spectrum());
    std::shared_ptr<Texture<Spectrum>> M = mp.GetSpectrumTexture("M", Spectrum());
    std::shared_ptr<Texture<Float>> bump = mp.GetFloatTextureOrNull("bumpmap");
    return new TBMaterial(B, M, bump);
}



} //namespace pbrt
