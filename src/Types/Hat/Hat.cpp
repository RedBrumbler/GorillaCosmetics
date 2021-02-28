#include "Types/Hat/Hat.hpp"
#include "cosmeticsloader/shared/CosmeticLoader.hpp"
#include "logging.hpp"

using namespace CosmeticsLoader;

namespace GorillaCosmetics
{
    Hat::Hat(std::string path) : manifest(HatManifest(path)) {};

    void Hat::Load()
    {
        CosmeticLoader<HatManifest>* loader = new CosmeticLoader<HatManifest>(manifest, [&, loader](std::string name , Il2CppObject* obj){
            INFO("Loaded Hat %s", this->manifest.get_descriptor().get_name().c_str());            
            this->object = obj;
            //delete(loader);
        }, "_Hat", il2cpp_utils::GetSystemType("UnityEngine", "GameObject"));
    }

    const Hat::Config& Hat::get_config() const
    {
        return manifest.get_config();
    }

    const Descriptor& Hat::get_descriptor() const
    {
        return manifest.get_descriptor();
    }

    const Hat::HatManifest& Hat::get_manifest() const
    {
        return manifest;
    }

    Il2CppObject* Hat::get_hat()
    {
        if (!object) ERROR("Asked for hat object but it was nullptr!");
        return object;
    }
}